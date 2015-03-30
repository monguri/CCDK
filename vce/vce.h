#ifndef _VCE_H_
#define _VCE_H_

#if defined(linux) || defined(__APPLE__) || defined(sun) /* linux or MacOS X or Solaris*/
#include <time.h> /* for time_t */
#include <sys/time.h>  /* for timeval */
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
typedef long long VCEI64;
#endif


#ifdef WIN32
#include <time.h> /* for time_t */
#include <string.h>
#include <assert.h>
typedef __int64 VCEI64; /* GCC's long long is not available */
#endif

#ifdef __cplusplus    
extern "C"
{
#endif

#ifdef _USRDLL /* Defined under VisualStudio DLL project environment */
#define EXPORT //_declspec (dllexport)
#else
#define EXPORT /* Don't have to use any special prefix under gcc */
#endif

#ifdef WIN32
EXPORT VCEI64 vce_htonll(VCEI64 x);
#define vce_ntohll(x) vce_htonll(x)
#else

#if defined(linux) || defined(sun)
//for little endian architecture
#define vce_htonll(x) \
    (((VCEI64)(ntohl((int)((x<<32)>>32)))<<32) | (unsigned int)ntohl(((int)(x>>32))))
#define vce_ntohll(x) vce_htonll(x)
#else
//for big endian architecture
#define vce_htonll(x) (x)
#define vce_ntohll(x) (x)
#endif
#endif

#ifndef __GNUC__
#define __attribute__(x)
#endif

typedef short SWCHAR;

#ifdef WIN32
EXPORT VCEI64 GET_64BIT_INT(const char *p);
EXPORT void SET_64BIT_INT(char *p,const VCEI64 i);
EXPORT int GET_32BIT_INT(const char *p);
EXPORT void SET_32BIT_INT(char *p,const int i);
EXPORT short GET_16BIT_INT(const char *p);
EXPORT void SET_16BIT_INT(char *p,const short i);
#define GET_8BIT_INT(p)    (*((char*)(p))) 
#define SET_8BIT_INT(p,i)  ((*((char*)(p)))=(char)(i)) 
#define GET_64BIT_NATIVEINT(p) ( *((VCEI64*)(p)) ) 
#define SET_64BIT_NATIVEINT(p,i) ((*((VCEI64*)(p))) = (VCEI64)(i)) 
#define GET_32BIT_NATIVEINT(p) ( *((int*)(p)) ) 
#define SET_32BIT_NATIVEINT(p,i) ((*((int*)(p))) = (int)(i)) 
#define GET_16BIT_NATIVEINT(p) ( *((short*)(p))) 
#define SET_16BIT_NATIVEINT(p,i) ((*((short*)(p))) = (short)(i)) 
#define GET_8BIT_NATIVEINT(p)  ( *((char*)(p))) 
#define SET_8BIT_NATIVEINT(p,i)  ((*((char*)(p))) = (char)(i)) 
#endif

#if defined linux || defined __APPLE__ || defined sun
/* Macros for intel machines */
#define GET_64BIT_INT(p)    vce_ntohll( *((VCEI64*)(p)) )                     
#define SET_64BIT_INT(p,i)    ((*((VCEI64*)(p))) = vce_htonll((VCEI64)(i)))     
#define GET_32BIT_INT(p)    ntohl( *((int*)(p)) )                     
#define SET_32BIT_INT(p,i)    ((*((int*)(p))) = htonl((int)(i)))     
#define GET_16BIT_INT(p)    ntohs( *((short*)(p)))         
#define SET_16BIT_INT(p,i)    ((*((short*)(p))) = htons((short)(i)))  
#define GET_8BIT_INT(p)    (*((char*)(p))) 
#define SET_8BIT_INT(p,i)  ((*((char*)(p)))=(char)(i)) 
#define GET_64BIT_NATIVEINT(p) ( *((VCEI64*)(p)) ) 
#define SET_64BIT_NATIVEINT(p,i) ((*((VCEI64*)(p))) = (VCEI64)(i)) 
#define GET_32BIT_NATIVEINT(p) ( *((int*)(p)) ) 
#define SET_32BIT_NATIVEINT(p,i) ((*((int*)(p))) = (int)(i)) 
#define GET_16BIT_NATIVEINT(p) ( *((short*)(p))) 
#define SET_16BIT_NATIVEINT(p,i) ((*((short*)(p))) = (short)(i)) 
#define GET_8BIT_NATIVEINT(p)  ( *((char*)(p))) 
#define SET_8BIT_NATIVEINT(p,i)  ((*((char*)(p))) = (char)(i)) 
#endif


#ifndef MIN
#define MIN(x,y)   ( (x) < (y) ? (x) : (y) )   
#endif
#ifndef MAX
#define MAX(x,y)   ( (x) > (y) ? (x) : (y) )   
#endif
#define ELEMENTOF(x) ( sizeof(x) / sizeof((x)[0]) )  


#include <stdarg.h>



// core.c
typedef struct _vce_limit_t
{
    int max_tcpcontext;
    int max_conn;
    int max_array;
    int sendbuf_work_size, recvbuf_work_size;
} vce_limit_t;


typedef struct {
    void *p;     // pointer to connection.  Don't use this pointer for comparison of conn_t, use vce_conn_is_equal()!!! 
    unsigned int serial;
} conn_t;


typedef void * tcpcontext_t;
    
EXPORT void vce_limit_clear( vce_limit_t *t );
EXPORT int vce_initialize( void ); 
EXPORT int vce_initialize_limited( vce_limit_t *lim ); 
EXPORT int vce_finalize( void ); 
EXPORT void vce_init_limit_t( vce_limit_t *t ); 
EXPORT void vce_heartbeat( void );
EXPORT void vce_heartbeat_on_single_conn( conn_t c );    
EXPORT void vce_set_heartbeat_wait_flag( int flag );
    
// uselog.c 
typedef struct _vce_stat_t {
    time_t boot_time;
    VCEI64 recv_byte, send_byte; /* total vce send/recv */

    /* system call count */
    VCEI64 recv_syscall , recv_syscall_e;
    VCEI64 send_syscall , send_syscall_e;
    VCEI64 accept_syscall , accept_syscall_e;
    VCEI64 connect_syscall , connect_syscall_e;

    VCEI64 conn_free , conn_alloc , conn_close , conn_write;
    VCEI64 keyex;
    VCEI64 tcpcontext_create , tcpcontext_cleanup;
    VCEI64 tcpcontext_connect;
    VCEI64 conn_timeout;
    VCEI64 log_count;  /* errout log count */
} vce_stat_t;


EXPORT void vce_set_verbose_mode( int m ); 
EXPORT void vce_set_read_write_log_mode( int m ); 
EXPORT void vce_errout( const char *format, ... ) __attribute__((format (printf,1,2))); 
EXPORT void vce_errout_v( const char *format, ... ) __attribute__ ((format (printf,1,2))); 
EXPORT void vce_get_stat( vce_stat_t *v ); 
EXPORT int vce_get_netstat_string( char *buf, int maxlen ); 


/* a macro for getting error string */
#define STRERR  (vce_strerror( vce_get_last_error()))  

/* BIN protocol max record length (1Gbytes) */
#define BIN16DATA_MAX ( 256 * 256  )
#define BIN32DATA_MAX ( 1024 * 1024 * 1024 )


#if defined __GNUC__
#if defined(linux) || defined(sun)
#pragma pack(1)
#endif
#elif defined(WIN32)
#pragma pack(push,1) /* Win32 VC only */
#endif





/* conn.c */
EXPORT int vce_conn_write( conn_t ct, char *b, size_t len ); 
EXPORT int vce_conn_writable( conn_t ct  ); 
EXPORT int vce_conn_writed( conn_t ct ); 
EXPORT void vce_conn_close( conn_t ct ); 
EXPORT void vce_conn_show_stat( void ); 
EXPORT void vce_conn_get_remote_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p  ); 
EXPORT void vce_conn_get_remote_ipv6_addr( conn_t ct, char *a, unsigned short *p );
EXPORT void vce_conn_get_local_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p  ); 
EXPORT void vce_conn_get_local_ipv6_addr( conn_t ct, char *a, unsigned short *p ); 
EXPORT void vce_conn_get_local_ipv6_addr( conn_t ct, char *a, unsigned short *p ); 
EXPORT char * vce_conn_get_remote_ipv4_addr_string( conn_t ct, char *s,int max);
EXPORT char * vce_conn_get_local_ipv4_addr_string( conn_t ct, char *s,int max);
EXPORT char * vce_conn_get_remote_ipv6_addr_string( conn_t ct, char *,int);
EXPORT char * vce_conn_get_local_ipv6_addr_string( conn_t ct, char *,int);
EXPORT char * vce_conn_get_remote_addr_string( conn_t ct, char *, int); 
EXPORT char * vce_conn_get_local_addr_string( conn_t ct, char *, int); 
EXPORT int vce_conn_get_index( conn_t c ); 
EXPORT conn_t vce_conn_get_struct_from_index( int index ); 
EXPORT void * vce_conn_get_state_buffer( conn_t c, int *len ); 
EXPORT tcpcontext_t vce_conn_get_tcpcontext( conn_t ct ); 
EXPORT int vce_conn_is_valid( conn_t c );
EXPORT int vce_conn_is_closed( conn_t c );
EXPORT int vce_conn_is_equal( conn_t c1, conn_t c2 ); 
EXPORT void vce_conn_get_buffer( conn_t ct, char **rb, int *rblen, char **wb, int *wblen ); 
EXPORT int vce_conn_shrink_readbuf( conn_t ct, int len ); 
EXPORT void vce_conn_clear( conn_t *ct ); 
EXPORT void vce_conn_close_tcpcontext_all( tcpcontext_t t );
EXPORT void vce_conn_break_heartbeat( void ); 
typedef struct _conn_stat_t {
    VCEI64 recv_byte, send_byte, conn_write;
    VCEI64 recv_syscall, send_syscall;
} conn_stat_t;
EXPORT void vce_conn_get_stat( conn_t ct, conn_stat_t *st ); 
EXPORT void vce_conn_set_timeout( conn_t ct, int sec );
EXPORT void vce_conn_set_parser( conn_t ct, int (*p)(conn_t), int (*pcb)(conn_t,char*,int));
EXPORT void vce_conn_set_io_callback( conn_t ct, void (*cb)( conn_t ct, int rwflag, char *data, size_t sz ));

    /* tcp.c */
