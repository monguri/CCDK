# VCE のエラーコードとエラーメッセージ

VCEでは2通りの方法でエラーを判別します。
ひとつは、vce_get_last_error 関数によってエラー番号を取得する方法、もうひとつは、エラーログ(vce_errout)に出力されている文字列をもとに判別する方法です。本文書では、その両方について説明します。


- <a href="#ecode">VCEのエラーコード</a>
- <a href="#elog">VCEのエラーログメッセージ</a>
  - <a href="#fatalerror">Fatalエラーメッセージ</a>
  -	<a href="#warning"> Warningメッセージ </a>
  -	<a href="#bug"> Bugメッセージの一覧 </a>
  - <a href="#note">Noteメッセージの一覧</a>




## <a name="ecode"></a>VCE のエラーコード

以下にVCEのエラーコードを列挙します。

以下の説明では、 vce.h の内容を引用しています。


- ```#define VCE_NOERROR (0) ``` エラーなし
- ```#define VCE_EGENERIC (-1) ``` 一般エラー
- ```#define VCE_EFULL  (-2)　``` バッファが一杯になった
- ```#define VCE_EBUG   (-3) ``` VCE内部のバグである可能性が高い
- ```#define VCE_ERANGE (-5) ``` 引数が範囲外である
- ```#define VCE_EINVAL (-6) ``` 引数が不正である
- ```#define VCE_EMEM   (-7) ``` メモリが足りない
- ```#define VCE_ENOENT (-8) ``` 検索でマッチしない、ファイルが見つからない
- ```#define VCE_EIO    (-9)```  ソケットまたはファイルのI/Oエラー
- ```#define VCE_ESOCKET (-10)```  socketシステムコールが失敗した
- ```#define VCE_EBIND (-11)``` bindシステムコールが失敗した
- ```#define VCE_EIPADDR ( -12)```  IPアドレスの指定が間違っている
- ```#define VCE_ELISTEN (-13)``` listen()システムコールが失敗した
- ```#define VCE_ECONFIG (-14)``` 設定値が異常である
- ```#define VCE_EHOSTNAME (-15)``` ホスト名が解決できない
- ```#define VCE_EFCNTL (-16)``` fcntl が失敗した
- ```#define VCE_ECONNECT (-17)``` connectシステムコールが失敗した
- ```#define VCE_EBUFSMALL (-18)``` 指定されたバッファが小さすぎる
- ```#define VCE_EPROTO    (-19)``` プロトコルのバイト列がおかしい
- ```#define VCE_ENOTREADY (-20)``` 暗号ネゴシエーションが完了していないのにアクセスした
- ```#define VCE_ENEGO    (-21)``` 暗号ネゴシエーションが失敗した
- ```#define VCE_EPROTO_INVAL (-22)``` プロトコルの引数がおかしい
- ```#define VCE_EPROTO_ODD (-23)``` プロトコルの入力レコードの長さが異常である
- ```#define VCE_EPROTO_TOOLONG (-24)``` プロトコルの入力データが長すぎる
- ```#define VCE_ENOCALLBACK (-25)``` コールバック関数が未定義である
- ```#define VCE_ESUPPORT  (-26)``` 現在はサポートされていない
- ```#define VCE_ECIRCSERIAL (-27)``` circ_tのシリアル番号が異なるためI/O不能
- ```#define VCE_ECONNSERIAL (-28)``` conn_tのシリアル番号が異なるためI/O不能
- ```#define VCE_EVECNOTREADY (-29)``` パケットベクトライザが準備できていない。
- ```#define VCE_ENOCIRCPARENT (-30)``` 仮想回路が含まれているはずのTCPコネクションが存在しない
- ```#define VCE_EALIGNMENT (-32)``` 指定されたオブジェクトのアラインメントがおかしい
- ```#define VCE_EFORMAT (-33)``` 文字列のフォーマットが異常である
- ```#define VCE_ESEARCH (-34)``` サーチエンジン内部エラー
- ```#define VCE_ECONTENTLEN (-35)``` プロトコルのレコードのデータ部の長さがおかしい
- ```#define VCE_ECONNINIT (-36)``` コネクション表が初期化されていない
- ```#define VCE_EBADKEYLEN (-37 )``` 暗号化キーの長さがおかしい
- ```#define VCE_EACCEPT (-38 )``` acceptシステムコールが失敗した
- ```#define VCE_ESETSOCKOPT (-39)```  setsockoptシステムコールが失敗した
- ```#define VCE_EACCESSFILE (-40)``` ファイルにアクセスできない
- ```#define VCE_EWINSOCKINIT (-41)``` Winsock の初期化に失敗(win32のみ)
- ```#define VCE_EWBFULL (-44)``` 書きこみバッファがいっぱいになっている
- ```#define VCE_ELONGINPUT (-45)``` 入力バッファが長すぎる
- ```#define VCE_ETOOSHORT (-46)``` 入力バッファ短すぎる
- ```#define VCE_EPROTO_BADLEN (-47)``` プロトコルの入力レコードの長さが異常(クラックのうたがいあり)
- ```#define VCE_EPROTO_RESULT (-48)``` プロトコルでサーバがエラーを返している
- ```#define VCE_EPROTO_SERVERINVAL (-49)``` サーバが異常な値を返してきた(クラックのうたがいあり)
- ```#define VCE_EPROTO_BADCOMMAND (-50)``` そのようなプロトコルコマンドはない
- ```#define VCE_EFOPEN_W (-51)``` 書きこみのためにファイルを開けない
- ```#define VCE_ERENAME (-52)``` rename(2) システムコールが失敗した
- ```#define VCE_ENOMORELOCK (-53)``` これ以上ロックを受けいれることができない
- ```#define VCE_ENOTFOUND (-54)``` 何かが見つからない(vce_get_???_search)
- ```#define VCE_ELENTOOLONG (-55)``` 長さの指定が大きすぎ
- ```#define VCE_EDATASHORT (-56)``` データ部分が短かすぎる
- ```#define VCE_EOPENDIR (-57)``` ディレクトリを開くことができない
- ```#define VCE_EFSEEK (-58)``` ファイルをfseekできない
- ```#define VCE_EFWRITE (-59)``` データをファイルに書きこめない
- ```#define VCE_EFREAD (-60)``` データをファイルから読めない
- ```#define VCE_EMKDIR (-61)``` ディレクトリを作れなかった
- ```#define VCE_EALREADY (-62)``` 同じ処理は2度できない。重複している。
- ```#define VCE_EFINALIZE (-63)``` VCEを解放するときのエラー。正しく解放されなかったため、メモリがリークしている可能性がある(VCEのバグか、使用方法の間違い)
- ```#define VCE_ECLOSED (-64)``` すでにコネクション等が閉じられているのにアクセスしようとした
- ```#define VCE_EGENCOMMAND (-65)``` genのプロトコル定義ファイルで定義されていない関数IDが呼び出された
- ```#define VCE_ENOCRYPTO (-66)``` そのようなブロック鍵暗号アルゴリズムは存在しない
- ```#define VCE_ETOOLONGNAME (-67)``` 指定された名前は、長すぎる
- ```#define VCE_ESIZE (-68)``` 指定されたサイズは異常
- ```#define VCE_ETASK (-69)``` 内部で使用するタスクを初期化できない
- ```#define VCE_ETASKG (-70)``` 内部で使用するタスクグループを初期化できない
- ```#define VCE_EMORESENDBUF (-77)``` より多くの送信バッファを必要としている。circ_t を利用している場合で、SWP への送信バッファが足りない場合に、書きこみ関数からこのエラーが返る。
- ```#define VCE_EINIT (-78)``` VCE が初期化されていないのに VCE の関数を呼ぼうとした。
- ```#define VCE_EARRAY (-79)``` VCE が内部で必要としている配列エンジンが不足している。vce_initialize_limited 関数で max_array メンバを調整するとよい。



