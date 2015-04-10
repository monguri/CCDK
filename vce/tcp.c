#include "vce.h"
#include "vcecommon.h"
#include "conn.h"
#include "tcp.h"
#include "uselog.h"
#include "protocol.h"
#include "osdep.h"
#include "core.h"
#include "util.h"




int vce_tcpcontext_mi = -1;


// select のタイムアウト調整 
int vce_select_timeout_us = 0;
int vce_fdwrap_select_nfds = -1;
int vce_select_timeout_flag = 0; // 1:select のタイムアウトをする

int vce_tcpcontext_init_world( void ) {
    if( vce_limit.max_tcpcontext > 0 ){
        vce_tcpcontext_mi = vce_init_array( sizeof( tcpcontext ), vce_limit.max_tcpcontext, "tcpctx" );
        if( vce_tcpcontext_mi < 0 ) return SET_LAST_ERROR(VCE_EARRAY);
    }
    return SET_LAST_ERROR(VCE_NOERROR);
}
int vce_tcpcontext_fin_world(void) {
    if( vce_tcpcontext_mi >= 0 ){
        vce_end_array( vce_tcpcontext_mi );
    }
    return 0;
}

//   あたらしいconnのシリアル番号を得る
static unsigned int vce_conn_serial = 0; //serialのインクリメント用
int vce_tcpcontext_get_next_conn_serial() {
    vce_conn_serial++;
    if( vce_conn_serial == 0 ){
        vce_conn_serial = 1;
    }
    SET_LAST_ERROR(VCE_NOERROR);
    return vce_conn_serial;
}

void vce_tcpcontext_userdata_set_pointer(tcpcontext_t tp,void *p) {
	tcpcontext *t=(tcpcontext*)tp;
	t->userdata=p;
}
void*vce_tcpcontext_userdata_get_pointer(tcpcontext_t tp) {
	tcpcontext *t=(tcpcontext*)tp;
	return t->userdata;
}

