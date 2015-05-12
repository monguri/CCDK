# gen.rb プロトコルジェネレータ リファレンス

gen.rb は、VCE用の、プロトコル処理用関数自動生成器です。
VCE 上の RPC を簡単に実現することができます。

gen.rb は、簡単な書式のプロトコル定義ファイルを読みこみ、Win32/UNIXでコンパイル可能なC言語のソースコードと、Rubyから利用可能なRubyのソースコードを出力します。ネットワークバイトオーダに対応しているため、異なるプロセッサ、言語間で通信が可能です。

## もくじ
- gen.rb コマンド詳細説明
  - <a href="#basic">基本的な考えかた</a>
  - <a href="#commandline">コマンドラインオプション</a>
  - <a href="#output">出力ファイル名</a>

- プロトコル定義ファイル
  - <a href="#infile">入力ファイル形式</a>
  - <a href="#comment">コメント</a>
  - <a href="#commands">指示行(ディレクティブ)</a>

- 出力コードの機能
  - <a href="#count">コマンド回数カウント</a>
  - <a href="#version">バージョン管理</a>
  - <a href="#antihack">不正クライアント対策</a>

  
## gen.rb コマンド詳細説明

### <a name="basic"></a>基本的な考えかた

gen.rb では、関数呼びだしのリモート化(RPC)のために必要なスタブコードを出力します。
つまり、リモート化される関数の実体をこのスタブファイルで定義すると同時に、 
リモートから呼びだされる関数を実際に呼びだすスイッチ関数(ディスパッチ関数)も定義します。

TCPcontextにおいては、

1. TCPコネクションからのデータ入力
2. パーサによるレコード分割
3. 各レコードごとに呼びだされるコールバック関数呼びだし

以上の3段階のプロトコル処理が行なわれますが、 生成されるスイッチ関数は、
レコードごとに呼びだされるコールバック関数に対応します。
gen.rb を用いることによって、ソケットの中を流れるデータをバイト単位で処理したりといった繁雑でバグを含みやすいコーディングを一切せずに、
通信アプリケーションを開発することができます。
また、 C言語によるサーバとRubyによるクライアントとが透過的に通信できるなど、
マルチプラットフォーム環境での通信プログラミングを容易にします。

### <h3><a name="commandline"></a>コマンドラインオプション

コマンドラインに引数を指定することによって、 プロトコル定義ファイルの内容を上書きすることができます。
プロトコル定義ファイル名はかならず必要です。


~~~
　ruby gen.rb [オプション] プロトコル定義ファイル名
~~~

オプションは以下の通りです。

~~~
　--protocolname NAME            
　--serverconnection conn|circ
~~~
　　

以上のオプションは、プロトコル定義ファイルに書けるものと同じで、オプションで指定した場合は定義ファイルの記述を上書きします。


~~~
　--noc  C言語のスタブファイルを出力しない
　--nocpp C++言語のスタブファイルを出力しない
　--noruby  Rubyのスタブファイルを出力しない</pre>
~~~
　　
以上のオプションは、引数をとらず、gen.rb の動作を設定します。


~~~
  --nocli クライアントファイルを出力しない
  --nosv  サーバファイルを出力しない    
　--identifier STRING</pre>
~~~
　　
プロトコル定義ファイルの関数を解釈する識別子を、デフォルトの"="から指定した文字列に変更します。

~~~
　--func_counter_type TYPE</pre>
~~~
　　
コールバック関数の呼びだし回数カウンタの型を変更します。


~~~
　--use_const
~~~
　　
一部の関数プロトタイプにconst修飾を追加します。

### <a name="output"></a>出力ファイル名

gen.rb は正常終了すると、

~~~
プロトコル名_sv.c      C言語のソースファイル、サーバ用
プロトコル名_cli.c     C言語のソースファイル、クライアント用
プロトコル名_sv.cpp    C++言語のソースファイル、サーバ用
プロトコル名_cli.cpp   C++言語のソースファイル、クライアント用
プロトコル名_sv.h      C/C++言語のヘッダファイル
プロトコル名_cli.h     C/C++言語のヘッダファイル
プロトコル名_sv.rb     Rubyのソースファイル、サーバ用
プロトコル名_cli.rb    Rubyのソースファイル、クライアント用
~~~

以上の8つのファイルを出力します。


