#
# gen_inner.rb
#
#
# Copyright (C) 2000-2005 Community Engine Inc. All rights reserved.
# For more information, please visit our website at www.ce-lab.net.
#

###########################################################################
# 初期化
###########################################################################


def initialize
  @identifier = '='
  @workbufsize = 65536
  @version = -1
  @idmax = 255
  @commandbits = 4
  @sizeofargs=0
  @currentid = 0
  @protocolname = "defaultproto"
  @protocolid = nil
  @serverconnection = :CONN
  @vpr = nil
  @enum = {}
  @enum_seq = 0
  @define = {}
  @static = {}
  @static_base  = {}
  @struct = {}
  @structname = []
  @s2c = []
  @c2s = []
  @q =[]
  @ids = {}
  @variable = {}
  @subversion = nil
  @printf_func = "vce_errout"
  @recvlimit={}
  @ifdef={}
  @sh = []
  @ch = []
  @cliclassmode = 0
end
attr_accessor :identifier, :workbufsize, :static, :static_base,
  :version, :idmax, :protocolname, :serverconnection, :ids, :struct, :structname,
  :enum, :define, :currentid, :s2c, :c2s, :q, :commandbits, :subversion,:sizeofargs,:recvlimit,:ifdef,
  :enum_typedefs, :protocolid, :vpr, :printf_func, :sh, :ch, :cliclassmode

RESERVED = {
  's2c'              => :S2C,
  'c2s'              => :C2S,
  'define'           => :DEFINE,
  'static'           => :STATIC,
  'enum'             => :ENUM,
  'protocolname'     => :PROTOCOLNAME,
  'idmax'            => :IDMAX,
  'workbufsize'      => :WORKBUFSIZE,
  'serverconnection' => :SERVERCONNECTION,
  'protocolid'       => :PROTOCOLID,
  'version'          => :VERSION,
  'sh'				 => :SH,
  'ch'				 => :CH,
  'cliclassmode'	 => :CLICLASSMODE, 
  'struct'           => :STRUCT,
  'recvlimit'        => :RECVLIMIT,
  'ifdef'            => :IFDEF,
  'char'             => :CHAR,
  'short'            => :SHORT,
  'int'              => :INT,
  'int64'            => :INT64,
  'float'            => :FLOAT,
  'uchar'             => :UCHAR,
  'ushort'            => :USHORT,
  'uint'              => :UINT,
  'uint64'            => :UINT64,
  'void'             => :VOID,
  'stringarray'      => :STRINGARRAY,
  'string'           => :STRING,
}
###########################################################################
# プロトコル定義を追加する。
###########################################################################
def add_proto( dest, fname, lineno, id, funcname, args)
  l = [ @s2c, @c2s]
  l.each do |p|
    p.each do |data|
      raise "#{fname}:#{lineno} Command ID #{id} is used again" if data['id'] == id
      raise "#{fname}:#{lineno} Too big ID : #{id} > #{@idmax}" if id > @idmax
    end
  end
  dest.push( { 'funcname' => funcname, 'id'=> id, 'args' => args})
end
###########################################################################
# enum に追加する。
###########################################################################
def add_enum( fname, line, typedef, name, expr)
  if @enum[name] or @define[name] then
    print "warning : #{fname}:#{line} redefined enum #{name}\n"
  end
  num = 0
  seq = -1
  unless expr then
    @enum.each do |key, value|
      if value[0] == typedef then
        if seq < value[2] then
          num = value[1] +1
          seq = value[2]
        end
      end
    end
  end
  @enum[name] = [typedef, expr ? expr: num, @enum_seq]
  @enum_seq += 1
end
###########################################################################
# define に追加する。
###########################################################################
def add_define( fname, line, name, expr)
  if @enum[name] or @define[name] or @static[name] then
    raise( GenError, "error : #{fname}:#{line} redefined define #{name}\n")
  end
  @define[name] = expr
end
###########################################################################
# static に追加する。
###########################################################################
def add_static( fname, line, name, expr)
  if @enum[name] or @static[name] or @define[name] then
    raise( GenError, "error : #{fname}:#{line} redefined static #{name}\n")
  end
  file=File.basename(fname,".*")
  @static[name] = expr
  @static_base[name] = file
end
###########################################################################
# 変数の値を取得する。
###########################################################################
def get_variables_value( fname, line, intern)
  if(@enum[intern])
    return @enum[intern][1]
  elsif(@define[intern])
    return @define[intern]
  elsif(@static[intern])
    return @static[intern]
  else
    raise( GenError, "#{fname}:#{line}: undefined #{intern.to_s}")
  end
