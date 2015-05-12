# gen.rb-C出力リファレンス

gen.rbがC/C++用に出力する関数を詳しく説明します。

以下の説明では、```PROTONAME```はプロトコル定義ファイルで設定したプロトコル名を指します。
関数名に```sv```と付くものはサーバ用の関数で、
同様に```cli```が付くものはクライアント用の関数です。

## アプリケーション側で定義し、コンパイル、リンクすることが必要な関数

- ```int PROTONAME_sv_sender( conn_t _c, char *data, int len )```
  レコードをひとつ送信するための関数です。

  引数:
  ~~~
  conn_t _c : このコネクションに対して関数を送信します。
  char *data : 送信するデータへのポインタ。gen.rbがシリアライズした結果です。
  int len : 送信するデータの長さ（バイト）
  ~~~
  実際に送信したデータの長さを返してください。負の値を返すと、エラー扱いとなり、コネクションが切断されます。

  以下は、65535バイトまで送れる送信レコード作成関数(unparser_bin16)で送る例です。
  ~~~
  int echoproto_sv_sender( conn_t _c, char *data, int len )
  {
    return vce_protocol_unparser_bin16( _c,data,len);
  }
  ~~~
  この例では、特別な処理を加えることなく、gen.rbでシリアライズされたデータをコネクションに流し込んでいます。

- ```int PROTONAME_sv_recv_error_callback( conn_t _c,int e )```
  不正なレコードを受信したときに呼ばれる関数です。

  引数:
  ~~~
  conn_t _c : 受信したコネクション
  int e : エラーコード
  ~~~
  returnで負の値を返すと、コネクションは切断されます。この関数の内容を定義することで、エラーの内容に応じて、すぐには切断しないような処理や、任意のログやエラー時の処理を実装することができます。
  以下の例では、エラーの番号を標準出力に表示して、そのまま切断させています。

  ~~~
  int echoproto_sv_recv_error_callback( conn_t _c,int e )
  {
    vce_errout( "cannot receive data err=%d(%s)\n", e, STRERR );
    return -1;
  }
  ~~~

- ```int PROTONAME_toolong_recv_warning( conn_t c,int proto_id,int length)```

  プロトコルで指定された可能な最大の長さよりも長いレコードを受信したときに呼ばれる関数です。レコードが異常に長い場合は、アプリケーションやVCEのバグだけはなく、攻撃を受けている可能性があります。

  引数:
  ~~~
  conn_t _c : 受信したコネクション<br>
  int proto_id : プロトコルID<br>
  int length : 受信したレコード長</p>
  ~~~
  returnで負の値を返すことで、コネクションを切断することができます。

  以下の例では、特別な処理を何も行わず、切断しています。
  ~~~
  int echoproto_toolong_recv_warning( conn_t c,int proto_id,int length)
  {
    return -1;
  }
  ~~~

## アプリケーション側で設定が必要なもの

以下の関数については、gen.rbが生成する関数のアドレスを、
VCEの関数を呼び出してVCEに知らせる必要があります。

- ```PROTONAME_sv_pcallback```
  ひとつのレコードの中身を解析して、必要なRPCを呼び出すためのディスパッチ関数です。
以下の例では、 vce_tcpcontext_set_conn_parser関数を使って tcpcontext_tに設定しています。
~~~
vce_tcpcontext_set_conn_parser( tcpctx,
                                vce_protocol_parser_bin16,
                                PROTONAME_sv_pcallback );
~~~


## その他の生成される定数など

- ```PROTONAME_MAX_CONNECTION```
  サーバ側で接続を受け入れる最大数です。
- ```PROTONAME_MAX_RECV_RECORD_LENGTH```
  サーバ側で受信するレコードの最大長が定義されます。この値は、プロトコル定義ファイルの関数定義の内容から計算される最初の値になります。

- ```unsigned int PROTONAME_sv_get_version(unsigned int *subv)```
  プロトコル定義ファイルのバージョンを取得します(サーバ側)。
- ```unsigned int PROTONAME_cli_get_version(unsigned int *subv)```
  プロトコル定義ファイルのバージョンを取得します(クライアント側)。
- ```VCEI64 PROTONAME_get_FUNCNAME_send_count(void)```
  FUNCNAMEは、各関数の名前です。各関数を送信した回数を取得します。
- ```VCEI64 PROTONAME_get_FUNCNAME_recv_count(void)```
  FUNCNAMEは、各関数の名前です。各関数を受信した回数を取得します。
- ```void PROTONAME_FUNCNAME_send_debugprint(int on_off)```
  関数を送信するときのデバッグ表示をon/offします。
- ```void PROTONAME_FUNCNAME_recv_debugprint(int on_off)```
  関数を受信したときのデバッグ表示をon/offします。デフォルトはすべてONです。
  デバッグ出力は、GEN_DEBUG_PRINTマクロを定義したときだけコンパイルされます。