/////
tcpcontext_t  vce_tcpcontext_create(
    int is_server,
    const char *bindaddr, unsigned short port, int maxcon ,
    size_t rblen , size_t wblen,
    int timeout ,
    int nonblock_connect,
    int nodelay,
    size_t statebuf_size
    )
{
    char aname[32];
    int ret_e = VCE_EGENERIC;
    tcpcontext *t;

    if( ( t = vce_alloc_array_object( vce_tcpcontext_mi ) )== NULL ){
        return NULL;
    }

	t->ps_host[0]=0;
	t->ps_mainport=0;
	t->ps_subport=0;

    t->max_conn = maxcon;
    t->is_server = is_server;

    t->rblen = rblen;
    t->erblen = rblen;
    t->wblen = wblen;
    t->ewblen = wblen;

    t->timeout_sec = timeout;
    t->accept_more = 1;
    t->nonblock_connect = nonblock_connect;
    t->nodelay = nodelay;

    t->conn_in_use = 0;
    t->conn_hiwater_thres = 999999999;
    t->sa.sin_port = htons( port );
    t->accept_count=t->accept_max=0;
    t->accept_lasttime=0;
    t->accept_warning=0;

    t->maxlen_record=0;
    t->maxlen_warning=0;
	t->userdata=NULL;

    t->call_parser_per_loop = 1;
    t->send_reset_timeout = 0;
    t->recv_reset_timeout = 1;
    t->protocol_parser = NULL;
    t->pcallback = NULL;
    t->protocol_acceptwatcher = NULL;
    t->protocol_hiwater_acceptwatcher = NULL;
    t->protocol_closewatcher = NULL;
    t->conn_finalizer = NULL;
    t->statebuf_mi = -1;

    t->index = vce_get_array_object_index( vce_tcpcontext_mi , t );

    if( is_server ){
        if( ( t->mainsock = vce_socket_tcp_socket() ) < 0 ){
            VCE_ERROUT3( FATAL_TCP_SOCKET_S_D_S,
                         bindaddr , (int) port ,
                         vce_get_os_errstr());
            vce_free_array_object( vce_tcpcontext_mi, t );
            SET_LAST_ERROR( VCE_ESOCKET );
            return NULL;
        }

        /* reuseaddr を設定する */
        if( vce_socket_set_reuseaddr( t->mainsock ) < 0 ){
            VCE_ERROUT1( FATAL_TCP_SETSOCKOPT_REUSE_S , vce_get_os_errstr());
            vce_free_array_object( vce_tcpcontext_mi, t );
            SET_LAST_ERROR(VCE_ESETSOCKOPT);
            return NULL;
        }
        if( vce_socket_set_keepalive( t->mainsock ) < 0 ){
#ifdef linux
            VCE_ERROUT1( "warning: vce_socket_set_keepalive fail (%s)\n",
                         vce_get_os_errstr());
#else
            VCE_ERROUT_V1( "warning: vce_socket_set_keepalive fail (%s)\n",
                           vce_get_os_errstr());
#endif
        }

        if( vce_socket_bind( t->mainsock, bindaddr,port ) < 0 ){
            VCE_ERROUT3( FATAL_TCP_BIND_S_S_D,
                         vce_get_os_errstr() , bindaddr , (int)port );
            vce_free_array_object( vce_tcpcontext_mi, t );
            SET_LAST_ERROR( VCE_EBIND );
            return NULL;
        }
        VCE_ERROUT_V1( "vce_tcpcontext bound to local port %d\n", port );

        if( vce_socket_listen( t->mainsock ) < 0 ){
            VCE_ERROUT3( FATAL_TCP_LISTEN_S_S_D,
                         vce_get_os_errstr() , bindaddr , (int) port );
            vce_free_array_object( vce_tcpcontext_mi, t );
            SET_LAST_ERROR( VCE_ELISTEN );
            return NULL;
        }
    }

    /* 状態管理用バッファ初期化。 */
    if( statebuf_size > 0 ){
        t->statebuf_size = statebuf_size;
        t->statebuf_num = t->max_conn;
        vce_snprintf( aname, sizeof(aname),
                      "stateb%d" , port); /* sizeofは 32 だよ */
        t->statebuf_mi = vce_init_array( t->statebuf_size,
                                         t->statebuf_num, aname);
        if( t->statebuf_mi < 0){
            VCE_ERROUT0( FATAL_TCP_STATEBUF_INIT );
            ret_e = VCE_EARRAY;
            goto return_error;
        }
        VCE_ERROUT_V0( NOTE_TCP_STATEBUF_INIT_OK );
    } else {
        t->statebuf_mi = -1;
    }

    /* 読みこみbufferなどを初期化 */
    vce_snprintf( aname,sizeof(aname),"rb%d", port);
    t->rbmaster_mi = vce_init_array( rblen, t->max_conn, aname );
    if( t->rbmaster_mi < 0 ){
        ret_e = VCE_EARRAY;
        goto return_error;
    }
    vce_snprintf( aname,sizeof(aname),"erb%d", port);
    /* ここの +8 は、暗号のヘッダ */
    /* さらに圧縮用のヘッダ */
    t->erbmaster_mi = vce_init_array( rblen+8+8, t->max_conn, aname );
    if( t->erbmaster_mi < 0 ){
        ret_e = VCE_EARRAY;
        goto return_error;
    }
    vce_snprintf( aname,sizeof(aname),"wb%d", port);
    t->wbmaster_mi = vce_init_array( wblen, t->max_conn, aname );
    if( t->wbmaster_mi < 0 ){
        ret_e = VCE_EARRAY;
        goto return_error;
    }
    /* ここの +8 は、暗号のヘッダ */
    /* さらに圧縮用のヘッダ */
    vce_snprintf( aname,sizeof(aname),"ewb%d", port);
    t->ewbmaster_mi = vce_init_array( wblen+8+8, t->max_conn, aname );
    if( t->ewbmaster_mi < 0 ){
        ret_e = VCE_EARRAY;
        goto return_error;
    }

    vce_usage_increment_tcpcontext_create();
    SET_LAST_ERROR(VCE_NOERROR);
    return (tcpcontext_t )t;

return_error:

    vce_end_array( t->rbmaster_mi );
    vce_end_array( t->erbmaster_mi);
    vce_end_array( t->wbmaster_mi );
    vce_end_array( t->ewbmaster_mi);
    vce_end_array( t->statebuf_mi );

    vce_socket_close( t->mainsock );

    vce_free_array_object( vce_tcpcontext_mi, t );
    SET_LAST_ERROR(ret_e);
    return NULL;
}