EXPORT int vce_tcpcontext_setup_p2p(tcpcontext_t t,int allocationsize,int allocationunits);
EXPORT int vce_tcpcontext_set_portscanner(tcpcontext_t t,const char *host,unsigned short mainport,unsigned short subport);

EXPORT tcpcontext_t vce_tcpcontext_create( int is_server,
                                           const char *bindaddr,
                                           unsigned short port, int maxcon ,
                                           size_t rblen , size_t wblen,
                                           int timeout ,
                                           int nonblock_connect,
                                           int nodelay,
                                           size_t statebuf_size);

EXPORT void vce_tcpcontext_set_conn_finalizer( tcpcontext_t t, void (*f)(conn_t));
EXPORT void vce_tcpcontext_cleanup( tcpcontext_t t ); 


EXPORT conn_t vce_tcpcontext_connect( tcpcontext_t t, const char *h , unsigned short p ); 
EXPORT int vce_tcpcontext_get_max_connection( tcpcontext_t t );
EXPORT int vce_tcpcontext_get_all_connection( tcpcontext_t t , conn_t *a, int max);     
EXPORT void vce_tcpcontext_set_conn_parser( tcpcontext_t tp, int (*parser)(conn_t), int (*c)(conn_t,char*,int));
EXPORT void vce_tcpcontext_set_conn_acceptwatcher( tcpcontext_t tp, int (*aw)(conn_t) );
EXPORT void vce_tcpcontext_set_conn_hiwater_acceptwatcher( tcpcontext_t tp, int water, int (*aw)(conn_t, int)); 
EXPORT void vce_tcpcontext_set_accept_max( tcpcontext_t t,int con_max,int (*accept_warning)(tcpcontext_t t));
    
typedef enum {
    CLOSE_REASON_NONE = -1,   /* used inside VCE */
    CLOSE_REASON_UNKNOWN = 0, /* reason unknown */
    CLOSE_REASON_REMOTE, /* socket closed by remote peer */
    CLOSE_REASON_APPLICATION,   /* socket closed by application */
    CLOSE_REASON_TIMEOUT, /* close by timeout */
    CLOSE_REASON_DECODER, /* protocol decoder fail */
    CLOSE_REASON_ENCODER, /* protocol encoder fail */
    CLOSE_REASON_PARSER, /* parser returns minus */
    CLOSE_REASON_INTERNAL, /* VCE internal error */
    CLOSE_REASON_FULL, /* (sw) buffer full */
} CLOSE_REASON;
EXPORT void vce_tcpcontext_set_conn_closewatcher( tcpcontext_t tp, int (*cw)(conn_t, CLOSE_REASON r )); 
EXPORT int vce_tcpcontext_set_conn_safety_read( tcpcontext_t tp, int p);
EXPORT void vce_tcpcontext_enable_accept( tcpcontext_t tp, int flag );

