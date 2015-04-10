#include "vce.h"
#include "vcecommon.h"
#include "conn.h"

#include "tcp.h"
#include "uselog.h"
#include "protocol.h"
#include "util.h"
#include "core.h"

// Number of active connections
int vce_conn_active_num =0 ;
int vce_conn_mi = -1;   // VCE's array index for connections



static int to_break_heartbeat; // used in vce_conn_break_heartbeat, thread unsafe!

int vce_conn_init_world( void ) {
    if( vce_limit.max_conn > 0 ){
        vce_conn_mi = vce_init_array( sizeof( conn ) , vce_limit.max_conn,"conn" );
        if( vce_conn_mi < 0 ) return SET_LAST_ERROR( VCE_EARRAY );
    }
    return SET_LAST_ERROR( 0 );
}
int vce_conn_fin_world(void) {
    if( vce_conn_mi >= 0 ){
        int ret;
        if( (ret = vce_end_array( vce_conn_mi ) ) < 0 ){
            return SET_LAST_ERROR(ret);
        }
    }
    return SET_LAST_ERROR(VCE_NOERROR);
}

conn * vce_conn_alloc( void ) {
    conn *c;
    if( vce_conn_mi < 0 ){
        SET_LAST_ERROR( VCE_ECONNINIT );
        return NULL;
    }
    c = vce_alloc_array_object( vce_conn_mi );
    if( !c ){
        SET_LAST_ERROR(VCE_EFULL);
        return c;
    }
    vce_conn_active_num ++;
    vce_usage_increment_conn_alloc();
    SET_LAST_ERROR( 0 );
    return c;
}
void vce_conn_free3( conn *c) {
    vce_socket_shutdown_rw( c->fd );
    vce_socket_close( c->fd );

    vce_sbuf_cleanup( &c->rb );
    vce_sbuf_cleanup( &c->wb );


    c->serial = 0;
    vce_free_array_object( vce_conn_mi, c );

    if(c->statebuf) memset(c->statebuf,0,c->statebuf_size);

    if( c->statebuf_mi >= 0 ){
        vce_free_array_object( c->statebuf_mi , c->statebuf );
        VCE_ERROUT_V0( NOTE_TCP_FREED_STATEBUF );
    }
    ((tcpcontext*)c->tcpc)->conn_in_use--;
    memset(c,0,sizeof(conn));
    vce_conn_active_num --;
    vce_usage_increment_conn_free();
    SET_LAST_ERROR(VCE_NOERROR);

}
void vce_conn_free2( conn *c) {
    if( ((tcpcontext*)c->tcpc)->conn_finalizer ){
        conn_t tmpc;
        tmpc.p = c;
        tmpc.serial = c->serial;
        VCE_ERROUT_V1( "vce_conn_free: calling finalizer serial: %d\n", c->serial );
        ((tcpcontext*)c->tcpc)->conn_finalizer( tmpc );
    }
    vce_conn_free3( c);
}
/* not exposed to user */
void vce_conn_free( conn *c, int closewatcher, CLOSE_REASON reason ) {
    if(c==0||c->serial==0)
        return;
    if( vce_conn_get_index_from_pointer( c ) < 0 ){
        VCE_ERROUT_V1( "conn.c : bad pointer %p\n", c );
        return;
    }

    /* closewatcher is called only after succeeding connect() or accept() and get valid connection */
    if( closewatcher && c->protocol_closewatcher ){
        conn_t ct;
        ct.p = c;
        ct.serial = c->serial;
        c->protocol_closewatcher(ct,reason);
    }
    vce_conn_free2( c);
}

int vce_conn_is_closed( conn_t ct ) {
    if( vce_conn_is_valid(ct) ) {
        conn *c = (conn*)ct.p;
        if(c->closed_flag) {
            return 1;
        }
    }
    return 0;
}
void vce_conn_close( conn_t ct ) {
    conn *c = (conn*)ct.p;
    if( !vce_conn_is_valid(ct)){
        SET_LAST_ERROR(VCE_EINVAL);
        return;
    }
    if( c->closed_flag ){
        VCE_ERROUT_V1( "vce_conn_close: already closed serial: %d\n", ct.serial );
        SET_LAST_ERROR(VCE_EALREADY);
        return;
    }
    c->closed_flag = 1;
    vce_usage_increment_conn_close();
    SET_LAST_ERROR(VCE_NOERROR);
}