void vce_tcpcontext_set_conn_finalizer( tcpcontext_t tp, void (*fin)(conn_t) ) {
    tcpcontext *t = ( tcpcontext * ) tp;
    t->conn_finalizer = fin;
}

void vce_tcpcontext_timeout_control( tcpcontext_t tp, int recv_reset, int send_reset ) {
    ((tcpcontext*)tp)->recv_reset_timeout = recv_reset;
    ((tcpcontext*)tp)->send_reset_timeout = send_reset;
}

void vce_tcpcontext_set_conn_parser( tcpcontext_t tp, int (*parser)(conn_t), int (*pcallback)(conn_t,char*,int)) {
    tcpcontext *t = (tcpcontext*) tp;
    t->protocol_parser = parser;
    t->pcallback = pcallback;
}
void vce_tcpcontext_set_conn_acceptwatcher( tcpcontext_t tp, int (*aw)(conn_t) ) {
    tcpcontext *t = (tcpcontext*) tp;
    t->protocol_acceptwatcher = aw;
}
void vce_tcpcontext_set_conn_hiwater_acceptwatcher( tcpcontext_t tp, int water, int (*aw)(conn_t,int)) {
    tcpcontext *t = (tcpcontext*) tp;
    t->protocol_hiwater_acceptwatcher = aw;
    t->conn_hiwater_thres = water;
}
void vce_tcpcontext_set_conn_closewatcher( tcpcontext_t tp, int (*cw)(conn_t, CLOSE_REASON r) ) {
    tcpcontext *t = (tcpcontext*) tp;
    t->protocol_closewatcher = cw;
}
void vce_tcpcontext_cleanup( tcpcontext_t tp ) {
    tcpcontext *t = ( tcpcontext * ) tp;

    vce_conn_close_tcpcontext_all( (tcpcontext_t) tp ); // すべてのコネクションを閉じる

    if( t->is_server ) vce_socket_close( t->mainsock );

    vce_end_array( t->rbmaster_mi );
    vce_end_array( t->erbmaster_mi );
    vce_end_array( t->wbmaster_mi );
    vce_end_array( t->ewbmaster_mi );
    vce_end_array( t->statebuf_mi );
    vce_free_array_object( vce_tcpcontext_mi , t );

    vce_usage_increment_tcpcontext_cleanup();
    SET_LAST_ERROR(VCE_NOERROR);
}


//////
void vce_tcpcontext_protocol_set_maxlength(tcpcontext_t ct,int maxlength,int(*errcall)(conn_t ct)) {
    tcpcontext *c = ( tcpcontext *) ct;
    c->maxlen_warning=errcall;
    c->maxlen_record=maxlength;
}

void vce_tcpcontext_set_accept_max(tcpcontext_t t,int con_max,int (*accept_warning)(tcpcontext_t t)) {
    tcpcontext *tp=(tcpcontext*)t;
    tp->accept_max=con_max;
    tp->accept_count=con_max;
    tp->accept_lasttime=vce_mainloop_utime_store;
    tp->accept_warning=accept_warning;
}


