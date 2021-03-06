# VCE FAQ

- <B>1000本以上の TCP コネクションを張ることができない</B>

  vce_initialize 関数を使って VCE を初期化すると、 最大接続数を 1000 として初期化します。
  vce_initialize_limited 関数を使って、 vce_limit_t の max_conn メンバの値を大きくして初期化してください。

- <B>vce_initialize するとメモリが数MB も確保されてしまう</B>

   vce_initialize 関数のかわりにvce_initialize_limited 関数を使用すれば、限界までメモリ使用量を減らすことができます。
  使用上の注意に関しては、 vce_initialize_limited 関数のリファレンスを参照してください。
	  
- <B>どうしても parser が呼びだされません。</B>

  ソースをどう見ても、おかしいところはないのに、 parser が呼びだされない問題です。
  考えられる原因はいくつかあります。

  - tcpcontext_connect の呼びだしとパーサ設定の順序の問題
    vce_tcpcontext_connect の後に vce_tcpcontext_set_conn_parser など、tcpcontext_t の設定をする関数を呼びだしている場合が多いです。vce_tcpcontext_connect など、新規コネクションを割りあてるような処理は、割りあて時点で tcpcontext_t の設定をコピーして使うためです。
    詳しくは、 vce_tcpcontext_connect, vce_tcpcontext_create のマニュアルを参照してください。

  - gen.rb を使う場合で、かつp2pアプリケーションの場合
    同じプログラムがクライアントにもサーバにもなるp2pアプリケーションでは、ひとつのプロトコル設定ファイルでそのプロトコルを共有する場合があります。
    この場合、 ```=c2s``` と ```=s2c``` を間違えて反対に書くと、プロトコル関数を呼びだしているのに相手に到達しなくなります。

    ~~~
    =c2s hello ( char name[100] )
    =s2c hello_reply ( char answer[100] )
    ~~~

    本来上のようにしたかったところを、

    ~~~
    =s2c hello ( char name[100] )
    =c2s hello_reply ( char answer[100] )
    ~~~

    としてしまった場合です。
    プロトコルファイルを再度チェックしてください。

- <B>vce_heartbeat が永久に再帰してしまう</B>

  vce_heartbeat から呼びだされる callback 関数(parser,acceptwatcher,closewatcher など) の中で vce_heartbeat
  を呼びだしています。呼びださないようなコードに変更してください。

- <B>メモリリーク検出プログラムで、メモリリークが発生しています</B>
  vce_tcpcontext_cleanup と、 vce_finalize を呼び出していない可能性があります。
  これらは tcpcontext_t や VCE 自体が使用しているメモリを解放します。
  vce_finalize 関数は tcpcontext_t のメモリを解放しないので、
  注意してください。(ちゃんと両方呼びだす必要があります。)
  このほかにも、 cleanup 関数を呼びだす必要のあるものがあります。

- <B>VCEはスレッドセーフか？</B>
  いいえ、VCEはスレッドセーフではありません。

- <B>クライアントかサーバの片方でVCEを使わないことはできるか？</B>

  はい、クライアントだけVCEを使い、サーバは通常のプログラムを使うとか、その逆も可能です。

- <B>vce_tcpcontext_create 関数が EINVALを返します</B>

  vce_initialize()関数を呼びだしていないかもしれません。

- <B>コネクションを閉じたのに、すぐ解放されません</B>

  vce_conn_close 関数を使ってコネクションを閉じる場合で、閉じたコネクションの送信バッファにデータが残っている場合、
  VCEはデフォルトのタイムアウト時間( vce_tcpcontext_create 関数の引数)まで、送信バッファに残っているデータを送ろうと努力します。

  クライアント側プログラムなど、そのような努力が必要ない場合は、
  vce_conn_set_timeout を用いて、当該コネクションだけタイムアウト値をゼロまたは短い値に設定して、
  迅速にコネクションが解放されるようにできます。
  詳しくは vce_conn_close 関数のリファレンスを参照してください。
  なお、ふたたび connect/accept して作成されたコネクションのタイムアウト時間は、通常の設定に戻っています。

- <B>1回の heartbeat でコールバック関数が1回しか呼ばれません</B>

  デフォルトでは1回ですが、 vce_tcpcontext_set_conn_call_parser_per_heartbeat 関数を用意して、この回数を調整できるようにしています。


- <B>vce_heartbeat を複数回呼ぶほうが性能が良くなるのですが</B>

  vce_tcpcontext_set_conn_call_parser_per_heartbeat を目一杯大きな値(10000とか)にしても、
  1回の vce_heartbeat よりも何回も呼びだすほうがコールバック呼びだしの性能がよくなる場合があります。
  これは VCE が、1回の vce_heartbeat で、1本のコネクションあたり32KB しか、ネットワークから取ってこないためです。
  この仕様はサーバプログラムでは各コネクションの負荷を均一にするほうがよいという配慮からですが、
  バルク転送をする場合や細かいクエリが多すぎる場合には、この動作影響して、限界パフォーマンスが低下することがあります。
  このような場合は、 vce_heartbeat を2〜3回連続して呼びだしてもかまいません。

- <B>"bind error" (VCE_EBIND) とは何ですか？</B>

  UNIX(Linux)において TCP/IP を使ったサーバを起動しておくためには、0番から65535番までの65536個のTCPポートを、サーバのプロセスが占有する必要があります。

  この「占有する」という動作はUNIXにおいては "bind" というシステムコールを発行することによって行ないます。
  VCEにおいては、 "bind" は vce_tcpcontext_create 関数を呼びだした時点で行なわれます。

  そのため、たとえば 20000番のポートを使うサーバプロセスがすでに動作している場合は、
  20000番を使うような別のサーバプロセスを起動しようとすると、
  "bind" がすでにされているためできないという意味の VCE_EBIND エラーが vce_tcpcontext_create 関数によって返されます。
  この場合は、すでに起動しているサーバを止めるなどして問題に対処する必要があります。

- <B>クライアントから接続したときの成功判定の方法がわかりません</B>

  [クライアントからの接続について](connect_ja.md) を参照してください。

- <B>VCEを使ってファイル転送プログラムやストリーミングアプリケーションを作る方法を教えてください。</B>

  これはVCEに限らず言えることですが、HTTPのようにサーバが一方的にデータを送りつけるのではなく、クライアント主導のデータ要求をするのが望ましいです。
  クライアント主導とは、クライアントが「データを1KB分欲しい」という意味のメッセージを送り、サーバはそれに対して素直に1KB分のデータを送りかえすように実装することです。
  クライアントはこのメッセージを1個送信するごとにカウンターを1だけインクリメントし、データが返ってくるごとに1だけデクリメントします。
  そしてこのカウンターの値が4以下に保たれるように要求送信の頻度を調整すれば、ネットワーク上には最大で4KB分しか乗らないことになります。
  こうすることで、ファイル転送のような、サーバのメモリに負荷がかかりやすいアプリケーションのサーバ負荷を大幅に軽減するとともに、サーバ側の帯域をまんべんなく利用することができるようになります。

- <B>VCEI64 型とは何ですか？</B>

  32ビットを越えるサイズの整数値を与えたい/返したいときに、Linux や MacOS Xでは、 long long 型を使いますが、Win32 では __int64 型を使います。
  このような違いを吸収するために、 VCEI64 型を定義しています。

- <B>VCE が依存しているライブラリは何ですか。</B>
  - Windows: WSOCK2_32.DLL
  - Linux, MacOS X : 特にありません

- <B>VCEの初期化のときにメモリが足りないと言われます。</B>
  vce_init_limit_t 関数を使って vce_limit_t構造体を初期化していますか？