void vce_conn_userdata_set_pointer(conn_t ct,void *p) {
    conn *c = (conn*) ct.p;
	if( !vce_conn_is_valid(ct)) return;
	c->userdata=p;
}

void*vce_conn_userdata_get_pointer(conn_t ct) {
    conn *c = (conn*) ct.p;
	if( !vce_conn_is_valid(ct)) return NULL;
	return c->userdata;
}

void vce_conn_set_timeout( conn_t ct, int sec ) {
    conn *c = (conn*) ct.p;
    if( !vce_conn_is_valid(ct)){
        SET_LAST_ERROR(VCE_EINVAL);
        return;
    }
    c->timeout_sec = sec;
    SET_LAST_ERROR(VCE_NOERROR);
}

int vce_conn_get_index( conn_t c ) {
    return vce_conn_get_index_from_pointer( c.p );
}

conn_t vce_conn_get_struct_from_index( int index ) {
    conn_t re;
    conn *c;

    c = vce_get_array_object_pointer_by_index( vce_conn_mi, index );
    re.p = c;
    re.serial = c->serial;
    return re;
}

int vce_conn_get_index_from_pointer( conn *c ) {
    return vce_get_array_object_index( vce_conn_mi, c );
}

void *vce_conn_get_state_buffer( conn_t ct, int *len ) {
    conn *c = (conn*) ct.p;
    if( !vce_conn_is_valid(ct)){
        SET_LAST_ERROR(VCE_EINVAL);
        return NULL;
    }
    SET_LAST_ERROR(VCE_NOERROR);
    if( c->statebuf_size >0 ){
        if(len) *len = (int)c->statebuf_size;
        return c->statebuf;
    } else {
        return NULL;
    }
}