#  return @enum[intern][1] if @enum[intern]
#  @define[intern] || raise( GenError, "#{fname}:#{line}: undefined #{intern.to_s}")
end
###########################################################################
# idmax をセットする。
###########################################################################
def set_idmax( id)
  @idmax = id
  if @idmax <= 255 then
    @commandbits = 1
  elsif @idmax <= 65535 then
    @commandbits = 2
  else
    @commandbits = 4
  end
end
###########################################################################
###########################################################################
def include_open( filename, lineno)
  dirs = [ "./"]
  @fname =~ /.*\//
  dirs.push( $&)
  dirs.each do |d|
    begin
      if File.stat( d + filename).file?
        parse_prepare( File.open( d + filename), d + filename)
        return
      end
    rescue
      next
    end
  end
  raise RuntimeError, "#{@fname}:#{lineno}: cannot find #{filename}"
end  
###########################################################################
# パースの前準備。字句解析ルーチン
###########################################################################
def parse_prepare( f, fname)
  @fname = fname
  @config_lines = []
  lineno = 1
  continueflag = false
  f.each do |line|
#    line.strip!
    # 指示行でない行は読み飛ばす。
    reg = Regexp::quote(@identifier)
    directive = line =~ /^#{reg}/ 
    if directive then
      line = $'
    else
      if continueflag then
      else
        lineno += 1
        next
      end
    end

    continueflag=false
    @config_lines.push( line)
    until line.empty? do
        case line
        when /\A\n/, /\A\r\n/
          # コメント
        when /\A\s+/, /\A\#.*/
          # include
        when /\Ainclude\s+"((?:[^"\\]+|\\.)*)"\s*/
          include_open( $1, lineno)
          @fname = fname

          #サーバー側に強制的に追加
        when /\Ash (.*)$/
	      text = $1.dup
#STDERR.print "test ", line ," :: test2 ", text, "::\n"
		  @q.push [ :SH, [lineno, text, fname ]]
          #クライアント側に強制的に追加
        when /\Ach (.*)$/
          text = $1.dup
          @q.push [ :CH, [lineno, text, fname ]]

          # 予約語
        when /\A[a-zA-Z_](\w|[\->\.])*/
          word = $&
          @q.push [ RESERVED[word] || :IDENT, [lineno, word.intern, fname]]
        when /\A[x\da-fA-F]+/
          @q.push [ :NUMBER, [lineno, eval($&), fname] ]
          # バックスラッシュは何もしない eval をしているのは，16進とか8進
          # とかをそのまま整数に変換するため
        when /\A("(?:[^"\\]+|\\.)*")\s*/
          @q.push [ :QSTR, [lineno, $1, fname] ]
        when /\A\\/
          continueflag = true
          # その他全て
        when /\A./
          @q.push [ $&, [lineno, $&, fname] ]
        else
          raise RuntimeError, 'must not happen'
        end
        line = $'
    end
    if continueflag != true then
      @q.push [ :EOL, [lineno, nil, fname]]
    end
    lineno += 1
  end
end
###########################################################################
# パースする。
###########################################################################
def jhash(str)
  result = 0
  mul = 1
  max_mod = 2**31 - 1

  str.chars.reverse_each do |c|
    result += mul * c.ord
    result %= max_mod
    mul *= 31
  end

  result  
end

def parse( f, fname)
  parse_prepare( f, fname)
  h = jhash(@config_lines.join( ""))
  @subversion = h % 1000000000

#  @q.each {|qq|
#    print "Q: #{qq}\n"
#  }
  if @q.size != 0 then
    @q.push [false, '$']
    do_parse
  end
  if @vpr then
    if @protocolid.nil? then
      raise GenError, "not found protocolid directive.\nYou have to set protocolid directive when you set to serverconnection vpr_circ."
    end
  end
end
###########################################################################
# 次のトークン
###########################################################################

def next_token
  @q.shift
end

###########################################################################
# エラーのとき。
###########################################################################
def on_error( t, v, values )
  if v then
    line = v[0]
    v = v[1]
  else
    line = 'last'
  end
  raise Racc::ParseError,
    "#{@fname}:#{line}: syntax error on #{v.inspect}"
end
class GenError < StandardError; end
class GenArgumentError < GenError; end