- C言語のサーバを開発する場合に使うファイル
```プロトコル名_sv.c``` をコンパイル/リンクし、 受信用関数を定義するソースファイルと送信関数を使用するすべてのソースファイルにおいて、
```プロトコル名_sv.h``` をincludeします。
また受信用関数のほかにも、 ```プロトコル名_sv_sender``` 関数と、 ```プロトコル名_sv_recv_error_callback``` 関数、
```プロトコル名_toolong_recv_warning``` 関数の３つを定義しなければなりません。
最後に、定義したプロトコルを使用する TCPcontextに対して、 ```プロトコル名_sv_pcallback ``` コールバック関数を設定します。

これらの関数の詳細については、[gen.rb-C出力リファレンス](genref_ja.md)</a>をご覧ください。

- C言語のクライアントを開発する場合に使うファイル
```プロトコル名_cli.c``` をコンパイル/リンクし、 受信用関数を定義するソースファイルと送信関数を使用するすべてのソースファイルにおいて、
```プロトコル名_cli.h``` を include します。
また受信用関数のほかに、 ```プロトコル名_cli_sender``` 関数と、 ```プロトコル名_cli_recv_error_callback```
関数のふたつを定義しなければなりません。
最後に、定義したプロトコルを使用する TCPcontextに対して、 ```プロトコル名_cli_pcallback``` コールバック関数を設定します。

これらの関数の詳細については、[gen.rb-C出力リファレンス](genref.md)</a>をご覧ください。

- C++を使って開発をする場合
C言語の場合と同じ問題ありませんが、拡張子がcppのファイルを利用することもできます。

- Rubyのサーバを開発する場合
アプリケーションソースから ```プロトコル名_sv.rb``` を require します。
そのソースにおいて、 ```プロトコル名_sv_sender(_co,	data )```  メソッドと
```プロトコル名_sv_recv_error_callback(_co, ecode )``` メソッドと
```プロトコル名_toolong_recv_warning(_co, proto_id, length)``` メソッドの中身を定義します。
さらに、 TCPcontextのインスタンスに対して ```set_[conn|circ]_parser``` メソッドを 呼びだすときに、
第二引数のコールバックProcとして ```$プロトコル名_sv_proc``` を指定します。
このProcインスタンスは、レコードを受信したときに処理のために呼びだされる
Proc オブジェクトであり、```プロトコル名_sv.rb``` で定義されているものです。

- Rubyのクライアントを開発する場合
アプリケーションソースから ```プロトコル名_cli.rb``` を require します。
そのソースにおいて、 ```プロトコル名_cli_sender(_co, data )``` メソッドと
```プロトコル名_cli_recv_error_callback(_co, ecode )``` メソッドの中身を定義します。　
さらに、 TCPcontextのインスタンスに対して set_conn_parserメソッドを 呼びだすときに、
第二引数のコールバックProcとして、 ```$プロトコル名_cli_proc``` 	を指定します。
このProcインスタンスは、レコードを受信したときに処理のために呼びだされる
Proc オブジェクトであり、```プロトコル名_cli.rb``` で定義されているものです。

## プロトコル定義ファイル

### <a name="infile"></a>入力ファイル形式

入力ファイルの形式はHTML,ASCII TEXT,など何でもかまいません。
行頭が '=' ではじまる行は、コマンド行として解釈されます。

この特徴を利用すれば、HTMLでプロトコルの説明を書きつつ、同時に コマンド行を適宜挿入して gen.rb
のプロトコル定義ファイルとしても使えるようにもできます。


gen.rb は入力ファイルを行ごとにパースし、行頭に '=' があると、 '=' に続くコマンドと引数を取りだし、コマンドに応じた処理をおこないます。

'='の後ろには、スペース文字などがいくつ続いてもひとつの空白文字として認識されます。
また、どの行も、 行末にバックスラッシュを書くことで、 複数の行にまたがることができます。
= の行は1行で書く必要があるため、 複数行にまたがってコマンド定義をしたい場合は

```=s2c 100 login ( int id, \
    char password[100] ) ```

という風になります。

### <a name="comment"></a>コメント

gen.rb の入力ファイルにおいて、'#' 記号の後ろに書かれている すべてのテキストは無視されます。

### <a name="commands"></a>指示行(ディレクティブ)

行頭に'='がある行はコマンド行(指示行)と呼ばれ、コマンド文字列が続きます。 以下は、コマンド一覧です。

- ``` protocolname NAME```

  プロトコル名を指定します。