//  int rf : readable flag
//  int wf : writable flag
void vce_conn_io( conn *c , int rf , int wf, int call_protoparser ) {
    conn_t ct = { c, c->serial};
    assert(c);

    if( rf ){
        int readlen , readret, again;
        int rest = vce_sbuf_get_rest( &c->rb );
        static char readbuf[OSDEP_RECV_UNIT];
        if( rest > OSDEP_RECV_UNIT ){
            readlen = OSDEP_RECV_UNIT;
        } else {
            readlen = rest;
        }
        if( readlen == 0 ) goto write_phase;

        readret = vce_socket_recv( c->fd, readbuf, readlen, &again );
        
        if( again == 1 ){
            goto write_phase;
        }
        if( readret > 0 ){
            if( c->readwrite_callback ) c->readwrite_callback( ct, 0, readbuf, readret );
            vce_sbuf_push( &c->rb, readbuf , readret );
            if( ((tcpcontext*)c->tcpc)->recv_reset_timeout ){
                c->last_access = vce_global_time;
            }
            vce_usage_increment_recv_syscall(c);
            vce_usage_add_recv_byte( readret, c );
            if( vce_log_read_write ){
                char s[64];
                VCE_ERROUT_V3( "\nread() %d bytes from %d (%s)\n",
                               readret , c->fd,
                               vce_conn_get_remote_addr_string(
                                                               ct,s,sizeof(s)) );
                vce_dump_buffer( readbuf, readret );
            }
        } else if( readret == 0 ){
            char e_addr[64];
            vce_conn_get_remote_addr_string( ct, e_addr, sizeof(e_addr));
            VCE_ERROUT_V2( NOTE_CONN_EOF_D_S, c->fd, e_addr );
            vce_usage_increment_recv_syscall_e (c);
            vce_conn_free(c,1,CLOSE_REASON_REMOTE );

            return;
        } else {
            char e_addr[64];
            vce_conn_get_remote_addr_string( ct, e_addr, sizeof(e_addr));
            VCE_ERROUT_V2( NOTE_CONN_READERROR_D_S, c->fd, e_addr );
            vce_usage_increment_recv_syscall_e(c);
            vce_conn_free(c,1, CLOSE_REASON_REMOTE );

            return;
        }
    }
write_phase:

    if( wf ){
        char *writebuf;
        int len , writeret, again;
        if(((tcpcontext*)(c->tcpc))->nonblock_connect &&
            c->nonblock_connect_ok == 0 ){
            c->nonblock_connect_ok = 1;
			if( ((tcpcontext*)(c->tcpc))->nodelay ){
				if( vce_socket_set_nodelay( c->fd ) < 0 ){
					VCE_ERROUT1( FATAL_TCP_SETSOCKOPT_S, vce_get_os_errstr());
				}
			}
            c->local_addr_len = sizeof( c->local_addr);
            vce_socket_getsockname( c->fd,
                                    c->local_addr,
                                    &c->local_addr_len,
                                    &c->local_port );
            goto callback_phase;
        }
        vce_sbuf_get_buffer( &c->wb, &writebuf, &len );
        if( len > OSDEP_SEND_UNIT ) len = OSDEP_SEND_UNIT;

        writeret = vce_socket_send( c->fd, writebuf, len, &again );
        
        if( again == 1 ){
            goto callback_phase;
        }
        if( writeret > 0 ){
            if( c->readwrite_callback ) c->readwrite_callback( ct, 1, writebuf, writeret );            
            vce_sbuf_shrink( &c->wb , NULL , writeret );
            if(((tcpcontext*)c->tcpc)->send_reset_timeout ){
                c->last_access = vce_global_time;
            }
            vce_usage_increment_send_syscall(c);
            vce_usage_add_send_byte( writeret, c );
            if( vce_log_read_write ){
                char s[64];
                VCE_ERROUT_V4( "\nwrite(%d,...,%d) returns %d (%s)\n",
                               c->fd, len, writeret,
                               vce_conn_get_remote_addr_string(
                                   ct, s, sizeof(s)));
                vce_dump_buffer( writebuf, writeret );
            }
        } else if( writeret <= 0 ){
            char e_addr[64];
            vce_conn_get_remote_addr_string( ct, e_addr, sizeof(e_addr));
            VCE_ERROUT_V2( "conn.c: os error is '%s' writelen is %d\n",
                           vce_get_os_errstr(), len );
            VCE_ERROUT_V3( NOTE_CONN_WRITEERROR_D_S_S, c->fd,
                           vce_get_os_errstr(), e_addr );

            vce_usage_increment_send_syscall_e(c);
            vce_conn_free(c,1, CLOSE_REASON_REMOTE );
            return;
        }
    }


  callback_phase:
    /* To balance load between all connections */
    if( vce_sbuf_get_use( &c->rb ) > 0 ){
        if( !c->protocol_parser ){
            VCE_ERROUT_V0( WARN_CONN_DOES_NOT_HAVE_PARSER );
        } else if( call_protoparser ){
            int pret, k;
            to_break_heartbeat = 0;
            for(k=0;k<c->call_parser_per_loop;k++){
                pret = c->protocol_parser( ct );
                if( pret < 0 ){
                    VCE_ERROUT_V2( NOTE_CONN_PROTOCOL_ERROR_D_D , c->fd ,pret );
                    vce_conn_free(ct.p,1,CLOSE_REASON_PARSER );
                    return;
                }
                if( to_break_heartbeat ) break;
            }
        }
    }
}

void vce_conn_break_heartbeat() {
    to_break_heartbeat = 1;
}

int vce_conn_write( conn_t ct, char *b, size_t len ) {
    conn *c = (conn*)ct.p;

    if( !c ) return SET_LAST_ERROR(VCE_EINVAL);
    if( !b || len <= 0 ) SET_LAST_ERROR(VCE_EINVAL);
    if( c->serial != ct.serial ) return SET_LAST_ERROR(VCE_ECONNSERIAL);
    if( ((tcpcontext*)c->tcpc)->nonblock_connect &&
        c->nonblock_connect_ok == 0 ) return SET_LAST_ERROR(VCE_ENOTREADY);
    if( c->closed_flag ) return SET_LAST_ERROR(VCE_ECLOSED);

    vce_usage_increment_conn_write(c);
    if( vce_log_read_write ){
        VCE_ERROUT_V2("\nconn_write(serial:%d len:%d)\n", ct.serial, (int)len );
    }
    return vce_sbuf_push( &c->wb, b, len );
}

int vce_conn_writable( conn_t ct ) {
    conn *c = (conn*) ct.p;
    if( vce_conn_is_valid(ct) == 0 ){
        return SET_LAST_ERROR(VCE_EINVAL);
    }
    if( ((tcpcontext*)(c->tcpc))->nonblock_connect != 0 && c->nonblock_connect_ok == 0 ) return SET_LAST_ERROR(VCE_NOERROR);

    return vce_sbuf_get_rest( &c->wb );
}

