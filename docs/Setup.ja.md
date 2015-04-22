CCDK セットアップ手順
====

セットアップに必要な手順は以下の通りです。

1. gitツールを用いてCCDKレポジトリをダウンロードする。
2. RubyやPythonなどの必要な外部ツールをインストールする。
3. CCDKのサンプルプログラムの動作確認を行う。
4. LinuxやMacOS Xでの動作確認


以上の1~4では、まずWindowsだけで完結する部分を説明します。
LinuxやMacOS Xに関することは最後の5.で説明します。



###1. gitツールを用いてCCDKレポジトリをダウンロードする。

gitレポジトリの位置は以下です。

~~~
https://github.com/ShinraTech/CCDK
~~~

このレポジトリをcloneすることでCCDKの全体が取得できます。
cloneするとすべてのバージョンを含む情報が得られるので、
gitのcheckoutコマンドを使って、後でいつでも必要なバージョンを取得することができます。

gitの使用方法を詳しく知っている方は、以下の説明を飛ばして、3の外部ツールのインストールに進んでいただいてもかまいません。

gitプログラムは、WindowsやLinux,MacOS Xなど各種のOSにおいて、
コマンドラインのもの、GUIのものなど、さまざまなものが利用可能です。

CCDKは主にWindows用のツールなので、以下では、GitHub社が提供しているGitHub for Windows
を例にとって説明をします。

まず、以下のURLからGitHub for Windowsをダウンロードしてインストールします。

~~~
https://windows.github.com/
~~~

インストールに成功すると、　「すべてのプログラム」→「GitHub, Inc」→「GitHub」でプログラムを起動できます。

GitHubプログラムを起動し、画面左上にある"+"ボタンを押すと、レポジトリを追加できます。

Addは既存のディレクトリを追加、Createは新規作成、 CloneはGitHub上にあるリモートのレポジトリをダウンロードすることを意味します。
ここでは、Cloneをクリックします。

ShinraTechのチームに参加していると、以下の図のように、ShinraTechのアイコンが見えます。

![githubclone](images/github_clone_ccdk.png)

アイコンをクリックすると、CCDK, hiredis, redisのように、ShinraTechのレポジトリの一覧が表示されるので、CCDKを選択します。これでcloneが実行され、数分以内にダウンロードが完了するはずです。

ダウンロードされたレポジトリは、デフォルトでは、ユーザー名がcloudの場合、
以下の位置に配置されます。このデフォルト位置は、GitHub for Windows
のバージョンによって頻繁に変わるので、歯車アイコンから設定を開いて確認してみてください。

~~~
C:¥Users¥cloud¥Documents¥GitHub¥CCDK
~~~


###2. RubyやPythonなどの必要な外部ツールをインストールする。
CCDKは、以下の外部ツールを利用しています。
以下では、Windows版のみ説明します。Linux(UNIX)については後述します。

* Python 3.4 (3.4.1)
* Ruby 2.1 (2.1.5p273)
* VisualStudio 2013
* Redis (MSOpenTech版)
    

それぞれ、バージョン番号の末尾の番号(マイナーバージョン)が一致していなくても動作するはずですが、開発チームでテストしているのは以上のバージョンのみです。
もし、動かなかったり、どうしてもほかのバージョンで検証する必要がある場合は、
開発チームのメンバーにご相談ください。

Python 3.4は、以下のURLのものをご利用ください。 

~~~
https://www.python.org/downloads/windows/
~~~

python.exeは、通常、以下のパスにインストールされます。環境変数PATHに追加しておいてください。

~~~
C:¥python34¥python.exe
~~~

cmd.exeなどを起動して、 pythonとタイプして以下のように表示されたら成功です。
![pythoncmd](images/cmd_python.png)

Ruby 2.1は、以下からインストーラーをダウンロードできます。

~~~
http://rubyinstaller.org/downloads/
~~~

ruby.exeは、通常、以下のパスにインストールされます。環境変数PATHに追加しておいてください。

~~~
C:¥ruby21-x64¥bin¥ruby.exe
~~~

rubyについてもPythonと同様にコマンドラインでrubyとタイプして、
プロンプトが表示されたらインストール成功です。


VisualStudio 2013については、無償版でも構いません。
CCDKの開発では、　Professional 2013を利用しています。

無償版のダウンロードは、以下のマイクロソフト社のサイトが利用できます。

~~~
https://www.visualstudio.com/downloads/
~~~