プロトコル名は、関数名やファイル名など随所に使用されるので、 C言語の識別子として正しいような文字列を使用すると問題がおこりません。
また、プロトコル関数であることをわかりやすくするために、 "proto"などと いう接尾語をつけるとよいでしょう。
デフォルトでは、defaultproto となっています。例:  ```=protocolname ssproto``` 


- ```serverconnection CONNECTION_TYPE```

  サーバが使用するコネクションの種類を指定します。CCDKでは常にconnを指定します。 ```=serverconnection conn```

- ```version NUMBER```

  プロトコルのバージョンを指定します。 NUMBERには整数値を指定することができます。
ここで指定したバージョン番号は、 ```int someproto_get_version( int *subv) ``` 関数の返り値として得ることができます。 <a href="#version">バージョン管理</a> を参照。

- ```idmax NUMBER```

  プロトコルの関数ID の最大値を設定します。
  この値が255以下の場合、 関数を識別するための内部データ構造は1バイトになり、
256以上65535以下なら2バイトになり、65536以上なら4バイトになります。
できるだけトラフィックを節約するためにも、この値は小さいほどよいでしょう。
デフォルトでは 255となっています。 c2s や s2c ディレクティブにおいて ID の値を idmax よりも大きくするとエラーとなります。


- ```define IDENTIFIER EXPRESSION```
  マクロを定義します。現在はCのみ対応。
``` =define TEST 1 ```  のように使用します。 これは、関数の引数で、配列の添字の定義に主に使用する事を目的とされている為、
``` =define TEST_A(x) (x+1) ``` のような引数付きマクロなど、複雑な定義は出来ない。
なお、これを定義すると ssproto_sv_h と ssproto_cli.h に ```#define SSPROTO_IDENTIFIER EXPRESSION```
のような名前でマクロが定義されます。
プロトコルでよく使用されるエラーコードやサイズ定数などは、この define 機能をつかって記述しておくと、
クライアントとサーバで定数定義ファイルを共有することができて開発効率が向上します。

- ```include FILENAME```
  指定したファイルを詠み込み、その位置に挿入します。
共通のマクロを定義したファイルを読み込む場合に利用できます。
例: ```=include "common.txt" ```

- ```static IDENTIFIER EXPRESSION```

  マクロを定義します。define と同様、引数付きマクロなど、複雑な定義はできない。
主に include するファイルで共通マクロを定義する場合に使用することを目的とされている。
xxproto_sv.h と xxproto_cli.hには define と同様、 ```#define xx_IDENTIFIER EXPRESSION ```
と定義されます。define との違いは、 xxが static を記述したファイル名になる点です。

  common.txtにおいて
~~~
=static ID_LEN 32
~~~
とし、testproto.txtにおいて
~~~
=protocolname testproto
=include "common.txt"
=define MAX_LEN 64          
~~~
とした場合、testproto_sv.h と testproto_cli.h には、
~~~
#define COMMON_ID_LEN 32
#define TESTPROTO_MAX_LEN 64
~~~
と定義されます。

- ```ifdef IDENTIFIER FUNCNAME```

  マクロを定義により処理するプロトコルを決めます。

  ``` =ifdef _DEBUG ping ```

  のようにするとプリプロセッサで_DEBUGが定義されているときのみクライアントのpingの送信関数およびサーバのping受信関数が動作します。


- ```enum ENUMTYPE IDENTIFIER [EXPRESSION]```

  define と同様、 C言語の enum を定義します。
~~~
=enum HOGE INVALID_ARGUMENT -999
=enum HOGE NOT_SUPPORTED
~~~

  のように定義すると、プロトコル名が GAMEPROTO の場合は、
~~~
typedef enum {
    GAMEPROTO_INVALID_ARGUMENT=-999,
    GAMEPROTO_NOT_SUPPORTED,
} GAMEPROTO_HOGE;
~~~

  というように、GAMEPROTO_HOGE という型をもつ enum がひとつ定義されます。
ENUMTYPE を複数にすることもでき、その場合は複数の enum 定義が 出力されます。
EXPRESSION のところに数値がきたとき (-?[0-9]+)は、その値が、enum の定義値として採用されます。 
数値を指定しないときは、デフォルト値をもつ enum として出力されます。


- ```struct IDENTIFIER{ ARGDECL } ```

  define と同様、C言語の構造体を定義します。