int vce_conn_writed( conn_t ct ) {
    conn *c = (conn*) ct.p;
    if( vce_conn_is_valid(ct) == 0 ){
        return 1;
    }
    if( ((tcpcontext*)(c->tcpc))->nonblock_connect != 0 &&
        c->nonblock_connect_ok == 0 ) return 1;
    if( vce_sbuf_get_use( &c->wb ) > 0 ){
        return 0;
    }else{
        return 1;
    }
}

void vce_conn_show_stat( void ) {
    conn *c;
    char work[32];
    int i=0;
    ARRAY_SCAN(vce_conn_mi,c){
        i++;
    }
    if(i==0)return;
    vce_errout( "=== SHOW CONNECTION STATISTICS ===\n" );
    ARRAY_SCAN( vce_conn_mi, c ){
        vce_errout( "A:%8p IP:%s:%05d Lst:%09u "
                    "I:%04d Sv:%1d R:%8p W:%8p \n",
                    c, 
                    vce_make_ipv4_dot_notation( c->remote_addr,
                                                c->remote_addr_len,
                                                work,sizeof(work) ),
                    c->remote_port,
                    (unsigned int)c->last_access,
                    c->index,
                    c->is_server,
                    &c->rb , &c->wb
                    );
    }
    vce_errout( "=== END ===\n" );
}

void vce_conn_get_remote_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p  ) {
    conn *c = (conn*) ct.p;
    if( a ){
        memcpy( a, c->remote_addr, MIN(4,c->remote_addr_len));
    }
    if( p ){
        *p = c->remote_port;
    }
}

void vce_conn_get_local_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p ) {
    conn *c = (conn*) ct.p;
    if( a ){
        memcpy( a, c->local_addr, MIN(4,c->local_addr_len));
    }
    if( p ){
        *p = c->local_port;
    }
}

void vce_conn_get_remote_ipv6_addr( conn_t ct, char *a, unsigned short *p ) {
    conn *c = (conn*) ct.p;
    if( a ){
        memcpy( a, c->remote_addr, MIN(16,c->remote_addr_len));
    }
    if( p ){
        *p = c->remote_port;
    }
}

void vce_conn_get_local_ipv6_addr( conn_t ct, char *a, unsigned short *p ) {
    conn *c = (conn*)ct.p;
    if( a ) {
        memcpy( a, c->local_addr, MIN(16,c->local_addr_len));
    }
    if( p ) {
        *p = c->local_port;
    }
}

char *vce_conn_get_remote_ipv4_addr_string( conn_t ct, char *s, int max ) {
    unsigned short p;
    unsigned int uia;
    char work[32];

    if( max < sizeof(work) ){
        SET_LAST_ERROR(VCE_ETOOSHORT);
        return NULL;
    }

    vce_conn_get_remote_ipv4_addr( ct, &uia, &p );

    vce_snprintf( s,max, "%s:%d",
                  vce_make_ipv4_dot_notation( (char*)&uia,4,
                                              work,sizeof(work)),
                  p );

    SET_LAST_ERROR(VCE_NOERROR);
    return s;
}

char *vce_conn_get_local_ipv4_addr_string( conn_t ct, char *s, int max ) {
    unsigned short p;
    unsigned int uia;
    char work[32];

    if( max < sizeof(work)) {
        SET_LAST_ERROR(VCE_ETOOSHORT);
        return NULL;
    }
    vce_conn_get_local_ipv4_addr( ct, &uia, &p );
    vce_snprintf( s, max, "%s:%d",
                  vce_make_ipv4_dot_notation((char*)&uia,4,work,sizeof(work)),
                  p );
    SET_LAST_ERROR(VCE_NOERROR);
    return s;
}

char *vce_conn_get_remote_ipv6_addr_string( conn_t ct, char *s, int max ) {
    char ia[16];
    unsigned short p;
    char work[50];

    if(max<sizeof(work)){
        SET_LAST_ERROR(VCE_ETOOSHORT);
        return NULL;
    }
    vce_conn_get_remote_ipv6_addr( ct, ia, &p );
    vce_snprintf( s, max, "%s:%d",
                  vce_make_ipv6_dot_notation( ia,16,work,sizeof(work)),p);
    SET_LAST_ERROR(VCE_NOERROR);
    return s;
}

