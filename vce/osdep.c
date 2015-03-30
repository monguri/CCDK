#ifdef WIN32
#include <winsock2.h>
#endif

#include "vce.h"
#include "vcecommon.h"
#include "osdep.h"
#include "uselog.h"
#include "tcp.h"
#include "conn.h"
#include "core.h"

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


/* GCC + glibc + linux */
#if defined(linux) || defined(__APPLE__) || defined(sun)
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/times.h>
#include <dirent.h>
#include <signal.h>
#endif



void vce_socket_close( int fd ) {
#ifdef WIN32
	closesocket(fd);
#endif

#if defined(linux) || defined(__APPLE__) || defined(sun)
	close(fd);
#endif


}


int vce_socket_set_nonblock( int fd ) {
#ifdef WIN32
	unsigned long flg = 1;
	int ret;
	ret = ioctlsocket( fd, FIONBIO, &flg );
	if( ret < 0 ){
		VCE_ERROUT0( "osdep.c: cannot ioctlsocket for FIONBIO\n" );
		return SET_LAST_ERROR(VCE_EFCNTL);
	} else {
		return SET_LAST_ERROR(0);
	}
#endif


#if defined(linux) || defined(__APPLE__) || defined(sun)
	int flags = fcntl( fd  , F_GETFL , 0 );
	if( fcntl( fd , F_SETFL, flags | O_NONBLOCK ) < 0 ){
		VCE_ERROUT1( FATAL_TCP_FCNTL_S, strerror(errno));
		return SET_LAST_ERROR(VCE_EFCNTL);
	} else {
		VCE_ERROUT_V0( NOTE_TCP_NONBLOCK_CON );
		return SET_LAST_ERROR(0);
	}
#endif
	
}
void vce_socket_shutdown_rw( int fd ) {
#if defined(linux) || defined(__APPLE__) || defined(sun)
	shutdown( fd, 2 );
#endif
#ifdef WIN32
	shutdown( fd, 2 );
#endif

}

/* connect したときに、ローカルアドレスも同時に取得する */
int vce_socket_connect( int fd, const char *hname, unsigned short port,
                        char *rad, int *rad_len,
                        char *lad, int *lad_len,
                        unsigned short *lport,
                        tcpcontext_t *tp )
{
	tcpcontext *t = (tcpcontext*)tp;	
#if defined(linux) || defined(__APPLE__) || defined(sun)
	struct sockaddr_in sa, localsa;
    socklen_t locallen;
    int ret;

	if( *rad_len < 4 ) return SET_LAST_ERROR(VCE_ETOOSHORT);
	
    memset( &sa, 0 , sizeof( sa ));
    sa.sin_family = AF_INET;
    sa.sin_port = htons( port );
	if( (ret=vce_get_ipv4_addr_by_name( &sa.sin_addr.s_addr, hname )) < 0 ){
        return ret;
    }
	if( connect( fd, (struct sockaddr*) &sa, sizeof(sa) ) < 0 ){
		vce_usage_increment_connect_syscall_e(t);
        if( errno != EINPROGRESS ){
            vce_socket_close( fd );
			return SET_LAST_ERROR( VCE_ECONNECT );
        }
	} else {
		vce_usage_increment_connect_syscall(t);
	}
	memcpy( rad, &sa.sin_addr.s_addr, sizeof(sa.sin_addr.s_addr));
	*rad_len = sizeof(sa.sin_addr.s_addr);
    locallen = sizeof( localsa );
    if( getsockname( fd, (struct sockaddr*) &localsa, &locallen ) < 0 ){
        VCE_ERROUT_V1( "Warning: getosockname() fail(connect):%d\n",errno);
        *lad_len = 0;
        *lport = 0;
    } else {
        memcpy( lad, &localsa.sin_addr.s_addr,
                sizeof( localsa.sin_addr.s_addr ));
        *lad_len = sizeof( localsa.sin_addr.s_addr);
        *lport = ntohs( localsa.sin_port );
    }
	return SET_LAST_ERROR(0);	
#endif
#ifdef WIN32
    int ret,locallen;
	struct sockaddr_in sa,localsa;
    memset( &sa, 0 , sizeof( sa ));
    sa.sin_family = AF_INET;
    sa.sin_port = htons( port );
	if( (ret=vce_get_ipv4_addr_by_name( &sa.sin_addr.s_addr, hname ))<0) {
        return ret;
    }
	if( connect( fd, (struct sockaddr*) &sa, sizeof(sa) ) < 0 ){
        int e = WSAGetLastError();
        if( e != WSAEWOULDBLOCK ){
			vce_usage_increment_connect_syscall_e(t);		
            vce_socket_close(fd);
            return SET_LAST_ERROR( VCE_ECONNECT );
        }
	} else {
		vce_usage_increment_connect_syscall(t);
	}
	memcpy( rad, &sa.sin_addr.s_addr, sizeof(sa.sin_addr.s_addr));
	*rad_len = sizeof(sa.sin_addr.s_addr);
    locallen = sizeof( localsa );
    if( getsockname( fd, (struct sockaddr*) &localsa, &locallen ) < 0 ){
        VCE_ERROUT_V1( "Warning: getosockname() fail(connect):%d\n",errno);
        *lad_len = 0;
        *lport = 0;
    } else {
        memcpy( lad, &localsa.sin_addr.s_addr,
                sizeof( localsa.sin_addr.s_addr ));
        *lad_len = sizeof( localsa.sin_addr.s_addr);
        *lport = ntohs( localsa.sin_port );
    }
	return SET_LAST_ERROR(0);
#endif

}
#ifdef WIN32
typedef int socklen_t;
#endif

