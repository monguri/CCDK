#include "vce.h"
#include "vcecommon.h"
#include "uselog.h"
#include "tcp.h"
#include "osdep.h"
#include "util.h"


static vce_stat_t vce_usage;


int vce_verbose_mode = 0; 
int vce_last_error = 0;       
int vce_log_read_write = 0; // read/write の様子を全部ログするフラグ 




// 0:normal 1:verbose -1:quiet
void vce_set_verbose_mode( int m ) {
    vce_verbose_mode = m;
}

void vce_set_read_write_log_mode( int m ) {
    vce_log_read_write = m;
}


void vce_errout( const char *format, ... ) {
	va_list arg;

	if( vce_verbose_mode < 0 ) return;
	
    va_start( arg, format );
    vfprintf( stderr , format, arg );
    va_end( arg );
}



void vce_errout_v( const char *format, ... ) {
    va_list arg;

	if( vce_verbose_mode <= 0 ) return;

    va_start( arg, format );
    vfprintf( stderr , format, arg );
    va_end( arg );
}

   
// vceusage の内容を操作する(ユーザに非公開)
void vce_usage_set_boot_time( time_t t ) {
    vce_usage.boot_time = t;
}
                        
void vce_usage_increment_conn_alloc(void) {
	vce_usage.conn_alloc ++;
}
void vce_usage_increment_conn_free(void) {
	vce_usage.conn_free ++;
}
void vce_usage_increment_conn_close( void ) {
	vce_usage.conn_close ++;
}
void vce_usage_increment_keyex( tcpcontext *t ) {
	t->keyex_count ++;
	vce_usage.keyex ++;
}
void vce_usage_increment_recv_syscall( conn *c ) {
	c->recv_syscall ++;
	((tcpcontext*)c->tcpc)->recv_syscall ++;
	vce_usage.recv_syscall ++;
}
void vce_usage_increment_recv_syscall_e( conn *c ) {
	((tcpcontext*)c->tcpc)->recv_syscall_e ++;
	vce_usage.recv_syscall_e ++;
}
void vce_usage_add_recv_byte( int v, conn *c ) {
	if( v < 0 )return;
	c->recv_byte += v;
	((tcpcontext*)c->tcpc)->recv_byte += v;
	vce_usage.recv_byte += v;
}
void vce_usage_increment_send_syscall( conn *c ) {
	c->send_syscall ++;
	((tcpcontext*)c->tcpc)->send_syscall ++;
	vce_usage.send_syscall ++;
}
void vce_usage_increment_send_syscall_e ( conn *c ) {
	((tcpcontext*)c->tcpc)->send_syscall_e ++;	
	vce_usage.send_syscall_e ++;
}
void vce_usage_add_send_byte( int v, conn *c ) {
	if( v < 0 )return;
	c->send_byte += v;
	((tcpcontext*)c->tcpc)->send_byte += v;
	vce_usage.send_byte += v;
}

void vce_usage_increment_conn_write( conn *c ) {
	c->conn_write ++;
	((tcpcontext*)c->tcpc)->conn_write ++;
	vce_usage.conn_write ++;
}
void vce_usage_increment_tcpcontext_create( void ) {
	vce_usage.tcpcontext_create ++;
}
void vce_usage_increment_tcpcontext_cleanup( void ) {
	vce_usage.tcpcontext_cleanup ++;
}
void vce_usage_increment_accept_syscall_e( tcpcontext *t ) {
	t->accept_syscall_e ++;
	vce_usage.accept_syscall_e ++;
}
void vce_usage_increment_accept_syscall( tcpcontext *t ) {
	t->accept_syscall ++;
	vce_usage.accept_syscall ++;
}

void vce_usage_increment_conn_timeout( tcpcontext *t ) {
	t->conn_timeout ++;
	vce_usage.conn_timeout ++;
}
void vce_usage_increment_connect_syscall_e( tcpcontext *t ) {
	t->connect_syscall_e ++;
	vce_usage.connect_syscall_e ++;
}
void vce_usage_increment_connect_syscall( tcpcontext *t ) {
	t->connect_syscall ++;
	vce_usage.connect_syscall ++;
}
void vce_usage_increment_tcpcontext_connect( tcpcontext *t ) {
	t->tcpcontext_connect ++;
	vce_usage.tcpcontext_connect ++;
}
void vce_usage_increment_log_count( void ) {
	vce_usage.log_count ++;
}



void vce_get_stat( vce_stat_t *v ) {
    memcpy( v, &vce_usage, sizeof( vce_stat_t ));
}

int vce_get_netstat_string( char *buf, int maxlen ) {
    /* まず全部の conn をリストアップ */
    conn *co;
    char oneline[256];
    int so_far = 0;
    
    ARRAY_SCAN(vce_conn_mi, co ) {
        conn_t c = { co, co->serial };
        char tmp[100], tmp2[100];
        int l;
        char type[20];
        vce_copy_cstring( type, sizeof(type), "conn" );
        
        vce_snprintf(oneline,sizeof(oneline),
                     "type=%s,r=%d,w=%d,rem=%s,loc=%s,"
                     "fd=%d,s=%u,last=%u,timeo=%u\n",
                     type,
                     vce_sbuf_get_use( &co->rb),
                     vce_sbuf_get_use( &co->wb),
                     vce_conn_get_remote_addr_string( c , tmp,sizeof(tmp)),
                     vce_conn_get_local_addr_string( c , tmp2,sizeof(tmp2)),
                     co->fd,
                     co->serial,
                     (unsigned int)co->last_access,
                     co->timeout_sec
                     );
        l = (int)strlen( oneline );
        if( (so_far+l) >= (maxlen-1) ){
            return SET_LAST_ERROR(VCE_EFULL);
        }
        memmove( buf + so_far, oneline, l );
        so_far += l;
    }

    buf[so_far]=0;
    return SET_LAST_ERROR(VCE_NOERROR);
}