typedef struct _tcpcontext_stat_t {
    int current_conn;
    VCEI64 recv_byte, send_byte;
    VCEI64 recv_syscall, recv_syscall_e;
    VCEI64 send_syscall, send_syscall_e;
    VCEI64 accept_syscall, accept_syscall_e;
    VCEI64 connect_syscall, connect_syscall_e;
    VCEI64 conn_write, conn_timeout, tcpcontext_connect;
} tcpcontext_stat_t;
EXPORT void vce_tcpcontext_get_stat( tcpcontext_t tp, tcpcontext_stat_t *s ); 
EXPORT int vce_tcpcontext_conn_iterate( tcpcontext_t tt, int (*f)(conn_t c)); 
EXPORT void vce_tcpcontext_set_conn_call_parser_per_heartbeat( tcpcontext_t tt, int v ); 
EXPORT void vce_tcpcontext_timeout_control( tcpcontext_t tp, int recv_reset, int send_reset ); 
EXPORT int vce_tcpcontext_count_connections( tcpcontext_t t, int *conn ); 
EXPORT void vce_tcpcontext_protocol_set_maxlength(tcpcontext_t ct,int maxlength,int(*errcall)(conn_t ct));

/* protocol.c */
EXPORT int vce_protocol_parser_bin16( conn_t ct ); 
EXPORT int vce_protocol_parser_bin32( conn_t ct ); 
EXPORT int vce_protocol_parser_through( conn_t ct ); 
EXPORT int vce_protocol_parser_text( conn_t ct ); 
EXPORT int vce_protocol_unparser_bin16( conn_t ct, char*,int); 
EXPORT int vce_protocol_unparser_bin32( conn_t ct, char*,int); 
EXPORT int vce_protocol_unparser_through( conn_t ct, char *,int); 
EXPORT int vce_protocol_unparser_text( conn_t ct, char *d, int l );
EXPORT int vce_protocol_acceptwatcher_deny( conn_t c ); 
EXPORT int vce_protocol_acceptwatcher_noop( conn_t c ); 
EXPORT int vce_protocol_closewatcher_noop( conn_t c ); 


/* pcallback.c */
EXPORT int vce_protocol_pcallback_echo_bin16(conn_t c,char *d,int l);
EXPORT int vce_protocol_pcallback_echo_text(conn_t ct,char *d,int l);
EXPORT int vce_protocol_pcallback_noop(conn_t ct ,char *d, int l );
EXPORT int vce_protocol_pcallback_dump(conn_t ct, char *d, int l );


/* util.c */
EXPORT void *VCEMALLOC( size_t size ); 
EXPORT void VCEFREE( void *p ); 
EXPORT void vce_dump_buffer( char *buf, int len ); 
EXPORT int vce_read_simple_config_file( const char *filename, int(*c)(char*,int, char*,char*));
EXPORT int vce_read_plain_text_file( const char *fn, int (*cb) (char*,int,char*)); 
EXPORT void vce_make_binary_array_from_hex(char *out, int outlen,const char *hex); 
EXPORT void vce_make_binary_array_from_line(const char *line,int linelen,char *out, int*outlen,int*ul);
EXPORT int vce_make_hex_from_binary_array( char *out, int outlen, const char *buf,int len, int folding); 
EXPORT int vce_make_hex_text_from_buffer( const char *buf , int len , char *out , int outlen ); 
EXPORT int vce_extract_data_from_hex_text( const char *buf, int len, char *out, int outlen );
EXPORT VCEI64 vce_get_current_utime( void ); 
EXPORT VCEI64 vce_utime_diff( struct timeval *b, struct timeval *a); 
EXPORT void vce_replace_malloc_funcs( void* (*a)(size_t), void* (*r)(void*,size_t), void (*f)(void*)); 

/* osdep.c */
EXPORT int vce_get_ipv4_addr_by_name( unsigned int *a, const char *s );
EXPORT void vce_snprintf( char *out, int len, const char *format, ... ) __attribute__ ((format (printf,3,4))); 


/* mem.c */
#define ARRAY_SCAN(ind,x)   for( (x) = vce_get_array_object_top(ind);x;(x)=vce_get_array_object_next(ind,x)) 

#define ARRAY_SCAN_INDEX( ind, x, i) for( i = 0,(x) = vce_get_array_object_top(ind);x;(x)=vce_get_array_object_next(ind,x),i++)

#define ARRAY_SCAN_TYPE(ind,x,type)   for( (x) = (type)vce_get_array_object_top(ind);x;(x)=(type)vce_get_array_object_next(ind,x)) 

#define ARRAY_SCAN_TYPE_INDEX(ind,x,type, i)   for( i = 0, (x) = (type)vce_get_array_object_top(ind);x;(x)=(type)vce_get_array_object_next(ind,x),i++) 

EXPORT int vce_init_array ( size_t size , int num , const char *nm ); 
EXPORT int vce_end_array( int index ); 
EXPORT void *vce_alloc_array_object( int index ); 
EXPORT int vce_free_array_object( int index , void *p ); 
EXPORT void *vce_get_array_object_top( int index ); 
EXPORT void * vce_get_array_object_next( int index , void *p ); 
EXPORT void * vce_get_array_object_last( int index ); 
EXPORT int vce_get_array_usenum( int index ); 
EXPORT int vce_get_array_object_index( int index , const void *p ); 
EXPORT void * vce_get_array_object_pointer_by_index( int i, int obji ); 
EXPORT void * vce_get_array_object_pointer_by_index_only_used( int index , int objindex ); 
EXPORT int vce_show_array_usage( int index , int show_all ); 
EXPORT void vce_end_all_array( void ); 
EXPORT int vce_if_included_in_array( int index, const void *p ); 
EXPORT void vce_free_array_object_all( int index ); 
EXPORT int vce_get_array_member_size( int index ); 
EXPORT int vce_get_array_maxnum( int index ); 
EXPORT int vce_array_object_inuse( int index, void *p ); 

    