int vce_socket_getsockname( int fd, char *ad, int *ad_len, unsigned short *p ) {
#if defined(linux) || defined(WIN32) || defined(__APPLE__) || defined(sun)
    struct sockaddr_in sai;
    socklen_t sailen = sizeof(sai);
    if( getsockname( fd, (struct sockaddr*)&sai, &sailen)<0){
        VCE_ERROUT_V1( "Warning: getsockname() fail: %d\n", errno);
        *ad_len = 0;
        *p = 0;
        return -1;
    } else {
        memcpy( ad, &sai.sin_addr.s_addr, sizeof( sai.sin_addr.s_addr ));
        *ad_len = sizeof( sai.sin_addr.s_addr );
        *p = ntohs( sai.sin_port );
        return 0;
    }
#endif

}
/* accept したときに、ローカルアドレスも同時に取得する */
int vce_socket_accept( int bindfd, char *rad, int *rad_len,
                       unsigned short *rport,
                       char *lad, int *lad_len,
                       unsigned short *lport, tcpcontext_t *tp )
{
	tcpcontext *t = (tcpcontext*)tp;
	
#if defined(linux) || defined(WIN32) || defined(__APPLE__) || defined(sun)
	int ns,clilen;
	struct sockaddr_in cliaddr;

	if( *rad_len < 4 ) return SET_LAST_ERROR(VCE_ETOOSHORT);
	clilen = sizeof(cliaddr);
	ns = (int)accept( bindfd, (struct sockaddr*)&cliaddr,
				 (unsigned int*)&clilen );
	if( ns < 0 && errno != EAGAIN && errno != EINTR ){
        VCE_ERROUT_V2( WARN_TCP_ACCEPT_S_D, 
                       strerror( errno ) , (int)ntohs(t->sa.sin_port ) );
        vce_usage_increment_accept_syscall_e(t);
		return SET_LAST_ERROR( VCE_EACCEPT );
	} else {
        vce_usage_increment_accept_syscall(t);
	}
	memcpy( rad, &cliaddr.sin_addr.s_addr, sizeof( cliaddr.sin_addr.s_addr));
	*rad_len = sizeof( cliaddr.sin_addr.s_addr);
	*rport = ntohs( cliaddr.sin_port );
    vce_socket_getsockname( ns, lad, lad_len, lport );
	return ns;
#endif

}

