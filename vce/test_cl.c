#include <stdio.h>
#include "vce.h"
#include "testproto_cli.h"



int conn_closewatcher( conn_t c, CLOSE_REASON reason ) {
    vce_errout("closewatcher. reason:%d\n", reason );
    return 0;
}
int testproto_cli_sender( conn_t c, char *data, int len ) {
    //    vce_errout( "testproto_cli_sender: len:%d\n",len);
    return vce_protocol_unparser_bin32( c, data, len );
}
int testproto_cli_recv_error_callback( conn_t c, int e ) {
    vce_errout( "testproto_cli_recv_error_callback: gen error: %d\n", e );
    return -1;
}


int g_sync_waiting_pong = 0; // for blocking PING
   
int testproto_pong_recv( conn_t c, int msgid, int majorversion, int minorversion, int tick ) {
    if( g_sync_waiting_pong ) {
        g_sync_waiting_pong = 0;
        assert( msgid == 5 && majorversion == 4 && minorversion ==3 && tick == 2 );
    } else {
        assert( msgid == 1 && majorversion == 2 && minorversion ==3 && tick == 4 );        
        static int cnt=0;
        cnt++;
        if( cnt%1000000 == 0 ) {
            vce_errout( "testproto_pong_recv: %d %d %d %d cnt:%d\n", msgid, majorversion, minorversion, tick, cnt  );
        }
    }
    return 0;
}

// blocking(=synchronized) ping
void syncPing( conn_t c ) {
    vce_errout( "send ping sync");
    testproto_ping_send( c, 5,4,3,2 );
    g_sync_waiting_pong = 1;
    while(1) {
        vce_heartbeat_on_single_conn(c);
        if( g_sync_waiting_pong == 0 ) {
            break;
        }
    }
    vce_errout( "received ping sync");    
}

int main( int argc, char **argv ) {
    tcpcontext_t tctx;

    vce_initialize();
    vce_set_verbose_mode(1);
    
    tctx = vce_tcpcontext_create( 0, // server
                                  NULL, 0, // addr, port
                                  10, // maxcon
                                  1024*32, 1024*32, // rblen, wblen
                                  60, // timeout
                                  0, // nonblock_connect
                                  0, // nodelay
                                  0 // statebuf_size
                                  );
    if(!tctx) {
        vce_errout( "tcpcontext_create: %s\n", STRERR );
        return 1;
    }
    vce_tcpcontext_set_conn_call_parser_per_heartbeat( tctx, 1000 );
    vce_tcpcontext_set_conn_parser( tctx, vce_protocol_parser_bin32, testproto_cli_pcallback );
    vce_tcpcontext_set_conn_closewatcher( tctx, conn_closewatcher );
    vce_set_heartbeat_wait_flag(1);
    //    vce_set_read_write_log_mode(1);
    
    
    conn_t c0 = vce_tcpcontext_connect( tctx, "localhost", 22282 );
    if( !vce_conn_is_valid(c0) ) {
        vce_errout( "vce_tcpcontext_connect failed for c0\n" );
        return 1;
    }
    conn_t c1 = vce_tcpcontext_connect( tctx, "localhost", 22282 );
    if( !vce_conn_is_valid(c1) ) {
        vce_errout( "vce_tcpcontext_connect failed for c1\n" );
        return 1;
    }

    int loop=0;
    while(1) {
        vce_heartbeat();
        loop++;
        if((loop%10000)==0) fprintf(stderr, "." );
        int i;
        for(i=0;i<30;i++) {
            if( vce_conn_writable(c0) > 200 ) {
                testproto_ping_send( c0, 1,2,3,4 );
            }
        }
        if( loop%100000==0) syncPing(c1);        
    }
    return 0;
}