char *vce_conn_get_local_ipv6_addr_string( conn_t ct, char *s, int max ) {
    char ia[16];
    unsigned short p;
    char work[50];
    if( max < sizeof(work) ){
        SET_LAST_ERROR(VCE_ETOOSHORT);
        return NULL;
    }
    vce_conn_get_local_ipv6_addr( ct, ia, &p );
    vce_snprintf( s, max, "%s:%d",
                  vce_make_ipv6_dot_notation(ia,16,work,sizeof(work)),p);
    SET_LAST_ERROR(VCE_NOERROR);
    return s;
}

char *vce_conn_get_remote_addr_string( conn_t ct, char *s, int max ) {
    conn *c = ct.p;
    if(!c) return NULL;

    if( c->remote_addr_len == 4 ){
        return vce_conn_get_remote_ipv4_addr_string( ct,s,max );
    } else if( c->remote_addr_len == 16 ){
        return vce_conn_get_remote_ipv6_addr_string( ct,s,max );
    } else {
        SET_LAST_ERROR(VCE_EINVAL);
        return NULL;
    }
}


char *vce_conn_get_local_addr_string( conn_t ct, char *s, int max ) {
    conn *c = ct.p;
    if( !c ) return NULL;

    if( c->local_addr_len == 4 ){
        return vce_conn_get_local_ipv4_addr_string( ct,s, max );
    } else if( c->local_addr_len == 16 ){
        return vce_conn_get_local_ipv6_addr_string( ct,s, max );
    } else {
        SET_LAST_ERROR( VCE_EINVAL );
        return NULL;
    }
}

void vce_conn_close_tcpcontext_all( tcpcontext_t t ) {
    conn *cur;
    int count = 0;
    ARRAY_SCAN( vce_conn_mi, cur ){
        if( (void*)cur->tcpc == (void*)t ){
            conn_t cont;
            cont.p = cur;
            cont.serial = cur->serial;
            vce_conn_close( cont );
            VCE_ERROUT_V1( "vce_conn_close_tcpcontext_all: closed serial %d\n",
                           cur->serial );
            count++;
        }
    }
    VCE_ERROUT_V1( "vce_conn_close_tcpcontext_all: closed %d connections\n",
                   count );
}

tcpcontext_t vce_conn_get_tcpcontext( conn_t ct ) {
    conn* c = ct.p;
    return c->tcpc;
}

int vce_conn_is_valid( conn_t ct ) {
    if( ct.serial == 0 ) return 0;
    if( ct.p == NULL ) {
        return 0;
    } else {
        if( vce_conn_get_index_from_pointer( ct.p ) < 0 ){
            VCE_ERROUT_V1( "conn.c : bad pointer %p\n", ct.p );
            return 0;
        } else {

            conn *c = (conn*)(ct.p);
            if( c->serial == ct.serial ){
                return 1;
            } else {
                return 0;
            }
        }
    }
}

int vce_conn_is_equal( conn_t c1 , conn_t c2 ) {
    if( c1.p == c2.p && c1.serial == c2.serial ){
        return 1;
    } else {
        return 0;
    }
}

void vce_conn_get_buffer( conn_t ct, char **rb, int *rblen, char **wb, int *wblen ) {
    conn *c = (conn*) ct.p;
    vce_sbuf_get_buffer( &c->rb,rb,rblen );
    vce_sbuf_get_buffer( &c->wb,wb,wblen );
}

int vce_conn_shrink_readbuf( conn_t ct, int len ) {
    conn *c = (conn*) ct.p;
    return vce_sbuf_shrink( &c->rb, NULL, len );
}

void vce_conn_clear( conn_t *c ) {
    memset( c, 0, sizeof( conn_t ));
}

void vce_conn_get_stat( conn_t ct, conn_stat_t *s ) {
    conn *c = (conn*)ct.p;
    s->recv_byte = c->recv_byte;
    s->send_byte = c->send_byte;
    s->recv_syscall = c->recv_syscall;
    s->send_syscall = c->send_syscall;
    s->conn_write = c->conn_write;
}


void vce_conn_set_parser( conn_t ct, int (*parser)(conn_t), int (*pcallback)(conn_t,char*,int)) {
    conn *c = (conn*)ct.p;
    if(c){
        c->protocol_parser = parser;
        c->pcallback = pcallback;
    }
}

void vce_conn_set_io_callback( conn_t ct, void (*cb)( conn_t ct, int rwflag, char *data, size_t sz ) ) {
    conn *c = (conn*)ct.p;
    if(c){
        c->readwrite_callback = cb;
    }
}
