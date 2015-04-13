#ifndef _TCP_H_
#define _TCP_H_

#include "vce.h"
#include "conn.h"

#ifdef WIN32
#include <windows.h>
#endif


/*

  tcpcontext structure. 

*/

typedef struct _tcpcontext
{
    int is_server;
    int timeout_sec; // default timeout of TCP connection
    int max_conn;  // max number of concurrent TCP connection alive
	int conn_in_use;

    // Length of read/write buffer per connection.  erb/ewb is for encrypted buffers.
    size_t rblen,erblen;
    size_t wblen,ewblen;

	// state management buffer
	size_t statebuf_size;
	int statebuf_mi;     // VCE memory index
	int statebuf_num;    // number of elements 


	int rbmaster_mi, wbmaster_mi, erbmaster_mi, ewbmaster_mi;


	// total count of read/write/accept() call
	VCEI64 recv_byte,send_byte,keyex_count;
	// sytem call counts
	VCEI64 recv_syscall, recv_syscall_e;
	VCEI64 send_syscall, send_syscall_e;
	VCEI64 accept_syscall, accept_syscall_e;
	VCEI64 connect_syscall, connect_syscall_e;

    // Count of VCE events
	VCEI64 conn_write,conn_timeout,tcpcontext_connect;

    // Server bind address
    struct sockaddr_in sa;

	// Maximum of new accept() per minute
	int accept_count,accept_max;
	VCEI64 accept_lasttime;
	int (*accept_warning)(tcpcontext_t t);

	
	void *userdata; // Userdata pointer 

	char ps_host[256];
	unsigned short ps_mainport;
	unsigned short ps_subport;
    
    int accept_more; // Set 0 to stop any new connections.
    int mainsock; // server socket to be bind() and listen().
    int index;    // Index in tcpcontext array
    int nonblock_connect;    // client connect blocks? 1:nonblock 0:block
	int nodelay; // set NODELAY socket option

    int ( *protocol_parser ) ( conn_t );

	int ( *protocol_acceptwatcher ) ( conn_t ); // Callback function when accept() succeeded
    int ( *protocol_hiwater_acceptwatcher ) (conn_t,int); // Callback function when more connections are coming than highwater set.
	int ( *protocol_closewatcher ) ( conn_t,CLOSE_REASON r ); // Callback function when a connection is closed
	int ( *pcallback)(conn_t,char*, int);  // Callback function when protocol parser gets a record from input
	void (*conn_finalizer)(conn_t);


    // set highwater threshold of concurrent connections
    int conn_hiwater_thres;

    // Avoiding exploits. bin16 parser's max length.
	int (*maxlen_warning)(conn_t ct);
	int maxlen_record;

    // Configure how many times protocol callback function is called per second.
    int call_parser_per_loop;

    int recv_reset_timeout; // reset connection timer when receiving data.
    int send_reset_timeout; // reset connection timer when writing data. (defaults 0)

} tcpcontext;



void vce_tcp_poll( int isolate_conn_serial );
int vce_tcpcontext_init_world( void );
int vce_tcpcontext_fin_world(void);
int vce_tcpcontext_get_next_conn_serial();

extern int vce_select_timeout_us;

#endif