static void tcpcontext_try_accept( tcpcontext *t ) {
    char remote_addr[16], local_addr[16];
    int remote_addr_len = sizeof( remote_addr );
    int local_addr_len = sizeof( local_addr );
    unsigned short remote_port, local_port;
    int statebuflen;
    char *statebuf;
    conn *newc;
    conn_t tmpconnt;
    int ns ;

    ns = vce_socket_accept( t->mainsock, remote_addr, &remote_addr_len,
                            &remote_port,
                            local_addr, &local_addr_len, &local_port,
                            (tcpcontext_t) t );
    if( ns < 0 ) return;

    // accept数チェック 
    if(t->accept_max) {
        // 時間経過分許可カウント増加
        while(t->accept_lasttime<vce_mainloop_utime_store) {
            t->accept_lasttime+=60*1000*1000/t->accept_max;
            if(t->accept_count<t->accept_max) {
                t->accept_count++;

                // 無駄なループを避けるため適当に抜けてしまう 
                if(t->accept_count==t->accept_max) {
                    t->accept_lasttime=vce_mainloop_utime_store+60*1000*1000/t->accept_max;
                    break;
                }
            }
        }
        if(t->accept_count>=0) {
            t->accept_count--;
        } else {
            // 許容数オーバー 
            int ret=-1;
            if(t->accept_warning) ret=t->accept_warning((tcpcontext_t)t);
            if(ret<0) {
                VCE_ERROUT_V0( WARN_TCP_NO_MORE_ACCEPT );
                vce_socket_close(ns);
                return;
            }
        }
    }

    // これ以上 acceptしない設定になってたらだめだよ 
    if( t->accept_more == 0 ){
        VCE_ERROUT_V0( WARN_TCP_NO_MORE_ACCEPT );
        vce_socket_close(ns);
        return;
    }

    // もしも、使用中コネクションのカウンタが、最大だったらこれ以上コネクションはれないよ 
    if( t->conn_in_use == t->max_conn ) {
        VCE_ERROUT_V1( WARN_TCP_MAX_CONN_IN_USE_D, t->max_conn );
        vce_socket_close(ns );
        return;
    }

    // connを1個わりつける 
    if( !( newc = vce_conn_alloc()) ){
        VCE_ERROUT_V2( WARN_TCP_MAXCON_D_D,
                       t->max_conn, htons(t->sa.sin_port ));
        return;
    }
    // 使用中の数を増やす 
    t->conn_in_use ++;
    // 状態管理バッファを初期化 
    if( t->statebuf_mi >= 0 ){
        newc->statebuf = vce_alloc_array_object( t->statebuf_mi );
        if( !newc->statebuf ){
            VCE_ERROUT0( BUG_TCP_STATEBUF_RUNSHORT );
            vce_conn_free(newc,0,CLOSE_REASON_NONE);
            return;
        }
        memset( newc->statebuf, 0, t->statebuf_size );
        VCE_ERROUT_V0( NOTE_TCP_STATEBUF_ALLOC );
        newc->statebuf_mi = t->statebuf_mi;
        newc->statebuf_size = t->statebuf_size;
    } else {
        newc->statebuf_mi = -1;
        newc->statebuf_size = 0;
    }

    newc->fd = ns;
    newc->closed_flag = 0;
    newc->nonblock_connect_ok = 0;
    newc->tcpc = (void*)t;
    memcpy( newc->remote_addr, remote_addr, remote_addr_len );
    memcpy( newc->local_addr, local_addr, local_addr_len );
    newc->remote_addr_len = remote_addr_len;
    newc->local_addr_len = local_addr_len;
    newc->remote_port = remote_port;
    newc->local_port = local_port;
    newc->is_server = t->is_server;
    newc->protocol_parser = t->protocol_parser;
    newc->protocol_acceptwatcher = t->protocol_acceptwatcher;
    newc->protocol_hiwater_acceptwatcher = t->protocol_hiwater_acceptwatcher;
    newc->protocol_closewatcher = t->protocol_closewatcher;
    newc->pcallback = t->pcallback;
    vce_update_time();
    newc->last_access = vce_global_time;
    newc->timeout_sec = t->timeout_sec;
    newc->index = vce_conn_get_index_from_pointer( newc );
    newc->serial = vce_tcpcontext_get_next_conn_serial();
    newc->call_parser_per_loop = t->call_parser_per_loop;
    newc->maxlen_record=t->maxlen_record;
    newc->maxlen_warning=t->maxlen_warning;
	newc->userdata=NULL;

    if(vce_sbuf_init( &newc->rb, t->rbmaster_mi )<0 ||
       vce_sbuf_init( &newc->wb, t->wbmaster_mi ) <0 ){
        VCE_ERROUT_V0( "accept: cannot allocate send/recv buf\n" );
        vce_conn_free(newc,0,CLOSE_REASON_NONE);
        return;
    }

    VCE_ERROUT_V3( NOTE_TCP_NEW_CONNECTION, ns , newc->index , (int)newc->rb.len);

    if( t->nodelay ){
        if( vce_socket_set_nodelay( ns ) < 0 ){
            VCE_ERROUT1( FATAL_TCP_SETSOCKOPT_S, vce_get_os_errstr());
        }
    }

    // accept したら、状態バッファをゼロクリア
    tmpconnt.p = newc;
    tmpconnt.serial = newc->serial;
    statebuf = vce_conn_get_state_buffer( tmpconnt, &statebuflen );
    if( statebuf )memset( statebuf,0, statebuflen );

    // 全部うまくいったら、acceptor を呼びだすのだ。cipher が1のときは、NEGO がおわってから ACCEPTED をメインに送る 
    if( newc->protocol_acceptwatcher ){
        if( t->conn_in_use >= (t->conn_hiwater_thres-1) ){
            VCE_ERROUT_V2( "try_accept: hiwater (now:%d hiw:%d)\n", t->conn_in_use, t->conn_hiwater_thres );
            if( newc->protocol_hiwater_acceptwatcher( tmpconnt,
                                                      t->conn_in_use ) < 0 ){
                VCE_ERROUT_V1( WARN_TCP_HIWATER_ACCEPTW_D, newc->fd );
                vce_conn_free( newc,0,CLOSE_REASON_NONE );
                return;
            }
        } else {
            if( newc->protocol_acceptwatcher( tmpconnt ) < 0 ){
                VCE_ERROUT_V1( WARN_TCP_ACCEPTW_D, newc->fd );
                vce_conn_free( newc,0,CLOSE_REASON_NONE );
                return;
            }
        }
    }

}