Redisは、Redis公式プロジェクトから派生した、
マイクロソフト社のオープンソース版をVisualStudioでコンパイルすると、
Redis用のライブラリファイルも生成されるので、それを使います。

Redisのソースコードは、GitHub for windowsを用いてcloneした場合、

~~~
CCDK/externals/redis
~~~

にチェックアウトされています。

~~~
CCDK/externals/redis/msvs/RedisServer.sln
~~~

この位置にあるソリューションファイルを開き、全体をビルドすると、

~~~
CCDK/externals/redis/msvs/Debug/hiredis.lib
CCDK/externals/redis/msvs/Debug/redis-server.exe
~~~

などが出力されます。
これらは後でバックエンドサーバーをビルドするときに使います。
DebugとReleaseの両方をビルドしてください。


###3. CCDKのサンプルプログラムの動作確認を行う。

1台のWindowsマシンだけで動作確認ができるプログラムは、以下のものがあります。

1. 1:1スケルトンプログラム(Windows)
2. N:Nスケルトンプログラム(Windows)
3. バックエンドサーバープログラム

CCDK全体の動作確認は、大きく2つの段階に分けられます。
まず最初にビデオストリーミングを使わないテストを行い、
その動作確認ができたら、次にビデオストリーミングを使って同じプログラムをテストします。

また、バックエンドサーバーは、N:Nスケルトンプログラムを使って動作確認しますが、
Windows版と、UNIX版(LinuxまたはOS X)があります。
Linux版を用いたテストは後述します。

したがって、全体の手順としては以下のような流れになります。

1. 全体をビルドする。
2. 1:1スケルトンをビデオストリーミング無しで確認
3. N:Nスケルトンをビデオストリーミング無しで確認
4. 1:1スケルトンをビデオストリーミングありで確認
5. N:Nスケルトンをビデオストリーミングありで確認


<B>手順1, まず全体をビルドします。</B>

CCDKレポジトリのトップレベルに、CCDK.slnがあるのでそれを開きます(図)。

![ccdksln](images/ccdk_sln.png)

単純に「ビルド」を実行すると全体がコンパイルされます。
その際、DirectX ToolKitというパッケージがNuGetにより、自動的に復元(インストール)されます。

<B>手順2, 1:1スケルトンをビデオストリーミング無しで確認。</B>

試しに、one_to_oneをスタートアッププロジェクトに設定して、デバッグ実行を開始してください。

![one_to_one_run](images/one_to_one_run.png)

上の図のように、フレームカウンタが増加しつづけているウインドウが表示されたら成功です。
ウインドウを閉じるか、Qキーを押すと終了します。

<B>手順3, N:Nスケルトンをビデオストリーミング無しで確認。</B>

バックエンドサーバーを起動せずに many_to_manyを起動してみます。

![many_to_many_no_backend](images/many_to_many_run_without_backend.png)

one_to_oneに比べると、 "Ping:0"と"Channelcast:0"が増えています。
Ping:0は、バックエンドサーバーに対するPingが返ってきた回数が0回、
つまり接続できていないことを示します。 Channelcast:0も同様です。

プログラムを一旦終了して、次にバックエンドサーバーを起動します。
今はデバッグをするのが目的ではないので、デバッガ無しでbackendプロジェクトを起動します。
バックエンドサーバーのデータベース機能を有効にする場合はRedisサーバも起動する必要がありますが、CCDK.slnのデフォルトの状態ではデータベース機能は使わないように設定してあります。
Redisを使う場合については後述します。

バックエンドサーバーが起動すると、以下の図のようにコンソールが表示されてログが出力されます。
このログはVisualStudioのデバッグ出力にもコピーされます。
![realtime_backend_run](images/realtime_backend_run.png)

デバッガ付きで起動したい場合は、VisualStudioのインスタンスを増やしてください。

さらに many_to_manyプロジェクトをデバッガ無しでひとつ起動すると以下の図のようになります。
![many_to_many_run_one](images/many_to_many_run_one.png)

Pingカウンタの値が増えていきます。バックエンドサーバーとの通信が成功していることがわかります。ただし、Channelcastは0のままです。これは、Channelcastが自分自身には送信しないためです。

さらにもうひとつmany_to_manyを起動します。

![many_to_many_run_two](images/many_to_many_run_two.png)