## <a name="elog"></a>VCE のエラーログメッセージ

VCEがログに吐きだすメッセージには、Fatal,Warning,Bug,Note の4種類があります。

すべてのメッセージには番号が振られていて、Fatalは1000番台、Warning は4000番台、Bugは7000番台、Noteは10000番台がわりあてられています。
すべて、 vce.h でマクロとして定義されています。

スクリプト言語などをもちいてサーバログをパースして利用するときには、
"Fatal:1101"のような番号のみを手がかりとするように注意してください。

### <a name="fatalerror"></a>Fatalエラーメッセージ

Fatalエラーメッセージは、主にアプリケーションがVCEの利用方法を間違っているか、
OSの設定が不足している(ポートの問題や、空きメモリ、パーミッションの問題など)
が原因です。細かく原因を追及していくと解決できるはずです。

- ```Fatal:1000 cannot initialize winsock``` Winsock を初期化できない
- ```Fatal:1003 array table scarcity (init_array)``` 配列表の残り数が不足している。 vce_init_array の回数が多すぎる。 配列リークしていないかチェックせよ。
- ```Fatal:1010 MALLOC fail (index=%d)``` MALLOC ( malloc のラッパ) が失敗してマスターバッファを確保できない。ほぼメモリ不足が原因。
- ```Fatal:1011 MALLOC fail (index=%d)``` MALLOC ( malloc のラッパ) が失敗してエントリリストを確保できない。ほぼメモリ不足が原因。
- ```Fatal:1012 MALLOC fail (index=%d)``` MALLOC ( malloc のラッパ) が失敗して使用リストを確保できない。ほぼメモリ不足が原因。
- ```Fatal:1020 array full in %s``` 配列の空き要素がひとつもない。予期せずこれが出力されたときは vce_free_array_object し忘れを確認せよ
- ```Fatal:1050 odd buffer size: %d``` バッファサイズが、「割りきれない数」になっている。
- ```Fatal:1080 please set buffer with length of n*256 bytes.``` 256の倍数以外の長さをもつバッファです。
- ```Fatal:1200 tcp: no more connections are availabe``` TCPのコネクションが、VCEの最大接続数制限にひっかかってそれ以上増やせない。
- ```Fatal:1202 tcp: bad encryption type specified:%d``` vce_tcpcontext_create の crypt 引数の値は0か1のみ
- ```Fatal:1203 need a parser when creating tcpcontext``` vce_tcpcontext_create するときには、すくなくてもパーサ関数は指定する必要がある。そうでないとソケットからの入力をどう処理すべきかが定義されないまま放置されることになる。
- ```Fatal:1204 socket() fail addr:%s port:%d os_errno:%s``` socket() システムコールが失敗しているため、その状況をCライブラリのエラー番号で返す
- ```Fatal:1205 gethostbyname() error: %s``` gethostbyname関数が失敗している。Cライブラリのエラー出力も表示します。
- ```Fatal:1206 gethostbyname() error: %s``` gethostbyname関数が失敗している。Cライブラリのエラー出力も表示します。
- ```Fatal:1207 bind() error. os_errno:%s addr:%s port:%d``` bind関数が失敗している。
- ```Fatal:1208 listen() error. os_errno:%s addr:%s port:%d``` listen関数が失敗している。
- ```Fatal:1209 setsockopt() fail. os_errno:%s``` setsockopt関数が失敗した。
- ```Fatal:1210 gethostbyname() error: %s``` gethostbyname関数が失敗している。Cライブラリのエラー出力も表示します。
- ```Fatal:1212 fcntl fail: %s``` fcntl 関数が失敗した。
- ```Fatal:1213 setsockopt() fail: %s``` setsockopt関数が失敗した。
- ```Fatal:1256 pointer to tcpcontext is null``` tcpcontext を指すポインタがNULLです。Sanityチェックにひっかかっている。
- ```Fatal:1260 win32 fatal: gethostbyname() error:%s``` Winsockにおいて、 gethostbyname が失敗した。
- ```Fatal:1265 Memory shortage when creating tcpcontext state buffer``` vce_tcpcontext_create において、メモリが不足しているため、状態つきプロトコル用の状態管理メモリを確保できなかった。
- ```Fatal:1277 setsockopt(SO_REUSEADDR) fail:%s``` SO_REUSEADDR の設定に失敗した。