// すべての接続をpollする
void vce_tcp_poll( int isolate_conn_serial ) {
    conn *c;
    tcpcontext *t;
    int read_ret,write_ret;
    int any_io = 0;

    vce_socket_fdwrap_clear();

	vce_fdwrap_select_nfds=0;
    
    // 全部の mainsock 
    ARRAY_SCAN( vce_tcpcontext_mi , t ){
        if( !t->is_server )continue;
        vce_socket_fdwrap_set_read( t->mainsock );
		if(t->mainsock>vce_fdwrap_select_nfds)
			vce_fdwrap_select_nfds=t->mainsock;
    }

    // 全部のconn 
    ARRAY_SCAN( vce_conn_mi, c ){
		if(c->fd>vce_fdwrap_select_nfds) vce_fdwrap_select_nfds=c->fd;

        // 閉じフラグが立っていない場合は、通常の select をしようとする 
        if( c->closed_flag == 0 ){
            if( vce_sbuf_get_use( &c->wb ) > 0 ||
                ( ((tcpcontext*)c->tcpc)->nonblock_connect &&
                  c->nonblock_connect_ok == 0 ) ){
                any_io |= 1;
                vce_socket_fdwrap_set_write( c->fd );
            }
            if( vce_sbuf_get_rest( &c->rb ) > 0 ){
                vce_socket_fdwrap_set_read( c->fd );
            }
            continue;
        }

        // closedでも、書きたいデータがまだある場合は送ろうと努力する。ない場合は素直に閉じる。
        if( vce_sbuf_get_use( &c->wb ) == 0  ){
            vce_conn_free( c, 1, CLOSE_REASON_APPLICATION );
            VCE_ERROUT_V0( "tcp.c: conn_free(c,1) and continue 1.\n");
            continue;
        }
        // ただし、最大時間の制限はつけとく
        if( c->last_access < ( vce_global_time - c->timeout_sec )){
            VCE_ERROUT_V1( "tcp.c: absolute close_timeout for ser:%d! calling closewatcher 2.\n", c->serial );
            vce_conn_free(c,1, CLOSE_REASON_TIMEOUT );
            VCE_ERROUT_V0( "tcp.c: conn_free(c,1) and continue 2.\n" );
            continue;
        }

        // closed で書きこみデータがあって、 timeout でもない場合は、read も write もフラグを立て続ける。 
        if( vce_sbuf_get_use( &c->wb ) > 0 ){
            any_io |= 8;
            vce_socket_fdwrap_set_write( c->fd );
            vce_socket_fdwrap_set_read( c->fd );
        }
    }

    // select(3)を呼ぶ。今のOSだとepoll,kqueueとかなくても十分速い。
    vce_socket_fdwrap_select( vce_fdwrap_select_nfds+1, &read_ret, &write_ret );

    // accept/read/write test 
    ARRAY_SCAN( vce_conn_mi , c ){
        int r,w;
        int to_call_protoparser = 1;
        
        if( c->last_access < ( vce_global_time - c->timeout_sec )){
            conn_t ct = { c, c->serial };
            VCE_ERROUT_V2( WARN_TCP_TIMEOUT_CON_D_D, c->fd , c->timeout_sec );
            vce_conn_close(ct);
            vce_usage_increment_conn_timeout((tcpcontext*)c->tcpc);
            continue;
        }

        if( ( read_ret > 0 ) && vce_socket_fdwrap_is_readable( c->fd ) ){
            any_io |= 4; 
            r = 1;
        } else {
            r = 0;
        }
        if( ( write_ret > 0 ) && vce_socket_fdwrap_is_writable( c->fd) ) w = 1; else w = 0;
        if( isolate_conn_serial && c->serial != isolate_conn_serial ) to_call_protoparser = 0;
        vce_conn_io( c, r, w, to_call_protoparser );
    }

    if( read_ret > 0 ){
        ARRAY_SCAN( vce_tcpcontext_mi , t ){
            if( !t->is_server ) continue;
            if( vce_socket_fdwrap_is_readable( t->mainsock ) ){
                any_io |= 2; // accept はれっきとした I/O
                tcpcontext_try_accept( t );
            }
        }

    }

    // ということで、any_io がここで真だったら select のタイムアウトをカナリ へらし、0だったら1  usふやす 
    if( vce_select_timeout_flag  ){
        if( any_io ){
            if( vce_select_timeout_us > 0 ) vce_select_timeout_us /= 2;
            vce_select_timeout_us -= 10;
            if( vce_select_timeout_us <= 0 ) vce_select_timeout_us = 1;
        } else {
            vce_select_timeout_us +=1;
            if( vce_select_timeout_us > 1000 * 100 ){  // 100ms 
                vce_select_timeout_us = 1000 * 100;
            }
        }
    } else {
        vce_select_timeout_us = 0;
    }
}