/* text.c */
EXPORT int vce_httptext_divide_header_and_content( const char *in , int inlen, char **head, int *headlen, char **b, int *);
EXPORT int vce_text_cmpnocase( const char *s1, const char *s2, int n ); 
EXPORT int vce_httptext_get_header_info( const char *h, int hlen , char *i, char *o, int);
EXPORT char * vce_text_split_index( const char *src, char c, int index ); 
EXPORT int vce_copy_cstring_upto( char *d, const char *s, char c,int );
EXPORT int vce_copy_cstring( char *dest , int l , const char *src ); 
EXPORT int vce_text_split_index_get_int(const char *s,char,int,int *v);
EXPORT int vce_text_split_index_get_string( const char *src, char c, int ind,char *out,int );
EXPORT int vce_strcmptail( const char *s1, const char *s2 ); 
EXPORT int vce_text_hashpjw( const char *s ); 
EXPORT char * vce_makecstr( char *, int, const char *, int ); 
EXPORT char * vce_chop_string_destroy( char *s ); 
EXPORT int vce_strlenmax( const char *s, int max ); 
EXPORT int vce_strncat( char *out, int outlen, const char *append );
EXPORT void vce_strncpy( char *to, int to_len, const char *from, int from_len ); 
EXPORT int vce_escape_string( char *to, int tolen, const char *from, int frl);
EXPORT int vce_descape_string( char *to, int tolen, const char *from ); 

/* bin.c */
typedef enum {
    SINGLE_CHAR,
    SINGLE_SHORT,
    SINGLE_INT,
    SINGLE_INT64,
    CHARARRAY_8,
    CHARARRAY_16,
    CHARARRAY_32,
    SHORTARRAY_8,
    SHORTARRAY_16,
    SHORTARRAY_32,
    INTARRAY_8,
    INTARRAY_16,
    INTARRAY_32,
    INT64ARRAY_8,
    INT64ARRAY_16,
    INT64ARRAY_32,
    STRARRAY_8,
    STRARRAY_16
} BINDATATYPE;

struct bin_info {
    BINDATATYPE t;
    unsigned int maxu; /* Not used when packing */
    unsigned int n;
    void *p;
};

EXPORT int vce_binary_unpack( struct bin_info *bi,int,char *,int);
EXPORT int vce_binary_pack( struct bin_info *bi,int,char *,int );

EXPORT int vce_binary_push_nb_i1( char *out, int ofs, int maxlen, char c );
EXPORT int vce_binary_push_nb_i2( char *out, int ofs, int maxlen, short s );
EXPORT int vce_binary_push_nb_i4( char *out, int ofs, int maxlen, int i );
EXPORT int vce_binary_push_nb_i8( char *out, int ofs, int maxlen, VCEI64 i );
EXPORT int vce_binary_push_nb_ia1( char *out, int ofs, int maxlen, const void *ia, int num );
EXPORT int vce_binary_push_nb_ia2( char *out, int ofs, int maxlen, const void *ia, int num );
EXPORT int vce_binary_push_nb_ia4( char *out, int ofs, int maxlen, const void *ia, int num );
EXPORT int vce_binary_push_nb_ia8( char *out, int ofs, int maxlen, const void *ia, int num );
EXPORT int vce_binary_push_nb_stra( char *out, int ofs, int maxlen, const char * const *stra, int num, int eachmax );
EXPORT int vce_binary_pop_nb_i1( const char *in, int len, int ofs, char *out);
EXPORT int vce_binary_pop_nb_i2( const char *in, int len, int ofs, short *out );
EXPORT int vce_binary_pop_nb_i4( const char *in, int len, int ofs, int *out );
EXPORT int vce_binary_pop_nb_i8( const char *in, int len, int ofs, VCEI64 *out );
EXPORT int vce_binary_pop_nb_ia1( const char *src, int len, int ofs, char *out, int *outlen );
EXPORT int vce_binary_pop_nb_ia2( const char *src, int len, int ofs, short *out, int *outlen );
EXPORT int vce_binary_pop_nb_ia4( const char *src, int len, int ofs, int *out, int *outlen );
EXPORT int vce_binary_pop_nb_ia8( const char *src, int len, int ofs, VCEI64 *out, int *outlen );
EXPORT int vce_binary_pop_nb_stra( const char *src, int len, int ofs, char **out, int *strnum, int eachmax );

int vce_set_variable_length_specifier( char *out, int outmax, unsigned int len_upper, unsigned int len_lower );
int vce_get_variable_length_specifier( const char *src, int srcmax, unsigned int *len_upper, unsigned int *len_lower );


/* ecode.c */
EXPORT char * vce_strerror( int ecode ); 
EXPORT int vce_get_last_error( void ); 
EXPORT char *vce_strerror_close_reason( CLOSE_REASON reason );


// additional user data  
EXPORT void vce_conn_userdata_set_pointer(conn_t ct,void *p);
EXPORT void*vce_conn_userdata_get_pointer(conn_t ct);
EXPORT void vce_tcpcontext_userdata_set_pointer(tcpcontext_t tp,void *p);
EXPORT void*vce_tcpcontext_userdata_get_pointer(tcpcontext_t tp);


#if defined __GNUC__
#if defined(linux) || defined(sun)
#pragma pack()
#endif
#elif defined(WIN32)
#pragma pack(pop) /* Win32 VC only */
#endif

#ifdef __cplusplus
}
#endif