//  Win32でDLLを作る場合のために、何もしない dllmain を定義する

#ifdef WIN32
#ifdef _USRDLL
BOOL WINAPI DllMain( HANDLE hInstDLL, DWORD dwReason, LPVOID pReserved ) {
    return 1;
}
#endif
#endif

int vce_get_ipv4_addr_by_name( unsigned int *a, const char *s ) {
#ifdef WIN32
    unsigned long ia;
    ia = inet_addr( s );
    if( ia == INADDR_NONE ){
        struct hostent *hoste;
        if( ( hoste = gethostbyname( s )) == NULL ){
            VCE_ERROUT1( FATAL_TCP_GETHOSTBYNAMEWIN_S, s );
            return SET_LAST_ERROR(VCE_EIPADDR);
        }
        memcpy( (void*)a, hoste->h_addr, hoste->h_length );
    } else {
        *a = ia;
    }
	return SET_LAST_ERROR(0);
#endif

#if defined(sun)
    unsigned long ia;
    ia = inet_addr( s );
    if( ia == -1 ){
        struct hostent *hoste;
        if( ( hoste = gethostbyname( s )) == NULL ){
            VCE_ERROUT1( FATAL_TCP_GETHOSTBYNAMEWIN_S, s );
            return SET_LAST_ERROR(VCE_EIPADDR);
        }
        memcpy( (void*)a, hoste->h_addr, hoste->h_length );
    } else {
        *a = ia;
    }
	return SET_LAST_ERROR(0);
#endif
#if defined(linux) || defined(__APPLE__)
    struct in_addr ia;
    if( inet_aton( s, &ia ) == 0 ){
        struct hostent *hoste;
        if( ( hoste = gethostbyname( s ) ) == NULL ){
            VCE_ERROUT1( FATAL_TCP_GETHOSTBYNAME3_S, s );
            return SET_LAST_ERROR( VCE_EIPADDR );
        }
        memcpy( (void*)&ia.s_addr, hoste->h_addr, hoste->h_length );

    }
    *a = ia.s_addr;
    return SET_LAST_ERROR(0);
#endif
}

int vce_socket_recvfrom( int fd, char *buf, int len, unsigned int *address,unsigned short *port) {
#if defined(linux) || defined(__APPLE__) || defined(sun)
	int r;
	struct sockaddr_in from;
	int fromlen=sizeof(from);
	r = recvfrom( fd, buf, len, 0,(struct sockaddr*)&from,(socklen_t*)&fromlen );
	*address=ntohl(*(unsigned int*)&from.sin_addr);
	*port=ntohs(from.sin_port);
	return r;
#endif

#ifdef WIN32
	int r;
	struct sockaddr_in from;
	int fromlen=sizeof(from);
	r = recvfrom( fd, buf, len, 0,(struct sockaddr*)&from,&fromlen );
	*address=ntohl(from.sin_addr.S_un.S_addr);
	*port=ntohs(from.sin_port);
	return r;
#endif

}

int vce_socket_recv( int fd, char *buf, int len, int *again ) {
#if defined(linux) || defined(__APPLE__) || defined(sun)
	int r;
	r = recvfrom( fd, buf, len, 0, NULL, NULL );
	if( r < 0 ){
		if( errno == EAGAIN ){
			*again = 1;
		} else {
			*again = 0;
		}
		return r;
	} else {
		*again = 0;
		return r;
	}
#endif

#ifdef WIN32
	*again=FALSE;
	return recvfrom( fd, buf, len, 0, NULL, NULL );	
#endif
}