### <a name="warning"></a>Warningメッセージ

Warningメッセージは、とりあえずVCEは動作を続けられるが、今後他の資源の枯渇や処理性能の低下を招く可能性がある場合に出力されます。

- ```Warning:4000 freeing null pointer in %s``` ヌルポインタをfree しようとしている。
- ```Warning:4001 freeing an out-of-bound element in %s address:%p master-address:%p``` 解放しようとしている要素は、配列のメモリ領域の外側に位置している。
- ```Warning:4002 freeing an oddly-aligned element in %s address:%p master-address:%p sizeof:%u``` 解放しようとしている要素は、配列の要素でない別なバッファへのポインタです。
- ```Warning:4003 freeing an out-of-bound element in %s address:%p master-address:%p sizeof:%u``` 解放しようとしている要素は、配列のメモリ領域の外側に位置している。
- ```Warning:4100 tcp: only %d connections are usable``` VCEのコネクション数制限にひっかかるため、表示の本数しか利用できません。
- ```Warning:4101 tcp: accept() error. os_errno:%s port:%d``` accept()エラー。
- ```Warning:4102 tcp: conn_alloc fail no more accept. max:%d port:%d``` VCEが管理できるコネクションの数の最大に達しているため、これ以上TCPコネクションを追加(accept)できない。
- ```Warning:4103 tcp: acceptwatcher fail fd:%d``` acceptwatcher として指定されている関数がエラーを返した。
- ```Warning:4104 select() returns %d: %s``` select()が不正な値を返した。
- ```Warning:4105 connection timeout. fd:%d sec:%d``` コネクションが、クライアントの調子がわるいせいでタイムアウトしてしまった。タイムアウトの値は、vce_tcpcontext_create 関数の呼びだしの時点で指定されている。
- ```Warning:4215 winsock select() returns SOCKET_ERROR, and WSAGetLastError:%d``` Winsockにおいて select がエラーコードを返している。
- ```Warning:4214 re-freeing an element in %s address:%p```  同じ要素を2回解放しようとしている。アプリケーションが2回free_array_object を呼びだした可能性が高い。
- ```Warning:4225 vce_tcpcontext_create: reached max connection num %d```	tcpコンテキストに設定された最大接続数に到達してしまった。
- ```Warning:4300 vce_conn_io: conn does not have parser function. use vce_tcpcontext_set_conn_parser``` TCPコネクション conn が、パーサを持っていない。vce_tcpcontext_set_conn_parser を用いてパーサを設定しないとデータ入力に対する処理ができない。


