#
# docgen0.rb
#
# $Revision: 1.3 $
# $Date: 2005/07/02 10:22:40 $
# $Id: docgen0.rb,v 1.3 2005/07/02 10:22:40 chiaki Exp $
#
# docgen : C言語などのサブルーチン定義型プログラミング言語の
# ソースコードから、リファレンスマニュアルを自動的に作りだすスクリプト。
# C言語形式の /* ... */や // や、その外の #... の中を一律にパースする。
# コメントの構造はまったく関知しない。また1行に1コマンドを必要とする。
# -shell 引数をつけると # の後ろをコメントとして認識するようになる。
#
# 以下はコメント文中に書くタグの一式である。
# タグは<cmd param> でできていて、 cmd も param もASCII テキストである。
#
# 各国語言語やバージョン(簡易版などなど)に対応するために、 
# paramに言語コード(自由に定義)を指定すると、
# docgen の引数によってそれぞれ語のテキストを出力することができる。
#
# 
# 定義は大きくわけて関数定義とツールの説明と、そのほかのファイルなどの
# 説明がある。関数定義には <func> を使い、その場合は以下のようなフォーマット
# になる。各行は stripされる。
#
# <sample lang>など複数行用のコマンドでも、
# <sample ja> ほへおげほげほへおげほげほげおおげ。
# のように同じ行に書くとドキュメントに含まれる。
#
# 結局、存在するタグをまとめると、
#
# <func> ... </func>
# <categorydesc> ... </categorydesc> <catd> ... </catd>
#
# <description lang> ... </description>     <desc lang> ... </desc>
# <sample lang> ... </sample>   <sam lang> ... </sam>
# <return lang> ... </return>   <ret lang> ... </ret>
# <usage lang> ... </usage>
# <bugs lang> ... </bugs>
# <argdef lang> ... </argf>      <def> ... </def>
# 
#
# <name>                                 
# <summary lang>   <sum lang>            
# <category> <cat>                       
# <arch>linux
# <prototype> <type>                     
# <also>                                 
# <arg>                                  番号ふりあり
# 以上の行たんいのやつは、複数行にわたって書く場合は、単にappendされるか、
# タグによっては特別な処理が追加される(argの場合は番号がふられるというように)
#
# となっている。余分なタグがあっても単に無視される。
# 間違った順番でタグを書いても、ちゃんとフォーマット通りに出力される。
# 
#
# docgen.conf には、入力ファイルや出力オプションなどを記述して、
# docgen0.rb に入力する。 docgen0.rb はまずコメントを理解して、
# docgenタグだけを集めたファイルを出力する。その後、 docgen1.rb を起動
# して、ドキュメントを生成するのだ。
#
#
# Usage:
#
# docgen0.rb infile.cf
#
#
# conf-file の書式。各行はstripされるよ
# 各行は
# command param param param ... 
# となっている。
#
#
# fileprefix vce-     出力ファイルの接頭辞を指定する。
# dirprefix              出力ディレクトリのprefixを指定する。
# ユーザが決めた言語コードごとにディレクトリがもう1段階掘られるので、
# たとえば dirprefix を vce とすると、
# hogehoge/en/vce-reference.html 
# hogehoge/ja/vce-reference.html となる。
# また、 hogehoge/ の中に index.html が出力される。
#
# lang en ja とすると、対応可能な言語をリストアップする。エラー処理のため。
# nkfopt で、最終出力の文字コードを決定するnkfのオプション
#
# 以下は見出し用の定数を docgen.conf で定義するためのコマンド。
# apidoctitle lang
# apinameindextitle lang
# categoryindextitle lang
# funcdeftitle lang
# copyrightinfotitle lang
# generalinfotitle lang

#
# ドキュメントになるべきデータ構造を定義する。
#
# * 関数リファレンスマニュアルページ(1枚)(名前順)
# * 関数ごとの名前順の目次ページ(リンクテーブル)
# * カテゴリごとの目次ページ(リンクテーブル)
# * 実行ファイルのリファレンスマニュアル(名前順)
# * サンプルコードディレクトリ
#
# 以上が各言語用に出力される。

#
# Copyright (C) 2000-2005 Community Engine Inc. All rights reserved.
# "PlayStation" is registered trademark and is trademark of Sony Computer 
# Entertainment Inc.
# For more information, please visit our website at www.ce-lab.net.
#


require "kconv"

# 各種データ
$s_translation_part_file = "translation_part.ringo"

# まず設定ファイルを読みこむ
$s_fileprefix = "docgen-"
$s_dirprefix = "docgen"
$a_langs = []
$h_langs = {}
$s_nkfopt = "-s"

$h_apidoctitle = {}  # ドキュメントのタイトル、APIマニュアル用

