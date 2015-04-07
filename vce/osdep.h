#ifndef _OSDEP_H_
#define _OSDEP_H_


#include "vce.h"

/* 最大接続数とかのデフォルト */
#ifdef linux
#define OSDEP_DEFAULT_MAXTCPCONTEXT 16
#define OSDEP_DEFAULT_MAXTASKGROUP 16
#define OSDEP_DEFAULT_MAX_ARRAY_INDEX 16384
#define OSDEP_DEFAULT_MAXCON 1000 /* linux での標準的な値 */
#define OSDEP_SEND_UNIT (1024*256)
#define OSDEP_RECV_UNIT (1024*256*4) /* サーバとして使われるので大きめ */
#define OSDEP_FD_SETSIZE FD_SETSIZE
#endif

#if defined(__APPLE__) || defined(sun)
/* Almost copied from linux config, but smaller max connections */
#define OSDEP_DEFAULT_MAXTCPCONTEXT 16
#define OSDEP_DEFAULT_MAXTASKGROUP 16
#define OSDEP_DEFAULT_MAX_ARRAY_INDEX 16384
#define OSDEP_DEFAULT_MAXCON 1000 
#define OSDEP_SEND_UNIT (1024*256)
#define OSDEP_RECV_UNIT (1024*256*4) 
#define OSDEP_FD_SETSIZE FD_SETSIZE
#endif

#ifdef WIN32
#define OSDEP_DEFAULT_MAXTCPCONTEXT 16
#define OSDEP_DEFAULT_MAXTASKGROUP 16
#define OSDEP_DEFAULT_MAX_ARRAY_INDEX 4096
#define OSDEP_DEFAULT_MAXCON 1000 
#define OSDEP_SEND_UNIT (1024*256)
#define OSDEP_RECV_UNIT (1024*256) 
#define OSDEP_FD_SETSIZE FD_SETSIZE
#endif


void vce_socket_close( int fd );
int vce_socket_set_nonblock( int fd );
void vce_socket_shutdown_rw( int fd );
int vce_socket_connect( int fd, const char *hname, unsigned short port,
						char *rad, int *rad_len ,
						char *lad, int *lad_len,
						unsigned short *lport, tcpcontext_t *t);
int vce_socket_accept( int bindfd, char *rad, int *rad_len,
					   unsigned short *rport,
					   char *lad, int *lad_len,
					   unsigned short *lport,
					   tcpcontext_t *tp );
int vce_socket_send( int fd, char *buf, int len, int *again );
int vce_socket_sendto( int fd,char *buf,int len,unsigned int addr,unsigned short port);
int vce_socket_recv( int fd, char *buf, int len, int *again );
int vce_socket_recvfrom(int fd,char *buf,int len,unsigned int *addr,unsigned short *port);
int vce_socket_tcp_socket( void );

int vce_socket_lib_os_init();
int vce_socket_bind( int fd, const char *addr , unsigned short port );
int vce_socket_listen( int fd );
int vce_socket_set_keepalive( int s );
int vce_socket_set_reuseaddr( int s );
int vce_socket_set_nodelay( int fd );
int vce_socket_getsockname( int fd, char *ad, int *ad_len, unsigned short *p );
void vce_update_time(void);
char *vce_get_os_errstr(void );


void vce_socket_fdwrap_clear( void );
void vce_socket_fdwrap_set_read( int fd );
void vce_socket_fdwrap_set_write( int fd );
void vce_socket_fdwrap_select( int n, int *rc, int *wc );
int vce_socket_fdwrap_is_readable( int fd );
int vce_socket_fdwrap_is_writable( int fd );


void vce_init_signal( void );


#endif