int vce_socket_sendto( int fd, char *buf, int len, unsigned int address,unsigned short port) {

#if defined(linux) || defined(__APPLE__) || defined(sun)
	int r,adrlen;
	struct sockaddr_in to;
	memset(&to,0,sizeof(to));
	*(unsigned int*)&to.sin_addr=htonl(address);
	to.sin_family=AF_INET;
	to.sin_port=htons(port);
	adrlen=sizeof(to);
	r = sendto( fd, buf, len, 0 ,(struct sockaddr*)&to,sizeof(to));
	return r;
#endif

#ifdef WIN32
	int adrlen;
	struct sockaddr_in to;
	memset(&to,0,sizeof(to));
	*(unsigned int*)&to.sin_addr=htonl(address);
	to.sin_family=AF_INET;
	to.sin_port=htons(port);
	adrlen=sizeof(to);
	return sendto( fd, buf, len, 0 ,(struct sockaddr*)&to,sizeof(to));
#endif
}

int vce_socket_send( int fd, char *buf, int len, int *again ) {
#if defined(linux) || defined(__APPLE__) || defined(sun)
	int r;
	r = send( fd, buf, len, 0 );
	if( r < 0 ){
		if( errno == EAGAIN ){
			*again = 1;
		} else {
			*again = 0;
		}
	} else {
        *again = 0;
    }
	return r;
#endif

#ifdef WIN32
    *again = 0;    
	return send( fd, buf, len, 0 );	
#endif

}

int vce_socket_tcp_socket( void ) {
    int s;
#if defined(linux) || defined(WIN32) || defined(__APPLE__) || defined(sun)
	s = (int)socket( AF_INET, SOCK_STREAM, 0 );
#endif
    if( s < 0 ) return SET_LAST_ERROR( VCE_ESOCKET );
    return s;
}

int vce_socket_lib_os_init() {

    // TCPを使うということは、 SIGPIPEがくるということ
    vce_init_signal();

#ifdef WIN32
    /* Win32 の場合は、winsock の初期化をする必要がある。 */
    {
        WSADATA wsaData;
        int iWsa;
        iWsa = WSAStartup( MAKEWORD(1,1), &wsaData );
        if( iWsa != 0 ){
            VCE_ERROUT0( FATAL_WINSOCK );
            return VCE_EWINSOCKINIT;
        }
    }
	 return 0;
#endif
#if defined(linux) || defined(__APPLE__) || defined(sun)
	 return 0;
#endif

}

int vce_socket_bind( int fd, const char *addr , unsigned short port ) {
#if defined linux || defined WIN32 || defined __APPLE__ || defined sun
	struct sockaddr_in sa;
	memset( &sa,  0 , sizeof( sa ));
	sa.sin_family = AF_INET;
	sa.sin_port = htons( port );
	if( addr == NULL ){
		sa.sin_addr.s_addr = INADDR_ANY;
//		vce_get_ipv4_addr_by_name( &sa.sin_addr.s_addr, "0.0.0.0" );
	} else {
		vce_get_ipv4_addr_by_name( &sa.sin_addr.s_addr, addr );
	}
#ifdef WIN32
	{
		BOOL f=FALSE;
		setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(char*)&f,sizeof(f));
	}
#endif
	if( bind( fd, (struct sockaddr*) &sa, sizeof(sa))<0){
		return SET_LAST_ERROR(VCE_EBIND);
	}
	return 0;
#endif

}
int vce_socket_listen( int fd ) {
#if defined(linux) || defined(__APPLE__) || defined(sun)
	return listen(fd,5);
#endif
#ifdef WIN32
	return listen(fd,5);
#endif

}

int vce_socket_set_keepalive( int s ) {
#if defined linux || defined WIN32 || defined __APPLE__ || defined sun

    int kaopt = 1;
    if( setsockopt( s, SOL_SOCKET, SO_KEEPALIVE,
                    (char*)&kaopt, sizeof(int)) < 0 ){
        return SET_LAST_ERROR(VCE_ESETSOCKOPT);
    }
    return 0;
#endif

}

