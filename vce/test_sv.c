#include <stdio.h>
#include "vce.h"
#include "testproto_sv.h"

struct cinfo {
    int cnt;
};


int conn_closewatcher( conn_t c, CLOSE_REASON reason ) {
    vce_errout("closewatcher. reason:%d\n", reason );
    return 0;
}
int conn_acceptwatcher( conn_t c ) {
    vce_errout("acceptwatcher");
    struct cinfo *ci = vce_conn_get_state_buffer( c, NULL );
    ci->cnt = 0;
    return 0;
}
int testproto_sv_recv_error_callback( conn_t c, int e ) {
    vce_errout( "testproto_sv_recv_error_callback e:%d\n",e );
    return 0;
}
int testproto_ping_recv( conn_t c, int msgid, int majorversion, int minorversion, int tick ) {
    struct cinfo *ci = vce_conn_get_state_buffer( c, NULL );
    ci->cnt++;
    if( ci->cnt%1000000==0) {
        vce_errout( "testproto_ping_recv: %d %d %d %d cnt:%d\n", msgid, majorversion, minorversion, tick, ci->cnt );
    }
    return testproto_pong_send( c, msgid, majorversion, minorversion, tick );
}
int testproto_sv_sender( conn_t c, char *data, int len ) {
    return vce_protocol_unparser_bin32( c, data, len );
}
int testproto_toolong_recv_warning( conn_t c,int proto_id,int length) {
    vce_errout( "testproto_toolong_recv_warning. proto_id:%d len:%d\n",proto_id, length );
    assert(0);
    return 0;
}


int main( int argc, char **argv ) {
    tcpcontext_t tctx;

    vce_initialize();
    vce_set_verbose_mode(1);
    
    tctx = vce_tcpcontext_create( 1, // server
                                  NULL, 22282, // addr, port
                                  10, // maxcon
                                  1024*32, 1024*32, // rblen, wblen
                                  60, // timeout
                                  0, // nonblock_connect
                                  0, // nodelay
                                  sizeof(struct cinfo) // statebuf_size
                                  );
    if(!tctx) {
        vce_errout( "tcpcontext_create: %s\n", STRERR );
        return 1;
    }
    vce_tcpcontext_set_conn_call_parser_per_heartbeat( tctx, 1000 );

    vce_tcpcontext_set_conn_parser( tctx, vce_protocol_parser_bin32, testproto_sv_pcallback );
    vce_tcpcontext_set_conn_closewatcher( tctx, conn_closewatcher );
    vce_tcpcontext_set_conn_acceptwatcher( tctx, conn_acceptwatcher );

    vce_set_heartbeat_wait_flag(1);
    //    vce_set_read_write_log_mode(1);    

    int loop=0;
    while(1) {
        vce_heartbeat();
        loop++;
        if((loop%10000)==0) fprintf(stderr, "." );
    }
    return 0;
}
