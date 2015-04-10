#ifndef _CONN_H_
#define _CONN_H_

#include "vce.h"
#include "sbuf.h"
#include "osdep.h"


//  TCPコネクション1本を表現する 
typedef struct _conn {
    int fd;

	/* closed flag。 close を呼びだしたらこのフラグが1になり、
	   チェックのときにこのフラグが1だったら実際に close される。
       アプリケーションが能動的に close を呼びだしたときだけ、
       このフラグが使われ、受動的に閉じられる場合は直接 conn_free が使われる。
    */
	int closed_flag;

	/* ノンブロッキング connect の connect が終了しているかどうかのフラグ。
	   tcpcontext の nonblock_connect が 1 でないときはこの変数は使われない */
	int nonblock_connect_ok;

    // accept/connect したときにわかるアドレス 
	char remote_addr[16]; // ipv4 の場合は先頭の4バイトに NBOrder で。 ipv6 の場合は全体に NBOrder 
	int remote_addr_len; // ipv4 なら4、 ipv6 なら 16 
	unsigned short remote_port; // network byte order
	char local_addr[16];
	int local_addr_len;
	unsigned short local_port;
    
    time_t last_access; // 最後にアクセスがあった時刻
    int timeout_sec;  // タイムアウトの設定

	sbuf rb,wb;

    void *tcpc; // tcpcontextへのptr

    int is_server;
    
    int index; // conn配列の中の index 
	void *userdata; // additional userdata pointer 
	char *statebuf; // 状態管理バッファ(tcpcontextのmiからとるポインタ
	size_t statebuf_size; // tcpcontextのコピー 
	int statebuf_mi; // tcpcontextのコピー 

    int ( *protocol_parser ) ( conn_t );

	int ( *protocol_acceptwatcher ) ( conn_t ) ;
    int ( *protocol_hiwater_acceptwatcher ) (conn_t, int);
	int ( *protocol_closewatcher ) ( conn_t, CLOSE_REASON r );

	int ( *pcallback)(conn_t,char*,int);	// プロトコルコールバック関数 
	
	unsigned int serial;  // 自分自身のシリアル番号 


    /* exploit対策、bin16パーサでの最大値設定 */
	/* tcpcontextから受け取る */
	int (*maxlen_warning)(conn_t ct);
	int maxlen_record;


	/* 統計情報 */
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
