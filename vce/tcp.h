#ifndef _TCP_H_
#define _TCP_H_

#include "vce.h"
#include "conn.h"

#ifdef WIN32
#include <windows.h>
#endif


/*************************************************************************

  tcpcontext構造体。 クライアントとサーバの両方に共通の最小公倍数設定。

 *************************************************************************/

typedef struct _tcpcontext
{
    int is_server;
    int timeout_sec; // デフォルトタイムアウト 
    int max_conn;  // このサーバーの最大接続数 
	int conn_in_use;

    /* r/w buffer の長さ(per conn)。未解読/暗号化済みのデータ用もまったく同じサイズを用意する。 */
    size_t rblen,erblen;
    size_t wblen,ewblen;

	/* 状態管理用バッファ。VECにlinkage されたら、数が変化するので、
	   一旦解放して、また割りあてなおす。(トリッキーだがね) */
	size_t statebuf_size;
	int statebuf_mi;     /* 配列 */
	int statebuf_num;    /* 個数 */


	int rbmaster_mi, wbmaster_mi, erbmaster_mi, ewbmaster_mi;


	/* トータルの読み/書き/accept などの回数 */
	VCEI64 recv_byte,send_byte,keyex_count;
	/* システムコールの回数 */
	VCEI64 recv_syscall, recv_syscall_e;
	VCEI64 send_syscall, send_syscall_e;
	VCEI64 accept_syscall, accept_syscall_e;
	VCEI64 connect_syscall, connect_syscall_e;

    /* VCEのイベント回数 */
	VCEI64 conn_write,conn_timeout,tcpcontext_connect;

    /* bind するアドレス、サーバの場合のみ */
    struct sockaddr_in sa;

	/* 一分あたりのaccept許容量 */
	int accept_count,accept_max;
	VCEI64 accept_lasttime;
	int (*accept_warning)(tcpcontext_t t);

	
	void *userdata; // userdata pointer 

	char ps_host[256];
	unsigned short ps_mainport;
	unsigned short ps_subport;
    
    int accept_more; // 今後acceptするかどうか。サーバの場合のみ
    int mainsock; // bind用socket(サーバの場合) 
    int index;    // tcpcontext の中のindex
    int nonblock_connect;    // client connectがブロックするか
	int nodelay; // ソケットをNODELAYにする

    int ( *protocol_parser ) ( conn_t );

	int ( *protocol_acceptwatcher ) ( conn_t ); /* accept したときの反応 */
    int ( *protocol_hiwater_acceptwatcher ) (conn_t,int);
	int ( *protocol_closewatcher ) ( conn_t,CLOSE_REASON r );/*closeしたとき */
    
	int ( *pcallback)(conn_t,char*, int);  // パーサが呼びだすこーるばっく関数 

	void (*conn_finalizer)(conn_t);


    /* 接続数の hiwater を診断するためのしきい値 */
    int conn_hiwater_thres;

    /* exploit対策、bin16パーサでの最大値設定*/
	/* tcpcontextから受け取る */
	int (*maxlen_warning)(conn_t ct);
	int maxlen_record;

	/* conn のシリアル番号の最大。ゼロだったら、
       serial の最大値のコントロールはしない(Default) */
    unsigned int conn_serial_max;

    /* 1 heartbeat に何回 parser を呼ぶか。デフォルトは 1 */
    int call_parser_per_loop;

	/* 書きこみ成功でもタイムアウトカウンタを初期化するなら、
       このフラグを1にする。通常は0でいい */
    int recv_reset_timeout, send_reset_timeout;

} tcpcontext;



void vce_tcp_poll( int isolate_conn_serial );
int vce_tcpcontext_init_world( void );
int vce_tcpcontext_fin_world(void);
int vce_tcpcontext_get_next_conn_serial();

extern int vce_select_timeout_us;

#endif