すると、今度はChannelcastの値が毎フレーム1づつ増えていくことがわかります。
現状のmany_to_manyプログラムは、チャネル(ID=12345)に対して、
毎フレーム1個づつのchannelcastパケットを送信します。
バックエンドに接続しているプログラムが増えれば増えるほど、
その数の2乗に比例した数のchannelcastパケットを受信します。
many_to_manyを、さらにいくつか起動して、パケットの受信速度を見てみてください。



<B>手順4, 1:1スケルトンをビデオストリーミングありで確認</B>

ビデオストリーミングを試すには、CCDK/mcsディレクトリに配置されている、
MCSのパッケージが必要です。 MCSパッケージを展開する位置はどこでもかまいません。
ここではCCDK内に置かれた位置でそのまま展開します(図)。
![ccdk_mcs_content](images/ccdk_mcs_content.png)

図の9101.8という番号はMCSのビルド番号で、新しいバージョンがリリースされるたびに変わります。

展開ができたらShinraDevelopmentStation.exeを実行します。
署名をしていないプログラムを実行する際のWindowsの警告が表示されますが、実行を選択してください。このプログラムを以降では"SDS"と呼びます。

SDSは内部でPythonを使うため、Pythonのセットアップが必要です。

実行すると以下のように空のウインドウが表示されます。
![sds_startup](images/sds_empty.png)

SDSはゲームプログラムのパッケージを作ったり使うためのGUIツールです。別のドキュメントで詳しく説明します。

SDSの設定をまず確認します。
メニューの```Settings > MCS Configuration```を選択すると、以下のような設定ダイアログが表示されます。
![](images/sds_mcs_configuration.png)

一番上はPythonの実行ファイルの位置を指定します。ファイルが存在しない場合は赤い枠で表示されます。
Shinra script path, Shinra MCS pathは、起動したSDSの位置が自動的に入力されます。
Games installation dirは、 SDSが動作時に保存するさまざまなファイルの置き場所で、ゲームを構成するファイル全部のコピーなどが置かれるところです。ディレクトリが無い場合は作成してください。 Default game user idは、そのままで構いません。


次にプロジェクトを作ります。
メニューの ```File > New``` を選択します。 
New Shinra Project というウインドウが表示されるので、
プロジェクトの設定を保存するためのファイル(.vcxprojのようなもの)の名前を入力してください。
仮にsdstestなどとします。 
ファイルを保存する位置は、Documentsフォルダなどを適当に指定してかまいません。
次にメニューの ```Project > Add Data pack```を選択します。
すると以下のようなウインドウが表示されます。
![](images/sds_add_datapack.png)
DataPackは、ゲームの実行に必要なファイルがすべて格納されているディレクトリです。

SDSを手早く試せるようにするため、CCDKレポジトリのトップレベルに、```CCDK/streamtest```というディレクトリがあります。ここに、one_to_one.exeとmany_to_many.exeと、必要な画像ファイルなどが配置されています(図)。
![](images/streamtest_dir.png)
念のためここで one_to_one.exeなどをダブルクリックして起動し、動作確認してください。

このディレクトリをDataPackとして、そのまま追加します。
メニューから```Project > Add Data Pack```を選択して、
Browseボタンを押し、 streamtestディレクトリを選択し、成功すると以下のように、左側のツリービューに ``` sdstest > Data packs > DataPack ``` と表示されます。
DataPackは複数追加できますが、今はひとつだけとします。

![](images/sds_add_streamtest.png)

次に,Startupという項目で、このDataPackの中のどのファイルが起動すべき実行ファイルなのかを指示します。
```Project > Add Startup configuration```を選択すると次のような画面が表示されます。
![](images/sds_add_startup.png)

Data packの項目が赤い枠になっていますが、これはDataPackがまだ選択されていないことを示しています。　赤い枠をクリックしてすでに追加されているDataPackを選択します。

次に Executableの入力欄に、 one_to_one.exeと直接入力します。赤い枠が消えたら、入力完了です。

Executableの次は、Work directoryを指定します。DataPackの中のトップディレクトリで動作させたいので、 "." (ダブルクォート記号は含まない)を指定します。


![](images/sds_set_executable_workdir.png)

最後に動作確認を行います。```Project > Start game > Startup ```を選択します。

![](images/sds_start_game_menu.png)

Startupを選択すると以下のような Start ボタンが表示されます。

![](images/sds_running_game.png)

ユーザー名や使われるポート番号などの情報が表示されていますが、それらは別のドキュメントで説明します。ここではStartボタンを押します。