#define VCE_NOERROR (0)      /* No error */
#define VCE_EGENERIC (-1)    /* Generic error */
#define VCE_EFULL  (-2)      /* Array/Mem/Buffer full. */
#define VCE_EBUG   (-3)      /* It's a bug. */
#define VCE_ERANGE (-5)      /* Value is out of range */
#define VCE_EINVAL (-6)      /* Bad value */
#define VCE_EMEM   (-7)      /* Memory shortage */
#define VCE_ENOENT (-8)      /* No such entry in [search|array] */
#define VCE_EIO    (-9)      /* I/O error ( read/write error ) */
#define VCE_ESOCKET (-10)    /* Socket error  */
#define VCE_EBIND (-11)      /* bind error ( already server is running? ) */
#define VCE_EIPADDR ( -12)   /* IP address error */
#define VCE_ELISTEN (-13)    /* Listen error */
#define VCE_ECONFIG (-14)    /* Bad configuration */
#define VCE_EHOSTNAME (-15)  /* Bad host name */
#define VCE_EFCNTL (-16)     /* Cannot set socket flags */
#define VCE_ECONNECT (-17)   /* Cannot connect  */
#define VCE_EBUFSMALL (-18)  /* Buffer is too small */
#define VCE_EPROTO    (-19)  /* Protocol error */
#define VCE_ENOTREADY (-20)  /* (Connection) is not ready */
#define VCE_ENEGO    (-21)  /* Encryption negotiation error */
#define VCE_EPROTO_INVAL (-22) /* invalid argument (protocol) */
#define VCE_EPROTO_ODD (-23)   /* Odd number of input bytes (protocol)*/
#define VCE_EPROTO_TOOLONG (-24) /* Data too long (protocol)*/
#define VCE_ENOCALLBACK (-25)  /* Callback function is not set */
#define VCE_ESUPPORT  (-26)    /* Not supported currently */
#define VCE_ECONNSERIAL (-28)  /* TCP connection serial number error */
#define VCE_EALIGNMENT (-32)    /* The object has long alignment */
#define VCE_EFORMAT (-33)       /* Bad string format */
#define VCE_ESEARCH (-34)       /* Search engine error */
#define VCE_ECONTENTLEN (-35)   /* Bad content length in protocol */
#define VCE_ECONNINIT (-36)     /* Connection table is not initialized */
#define VCE_EBADKEYLEN (-37 )   /* Bad key length */
#define VCE_EACCEPT (-38 )      /* Accept error */
#define VCE_ESETSOCKOPT (-39)   /* setsockopt() error */
#define VCE_EACCESSFILE (-40)   /* cannot access the file */
#define VCE_EWINSOCKINIT (-41)  /* Winsock initialization error */
#define VCE_EWBFULL (-44)       /* write buffer is full */
#define VCE_ELONGINPUT (-45)    /* input buffer is too long */
#define VCE_ETOOSHORT (-46)     /* input buffer is too short */
#define VCE_EPROTO_BADLEN (-47) /* bad content length (protocol) */
#define VCE_EPROTO_RESULT (-48) /* error is indicated by result code (protocol) */
#define VCE_EPROTO_SERVERINVAL (-49) /* invalid argument by server (protocol)*/
#define VCE_EPROTO_BADCOMMAND (-50) /* bad command (protocol)*/
#define VCE_EFOPEN_W (-51)      /* cannot open file to write */
#define VCE_ERENAME (-52)       /* rename(2) fail */
#define VCE_ENOTFOUND (-54)     /* not found */
#define VCE_ELENTOOLONG (-55)   /* len is too long */
#define VCE_EDATASHORT (-56)    /* actual data is too short */
#define VCE_EOPENDIR (-57)      /* cannot open directory for some reason */
#define VCE_EFSEEK (-58)        /* cannot seek file */
#define VCE_EFWRITE (-59)       /* cannot write data to file */
#define VCE_EFREAD (-60)        /* cannot read data from file */
#define VCE_EMKDIR (-61)        /* cannot create a directory */
#define VCE_EALREADY (-62)      /* operation is already done */
#define VCE_EFINALIZE (-63)     /* cannot finalize VCE */
#define VCE_ECLOSED (-64)       /* already closed */
#define VCE_EGENCOMMAND (-65)   /* protocol generator command error */
#define VCE_ENOCRYPTO (-66)     /* no such crypto engine */
#define VCE_ETOOLONGNAME (-67)  /* specified name is too long */
#define VCE_ESIZE (-68)         /* invalid size */
#define VCE_ESWNOTREADY (-71)   /* switchcontext is not ready */
#define VCE_ESERVERDOWN (-72)   /* server is down */
#define VCE_EODDBUFSIZE (-74)   /* odd buffer size (cipher) */
#define VCE_EODDKEYSIZE (-75)   /* odd key size (cipher) */
#define VCE_EKEYEX (-76)        /* key exchange negotiaion error */
#define VCE_EMORESENDBUF (-77)  /* need more send buffer */
#define VCE_EINIT (-78)         /* vce not initialized */
#define VCE_EARRAY (-79)         /* needs more internal array */


/* Fatal error messages */
#define FATAL_WINSOCK "Fatal:1000 cannot initialize winsock\n"
#define FATAL_FLQ_ARRAY_S "Fatal:1001 cannot initialize fileloader queue ( not used after 0.3.17 ): %s\n"
#define FATAL_FL_TCPCTX_S "Fatal:1002 cannot initialize fileloader tcpc ( not used after 0.3.17 ): %s\n"
#define FATAL_ARRAY_SCARCE "Fatal:1003 array table scarcity (init_array)\n"
#define FATAL_ARRAY_FMALLOC_D "Fatal:1010 MALLOC fail (index=%d)\n"
#define FATAL_ARRAY_FMALLOC1_D "Fatal:1011 MALLOC fail (index=%d)\n"
#define FATAL_ARRAY_FMALLOC2_D "Fatal:1012 MALLOC fail (index=%d)\n"
#define FATAL_ARRAY_FULL_S "Fatal:1020 array full in %s\n"
#define FATAL_ODD_BUFFER_SIZE_D "Fatal:1050 odd buffer size: %d\n"
#define FATAL_SINT_FMALLOC1 "Fatal:1090 int-search: MALLOC fail\n"
#define FATAL_SINT_INITA_D "Fatal:1091 int-search: init_array fail (index=%d)\n"
#define FATAL_SINT_UPDATE1_D "Fatal:1092 int-search: entry full! index=%d\n"
#define FATAL_SINT_UPDATE2_D "Fatal:1093 int-search: entry full! index=%d\n"
#define FATAL_SSTR_FMALLOC1 "Fatal:1094 str-search: MALLOC fail\n"
#define FATAL_SSTR_INITA_D "Fatal:1095 str-search: init_array fail (index=%d)\n"
#define FATAL_SSTR_UPDATE1_D "Fatal:1097 str-search entry full! index=%d\n"
#define FATAL_SSTR_UPDATE2_D "Fatal:1098 str-search entry full! index=%d\n"
#define FATAL_SINT2_FMALLOC1 "Fatal:1100 int2-search: MALLOC fail\n"
#define FATAL_SINT2_INITA_D "Fatal:1101 int2-search: init_array fail index=%d\n"
#define FATAL_SINT2_UPDATE1_D "Fatal:1102 int2-search: entry full! index=%d\n"
#define FATAL_SINT2_UPDATE2_D "Fatal:1103 int2-search: entry full! index=%d\n"

#define FATAL_SINT4_FMALLOC1 "Fatal:1110 int4-search: MALLOC fail\n"
#define FATAL_SINT4_INITA_D "Fatal:1111 int4-search: init_array fail index=%d\n"
#define FATAL_SINT4_UPDATE1_D "Fatal:1112 int4-search: entry full! index=%d\n"
#define FATAL_SINT4_UPDATE2_D "Fatal:1113 int4-search: entry full! index=%d\n"