~~~
=struct hoge { int x, int y }
~~~
のように定義すると、
~~~
typedef struct _hoge {
    int x,
    int y,
} hoge;
~~~
というように、構造体が定義されます。
<b>ARGDECL</b>には、メンバを定義します。
次項の引数のタイプと同じものや構造体を使用できます。</p>
~~~
=struct hoge { int a, int b[20], char c[21], string d[22], stringarray e[23][24] }
~~~
と定義すると、gen.rbによって以下の定義文が生成されます。
~~~
typedef struct _hoge {
    int a;
    int b[20];
    int b_len;
    char c[21];
    int c_len;
    char d[22];
    char e[23][24];
    int e_len;
    char *e_p;
    int e_i;
} hoge;
~~~

- ```c2s ID FUNCNAME ( ARGDECL )``` または ```s2c ID FUNCNAME ( ARGDECL )```

  <B>c2s</B>または<B>s2c</B>は、gen.rb が出力する関数を定義します。 c2s,s2cは、1ファイル中に合計idmax個まで書けます。
c2s は "client to server" の略で、クライアント側に送信関数を、 サーバ側に受信関数を定義します。
つまり、 c2s ディレクティブを1個書くと、 ```プロトコル名_cli.c```に送信関数が1個、
```プロトコル名_sv.c``` では受信関数呼びだしが1個(定義ではない) 追加されます。
呼びだしが1個という意味は、 受信して実際に何をするかはアプリケーションが定義するので その関数の呼びだしだけを行なうという意味です。
<B>ID</B>には、idmax以下の、メッセージIDを指定します。
メッセージIDとは、クライアントとサーバが関数の特定のために使うIDであり、 s2cとc2s合計でidmax種類までの関数をやりとりできることになります。
このIDを手動で設定する理由は、新しい関数を後から追加しても過去のプロトコルと互換性を保つためです。
なので、 将来関数を追加することがわかっている場合は、IDを飛び番号にするなどの 工夫をしておくとよいでしょう。

  <B>FUNCNAME</B>には、関数名を指定します。
関数名は、C言語の識別子として正しい文字列を指定しなければなりません。

  <B>ARGDECL</B>には、それぞれの関数の引数列を定義します。
引数には以下のタイプがあります。
~~~
int i       : int型整数
uint i       : unsigned int型整数
short i     : short型整数
ushort i    : unsigned short型整数
char i      : char 型整数
uchar i	     : unsigned char型整数
int64 i	     : int64型整数
float i	     : float型浮動小数点数（環境によっては正常に通信できない）
int a[100]  : int型配列
short a[100] : short 型配列
char a[100]  : char 型配列
float a[100] : float 型配列（環境によっては正常に通信できない）
string a[100]: 文字列
stringarray a[100][100] : 文字列の配列 [文字列の最大数][各文字列の最大文字数]
~~~

  配列を指定する場合は、サイズを必ず指定しなければなりません。
これは、gen.rb の出力コードの中で確保するワーク領域がバッファオーバーフローすることを確実に防ぐために必要だからです。
ここで注意が必要なのは、そのワーク領域はスタック上に取られるため、
数千バイトのオーダならまったく問題ありませんが、それを超える極端に大きな値を指定するとスタックが足りなくなることです。

  配列のサイズは「最大サイズ」なので、大きくても実際にはそれだけの量は通信されません。
たとえば char a[100] の最初の10バイトしか使われなかった場合は、10バイトしか送信しません。
また、配列を引数に指定した場合は、配列の要素数をあらわす int型の引数が、長さ渡し用に追加されます。
その名前は、変数名_len となります。

  以下は、設定と出力される関数の対応の例です。 someproto はプロトコル名です。
~~~
=s2c 100 login( int id, char passwd[20] )
~~~
この定義により、Cでは以下が、
~~~
int someproto_login_send( conn_t _c, int id, char *passwd, int passwd_len )
~~~
Rubyでは以下が生成されます。
~~~
someproto_login_send( Conn c, Fixnum id, String passwd )
~~~
次にの定義により
~~~
=c2s 101 sendbig( int bigdata[1000] )
~~~
Cでは以下が
~~~
int someproto_sendbig_send( conn_t _c, int *bigdata, int bigdata_len )
~~~
Rubyでは以下が生成されます。
~~~
someproto_sendbig_send( Conn c, Array ia )
~~~
配列の最大サイズはバイト数ではなく、要素数であることに注意が必要です。

- ```=sh Code``` または ```=ch Code```

  <B>sh</B>はサーバ側のヘッダーファイルに任意のコードを追加します。
