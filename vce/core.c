#include "vce.h"
#include "vcecommon.h"
#include "conn.h"
#include "tcp.h"


#include "uselog.h"
#include "osdep.h"
#include "core.h"
#include "search.h"
#include "mem.h"

vce_limit_t vce_limit = {
    OSDEP_DEFAULT_MAXTCPCONTEXT,
#if ( OSDEP_FD_SETSIZE > 1024 )
    1000,
#else
    OSDEP_DEFAULT_MAXCON,
#endif
    OSDEP_DEFAULT_MAX_ARRAY_INDEX,
    OSDEP_SEND_UNIT,
    OSDEP_RECV_UNIT
};

char *vce_sendbuf_work = NULL;
char *vce_recvbuf_work = NULL;

/*
  Set 1 when socket library(winsock in windows) is ready.
  "Ready" means that socket() and connect(), accept() is available.
  Linux and OSX: always 1, Windows: start from 0, and 1 after winsock initialization.
  vce_heartbeat will do nothing whenthis flag is 0 .
*/
int vce_socket_library_ok = 0;  

int vce_initialize( void ) {
	int ret;

    if( vce_socket_library_ok == 0 ) {
        if( vce_socket_lib_os_init() == 0 ){
            vce_socket_library_ok = 1;
        }
    }

	vce_update_time();

	// fixed size of send/recv buffer.
	vce_sendbuf_work = (char*) VCEMALLOC( vce_limit.sendbuf_work_size );
	vce_recvbuf_work = (char*) VCEMALLOC( vce_limit.recvbuf_work_size );
	if( !vce_sendbuf_work || !vce_recvbuf_work ){
		if( vce_sendbuf_work ) VCEFREE( vce_sendbuf_work );
		if( vce_recvbuf_work ) VCEFREE( vce_recvbuf_work );
		return SET_LAST_ERROR(VCE_EMEM);
	}

    if( (ret = vce_array_init_world()) < 0 ){
        return SET_LAST_ERROR(ret);
    }

	if( (ret = vce_conn_init_world()) < 0 ){
        vce_array_fin_world();
		return SET_LAST_ERROR(ret);
	}

	if( ( ret = vce_tcpcontext_init_world())<0){
		vce_conn_fin_world();
        vce_array_fin_world();
		return SET_LAST_ERROR(ret);
	}

    vce_usage_set_boot_time( vce_global_time );

    return SET_LAST_ERROR(0);
}

////////
void vce_limit_clear( vce_limit_t *t ) {
    t->max_tcpcontext = -1;
    t->max_conn = -1;
    t->max_array = -1;
    t->sendbuf_work_size = -1;
    t->recvbuf_work_size = -1;
}
int vce_initialize_limited( vce_limit_t *lim ) {
	if(  lim->max_tcpcontext != -1 ){
		vce_limit.max_tcpcontext = lim->max_tcpcontext;
	}
	if(  lim->max_conn != -1 ){
		vce_limit.max_conn = lim->max_conn;
	}
    if( lim->max_array != -1 ){
        vce_limit.max_array = lim->max_array;
    }
    if( lim->sendbuf_work_size != -1 ){
    	vce_limit.sendbuf_work_size = lim->sendbuf_work_size;
    }
    if( lim->recvbuf_work_size != -1 ){
    	vce_limit.recvbuf_work_size = lim->recvbuf_work_size;
    }

#define ARRAY_HARD_MINIMUM 8
    if( vce_limit.max_array < ARRAY_HARD_MINIMUM ){
        vce_limit.max_array = ARRAY_HARD_MINIMUM;
    }
    if( lim->sendbuf_work_size != -1 ){
    	vce_limit.sendbuf_work_size = lim->sendbuf_work_size;
    }
    if( lim->recvbuf_work_size != -1 ){
    	vce_limit.recvbuf_work_size = lim->recvbuf_work_size;
    }


	return vce_initialize();
}
void vce_init_limit_t( vce_limit_t *t ) {
    t->max_tcpcontext = -1;
    t->max_conn = -1;
    t->max_array = -1;
    t->sendbuf_work_size = -1;
    t->recvbuf_work_size = -1;
}
int vce_finalize( void ) {
	int e = 0;

	if( vce_tcpcontext_fin_world() < 0 ) e = 1;
	if( vce_conn_fin_world() < 0 ) e = 1;
    if( vce_array_fin_world() < 0 ) e = 1;

	VCEFREE( vce_sendbuf_work );
	VCEFREE( vce_recvbuf_work );

	VCE_ERROUT_V0( NOTE_VCE_FINALIZED );
	if( e ){
		return SET_LAST_ERROR(VCE_EFINALIZE);
	} else {
		return SET_LAST_ERROR(0);
	}
}


VCEI64 vce_mainloop_utime_store = 0;
int vce_mainloop_counter = 0; 

time_t vce_global_time = 0; // To reduce frequency of systemcalls called.


void vce_heartbeat( void ) {
	vce_mainloop_counter ++;
	vce_tcp_poll(0);
	vce_update_time(); 
}

void vce_heartbeat_on_single_conn( conn_t c ) {
    conn *ptr = (conn*)c.p;
    vce_mainloop_counter++;
    vce_tcp_poll( ptr->serial );
    vce_update_time();
}


void vce_set_heartbeat_wait_flag( int flag ) {
	vce_select_timeout_flag = flag;
}


VCEI64 vce_get_current_utime( void ) {
	return vce_mainloop_utime_store;
}