#define FATAL_TCP_NO_MORE_CON "Fatal:1200 tcp: no more connections are availabe\n"
#define FATAL_TCP_BAD_KEYLEN_D "Fatal:1201 tcp: bad secret key length: %d\n"
#define FATAL_TCP_BAD_ENCRYPT_TYPE_D "Fatal:1202 tcp: bad encryption type specified:%d\n"
#define FATAL_TCP_NEED_PARSER "Fatal:1203 need a parser when creating tcpcontext\n"
#define FATAL_TCP_SOCKET_S_D_S "Fatal:1204 socket() fail addr:%s port:%d os_err:%s\n"
#define FATAL_TCP_GETHOSTBYNAME_S "Fatal:1205 gethostbyname() error: %s\n"
#define FATAL_TCP_GETHOSTBYNAME2_S "Fatal:1206 gethostbyname() error: %s\n"
#define FATAL_TCP_BIND_S_S_D "Fatal:1207 bind() error. os_err:%s addr:%s port:%d\n"
#define FATAL_TCP_LISTEN_S_S_D "Fatal:1208 listen() error. os_err:%s addr:%s port:%d\n"
#define FATAL_TCP_SETSOCKOPT_S "Fatal:1209 setsockopt() fail. os_err:%s\n"
#define FATAL_TCP_GETHOSTBYNAME3_S "Fatal:1210 gethostbyname() error: %s\n"
#define FATAL_TCP_FCNTL_S "Fatal:1212 fcntl fail: %s\n"
#define FATAL_TCP_SETSOCKOPT2_S "Fatal:1213 setsockopt() fail: %s\n"
#define FATAL_TCP_STARTKEYEX_D "Fatal:1214 keyex_start_client fail on fd:%d\n"
#define FATAL_USELOG_WRITE1_S "Fatal:1230 cannot write data in %s\n"
#define FATAL_USELOG_WRITE2_S "Fatal:1231 cannot write data in %s\n"
#define FATAL_VEC_INIT_SEARCH "Fatal:1250 cannot init vpaddr search engine\n"
#define FATAL_VEC_INITMAIN_MALLOC "Fatal:1251 cannot MALLOC master rb.\n"
#define FATAL_VEC_INIT_INT4SEARCH_S "Fatal:1253 cannot initialize int4 search engine:%s\n"
#define FATAL_TCP_CLOSECTX_NULL "Fatal:1256 pointer to tcpcontext is null\n"
#define FATAL_TCP_GETHOSTBYNAMEWIN_S "Fatal:1260 win32 fatal: gethostbyname() error:%s\n"
#define FATAL_TCP_STATEBUF_INIT "Fatal:1265 Memory shortage when creating tcpcontext state buffer\n"
#define FATAL_VEC_REALLOCATE_STATEBUF_S "Fatal:1268 Cannot reallocate vec's state buffer array. (%s)"
#define FATAL_TCP_SETSOCKOPT_REUSE_S  "Fatal:1277 setsockopt(SO_REUSEADDR) fail:%s\n"


/* Warning messages */
#define WARN_FREE_NULL_S "Warning:4000 freeing null pointer in %s\n"
#define WARN_FREE_OUTR_S_P_P "Warning:4001 freeing an out-of-bound element in %s address:%p master-address:%p\n"
#define WARN_FREE_ALIGN_S_P_P_U "Warning:4002 freeing an oddly-aligned element in %s address:%p master-address:%p sizeof:%u\n"
#define WARN_FREE_OUTR2_S_P_P_U "Warning:4003 freeing an out-of-bound element in %s address:%p master-address:%p sizeof:%u\n"
#define WARN_BFENC_NOSPACE_D "Warning:4080 bfenc: no space left on %d's ewb\n"
#define WARN_TCP_ONLY_CON_D "Warning:4100 tcp: only %d connections are usable\n"
#define WARN_TCP_ACCEPT_S_D "Warning:4101 tcp: accept() error. os_err:%s port:%d\n"
#define WARN_TCP_MAXCON_D_D "Warning:4102 tcp: conn_alloc fail no more accept. max:%d port:%d\n"
#define WARN_TCP_ACCEPTW_D "Warning:4103 tcp: acceptwatcher fail fd:%d\n"
#define WARN_TCP_SELECT_MINUS_D_S "Warning:4104 select() returns %d: %s\n"
#define WARN_TCP_TIMEOUT_CON_D_D "Warning:4105 connection timeout. fd:%d sec:%d\n"
#define WARN_TCP_HIWATER_ACCEPTW_D "Warning: 4106 tcp: hiwater acceptwatcher fail fd:%d\n"
#define WARN_VEC_BUFFER_FULL "Warning:4200 vecp buffer full. closing client connection.\n"
#define WARN_VEC_BUFFER_FULL2 "Warning:4201 vecp buffer full. closing client connection.\n"
#define WARN_VEC_FSEARCH_D "Warning:4202 vecp cannot update search engine on fd:%d\n"
#define WARN_VEC_BUFFER_FULL3 "Warning:4203 vecp buffer full. closing client connection.\n"
#define WARN_VEC_BAD_PROTO_MAGIC "Warning:4204 vecp: bad protocol magic\n"
#define WARN_VEC_BAD_VERSION "Warning:4205 vecp: bad version number\n"
#define WARN_VEC_BAD_CLEN_D "Warning:4206 vecp: bad content length:%d\n"
#define WARN_VEC_BAD_PROTO_MAGIC2 "Warning:4207 vecsv: bad protocol magic on vp connection\n"
#define WARN_VEC_BAD_VERSION2 "Warning:4208 vecsv: bad version number on vp connection\n"
#define WARN_VEC_BAD_CLEN2_D "Warning:4209 vecsv: bad content length:%d\n"
#define WARN_VEC_EWRITE "Warning:4210 vecsv: cannot write data into vp connection\n"
#define WARN_REFREE_S_P "Warning:4214 re-freeing an element in %s address:%p\n"
#define WARN_TCP_SELECT_WINERROR_D "Warning:4215 winsock select() returns SOCKET_ERROR, and WSAGetLastError:%d\n"
#define WARN_RETURNING_EWBFULL_D_D "Warning:4223 bin16: unparser cannot write full record. try:%d actual:%d\n"
#define WARN_TCP_MAX_CONN_IN_USE_D "Warning:4225 vce_tcpcontext_create: reached max connection num %d\n"
#define WARN_CONN_DOES_NOT_HAVE_PARSER "Warning:4300 vce_conn_io: conn does not have parser function. use vce_tcpcontext_set_conn_parser\n"
#define WARN_TCP_NO_MORE_ACCEPT "Warning:4312 tcpcontext_try_accept: no more accept\n"