### <a name="bug"></a>Bugメッセージの一覧

Bugメッセージは、VCE自体のバグが疑われる内部エラーです。

- ```Bug:7000 blank-list stack overflow: %s``` 配列の空きリストの管理異常。
- ```Bug:7002 use flag is 0! in %s address:%p``` vce_show_array_usage 関数の配列 sanity チェック時のエラー
- ```Bug:7003 usenum doesn't match in %s stack:%d link_inuse:%d``` 使用中カウントの数が、スタックが実際に伸びている長さと異なる。
- ```Bug:7010 tcp: nobuf?``` TCP用の空きバッファが、空いてるはずが、不足している。
- ```Bug:7011 tcp: nomem?``` TCP用の空きメモリが、確保されてるはずが、不足している。
- ```Bug:7109 state buffer is full.(accept)```	コネクションは一杯でないのに、状態管理バッファだけ一杯になっている。あきらかに、VCEのバグです。
- ```Bug:7112 connect: statebuf shortage```	  vce_tcpcontext_connect するときに、状態管理バッファだけ一杯になっている。これはVCEのバグです。

### <a name="note"></a>Noteメッセージの一覧

Noteメッセージは、VCEを verbose モードに設定したときだけ出力される。
VCE が Fatal や Warning のメッセージを出力しているときに、それらに対してデバッグしたいときや、VCE の動作を詳細にログしたいときに verbose モードに設定して Noteメッセージを出力させ、デバッグに役立てることができる。

- ```Note:10001 NOOP PROTOCOL: %d bytes from conn_t. serial:%d``` NOOP プロトコルでデータを受信した。
- ```Note:10002 DUMP PROTOCOL: %d bytes from conn_t. serial:%d``` DUMP プロトコルでデータを受信した。
- ```Note:10200 new connection fd:%d I:%d sbuflen:%d``` 新規コネクションをacceptした
- ```Note:10201 non blocking connect().``` コネクションをnon blocking に設定した
- ```Note:10202 connect ok on %d``` connect()が成功した
- ```Note:10220 malloc(%u) returns %p```malloc が値を返した
- ```Note:10221 free(%p)``` freeした
- ```Note:10310 init_array OK index:%d bufmaster:%p size:%u num:%d name:%s``` 配列を初期化した。
- ```Note:10320 conn_t detected EOF on fd %d``` TCPにおいて read が 0 を返した
- ```Note:10321 conn_t detected read error on fd %d``` TCPにおいて read が -1 を返した
- ```Note:10322 conn_t detected write error on fd %d (%s)``` TCPにおいて write が-1 を返した。errno の値を表示。
- ```Note:10323 conn_t detected encryption negotiation error on fd %d error code:%d``` 暗号化セッションの初期化ネゴシエーションに失敗、セッション成立せず
- ```Note:10326 conn_t detected protocol error on fd %d error code: %d``` プロトコル関数(vce_protocol_parser_bin16など)がエラーコード(負)を返した
- ```Note:10342 allocated state buffer for conn.```	  コネクション(仮想回路ではない)に対して状態管理バッファを割りあてた。
- ```Note:10345 vce_tcpcontext_create could allocate state buffer.``` vce_tcpcontext_create 関数は、無事に状態管理バッファをわりあてることができた。
- ```Note:10347 freed state buffer for conn``` 状態管理バッファを解放できた。
- ```Note:10400: vce: finalized``` VCEが正常に終了した。 vce_finalize 関数が成功すると出力される。