$h_categoryindexindextitle = {} # カテゴリのリスト用
$h_apinameindextitle = {}  # 名前順目次のタイトル APIマニュアル用
$h_categoryindextitle = {} # カテゴリIndexタイトル(API用)
$h_funcdeftitle = {}    # 各関数の詳細説明部分用タイトル ( API用)
$h_returntitle = {} 
$h_generalinfotitle = {}
$h_copyright = {}

# func,categorydesc各def中の表の見出し
$h_def_summary_title = {}
$h_def_category_title = {}
$h_def_prototype_title = {}
$h_def_arch_title = {}
$h_def_return_title = {}
$h_def_description_title = {}
$h_def_sample_title = {}
$h_def_bugs_title = {}
$h_def_also_title = {}
$h_def_usage_title = {}



#
# ドキュメントの内容を記憶しておくハッシュたち
#
$h_func_name = {}     # "単に関数名"
$h_categorydesc_name = {}  # 単にカテゴリ名"
$h_category = {}          # 無言語。 "RUNMODE..NAME"
$h_summary = {}           # 有言語。 "RUNMODE.LANG.NAME"
$h_sample = {}            # 有言語。 "RUNMODE.LANG.NAME"
$h_argdef = {}            # 有言語+index。 "RUNMODE.LANG.NAME.IND"
$h_arg = {}               # 無言語+index。 "RUNMODE..NAME.IND"
$h_prototype = {}         # 無言語。 "RUNMODE..NAME"
$h_arch = {}              # 無言語。 "RUNMODE..NAME"
$h_also = {}              # 無言語。 "RUNMODE..NAME"
$h_return = {}            # 有言語。 "RUNMODE.LANG.NAME"
$h_description = {}       # 有言語。 "RUNMODE.LANG.NAME"
$h_usage = {}             # 有言語。 "RUNMODE.LANG.NAME"
$h_bugs = {}              # 有言語。 "RUNMODE.LANG.NAME"

# 前もってタグがはじまるか終わる前に状態として持っておく必要があるもの
$s_name = ""
$s_lang = ""   
$s_second_parm =""
$i_argcount = 0
$i_extract_translation_part = 0
$s_primary_lang = ""



#
#
#