<B>ch</B>はクライアント側のヘッダーファイルに任意のコードを追加します。
例えばプロトコルファイル(testproto.txt)を次のように書いた場合、
~~~
=sh #include "server.h"
=sh extern Server * sv;
=sh extern Server2 sv2;
=ch #include "client.h"
=ch extern Client * cli;
=ch extern Client2 cli2;
~~~
以下のように変換されます。まず testproto_sv.hに　
~~~
#ifndef _TESTPROTO_SV_H_
#define _TESTPROTO_SV_H_
#include "vce.h"
#include "server.h"
extern Server * sv;
extern Server2 sv2;
#undef TESTPROTO_MAX_CONNECTION
#define TESTPROTO_MAX_CONNECTION 1024
....
~~~
次に testproto_cli.hに
~~~
#ifndef _TESTPROTO_CLI_H_
#define _TESTPROTO_CLI_H_
#include "vce.h"
#include "client.h"
extern Client * cli;
extern Client2 cli2;
#ifdef __cplusplus
extern "C" {
....
~~~

        
## 出力コードの機能
		
### <a name="count"></a>関数回数カウント

gen.rb は、 プロトコル設定に記述されている各関数の送信と受信の回数を数える関数を定義します。
関数名は、クライアントからサーバに "login" という関数を送る場合は、クライアント側に、C言語では以下の関数が
~~~
VCEI64 someproto_get_login_send_count(void)
~~~
Rubyでは以下が生成されます。
~~~
someproto_get_login_send_count()
~~~
またサーバ側には、C言語では以下の関数が
~~~
VCEI64 someproto_get_login_recv_count(void)
~~~
Rubyでは以下が生成されます。
~~~
someproto_get_login_recv_count()
~~~
返り値は VCEI64 がデフォルトですが、```--func_counter_type``` 引数や、```=func_counter_type ``` ディレクティブで型を変更できます。

### <a name="version"></a>バージョン管理

プロトコルは開発中にたえず修正していくものなので、 バージョン管理が不可欠です。
gen.rb では、 プログラマが指定するプロトコルのバージョン番号と、プロトコル定義ファイルの内容をhashして得られる、厳密な「内容の指紋」として使えるサブバージョン番号の2つの値を使ってプロトコルのバージョンを管理する方法を提案します。

バージョン番号は、 ```=version``` ディレクティブで指定します。
これをメジャーバージョンと呼びます。

以下、各環境でバージョン番号を得る方法を列挙します。

Cサーバでは
~~~
unsigned int someproto_sv_get_version(unsigned int *subv )
~~~
Cクライアントでは
~~~
unsigned int someproto_cli_get_version(unsigned int *subv )
~~~
Rubyサーバでは
~~~
someproto_sv_get_version()
~~~
Rubyクライアントでは
~~~
someproto_cli_get_version()
~~~

これらの関数は、返り値として、プロトコル定義ファイル中で指定した メジャー番号を返し、subv のポインタが指すunsigned int値に対して、 サブバージョンを返します返します。
subv には NULL を指定して、無視させることもできます。

定義ファイル中に、 ```=version``` がない場合は、 この関数はメジャー番号として常に 0xffffffff を返します。

Ruby版メソッドは、常に2要素の配列を返し、0番目の要素がメジャーバージョンで、 1番目の要素がサブバージョンです。


【使用例】

~~~
// version : メジャーバージョン, hashver : サブバージョン        
unsigned int hashver;
unsigned int version = someproto_sv_get_version(&hashver);  
~~~
        

### <a name="antihack"></a>不正クライアント

ユーザ自身がチートまたはサービス不可攻撃目的で不正な通信をする場合があります。
特にプログラムがクラックされ、負荷の高いプロトコルまで解析され、それが連続で発行されると
サーバの過負荷やクラッシュに繋がります(DoS攻撃)。
まず、通信バッファや帯域を圧迫させないためには異常に長いプロトコルは早い段階で破棄/切断する必要があります。
gen.rbのサーバヘッダファイルにはすべてのプロトコルの中から一番長いものが
```プロトコル名_MAX_RECV_RECORD_LENGTH``` として定義されています。
これを ```vce_tcpcontext_protocol_set_maxlength``` 関数を使い設定することで異常に長いプロトコルをはじく事ができます。

また、プロトコル毎に予期しない長さのデータが受信されたら ```プロトコル名_toolong_recv_warning```
関数が呼び出されます。