/* Internal bug detection messages */
#define BUG_FREESTACK_OVERFLOW_S "Bug:7000 blank-list stack overflow: %s\n"
#define BUG_SHOW_ARRAY_USAGE_S_P "Bug:7002 use flag is 0! in %s address:%p\n"
#define BUG_USENUM_NOMATCH_S_D_D "Bug:7003 usenum doesn't match in %s stack:%d link_inuse:%d\n"
#define BUG_TCP_NOBUF "Bug:7010 tcp: nobuf?\n"
#define BUG_TCP_NOMEM "Bug:7011 tcp: nomem?\n"
#define BUG_VEC_DELETE_SEARCH "Bug:7100 vecp: cannot delete search entry\n"
#define BUG_VEC_NOTFOUND_CLI "Bug:7101 vecp: cannot find client connection\n"
#define BUG_VEC_NOTFOUND_CLI2 "Bug:7102 vecp: cannot find client connection\n"
#define BUG_VEC_DELETE_SEARCH2 "Bug:7103 vecsv: cannot delete search entry\n"
#define BUG_VEC_NOTFOUND_CLI3 "Bug:7104 vecsv: cannot find client connection\n"
#define BUG_VEC_DELETE_SEARCH3 "Bug:7105 vecsv: cannot delete client circuit from search engine.\n"
#define BUG_VEC_DELETE_SEARCH_WHEN_CLOSE "Bug:7106 vecsv: vce_circ_close fail\n"
#define BUG_TCP_STATEBUF_RUNSHORT "Bug:7109 state buffer is full.(accept)\n"
#define BUG_TCP_CONNECT_STATEBUF_RUNSHORT "Bug:7112 connect: statebuf shortage\n"

/* Notify messages */
#define NOTE_NOOP_PROTOCOL_D_D "Note:10001 NOOP PROTOCOL: %d bytes from conn_t. serial:%d\n"
#define NOTE_DUMP_PROTOCOL_D_D "Note:10002 DUMP PROTOCOL: %d bytes from conn_t. serial:%d\n"
#define NOTE_BFDEC_INIT_D "Note:10010 init blowfish decoder on fd:%d\n"
#define NOTE_BFENC_INIT_D "Note:10011 init blowfish encoder on fd:%d\n"
#define NOTE_RIJDEC_INIT_D "Note:10012 init rijindael decoder on fd:%d\n"
#define NOTE_RIJENC_INIT_D "Note:10013 init rijndael encoder on fd:%d\n"
#define NOTE_SINT_OK_S_D_D "Note:10100 init int-search OK name:%s htsize:%d entnum:%d\n"
#define NOTE_SSTR_OK_S_D_D "Note:10101 init str-search OK name:%s htsize:%d entnum:%d\n"
#define NOTE_SINT2_OK_S_D_D "Note:10102 init int2-search OK name:%s htsize:%d entnum:%d\n"
#define NOTE_SINT4_OK_S_D_D "Note:10102 init int4-search OK name:%s htsize:%d entnum:%d\n"
#define NOTE_SE_CLEAN_S "Note:10103 cleaned up search engine %s\n"
#define NOTE_TCP_NEW_CONNECTION "Note:10200 new connection fd:%d I:%d sbuflen:%d\n"
#define NOTE_TCP_NONBLOCK_CON "Note:10201 non blocking connect().\n"
#define NOTE_TCP_CONNECT_OK_D "Note:10202 connect ok on %d\n"
#define NOTE_UTIL_MALLOC_U_P "Note:10220 malloc(%u) returns %p\n"
#define NOTE_UTIL_FREE_P "Note:10221 free(%p)\n"
#define NOTE_VEC_REGISTER_D "Note:10300 vec REGISTERED remoteport:%d\n"
#define NOTE_VEC_UNREGISTER_X_D "Note:10301 vec UNREGISTERED remoteaddr:%x:%d\n"
#define NOTE_VEC_CLOSE_FROM_SERVER "Note:10302 vec CLOSE command from server\n"
#define NOTE_VEC_ACCEPT_OK_X_D "Note:10303 vec ACCEPT OK on %x:%d\n"
#define NOTE_VEC_CLOSE_OK_X_D "Note:10304 vec CLOSE OK on %x:%d\n"
#define NOTE_INIT_ARRAY_OK_D_P_U_D_S "Note:10310 init_array OK index:%d bufmaster:%p size:%u num:%d name:%s\n"
#define NOTE_CONN_EOF_D_S "Note:10320 conn_t detected EOF on fd %d addr:%s\n"
#define NOTE_CONN_READERROR_D_S "Note:10321 conn_t detected read error on fd %d addr:%s\n"
#define NOTE_CONN_WRITEERROR_D_S_S "Note:10322 conn_t detected write error on fd %d (%s) addr:%s\n"
#define NOTE_CONN_NEGO_ERROR_D_D "Note:10323 conn_t detected encryption negotiation error on fd %d error code:%d\n"
#define NOTE_CONN_DECODING_ERROR_D_D "Note:10324 conn_t detected decoding error on fd %d error code: %d\n"
#define NOTE_CONN_ENCODING_ERROR_D_D "Note:10325 conn_t detected encoding error on fd %d error code: %d\n"
#define NOTE_CONN_PROTOCOL_ERROR_D_D "Note:10326 conn_t detected protocol error on fd %d error code: %d\n"
#define NOTE_KEYEX_BAD_CLIPUBKEYLEN_D "Note:10330 key exchange: bad client public key length: %d\n"
#define NOTE_KEYEX_NEGO_DONE_D "Note:10331 key exchange: encryption negotiation is done on fd %d\n"
#define NOTE_KEYEX_NEGO_DONE2_D "Note:10332 key exchange: encryption negotiation is done on fd %d\n"
#define NOTE_KEYEX_BAD_MAJOR_VERSION_D "Note:10333 key exchange: bad encryption version %d\n"
#define NOTE_KEYEX_BAD_SECRET_KEY_LENGTH_D "Note:10334 key exchange: bad secret key length: %d\n"
#define NOTE_VEC_CLOSE_OK2_X_D "Note:10338 vce_circ_close successful:%x %d\n"
#define NOTE_VEC_REALLOCATE_STATEBUF_D "Note:10340 vec: reallocated state buffer size:%d\n"
#define NOTE_TCP_STATEBUF_ALLOC "Note:10342 allocated state buffer for conn.\n"
#define NOTE_TCP_STATEBUF_INIT_OK "Note:10345 vce_tcpcontext_create could allocate state buffer.\n"
#define NOTE_TCP_FREED_STATEBUF "Note:10347 freed state buffer for conn\n"
#define NOTE_VEC_STATEBUF_ALLOC_OK "Note:10348 vec: statebuf allocate ok\n"
#define NOTE_VEC_FREED_STATEBUF "Note:10349: vec: freed state buffer for a circ\n"
#define NOTE_VCE_FINALIZED "Note:10400: vce: finalized\n"