def main

	if( ARGV.size < 1 ) then
		STDERR.print "Usage: docgen0.rb infile infile ...\n"
		STDERR.print "Please put 'docgen.conf' in the working directory.\n"
		exit 0
	end

    `rm -f #{$s_translation_part_file}`
	i_lineno=0

	File.open( "docgen.conf" ,"r" ).readlines.each { |i|
		i_lineno += 1
		i.chomp!
		i.strip!
		next if( i =~ /^#/ );
		next if( i == "" );

		tk = i.split( / / )
		command = tk.shift
		if( command == "fileprefix" ) then 
			$s_fileprefix = tk.join( " " )
		elsif( command == "dirprefix" ) then 
			$s_dirprefix = tk.join( " " )
		elsif( command == "lang" ) then 
			$a_langs = tk
			tk.each { |ll|
				$h_langs.store( ll, ll );
			}
        elsif( command == "primary_lang" ) then
            $s_primary_lang = tk.shift
        elsif( command == "extract_translation_part" ) then
            $i_extract_translation_part = tk.shift.to_i
		elsif( command == "nkfopt" ) then
			$s_nkfopt = tk.shift
		elsif( command == "apidoctitle" ) then
			test_lang(  l = tk.shift , "apidoctitle" )
			$h_apidoctitle.store( l, tk.join(" "))
		elsif( command == "categoryindexindextitle" ) then
			test_lang( l = tk.shift , "cateogryindexindextitle" )
			$h_categoryindexindextitle.store(l,tk.join(" "))
		elsif( command == "apinameindextitle" ) then
			test_lang( l = tk.shift , "apinameindextitle" )
			$h_apinameindextitle.store( l, tk.join(" "))
		elsif( command == "categoryindextitle" ) then
			test_lang( l = tk.shift , "cateogryindextitle" )
			$h_categoryindextitle.store(l,tk.join(" "))
		elsif( command == "funcdeftitle" ) then
			test_lang( l = tk.shift , "funcdeftitle" )
			$h_funcdeftitle.store(l,tk.join(" " ))
		elsif( command == "returntitle" ) then
			test_lang( l = tk.shift , "returntitle" )
			$h_returntitle.store(l,tk.join(" "))
		elsif( command == "generalinfotitle" ) then
			test_lang( l = tk.shift , "generalinfotitle" )
			$h_generalinfotitle.store(l,tk.join(" "))
		elsif( command == "def_summary_title" ) then
			test_lang( l = tk.shift , "def_summary_title" )
			$h_def_summary_title.store(l,tk.join( " " ))
		elsif( command == "def_category_title" ) then
			test_lang( l = tk.shift , "def_category_title" )
			$h_def_category_title.store(l,tk.join( " " ))
		elsif( command == "def_prototype_title" ) then
			test_lang( l = tk.shift , "def_prototype_title" )
			$h_def_prototype_title.store(l,tk.join( " " ))
		elsif( command == "def_arch_title" ) then
			test_lang( l = tk.shift , "def_arch_title" )
			$h_def_arch_title.store(l,tk.join(" " ))
		elsif( command == "def_return_title" ) then
			test_lang( l = tk.shift , "def_return_title" )
			$h_def_return_title.store(l,tk.join( " " ))
		elsif( command == "def_description_title" ) then
			test_lang( l = tk.shift , "def_description_title" )
			$h_def_description_title.store(l,tk.join( " " ))
		elsif( command == "def_sample_title" ) then
			test_lang( l = tk.shift , "def_sample_title" )
			$h_def_sample_title.store(l,tk.join( " " ))
		elsif( command == "def_bugs_title" ) then
			test_lang( l = tk.shift , "def_bugs_title" )
			$h_def_bugs_title.store(l,tk.join( " " ))
		elsif( command == "def_also_title" ) then
			test_lang( l = tk.shift , "def_also_title" )
			$h_def_also_title.store(l,tk.join( " " ))
		elsif( command == "def_usage_title" ) then
			test_lang( l = tk.shift , "def_usage_title" )
			$h_def_usage_title.store( l, tk.join( " "))
		elsif( command == "copyright" ) then
			test_lang( l = tk.shift , "copyright" )
			$h_copyright.store( l , tk.join(" " ) )
		else
			raise( "unknown command in line #{i_lineno}:#{command}" )
		end
	}

	all_lines = []

	ARGV.each { |i|
		STDERR.print "Scanning #{i}\n"
#		lines = Kconv.toeuc( `expand -t 4 #{i}`).split("\n")
		lines = do_Kconv( $s_nkfopt, `expand -t 4 #{i}`).split("\n")
#		lines = Kconv.toeuc(File.open(i,"r").read).split("\n")
		if( i =~ /.*\.c$/ || i =~ /.*\.h$/ || i =~ /.*\.cpp$/ ) then
			all_lines += extract_text_c(i,lines)
		elsif( i =~ /.*\.rb$/ || i=~ /.*\.sh$/ || i=~ /.*\.csh$/ ) then
			all_lines += extract_text_shell(i,lines)
		else
			all_lines += extract_text_plain(i,lines)
		end
	}
	# 全部の行をゲットしおわった。データはすべてグローバル変数に入ってる
	parse_all_lines( all_lines )

	$a_langs.each{ |lng|
		# ディレクトリを整備
		system( "mkdir -p #{$s_dirprefix}/#{lng}" )
		system( "mkdir -p #{$s_dirprefix}/#{lng}/man")
		system( "mkdir -p #{$s_dirprefix}/#{lng}/man/man1")
		system( "mkdir -p #{$s_dirprefix}/#{lng}/man/man3")
		system( "mkdir -p #{$s_dirprefix}/#{lng}/man/man5")
		apifilename = "#{$s_dirprefix}/#{lng}/#{$s_fileprefix}-api.html"
		
		apiref = make_api_reference( lng )
		
		allfuncs = $h_func_name.keys.sort
		allfuncs.each { |i|
			apimanref = make_man_funcdef_one(i,lng)
			apimanfilename = "#{$s_dirprefix}/#{lng}/man/man3/#{i}.3"
			begin
				STDERR.print( "Writing #{lng} API man document #{i}\n" )
				out = File.open( apimanfilename, "w" )
				out.write(apimanref)
				out.close
				system( "nkf -w #{apimanfilename} > /tmp/docgen0.tmp" )
				system( "mv /tmp/docgen0.tmp #{apimanfilename}" )
				system( "gzip #{apimanfilename}" )
			rescue
				STDERR.print( "docgen0.rb: cannot open file #{$!}" )
				exit 1
			end
		}

		begin
			STDERR.print( "Writing #{lng} API document\n" )
			out = File.open( apifilename, "w" )
			out.write(apiref)
			out.close
			system( "nkf #{$s_nkfopt} #{apifilename} > /tmp/docgen0.tmp" )
			system( "mv /tmp/docgen0.tmp #{apifilename}" )
		rescue
			STDERR.print( "docgen0.rb: cannot open file #{$!}" )
			exit 1
		end
	}
end

def test_lang(l,cf)
	raise "'#{cf}' needs language." if( l == nil || l == "" )
end


# accumlines に各行がはいっていて、行頭からタグがあるのさ。
# タグは行頭に1個だけという約束になっているので、それを単に
# パースするのだ。


def test_4runmode(r,n)
	if( r == "out" ) then
		raise( "#{n} has to be inside func|categorydesc tag." )
	end
end
def test_subrunmode(subr,shouldbe,tag)
	if( subr != shouldbe ) then
		raise( "'#{tag}' has to be inside '#{shouldbe}'." )
	end
end
def test_str(a)
	raise "empty string" if( a == nil || a == "" ) 
end


def parse_all_lines( all_lines )
	# runmode の推移
	# out -> func|categorydesc -> out
	runmode = "out"
	subrunmode = "out"
	part_content = ""         # 複数行にわたる時のコンテンツ
	all_lines.each{ |i|
		linetk = i.split(":")
		filename = linetk.shift
		lineno = linetk.shift
		line_content = linetk.join("") 
		line_content =~ /^(\s*)<(.*)>(.*)$/
		spaces = $1
		tagname = $2
		tagline_text = $3

		#	print "LINE_content : '#{i}' '#{line_content}'\n"
		#	print "'#{filename}' '#{lineno}' '#{spaces}' '#{tagname}' '#{tagline_text}'\n"

		if( tagname ) then
			tagtk = tagname.split(/\s+/)
		else
			part_content += line_content + "\n" 
			next
		end
		
		if( tagtk.size == 1 ) then       # 普通のタグ
			tagname = tagtk.shift
			$s_second_param = nil
		elsif( tagtk.size == 2 ) then    # 引数つきのタグ
			tagname = tagtk.shift
			$s_second_param = tagtk.shift
			if( $h_langs[ $s_second_param ] == $s_second_param ) then
				$s_lang = $s_second_param
			end
		end

		case tagname
		when "func"
			if( runmode != "out" ) then
				raise "cannot nest <func> or parse error."
			else
				runmode = "func"
			end
			part_content = ""
			$s_name = ""
			$i_argcount = 0      # argがくるたびに1追加。

		when "/func"
			raise "unmatched </func>." if( runmode != "func" ) 
			runmode = "out"
			STDERR.print( "-Func '#{$s_name}'\n" )
			$h_func_name[ $s_name ] = $s_name

		when "categorydesc" , "catdesc"
			if( runmode != "out" ) then
				raise "cannot nest <categorydesc> or parse error." 
			else 
				runmode = "categorydesc"
			end
			part_content = ""

		when "/categorydesc" , "/catdesc"
			raise "unmatched </categorydesc>." if( runmode != "categorydesc" )
			runmode = "out"
			STDERR.print( "-Categorydesc '#{$s_name}'\n" )
			$h_categorydesc_name[$s_name] = $s_name

		when "name"
			# name はすべてのモードの時に有効。
			if( runmode == "out" ) then
				raise "<name> tag has to be in func|categorydesc."
			end
			$s_name = tagline_text

			######
		when "description" , "desc"
			test_lang( $s_second_param, "description" )
			test_4runmode( runmode, "description" )
			test_subrunmode( subrunmode, "out" , "description" )
			subrunmode = "description"
			part_content = ""
			

		when "/description" , "/desc"
			test_subrunmode( subrunmode, "description", "/description" )
			subrunmode = "out"
			test_str( $s_name )
			$h_description[ "#{runmode}.#{$s_lang}.#{$s_name}" ] = part_content

		when "sample" , "sam"
			test_lang( $s_second_param, "sample" )
			test_4runmode( runmode, "sample" )
			test_subrunmode( subrunmode, "out" , "sample" )
			subrunmode = "sample"
			part_content = ""

		when "/sample" , "/sam"
			test_subrunmode( subrunmode, "sample" , "/sample" )
			subrunmode = "out"
			test_str( $s_name )
			$h_sample[ "#{runmode}.#{$s_lang}.#{$s_name}"]=part_content
			
		when "return" , "ret"
			test_lang( $s_second_param, "return" )
			raise "'return' has to be in <func>." if( runmode != "func" ) ;
			test_subrunmode( subrunmode, "out" , "return" )
			subrunmode = "return"
			part_content = ""

		when "/return" , "/ret"
			test_subrunmode( subrunmode, "return" , "/return" )
			subrunmode = "out"
			test_str( $s_name )
			$h_return[ "#{runmode}.#{$s_lang}.#{$s_name}"]=part_content


		when "usage" 
			test_lang( $s_second_param, "usage" )
			test_4runmode( runmode, "usage" )
			test_subrunmode( subrunmode, "out" , "usage" )
			subrunmode ="usage"
			part_content = ""

		when "/usage"
			test_subrunmode( subrunmode, "usage" , "/usage" )
			subrunmode = "out"
			test_str( $s_name )
			$h_usage[ "#{runmode}.#{$s_lang}.#{$s_name}"]=part_content

		when "bugs"
			test_lang( $s_second_param, "bugs" )
			test_4runmode( runmode, "'bugs'" )
			test_subrunmode( subrunmode, "out" , "bugs" )
			subrunmode = "bugs"
			part_content = ""

		when "/bugs"
			test_subrunmode( subrunmode, "bugs" , "/bugs" )
			subrunmode = "out"
			test_str($s_name)
			$h_bugs[ "#{runmode}.#{$s_lang}.#{$s_name}"]=part_content

		when "argdef" , "def"
			test_lang( $s_second_param, "argdef" )
			raise "'argdef' has to be in <func>." if( runmode != "func" );
			test_subrunmode( subrunmode, "out" , "argdef" )
			subrunmode = "argdef"
			part_content = ""

		when "/argdef" , "/def"
			test_subrunmode( subrunmode, "argdef" , "/argdef" )
			subrunmode = "out"
			test_str( $s_name )
			$h_argdef["func.#{$s_lang}.#{$s_name}.#{$i_argcount}"] = part_content
		when "summary" , "sum"
			test_lang( $s_second_param, "summary" )
			test_4runmode( runmode, "'summary'" )
			test_subrunmode( subrunmode, "out" , "summary" )
			$h_summary["#{runmode}.#{$s_lang}.#{$s_name}"]=tagline_text

		when "prototype" , "type"
			raise "'prototype' has to be in <func>." if( runmode != "func");
			test_subrunmode( subrunmode, "out" , "prototype" )
			$h_prototype["func..#{$s_name}"]=tagline_text

		when "arch"
			test_4runmode( runmode, "'arch'" )
			test_subrunmode( subrunmode, "out", "arch" )
			$h_arch["#{runmode}..#{$s_name}"] = tagline_text

		when "category" , "cat"
			test_4runmode( runmode, "'category'" )
			test_subrunmode( subrunmode , "out" , "category" )
			$h_category["#{runmode}..#{$s_name}"]=tagline_text

		when "also"
			test_4runmode( runmode, "'also'" )
			test_subrunmode( subrunmode, "out" , "also" )
			$h_also["#{runmode}..#{$s_name}"]=tagline_text

		when "arg"
			raise "'arg' has to be in <func>." if( runmode != "func" );
			test_subrunmode( subrunmode, "out" , "arg" )
            $i_argcount += 1
			$h_arg["func..#{$s_name}.#{$i_argcount}"]=tagline_text
		else
			# HTMLのタグが行頭にきてるだけかもしれないので、
			# そのまま出力するのだ。いちおうwarnだす
#            STDERR.print "Warning: unknown tag #{tagname} : HTML tag?\n"
			part_content += line_content + "\n"
		end
	}
end

#######################################
#
# さてパースが終わったので、ドキュメント生成といくか。
#
#######################################

# a = $h_sample["func.ja.vce_set_mainloop_callback"]
# STDERR.print( "SAMPLE: #{a}\n" )


# APIメインドキュメントのドキュメント形式:
#
# name順もくじも、内容も、ぜんぶ1個のファイルに入っている。
# category順ソートも入っているぞ
#
# DOCUMENT :: TITLE HEADER BODY FOOTER
#
# TITLE :: タイトル部分 _TITLE_ でおきかえ
#
# HEADER :: NAMEINDEX CATEGORYINDEX
#           
# NAMEINDEX :: もくじをnameindex_html_part で作ったものを名前順に並べたもの
# 
# CATEGORYINDEX :: categoryindex_html_part をカテゴリ別に並べたもの。
#
# FOOTER :: バージョン情報、著作権情報、全体に関する情報
#
# BODY :: FUNCDEF FUNCDEF ...
# 
# FUNCDEF :: 関数定義をfuncdef_html_part で作ったもの
#
# erubyを使ったらもっと簡単になるかな。。。でもでかいスクリプトを
# eruby用HTMLに埋めこむのはつらい。


#####################################################################
# カテゴリのもくじをつくる。
# href の先は、各カテゴリ．
# 文字コードに関係なく出力可能。
#####################################################################
def make_categoryindexindex(lng)
	allcats = $h_categorydesc_name.keys.sort

	re = "<!-- make_categoryindexindex -->\n<ol>\n"
	allcats.each{ |i|
		re += "<li><a href=\"##{i}\">#{i}</a></li>\n" 
	}
	re += "</ol>\n"
	return re
end

#####################################################################
# 関数のもくじをつくる。
# また href の先は、関数名のみ。
# 文字コードに関係なく出力可能。
#####################################################################
def make_nameindex(lng)
	allfuncs = $h_func_name.keys.sort

	re = "<!-- make_nameindex -->\n<ol>\n"
	allfuncs.each{ |i|
		re += "<li><a href=\"##{i}\">#{i}</a></li>\n" 
	}
	re += "</ol>\n"
	return re
end
#####################################################################
# カテゴリもくじ1カテゴリ分を作る
# <table> .. </table> で1個のカテゴリの説明
#####################################################################
def make_categoryindex(lng)
	allcats = $h_categorydesc_name.keys.sort
	
	re = "<!-- make_categoryindex -->\n"
	allcats.each { |i|
        re += "<a name=\"#{i}\"></a>\n"
		re += "<h3>#{i}</h3>\n"
		desc = $h_description[ "categorydesc.#{lng}.#{i}" ]
		re += "<p>#{desc}</p>\n"
		re += "<table id=\"categoryindex\">\n"
		re += "<tr><td>Functions:</td></tr>\n"
		re += "<tr><td>\n"
		# href の集合をつくる
		allfuncs = $h_func_name.keys.sort
		allfuncs.each { |fn|
			if( $h_category[ "func..#{fn}" ] == i ) then
				re += "<a href=\"##{fn}\">#{fn}</a><BR>\n"
			end
		}
		re += "</td></tr>\n"
#		re += "</table><BR><R>\n"
		re += "</table>\n"
	}
	return re
end
#####################################################################
# いらないtagを取り除いたりする。
#####################################################################
def tagstrip( str)
	return if str.nil?
	str = str.gsub( /<[bB]>.*<\/[bB]>/) do |s|
		s.gsub!( /<[bB]>/, "<br>.B ")
		s.gsub( /<\/[bB]>/, "<br>")
    end
	str = str.gsub( /<[pP][rR][eE]>.*<\/[pP][rR][eE]>/m) do |s|
		s.gsub!( /<[pP][rR][eE]>/, "")
        s.gsub!( /<\/[pP][rR][eE]>/, "")
		s.gsub( "\n", "<br>")
	end
	str.gsub( /\t/, "").gsub( /\n/, "").gsub( /<[lL][iI]>/, ": ").gsub( /<[bB][rR]>/, "\n").gsub( /<.+>/, "")
	
end

#####################################################################
# 関数定義1個分を作る。(for man)
# funcname: 関数名 lng: 言語
#####################################################################
def make_man_funcdef_one( funcname, lng)
	manpage = 3
	re = ".TH #{funcname} #{manpage} \"#{$h_apidoctitle[lng]}\"\n"
	re += ".SH #{$h_def_summary_title[lng]}\n"
	sum = tagstrip( $h_summary["func.#{lng}.#{funcname}"])
	re += "#{funcname} \\- " + sum + "\n" if !sum.nil?
	re += ".SH #{$h_def_category_title[lng]}\n"
	cat = tagstrip( $h_category["func..#{funcname}"])
	re += cat + "\n" if !cat.nil?
	re += ".SH #{$h_def_arch_title[lng]}\n"
	arch = tagstrip( $h_arch["func..#{funcname}"])
	re += arch + "\n" if !arch.nil?
	
	re += ".SH #{$h_def_prototype_title[lng]}\n"
	ptype = tagstrip( $h_prototype["func..#{funcname}"])
	re += ptype + "\n" if !ptype.nil?

	# ループをまわして引数定義をつくるのだ。
	(1 .. 9999 ).each{ |i|
		arg = $h_arg["func..#{funcname}.#{i}"]
		argdef = tagstrip($h_argdef["func.#{lng}.#{funcname}.#{i}"])
		break if( arg == nil || arg == "" )
		re += ".SH arg #{i}\n"
		re += ".I #{arg}\n"
		re += "#{argdef}\n"
	}
	
	re += ".SH #{$h_def_return_title[lng]}\n"
	retd = tagstrip( $h_return["func.#{lng}.#{funcname}"])
	re += retd + "\n" if !retd.nil?
	
	re += ".SH #{$h_def_description_title[lng]}\n"
	desc = tagstrip( $h_description["func.#{lng}.#{funcname}"])
	re += desc + "\n" if !desc.nil?
	
	smp = $h_sample[ "func.#{lng}.#{funcname}" ]
	if( smp != nil and smp != "" ) then
		re += ".SH #{$h_def_sample_title[lng]}\n"
		smp = tagstrip( smp)
		re += smp + "\n"
	end
	
	bugs = $h_bugs[ "func.#{lng}.#{funcname}" ]
	if( bugs != nil and bugs != "" ) then
		re += ".SH #{$h_def_bugs_title[lng]}\n"
		bugs = tagstrip( bugs)
		re += bugs + "\n"
	end
	
	also = $h_also[ "func.#{lng}.#{funcname}" ]
	if( also != nil and also != "" ) then
		re += ".SH #{$h_def_also_title[lng]}\n"
		also = tagstrip( also)
		re += also + "\n"
	end
	re
end
#####################################################################
# 関数定義1個分を作る。
# funcname: 関数名 lng: 言語
#####################################################################
def make_funcdef_one(funcname,lng)
#	left_w = 120
	re  = "<a name=\"#{funcname}\"></a>\n"
	re += "<table id=\"funcdef\">\n"
	re += "<tr><th colspan=\"2\" id=\"funcdef_title\">\n"
	re += "#{funcname}</th></tr>\n"
	sum = $h_summary["func.#{lng}.#{funcname}"]
	re += "<tr><th>#{$h_def_summary_title[lng]}</th>"
	re += "<td>#{sum}</td></tr>\n"
	cat = $h_category["func..#{funcname}"]
	re += "<tr><th>#{$h_def_category_title[lng]}</th>"
	re += "<td>#{cat}</td></tr>\n"
	arch = $h_arch["func..#{funcname}"]
	re += "<tr><th>#{$h_def_arch_title[lng]}</th>"
	re += "<td>#{arch}</td></tr>\n"
	ptype = $h_prototype["func..#{funcname}"]
	re += "<tr><th>#{$h_def_prototype_title[lng]}</th>"
	re += "<td><b>#{ptype}</b></td>\n"

	# ループをまわして引数定義をつくるのだ。
	(1 .. 9999 ).each{ |i|
		arg = $h_arg["func..#{funcname}.#{i}"]
		argdef = $h_argdef["func.#{lng}.#{funcname}.#{i}"]
		break if( arg == nil || arg == "" )
		re += "<tr><th>arg #{i}</Th>"
		re += "<td>#{arg}</td></tr>\n"
		re += "<tr><th></th><td>#{argdef}</td></tr>\n"
        if( argdef == "") then
            primlang_argdef = $h_argdef["func.#{$s_primary_lang}.#{funcname}.#{i}"]
            output_translation_part("#{funcname} arg #{i}",
                                    primlang_argdef )
        end
	}

	retd = $h_return[ "func.#{lng}.#{funcname}" ]
	re += "<tr><th>#{$h_def_return_title[lng]}</th>"
	re += "<td>#{retd}</td></tr>\n"
    if( retd == "" ) then
        primlang_retd = $h_return[ "func.#{$s_primary_lang}.#{funcname}"]
        output_translation_part( "#{funcname} Return definition",
                                primlang_retd );
    end

	desc = $h_description[ "func.#{lng}.#{funcname}" ]
	re += "<tr><th>#{$h_def_description_title[lng]}</th>"
	re += "<td>#{desc}</td></tr>\n"
    if( desc == "" ) then
        primlang_desc = $h_description[ "func.#{$s_primary_lang}.#{funcname}"]
        output_translation_part( "#{funcname} Description",
                                primlang_desc );
    end
	
	smp = $h_sample[ "func.#{lng}.#{funcname}" ]
	if( smp != nil and smp != "" ) then
		re += "<tr><th>#{$h_def_sample_title[lng]}</th>"
		re += "<td>#{smp}</td></tr>\n"
	end
    if( smp == "" ) then
        primlang_smp = $h_sample[ "func.#{$s_primary_lang}.#{funcname}"]
        output_translation_part( "#{funcname} Sample",
                                primlang_smp );
    end

	bugs = $h_bugs[ "func.#{lng}.#{funcname}" ]
	if( bugs != nil and bugs != "" ) then
		re += "<tr><th>#{$h_def_bugs_title[lng]}</th>"
		re += "<td>#{bugs}</td></tr>\n"
	end
    if( bugs == "" ) then
        primlang_bugs = $h_bugs[ "func.#{$s_primary_lang}.#{funcname}"]
        output_translation_part( "#{funcname} Bugs",
                                primlang_bugs );
    end

	also = $h_also[ "func..#{funcname}" ]
	if( also != nil and also != "" ) then
		re += "<tr><th>#{$h_def_also_title[lng]}</th>"
		re += "<td>\n"
		also.split( /,/ ).sort.each { |i|
			re += "<a href=\"##{i}\">#{i}</a>\n"
		}
		re += "</td></tr>\n"
	end

	re  += "</table><br><br>\n"

	return re
end
def make_funcdef(lng)
	allfuncs = $h_func_name.keys.sort
	re = "<!-- make_funcdef start -->\n"
	
	allfuncs.each { |i|
		re += make_funcdef_one(i,lng)
	}
	re += "<!-- make_funcdef end -->\n<BR><BR>\n"
	return re
end	

# copyright を出力する(言語に依存)
def make_copyright(lng)
	re  = "Copyright #{$h_copyright[lng]}\n"
	return re
end
# general info を出力する
def make_generalinfo(lng)
	return "Not available now"
end
#####################################################################
# APIリファレンスメインを出力する関数
#####################################################################
def make_api_reference( lng )
	re  = "<html>\n"
	re += "<head>\n"
	re += get_http_equiv_encode( lng, $s_nkfopt );
	re += "<link rel=\"stylesheet\" href=\"../vce.css\" type=\"text/css\">\n"
	re += "<title> #{$h_apidoctitle[lng]} </title>\n"
	re += "</head>\n"
	re += "<body>\n"

	# ABSOLUTE HEADER
	re += "<h1> #{$h_apidoctitle[lng]} </h1>\n"

    # CATEGORYINDEX_INDEX
	re += "<h2>#{$h_categoryindexindextitle[lng]}</h2>\n"
	re += make_categoryindexindex(lng)

	# NAMEINDEX
	re += "<h2>#{$h_apinameindextitle[lng]}</h2>\n"
	re += make_nameindex(lng)

	# CATEGORYINDEX
	re += "<h2>#{$h_categoryindextitle[lng]}</h2>\n"
	re += make_categoryindex(lng)

	# FUNCDEFBODY
	re += "<h2>#{$h_funcdeftitle[lng]}</h2>\n"
	re += make_funcdef(lng)

	re += "<p><a href=\"index.html\">#{$h_returntitle[lng]}</a><br></p>\n"

	# GENERALINFO
#	re += "<h2>#{$h_generalinfotitle[lng]}</h2>\n"
#	re += make_generalinfo(lng)

	# COPYRIGHT
	re += "<div id=\"footer\">\n"
	re += make_copyright(lng)
	re += "</div>\n"

	re += "</body>\n"
	re += "</html>\n"

	return re

end


#
#
#
#
# タグの外を捨てる、配列の要素にnilを返す(そしてcompact!)
def omit_useless(fn,lines)

	intag = ""
	lines.collect! { |i|
		if(i==nil) then
			nil
			next
		else
			i.chomp!
		end
		ret = nil

		if( i =~ /^(.+):[0-9]+:\s*<(func|categorydesc)>/ ) then
			if( intag.empty? ) then
				intag = $2
				i
			else
				raise "prep: <#{$2}> inside <#{intag}> : #{i}"
			end
		elsif( i =~ /^(.+):[0-9]+:\s*<\/(func|categorydesc)>/ ) then
			if( intag != $2 ) then
				raise "prep: </#{$2}> outside <#{intag}> : #{i}"
			else
				intag = ""
				i
			end
		elsif( intag.empty? ) then
			nil
		else
			i
		end
	}
	return lines.compact!
end

def extract_text_c(fn,lines)
	incom = false
	lineno = 0
	lines.collect! { |i|
		lineno += 1
		# 1行ではじまり、終わるコメントがあったら無視
		if( i=~ /\/\*.*\*\// ) then
			nil
			next
		end
		if( i=~ /\/\*(.*)/ ) then
			if( incom == true ) then
				raise "prep: comment-open in comment. #{fn}:#{lineno}"
			end
			incom = true
			nil
			next
		end
		if( i =~ /(.*)\*\// ) then
			if( incom == false ) then
				raise "prep: comment-close outside comment. #{fn}:#{lineno}"
			end 
			incom = false
			nil
			next
		end

		if( incom == false ) then
			nil
		else
			"#{fn}:#{lineno}:#{i}\n" 
		end
	}
	return omit_useless(fn,lines)
end

def extract_text_shell(fn,lines)
	lineno = 0
	lines.collect! { |i|
		lineno += 1
		if( !( i=~ /^#(.*)/ ) ) then
			nil
		else
			"#{fn}:#{lineno}:#{$1}\n"
		end
	}

	return omit_useless(fn,lines)
end
def extract_text_plain(fn,lines)
	lineno = 0
	lines.collect! { |i|
		lineno += 1
		"#{fn}:#{lineno}:#{i}\n"
	}
	return omit_useless(fn,lines)
end

def get_http_equiv_encode( lng, nkfopt )
	charset_name = ""

	if( lng == "ja" ) then
		if( nkfopt == "-s" ) then
			charset_name = "Shift-JIS"
		elsif( nkfopt == "-j" ) then
			charset_name = "iso-2022-jp"
		elsif( nkfopt == "-e" ) then
			charset_name = "euc-jp"
        elsif( nkfopt == "-w" ) then
			charset_name = "UTF-8"
		end
	elsif( lng == "en" ) then
		return ""
	end
	return "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=#{charset_name}\">\n"
end


def output_translation_part( headline, string )
    return if( $i_extract_translation_part == 0 ) 
    f = File.open( $s_translation_part_file, "a+")
    f.print "\n"
    f.print "------------------------------------------------------\n"
    f.print headline , "\n\n"
    f.print string , "\n"
    f.close
end


def do_Kconv( nkfopt, str )
	if( nkfopt == "-s" ) then
        return Kconv.tosjis(str)
	elsif( nkfopt == "-j" ) then
		return Kconv.tojis(str)
	elsif( nkfopt == "-e" ) then
		return Kconv.toeuc(str)
    elsif( nkfopt == "-w" ) then
		return Kconv.toutf8(str)
	end
end
#
#
#
main()