int vce_tcpcontext_set_portscanner( tcpcontext_t tp,const char *host,unsigned short mainport,unsigned short subport) {
    tcpcontext *t = ( tcpcontext * ) tp;
	strcpy(t->ps_host,host);
	t->ps_mainport=mainport;
	t->ps_subport=subport;
	return 1;
}

conn_t vce_tcpcontext_connect( tcpcontext_t tp, const char *hname , unsigned short port ) {
    conn_t null_ct = { NULL, 0 };
    int fd;
    conn *newc = NULL;
    tcpcontext *t = ( tcpcontext * ) tp;
    conn_t return_conn_t;
    char remote_addr[16], local_addr[16];
    int remote_addr_len, local_addr_len;
    unsigned short local_port;
    int return_error = VCE_EBUG;


    if( ( fd = vce_socket_tcp_socket() ) < 0 ){
        SET_LAST_ERROR(VCE_ESOCKET);
        return null_ct;
    }

    if( t->nonblock_connect ){
        if( vce_socket_set_nonblock( fd ) < 0 ){
            vce_socket_close(fd);
            SET_LAST_ERROR(VCE_ESETSOCKOPT);
            return null_ct;
        }
    }
    if( vce_socket_set_keepalive( fd ) < 0 ){
        VCE_ERROUT0( "warning: failed to set KEEPALIVE socket option\n");
    }

    if( t->conn_in_use >= t->max_conn ){
        vce_socket_close(fd);
        VCE_ERROUT2( "error: cannot over max conn, conn_in_use=%d, max_conn=%d\n", t->conn_in_use, t->max_conn );
        SET_LAST_ERROR(VCE_EFULL);
        return null_ct;
    }

    remote_addr_len = sizeof( remote_addr );
    local_addr_len = sizeof( local_addr );
    if( vce_socket_connect( fd, hname, port,
                            remote_addr, &remote_addr_len,
                            local_addr, &local_addr_len,
                            &local_port,
                            (tcpcontext_t)t) < 0 ){
        vce_socket_close(fd);
        VCE_ERROUT_V2( "tcp.c : connect: returning null_ct %p, %d\n",
                       null_ct.p, null_ct.serial );
        SET_LAST_ERROR( VCE_ECONNECT);
        return null_ct;
    }

    VCE_ERROUT_V1( NOTE_TCP_CONNECT_OK_D , fd );

    // 新しいconn が1個ないとはじまらんよね。 
    if( ( newc = vce_conn_alloc()) == NULL ){
        return_error = VCE_EFULL;
        goto error_return;
    }
    t->conn_in_use ++;

    // 状態管理バッファも初期化
    if( t->statebuf_mi >= 0 ){
        newc->statebuf = vce_alloc_array_object( t->statebuf_mi );
        if( !newc->statebuf ){
            VCE_ERROUT0( BUG_TCP_CONNECT_STATEBUF_RUNSHORT );
            return_error = VCE_EMEM;
            goto error_return;
        }
        newc->statebuf_mi = t->statebuf_mi;
        newc->statebuf_size = t->statebuf_size;
        memset( newc->statebuf, 0, t->statebuf_size );
    } else {
        newc->statebuf_mi = -1;
        newc->statebuf_size = 0;
        newc->statebuf = NULL;
    }


    newc->fd = fd;
    newc->closed_flag = 0;
    newc->nonblock_connect_ok = 0;


    newc->is_server = 0;
    memcpy( newc->remote_addr, remote_addr, remote_addr_len );
    memcpy( newc->local_addr, local_addr, local_addr_len );
    newc->remote_addr_len = remote_addr_len;
    newc->local_addr_len = local_addr_len;
    newc->remote_port = port;
    newc->local_port = local_port;
    newc->protocol_parser = t->protocol_parser;
    newc->protocol_acceptwatcher = t->protocol_acceptwatcher;
    newc->protocol_hiwater_acceptwatcher = t->protocol_hiwater_acceptwatcher;
    newc->protocol_closewatcher = t->protocol_closewatcher;
    newc->pcallback = t->pcallback;
    newc->tcpc = (void*)t;
    vce_update_time();
    newc->last_access = vce_global_time;
    newc->timeout_sec = t->timeout_sec;
    newc->index = vce_conn_get_index_from_pointer( newc );

    newc->serial = vce_tcpcontext_get_next_conn_serial();

    newc->call_parser_per_loop = t->call_parser_per_loop;

    newc->maxlen_record=t->maxlen_record;
    newc->maxlen_warning=t->maxlen_warning;
	newc->userdata=NULL;

    newc->readwrite_callback = NULL;
    
    if( vce_sbuf_init( &newc->rb, t->rbmaster_mi )<0 ||
        vce_sbuf_init( &newc->wb, t->wbmaster_mi )<0 ){
        VCE_ERROUT_V0( "connect: cannot allocate send/recv buf\n" );
        return_error = VCE_EMEM;
        goto error_return;
    }

	if( t->nodelay&&!t->nonblock_connect ){
        if( vce_socket_set_nodelay( newc->fd ) < 0 ){
            VCE_ERROUT_V1( FATAL_TCP_SETSOCKOPT2_S, vce_get_os_errstr());
            return_error = VCE_ESETSOCKOPT;
            goto error_return;
        }
    }

    return_conn_t.p = newc;
    return_conn_t.serial = newc->serial;
    vce_usage_increment_tcpcontext_connect(t);

    SET_LAST_ERROR(VCE_NOERROR);
    return return_conn_t;


  error_return:
    if(newc){
        vce_sbuf_cleanup( &newc->rb );
        vce_sbuf_cleanup( &newc->wb );
        vce_conn_free(newc,0,CLOSE_REASON_NONE );
    }
    vce_socket_close(fd);
    SET_LAST_ERROR(return_error);
    return null_ct;
}


