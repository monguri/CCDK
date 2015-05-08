バックエンドサーバーの使い方
====

バックエンドサーバーは、LinuxまたはMacOS X上で動作する、
マルチプレイゲームを実装するための通信サーバーです。

リアルタイムモードとデータベースモードの2つのモードがあり、
ひとつのプロセスで両方のモードの機能を同時に提供できます。

VCEを用いて実装されており、通信のプロトコルは ssproto.txtファイルで定義されています。



## ソースコード
ソースコードは、 ```CCDK/backend``` にあります。
ビルドすると ssvと ssbenchという2つのプログラムが生成されます。

バックエンドサーバーのソースコードは全体が公開されています。
自動生成される分をのぞいた実質的なC++コードは、
コメントも入れてmain.cppとpresence.hの2つで合計約2000行の小さなものです。

現状のバージョンで実装されていない機能を追加したり、
不要な機能を削除したり自由に改変し、プロジェクトで利用してください。

またシンラ・システムでは、ゲームサーバーをスケールアウトさせる場合に、
必ずCCDKに添付されているbackendサーバーを利用する必要があるわけではありません。


## ssv 起動時のオプション

ssvを起動すると以下のような説明が表示されます。

~~~
bash$ ./ssv
Usage:
ssv realtime [OPTIONS]
ssv database [OPTIONS]
ssv realtime database [OPTIONS]
Options:
--dump-sp : dump shared projects with interval
--dump-p : dump projects with interval
--debug-protocol : abort on protocol parser error (for special debug case, dont use in production)
--maxcon=NUMBER : set max number. Absolute max is 200. Requires huge memory if maxcon gets larger.
--emulate-slow-disk=NUMBER : Enable slow disk emulation by milliseconds (sleep after each disk access) 
--channel_max=NUMBER : set max concurrent number of channel members.
--tcp_timeout=SECONDS : set TCP timeout for database and realtime connections
--enable-fsync : Use fsync() when writing a static file (not affect on Redis storage)
--redis-addr HOSTNAME : Address of the redis server.  Default is localhost
~~~

ssvは最低1個の引数が必要です。
以下はすべて有効なコマンドラインです。

```realtime``` または ```database``` は、動作モードを指定するもので、
どちらかひとつか両方を必ず指定する必要があります。

~~~
bash$ ./ssv realtime
bash$ ./ssv database
bash$ ./ssv database realtime
bash$ ./ssv database realtime --maxcon=20
bash$ ./ssv database --maxcon=20 --redis-addr 192.168.1.181
bash$ ./ssv database realtime --maxcon=20 --dump-sp --dump-p
bash$ ./ssv database realtime --emulate-slow-disk=5
bash$ ./ssv database realtime --channel_max=300 --redis
bash$ ./ssv realtime --channel_max=300
~~~

それぞれのオプションの意味は次の通りです。

* ```--dump-sp``` 一定時間ごとに、共有されているプロジェクトの一覧を表示し続けます。デバッグ用です。
* ```--dump-p``` 一定時間ごとに、バックエンドサーバーがホストしているプロジェクトの一覧を表示し続けます。デバッグ用です。
* ```--debug-protocol``` 受信したRPCの関数に関して、詳しいログを出力します。非常に膨大な量のログを生成するので、開発以外の目的で使用するのは危険です。
* ```--maxcon=NUMBER``` 最大接続数を指定します。設定限界値は200です。上限の理由は、通信に必要なメモリバッファのサイズです。(VCEが固定サイズを最初に確保するため)
* ```--emulate-slow-disk=NUMBER``` 回転式のHDDのような遅いディスクをバックエンドサーバーでエミュレートし、databaseモードのサービスに遅延を発生させます。これによってゲームの動作がどのように影響を受けるかを検証できます。
* ```--channel_max=NUMBER``` 同時にアクティブになっているチャネルの合計数の最大値を設定します。
* ```--tcp_timeout=SECONDS``` TCPのタイムアウト時間を設定します。デフォルトは10秒に設定されています。
* ```--enable-fsync``` 静的ファイルに書き込んだ後にfsync()を毎回発行します。Redisに対する操作に影響はありません。
* ```--redis-addr HOSTNAME``` Redisサーバーの位置を指定します。デフォルト値は ```localhost```です。


##ssproto.txtの修正方法


UNIX(Linux, MacOS X)では、簡単にssproto.txtの内容を変更して、新しいコマンドを追加したりできます。

以下、コマンドを追加した場合に必要な手順は以下の通りです。

1. ssproto.txtの内容を変更する。たとえば、 ```=c2s foo( int bar )``` という、クライアントから発行するコマンドを定義したとします。
2. ビルドします。 VCEのgen.rbが動作し、 ssproto_sv.cpp, ssproto_sv.h, ssproto_cli.cpp, ssproto_cli.h などが生成されます。
3. ssproto_foo_recv()関数が未定義であるというコンパイルエラーが表示されます。
4. ssproto_foo_recv()関数の実体をサーバー側に定義します。
5. ssproto_foo_send()関数をクライアント側で呼び出して動作確認を行います。

CCDKでは将来、Windowsにおいてもssproto.txtを変更した場合のビルドができるようにする予定です。

gen.rbの詳しい仕様については、VCEのドキュメントを参照してください。