int vce_socket_set_reuseaddr( int s ) {
#if defined linux || defined WIN32 || defined __APPLE__ || defined sun
	int reuseopt = 1;
	if( setsockopt( s, SOL_SOCKET, SO_REUSEADDR,
					(char*)&reuseopt, sizeof(int)) < 0 ){
		return SET_LAST_ERROR(VCE_ESETSOCKOPT);
	}
	return 0;
#endif

}


int vce_socket_set_nodelay( int fd ) {
#if defined linux || defined WIN32 || defined __APPLE__ || defined sun
    int flag = 1;
    if( setsockopt( fd, IPPROTO_TCP , TCP_NODELAY,
                    (char*)&flag , sizeof( int ) ) < 0 ){
        return SET_LAST_ERROR(VCE_ESETSOCKOPT);
    } else {
        return 0;
    }
#endif

}

/* heartbeat の中以外で vce_global_time を使うときは，
   すごく古い値が入ってるかもしれないので，毎回 update_time する事! */
void vce_update_time(void) {
	
#if defined linux || defined __APPLE__ || defined sun
	struct timeval tmv;
	gettimeofday( &tmv, NULL );
	vce_mainloop_utime_store = (VCEI64)tmv.tv_sec * 1000000 + tmv.tv_usec;
	vce_global_time = tmv.tv_sec;
#endif

#ifdef WIN32
	/* win32 でマイクロ秒の精度をもつ時刻取得関数はない */
	SYSTEMTIME st;
	GetSystemTime( &st );
	time( &vce_global_time );
	vce_mainloop_utime_store = (VCEI64)vce_global_time * 1000000 +
        (VCEI64) st.wMilliseconds * 1000;
#endif
	
}

/*
  キーを生成する、ただし毎回ランダムなもの。

  char *k : 出力キー
  int len : 最大長さ
  
 */
char itoxc(unsigned int i) {
	i=i&0xf;
	return i<10?'0'+i:('a'-10)+i;
}

void itox(char *out,unsigned int i) {
	*out++=itoxc(i>>28);
	*out++=itoxc(i>>24);
	*out++=itoxc(i>>20);
	*out++=itoxc(i>>16);
	*out++=itoxc(i>>12);
	*out++=itoxc(i>>8);
	*out++=itoxc(i>>4);
	*out++=itoxc(i);
}

// linux の場合は、fd_set がでかいことを要求する 
#if (defined linux) && ( FD_SETSIZE < OSDEP_FD_SETSIZE )
#error "VCE have to be compiled having FD_SETSIZE == OSDEP_FD_SETSIZE !!"
#endif

// fd_set の型名が違うときもある 
#if defined linux || defined WIN32 || defined __APPLE__ || defined sun
static fd_set vce_wfds, vce_rfds;
#endif

void vce_socket_fdwrap_clear( void ) {
#if defined linux || defined WIN32 || defined __APPLE__ || defined sun
	FD_ZERO( &vce_wfds );
	FD_ZERO( &vce_rfds );
#endif

}

void vce_socket_fdwrap_set_read( int fd ) {
#if defined linux || defined WIN32 || defined __APPLE__ || defined sun
	FD_SET( fd, &vce_rfds );
#endif

}
void vce_socket_fdwrap_set_write( int fd ) {
#if defined linux || defined WIN32  || defined __APPLE__ || defined sun
	FD_SET( fd, &vce_wfds );
#endif

}

void vce_socket_fdwrap_select( int num, int *rc, int *wc ) {
    struct timeval tmv;
    memset( &tmv, 0, sizeof(tmv));
	tmv.tv_sec = 0;
	tmv.tv_usec = vce_select_timeout_us;    
	*rc = select( num, &vce_rfds,
				  (fd_set*)NULL, (fd_set*)NULL, &tmv );
	tmv.tv_usec = tmv.tv_sec = 0;
	*wc = select( num, (fd_set*)NULL,
				  &vce_wfds, (fd_set*)NULL, &tmv );
}