/////
int vce_tcpcontext_get_max_connection( tcpcontext_t t ) {
    tcpcontext *tcpc = (tcpcontext*) t;
    return tcpc->max_conn;
}
int vce_tcpcontext_get_all_connection( tcpcontext_t t , conn_t *a, int max) {
    conn *cur;
    int fill_count = 0;
    if( !t ) return SET_LAST_ERROR(VCE_EINVAL);
    ARRAY_SCAN( vce_conn_mi, cur ){
        if( (void*)cur->tcpc == (void*)t ){
            a[fill_count].p = cur;
            a[fill_count].serial = cur->serial;
            fill_count++;
            if( fill_count == max ) return fill_count;
        }
    }
    return fill_count;
}

int vce_tcpcontext_count_connections( tcpcontext_t t, int *co ) {
    conn *cur;
    int conn_count=0;
    if( !t) return SET_LAST_ERROR(VCE_EINVAL);
    ARRAY_SCAN(vce_conn_mi,cur){
        if( cur->tcpc == (tcpcontext*)t){
            conn_count++;
        }
    }
    if(co) *co = conn_count;
    return SET_LAST_ERROR(VCE_NOERROR);
}


void vce_tcpcontext_enable_accept( tcpcontext_t tp, int flag ) {
    tcpcontext * t = (tcpcontext*)tp;
    t->accept_more = flag;
    VCE_ERROUT_V2( "vce_tcpcontext_enable_accept: set flag %d to %p\n", flag, tp );
}
void vce_tcpcontext_get_stat( tcpcontext_t tp, tcpcontext_stat_t *s ) {
    conn *cur;
    tcpcontext *t = (tcpcontext*)tp;

    s->current_conn = 0;
    ARRAY_SCAN(vce_conn_mi,cur){
        if( (void*)cur->tcpc == (void*)t){
            s->current_conn ++;
        }
    }

    s->recv_byte = ((tcpcontext*)tp)->recv_byte;
    s->send_byte = ((tcpcontext*)tp)->send_byte;
    s->recv_syscall = ((tcpcontext*)tp)->recv_syscall;
    s->recv_syscall_e = ((tcpcontext*)tp)->recv_syscall_e;
    s->send_syscall = ((tcpcontext*)tp)->recv_syscall;
    s->send_syscall_e = ((tcpcontext*)tp)->send_syscall_e;
    s->accept_syscall = ((tcpcontext*)tp)->accept_syscall;
    s->accept_syscall_e = ((tcpcontext*)tp)->accept_syscall_e;
    s->connect_syscall = ((tcpcontext*)tp)->connect_syscall;
    s->connect_syscall_e = ((tcpcontext*)tp)->connect_syscall_e;
    s->conn_write = ((tcpcontext*)tp)->conn_write;
    s->conn_timeout = ((tcpcontext*)tp)->conn_timeout;
    s->tcpcontext_connect = ((tcpcontext*)tp)->tcpcontext_connect;
}


int vce_tcpcontext_conn_iterate( tcpcontext_t tt, int (*f)(conn_t c)) {
    conn *cur;
    tcpcontext *t = (tcpcontext*) tt;
    if( !t ) return SET_LAST_ERROR(VCE_EINVAL);
    ARRAY_SCAN( vce_conn_mi, cur ){
        if( (void*)cur->tcpc == (void*)t){
            conn_t tmpc = { cur, cur->serial };
            if( f( tmpc )< 0 ) break;
        }
    }
    return SET_LAST_ERROR(VCE_NOERROR);
}

void vce_tcpcontext_set_conn_call_parser_per_heartbeat( tcpcontext_t tt, int v ) {
    tcpcontext *t = (tcpcontext*) tt;
    t->call_parser_per_loop = v;
}


