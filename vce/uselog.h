#ifndef _USELOG_H_
#define _USELOG_H_

#include "conn.h"
#include "tcp.h"

void vce_usage_set_boot_time( time_t t );
void vce_usage_increment_conn_alloc( void );
void vce_usage_increment_conn_free( void );
void vce_usage_increment_conn_close( void );
void vce_usage_increment_keyex( tcpcontext *t );
void vce_usage_increment_recv_syscall( conn *c);
void vce_usage_increment_recv_syscall_e( conn *c);
void vce_usage_add_recv_byte( int v , conn *c);
void vce_usage_increment_send_syscall( conn *c );
void vce_usage_increment_send_syscall_e ( conn *c);
void vce_usage_add_send_byte( int v, conn *c );
void vce_usage_increment_conn_write( conn *c );
void vce_usage_increment_tcpcontext_create( void );
void vce_usage_increment_tcpcontext_cleanup( void );
void vce_usage_increment_accept_syscall_e( tcpcontext *t );
void vce_usage_increment_accept_syscall( tcpcontext *t );
void vce_usage_increment_conn_timeout( tcpcontext *t );
void vce_usage_increment_connect_syscall_e( tcpcontext *t );
void vce_usage_increment_connect_syscall( tcpcontext *t );
void vce_usage_increment_tcpcontext_connect( tcpcontext *t );
void vce_usage_increment_log_count( void );


#endif /* _USELOG_H_ */