int vce_socket_fdwrap_is_readable( int fd ) {
	return FD_ISSET( fd, &vce_rfds );
}

int vce_socket_fdwrap_is_writable( int fd ) {
	return FD_ISSET( fd, &vce_wfds );
}

void vce_snprintf( char *out, int len, const char *format, ... ) {
	va_list arg;
	va_start( arg, format );
#if defined linux || defined __APPLE__ || defined sun
	vsnprintf( out, len, format, arg );
#endif

#ifdef WIN32
	_vsnprintf( out, len, format, arg );
#endif

	va_end(arg);
}




#ifdef WIN32

VCEI64 vce_htonll(VCEI64 x) {
	VCEI64 d;
	__asm
	{
		lea esi,x
		lea edi,d
		mov eax,[esi]
		bswap eax
		mov ebx,[esi+4]
		bswap ebx
        mov [edi+4],eax
		mov [edi],ebx
	};
	return d;
}

VCEI64 GET_64BIT_INT(const char *p) {
	VCEI64 d;
	__asm
	{
		mov esi,p
		lea edi,d
		mov eax,[esi]
		bswap eax
		mov ebx,[esi+4]
		bswap ebx
        mov [edi+4],eax
		mov [edi],ebx
	};
	return d;
}

void SET_64BIT_INT(char *p,const VCEI64 i) {
	__asm
	{
		mov edi,p
		lea esi,i
		mov eax,[esi]
		bswap eax
		mov ebx,[esi+4]
		bswap ebx
        mov [edi+4],eax
		mov [edi],ebx
	};
}

int GET_32BIT_INT(const char *p) {
	int d;
	__asm
	{
		mov esi,p
		mov eax,[esi]
		bswap eax
		mov d,eax
	};
	return d;
}

void SET_32BIT_INT(char *p,const int i) {
	__asm
	{
		mov edi,p
		mov eax,i
		bswap eax
		mov [edi],eax
	};
}

short GET_16BIT_INT(const char *p) {
	short d;
	__asm
	{
		mov esi,p
		mov ax,[esi]
		xchg al,ah
		mov d,ax
	};
    return d;
}

void SET_16BIT_INT(char *p,const short i) {
	__asm
	{
		mov edi,p
		mov ax,i
		xchg al,ah
		mov [edi],ax
	};
}

#endif

VCEI64 vce_utime_diff( struct timeval *before, struct timeval *after ) {
    VCEI64 sec_d = after->tv_sec - before->tv_sec;
    VCEI64 sec_d_m = 1000 * 1000 * sec_d;
    VCEI64 usec_d = after->tv_usec - before->tv_usec;
    return sec_d_m + usec_d;
}


char *vce_get_os_errstr(void ) {

#ifdef WIN32
    static char vce_get_os_errstr_return_val[64];    
    int e = WSAGetLastError();
    vce_snprintf( vce_get_os_errstr_return_val,
                  sizeof(vce_get_os_errstr_return_val),
                  "errno:'%s' WSAGetLastError:%d",
                  strerror(errno), e );
                  
    return vce_get_os_errstr_return_val;
#endif

#if defined linux || defined __APPLE__ || defined sun
    return strerror(errno);    
#endif    
}

void vce_init_signal( void ) {

#if defined(linux) || defined(sun) || defined(__APPLE__)
	{
		/* Block only SIGPIPE */
		struct sigaction s, os;
		memset( &s, 0 , sizeof( s ));
		s.sa_handler = SIG_IGN;
		sigemptyset( &s.sa_mask );
		s.sa_flags = 0;
#ifdef SA_RESTART
		s.sa_flags |= SA_RESTART; /* SVR4, 4.3+BSD */
#endif		
		sigaction( SIGPIPE, &s, &os );
	}
#endif
}