ウインドウが2つ表示されます(初回実行時は、Windowsの警告が表示されますが、つねに許可を選択してください。) ひとつは、 "Direct3D Win32 Game1" で、これは、one_to_one.exeのウインドウです。もうひとつは ShinraClient で、これがビデオストリームのビューワです。

![](images/sds_start_game_and_client.png)

ShinraClientにフォーカスしてEnterを押すと、以下のようにビデオストリームが見えます。
ビデオストリームを介さない描画と画質が違っているのがわかります。また、Pキーを押してサウンドを再生した際、タイミングが若干遅れているのもわかります。　映像と音声のクオリティや遅延については、シンラ・システムの商用サービスと異なっていることに注意してください。
one_to_one.exeのウインドウは、画面に対しては描画していないので、真っ白のままになります。

![](images/sds_one_to_one_stream_work.png)

ShinraClientを閉じ、 SDSのStopボタンを押してテストを終了します。


<B>手順5, N:Nスケルトンをビデオストリーミングありで確認</B>

手順4でDataPackとして指定した CCDK/streamtestというディレクトリには、
many_to_many.exeも含まれています。SDSを用いて、Startupをもうひとつ追加するだけで、
many_to_manyのビデオストリームを試すことができます。

まず、手順3の方法で、CCDK.slnからバックエンドサーバーを起動してください。
これはデバッガあり・なしどちらでもかまいません。

次に、SDSで```Project > Add Startup configuration```を選択し、Data packとしてDataPackを、Executableとして many_to_many.exeを追加し, Work directoryも手順4と同様"."を指定します(図)。
![](images/sds_add_many_to_many_startup.png)

このとき新しいStartup1というStartup configurationが追加されているのが、左側のツリービューでわかります。

追加できたら ```Project > Start game  > Startup1```を選択して、手順4と同様に起動します。ビデオストリームが表示され、Pingの値が増加していけば成功です(図)。

![](images/sds_many_to_many_stream_work.png)

複数のmany_to_many.exeを起動するには、Startボタンが表示されているウインドウの灰色の部分で右クリックをしてポップアップメニューを表示し、```Add game instance```を選択します(図).
![](images/sds_add_game_instance.png)

すると以下の図のように、異なるポート番号が割り当てられた2つのゲームを起動することができるようになります。

![](images/sds_two_instances.png)

それぞれのStartボタンを押して2組の many_to_many.exeと ShinraClientを起動します(図)。

![](images/sds_two_many_to_many_stream_work.png)

Channelcastのカウンタ値が増えていくのが見えたら完了です。
同じ要領で、クライアントをいくつでも追加することができます。



###4. LinuxやMacOS Xでの動作確認
バックエンドサーバーだけは、LinuxやMacOS X で動作させることができます。
手順は以下の通りです。

1. Linux自体をセットアップする
2. 必要な外部ツールやライブラリをインストールする
3. gitでCCDKを取得する
4. バックエンドサーバーをビルド
5. Redisサーバーを起動する
6. バックエンドサーバーを起動する


<B>手順1, Linux自体をセットアップする</B>

CCDKは、Ubuntu server 14.04.2または 10.04 で試しています。
特に新しいカーネル機能などを利用していないうえ、
必要なすべてをソースコードで提供しているので、
ほとんどのディストリビューションで問題はないはずです。

Linuxのセットアップに慣れている方は手順2に進んで構いません。
またLinuxではなくMacOS Xを用いる場合は、この手順は必要ありません。

ここでは、VirtualBoxとUbuntu Serverを用いて、
完全に無料でローカルにLinuxサーバー環境を構築する方法を紹介します。

まずVirtualBoxを公式サイトからダウンロードします。

