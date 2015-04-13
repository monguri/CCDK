#ifndef _CONN_H_
#define _CONN_H_

#include "vce.h"
#include "sbuf.h"
#include "osdep.h"


// Represent a TCP connection(socket).
typedef struct _conn {
    int fd;

	// Indicate that this connection is about to close.
    // This flag is set 1 only when vce_conn_close() is called.
    // close(2) systemcall will be called inside vce_heartbeat() if this flag is set.
    // VCE don't set this flag internally. In that case VCE uses conn_free directly.
	int closed_flag;

	// Connect() succeeded or not, in non-blocking connect socket.
    // This flag won't be used if tcpcontext's nonblock_connect is not set 1.
	int nonblock_connect_ok;

    // Internet address of a connection, initialized when successful accept/connect()
	char remote_addr[16]; // ipv4:top 4 bytes network byte order. ipv6:16bytes net byte order.
	int remote_addr_len; // ipv4:4 ipv6:16 
	unsigned short remote_port; // network byte order
	char local_addr[16];
	int local_addr_len;
	unsigned short local_port;
    
    time_t last_access; // time of last access
    int timeout_sec;  // connection timeout thres

	sbuf rb,wb;

    void *tcpc; // pointer totcpcontext

    int is_server;
    
    int index; // index to conn array
	void *userdata; // additional userdata pointer 
	char *statebuf; // master state buffer ( from tcpcontext's mem index)
	size_t statebuf_size; // copy from tcpcontext
	int statebuf_mi; // copy from tcpcontext

    int ( *protocol_parser ) ( conn_t );

	int ( *protocol_acceptwatcher ) ( conn_t ) ;
    int ( *protocol_hiwater_acceptwatcher ) (conn_t, int);
	int ( *protocol_closewatcher ) ( conn_t, CLOSE_REASON r );

	int ( *pcallback)(conn_t,char*,int);	// protocol callback function
	
	unsigned int serial;  // serial number of itself


    // Avoiding exploit. bin16 parser max length.
	// tcpcontext gives this
	int (*maxlen_warning)(conn_t ct);
	int maxlen_record;


	// stats
    VCEI64 recv_byte, send_byte, conn_write;
    VCEI64 recv_syscall, send_syscall;


    int call_parser_per_loop;

    void (*readwrite_callback)( conn_t, int rwflg, char *buf, size_t len );
} conn;


int vce_conn_init_world( void );
int vce_conn_alloc_num( int num );
void vce_conn_free_num( int num );
void vce_conn_free( conn *c, int closewatcher, CLOSE_REASON reason );
void vce_conn_free2( conn *c);
void vce_conn_free3( conn *c);

conn * vce_conn_alloc( void );
int vce_conn_get_index_from_pointer( conn *c );
void vce_conn_io( conn *c , int rf , int wf, int call_protoparser );

int vce_conn_init_world(void);
int vce_conn_fin_world(void);

void vce_conn_set_enable_protocol_callback( conn_t ct, int val ) ;


extern int vce_conn_mi;

#endif