#define STRDEF_EMESG_NOERROR        "No error"
#define STRDEF_EMESG_EGENERIC       "Generic error"
#define STRDEF_EMESG_EFULL          "Array/Mem/Buffer full"
#define STRDEF_EMESG_EBUG           "It can be a bug"
#define STRDEF_EMESG_ERANGE         "Value is out of range"
#define STRDEF_EMESG_EINVAL         "invalid argument"
#define STRDEF_EMESG_EMEM           "Memory shortage"
#define STRDEF_EMESG_ENOENT         "No such entry in [search|array]"
#define STRDEF_EMESG_EIO            "I/O error ( read/write error )"
#define STRDEF_EMESG_ESOCKET        "Socket error"
#define STRDEF_EMESG_EBIND          "bind error ( already server is running ?)"
#define STRDEF_EMESG_EIPADDR        "IP address error"
#define STRDEF_EMESG_ELISTEN        "Listen error"
#define STRDEF_EMESG_ECONFIG        "Bad configuration"
#define STRDEF_EMESG_EHOSTNAME      "Bad host name"
#define STRDEF_EMESG_EFCNTL         "Cannot set socket flags"
#define STRDEF_EMESG_ECONNECT       "Cannot connect"
#define STRDEF_EMESG_EBUFSMALL      "Buffer is too small"
#define STRDEF_EMESG_EPROTO         "protocol error"
#define STRDEF_EMESG_ENOTREADY      "(Connection) is not ready"
#define STRDEF_EMESG_ENEGO          "Encryption negotiation error"
#define STRDEF_EMESG_EPROTO_INVAL   "Protocol error ( invalid argument )"
#define STRDEF_EMESG_EPROTO_ODD     "Odd number of input bytes (protocol)"
#define STRDEF_EMESG_EPROTO_TOOLONG "Data too long (protocol)"
#define STRDEF_EMESG_ENOCALLBACK    "Callback function is not set"
#define STRDEF_EMESG_ESUPPORT       "Not supported currently"
#define STRDEF_EMESG_ECIRCSERIAL    "Virtual circuit serial number error"
#define STRDEF_EMESG_ECONNSERIAL    "TCP connection serial number error"
#define STRDEF_EMESG_EVECNOTREADY   "Vectorizer is not initialized"
#define STRDEF_EMESG_ENOCIRCPARENT  "No parent connection for a circuit"
#define STRDEF_EMESG_EALIGNMENT     "The object has long alignment"
#define STRDEF_EMESG_EFORMAT        "Bad string format"
#define STRDEF_EMESG_ESEARCH        "Search engine error"
#define STRDEF_EMESG_ECONTENTLEN    "Bad content length in protocol"
#define STRDEF_EMESG_ECONNINIT      "Connection table is not initialized"
#define STRDEF_EMESG_EBADKEYLEN     "Bad key length"
#define STRDEF_EMESG_EACCEPT        "Accept error"
#define STRDEF_EMESG_ESETSOCKOPT    "setsockopt() error"
#define STRDEF_EMESG_EACCESSFILE    "cannot access file ( generic )"
#define STRDEF_EMESG_EWINSOCKINIT   "winsock init fail"
#define STRDEF_EMESG_EWBFULL        "write buffer is full."
#define STRDEF_EMESG_ELONGINPUT     "input data is too long"
#define STRDEF_EMESG_ETOOSHORT      "input data is too short"
#define STRDEF_EMESG_EPROTO_BADLEN  "bad content length (protocol)"
#define STRDEF_EMESG_EPROTO_RESULT  "error in result code (protocol)"
#define STRDEF_EMESG_EPROTO_SERVERINVAL "invalid argument by server(protocol)"
#define STRDEF_EMESG_EPROTO_BADCOMMAND "bad command (protocol)"
#define STRDEF_EMESG_EFOPEN_W       "cannot open file to write (fopen fail)"
#define STRDEF_EMESG_ERENAME        "cannot rename a file (rename fail)"
#define STRDEF_EMESG_ENOTFOUND      "not found (generic) "
#define STRDEF_EMESG_ELENTOOLONG    "len is too long"
#define STRDEF_EMESG_EDATASHORT     "actual data is too short"
#define STRDEF_EMESG_EOPENDIR       "cannot open directry"
#define STRDEF_EMESG_EFSEEK         "cannot seek file"
#define STRDEF_EMESG_EFWRITE        "cannot write data to file"
#define STRDEF_EMESG_EFREAD         "cannot read data from file"
#define STRDEF_EMESG_EMKDIR         "cannot create a directory"
#define STRDEF_EMESG_EALREADY       "operation is already done"
#define STRDEF_EMESG_EFINALIZE      "cannot finalize VCE"
#define STRDEF_EMESG_ECLOSED        "already closed"
#define STRDEF_EMESG_EGENCOMMAND    "protocol generator command error"
#define STRDEF_EMESG_ENOCRYPTO      "no such crypto engine"
#define STRDEF_EMESG_ETOOLONGNAME   "specified name is too long"
#define STRDEF_EMESG_ESIZE          "invalid size"
#define STRDEF_EMESG_ESWNOTREADY    "switchcontext is not ready"
#define STRDEF_EMESG_ESERVERDOWN    "server is down"
#define STRDEF_EMESG_ESWTRANSIENT   "now the circ is in transient state"
#define STRDEF_EMESG_EODDBUFSIZE    "odd buffer size (cipher)"
#define STRDEF_EMESG_EODDKEYSIZE    "odd key size (cipher)"
#define STRDEF_EMESG_EKEYEX         "key exchange negotiation error"
#define STRDEF_EMESG_EMORESENDBUF   "need more send buffer"
#define STRDEF_EMESG_EINIT          "vce not inintialized"
#define STRDEF_EMESG_EARRAY         "need more internal array"
#define STRDEF_UNKNOWNERROR         "Unknown error code"



#endif /* VCE_H */