[http://www.oracle.com/technetwork/server-storage/virtualbox/downloads/index.html](http://www.oracle.com/technetwork/server-storage/virtualbox/downloads/index.html)

ホストOSは、MacOS X, Windows どちらでもかまいません。

次に、Ubuntu Serverを公式サイトからダウンロードします。
[http://www.ubuntu.com/download/server](http://www.ubuntu.com/download/server) 

必要なファイルは、```ubuntu-14.04.2-server-amd64.iso```のような名称の、600MBほどの大きさです。多少バージョン番号が違っていても構いません。Ubuntu-desktopでも構いません。

VirtualBoxを起動してNewボタンをクリックし、Linux, Ubuntu 64bitを選択して、
メモリ量は2GB程度、ディスク容量は、可変で20GB程度を設定します。
起動時にディスクイメージのファイル位置を入力するよう促されるので、
さきほどダウンロードしたISOファイルを指定します。
あとは通常のUbuntuのインストールと同様、キーボードや時刻、
ユーザーアカウント名などを設定してください。
![](images/ubuntu_1404_setup_done.png)
以上のようなログインコンソールが表示されたらセットアップ完了です。




<B>手順2, 必要な外部ツールやライブラリをインストールする</B>

以下、Ubuntuでの方法を説明します。
Ubuntu serverの場合、初期は最小の構成になっているので、
git, make, gcc, ruby, ruby-dev, racc, g++, zlib1g-dev, redis-server
をインストールする必要があります。それぞれ以下のようにしてインストールします。

~~~
bash$ sudo apt-get install git
bash$ sudo apt-get install make
bash$ sudo apt-get install gcc
bash$ sudo apt-get install ruby
bash$ sudo apt-get install ruby-dev
bash$ gem install racc
bash$ sudo apt-get install g++
bash$ sudo apt-get install zlib1g-dev
bash$ sudo apt-get install redis-server
~~~

次にhiredisをインストールします。
hiredisは、Redisサーバーに対してプログラムからアクセスするためのライブラリです。
Ubuntuでは、hiredisがパッケージで提供されていません。
そこで、ソースからビルドする必要があります。

hiredisのソースコードは、以下のコマンドラインで取得,ビルドできます。

~~~
bash$ git clone git@github.com:ShinraTech/hiredis
bash$ cd hiredis
bash$ make
bash$ make install
~~~

Ubuntu 10.04ではこれだけです。他のディストリビューションでは検証していませんが、
似たような方法でインストールできるはずです。
Linuxでは、バックエンドサーバーの起動時にhiredisの共有ライブラリが必要になるので、
.bashrcなどに、以下のような動的リンカ用の環境変数を書き込んでおくと良いでしょう。
共有ライブラリの実際の位置は、```make install```したときの出力をみて確認してください。

~~~
LD_LIBRARY_PATH=/usr/local/lib
~~~



MacOS Xの場合は、XCode と command line toolsがインストールされている状態で、
Homebrew環境の場合、 redis, hiredis, racc だけが追加で必要です。

~~~
bash$ brew install redis
bash$ brew install hiredis
bash$ gem install racc
~~~

とするだけです。

<B>手順3, gitでCCDKを取得する</B>
Linux, MacOS Xともに共通です。
MacOS Xでは[GitHub for Mac](https://mac.github.com/) というGUIアプリも使えますが、
ここではコマンドラインの方法を説明します。

~~~
bash$ git clone git@github.com:ShinraTech/CCDK
~~~

以上のようにするだけです。
この段階では、redisやmoyaiなどのサブモジュールはまだ取得されていません。


<B>手順4, バックエンドサーバーをビルド</B>

Linux, MacOS Xともに共通です。

CCDKのトップディレクトリに、全体を一気にビルドするためのMakefileを用意しています。

~~~
bash$ cd CCDK
bash$ make setup
~~~

make setupをすることで、gitのサブモジュールをすべて取得し、コンパイルを行います。
コンパイルができたら、 backendディレクトリ内に、 ssvと ssbenchと2つのプログラムができているはずです(図)。 ssvがバックエンドサーバーです。 datadirは静的ファイルを保存するディレクトリで、ssvの動作に必要です。

![](images/backend_compiled.png)

backendディレクトリにおいて、次のようにしてssvを起動します。

~~~
bash$ ./ssv
~~~

LD_LIBRARY_PATHが設定されていないなどが原因で、hiredisが見つからない場合は、以下のようなエラーがでて起動できないかもしれません。

~~~
./ssv: error while loading shared libraries: libhiredis.so.0.12: cannot open shared object file: No such file or directory
~~~

ssvは、引数無しで起動すると、使用方法の説明を表示して終了します(図)。
![](images/ssv_noopt_run.png)


<B>手順5, Redisサーバーを起動する</B>
ssvは、データを永続化するために、SQLのサーバーではなくRedisを用います。
Redisを起動するには、任意の場所で、

~~~
bash$ redis-server 
~~~

として起動するだけです。起動するとロゴマークのアスキーアートが出力されます(図)。
![](images/redis_server_run.png)


<B>手順6, バックエンドサーバーを起動する</B>
```CCDK/backend``` ディレクトリに移動して、

~~~
bash$ ./ssv realtime database 
~~~

として起動すると、以下の図のようにssvが稼働開始します。 
![](images/ssv_opt_run.png)





