# coding: utf-8

class Gen

prechigh
  nonassoc UMINUS
  left '*' '/'
  left '+' '-'

preclow

rule
# ディレクティブの集合から成る
prog : directive_list

# ディレクティブの集合とはディレクティブの集まりである。
directive_list : directive EOL
                | directive_list directive EOL
                

sh : SH
{
  @sh.push( val[0][1] )
}

ch : CH
{
  @ch.push( val[0][1] )
}

# ディレクティブは以下の要素からできている。
directive: defun
        | workbufsize
        | protocolname
        | enum
        | define
        | static
        | idmax
        | serverconnection
        | protocolid
        | version
        | struct
        | recvlimit
        | ifdef
        | directive EOL
        | sh
		| ch
		| cliclassmode
  
workbufsize:      WORKBUFSIZE expr       { @workbufsize = val[1]}
protocolname:     PROTOCOLNAME IDENT
  {
    if @protocolname == "defaultproto"
      @protocolname = val[1][1].to_s 
    end
  }
  
define: DEFINE IDENT expr
{
  add_define( val[0][2], val[0][0], val[1][1], val[2])
}
#      | DEFINE IDENT QSTR
#{
#  add_define( val[0][2], val[0][0], val[1][1],"#{val[3][1]}")
#}

static:           STATIC IDENT expr      { add_static( val[0][2], val[0][0], val[1][1], val[2]) }
#      |      STATIC IDENT '\"'IDENT'\"'     { add_static( val[0][2], val[0][0], val[1][1],"\"#{val[3][1]}\"") }
idmax:            IDMAX expr             { set_idmax( val[1]) }
cliclassmode:     CLICLASSMODE expr      
  { 
    @cliclassmode = val[1].to_i
  }

enum: ENUM IDENT IDENT
  {
    add_enum( val[0][2], val[0][0], val[1][1], val[2][1], nil)
  }
    | ENUM IDENT IDENT expr
  {
    add_enum( val[0][2], val[0][0], val[1][1], val[2][1], val[3])
  }
  
serverconnection: SERVERCONNECTION IDENT
  {
    if val[1][1] != :conn and val[1][1] != :circ and val[1][1] != :vpr_circ then
      raise GenError, "#{val[1][2]}:#{val[1][0]}: serverconnection has to be 'conn' or 'circ' or 'vpr_circ'."
    end
    if val[1][1] == :vpr_circ then
      @vpr = true
      @serverconnection = :circ
    else
      @serverconnection = val[1][1]
    end
  }

protocolid: PROTOCOLID NUMBER
  {
    id = val[1][1].to_i
    if id <= 0 or id > 255 then
      raise GenError, "#{val[1][2]}:#{val[1][0]}: you should set protocol id from 1 to 255 [#{id}]\n"
    end
    @protocolid = val[1][1]
  }
version:          VERSION expr
{
  if @version == -1
    @version = val[1]
   end
}

struct:  STRUCT IDENT '{' name_list '}'
  {
    str = @protocolname + "_" + val[1][1].to_s
    @structname.push( str )
    @struct[str] = val[3]
  }

ifdef: IFDEF IDENT IDENT
  {
    @ifdef["#{val[2][1]}"]=val[1][1]
  }
  
recvlimit: RECVLIMIT IDENT NUMBER NUMBER
  {
    @recvlimit["#{val[1][1]}.limit"]=val[2][1]
    @recvlimit["#{val[1][1]}.time"]=val[3][1]
  }

#プロトコル定義
defun : S2C NUMBER IDENT param
  {
    add_proto( @s2c, val[1][2], val[1][0], val[1][1], val[2][1], val[3])
    @currentid = val[1][1]
  }
      # id が無い場合は自動的に前回のid+1した物が使用される。
      | S2C IDENT param
  {
    @currentid += 1
    add_proto( @s2c, val[1][2], val[1][0], @currentid, val[1][1], val[2])
  }
      | C2S NUMBER IDENT param
  {
    add_proto( @c2s, val[1][2], val[1][0], val[1][1], val[2][1], val[3])
    @currentid = val[1][1]
  }
      # id が無い場合は自動的に前回のid+1した物が使用される。
      | C2S IDENT param
  {
    @currentid += 1
    add_proto( @c2s, val[1][2], val[1][0], @currentid, val[1][1], val[2])
  }
                
# プロトコルパラメータ
param : '(' name_list ')' { result = val[1] }
      | '(' ')'           { result = [] }
      | '(' VOID ')'      { result = [] }
      
# パラメータのリスト
name_list : arg                { result = [ val[0]] }
          | name_list ',' arg  { result.push val[2] }
          
# パラメータとは。
arg : type variable
  {
    # パラメータが配列の時
    if val[1].is_a? Array then
      result = { 'type' => :array, 'vartype' => val[0], 'name' => val[1][0], 'value' => val[1][1]}
    else
      result = { 'type' => :single, 'vartype' => val[0], 'name' => val[1], 'value' => [nil,nil]}
    end
  }
    | STRINGARRAY array_2d
  {
    result = { 'type' => :array, 'vartype' => val[0][1], 'name' => val[1][0], 'value' => val[1][1]}
  }
    
# タイプとは
type : INT   { result = val[0][1] }
     | CHAR  { result = val[0][1] }
     | SHORT { result = val[0][1] }
     | INT64 { result = val[0][1] }
     | UINT  { result = val[0][1] }
     | USHORT { result = val[0][1] }
     | UCHAR  { result = val[0][1] }
     | STRING { result = val[0][1] }
     | IDENT  { result = val[0][1] }
     | FLOAT  { result = val[0][1] }

# 変数
variable : IDENT { result = val[0][1] }
         | array { result = val[0] }
         

# 配列とは
array   : IDENT element         { result = [val[0][1], [val[1]]] }

# 二次元配列までしかサポートしない
array_2d: IDENT element element { result = [val[0][1], [val[1], val[2]]] }

# 配列の添字
element : '[' expr ']' { result = val[1] }

# 演算
expr : expr '+' expr { result = val[0] + val[2] }
     | expr '-' expr { result = val[0] - val[2] }
     | expr '*' expr { result = val[0] * val[2] }
     | expr '/' expr { result = val[0] / val[2] }
     | primary

# 括弧とか
primary : realprim
        | '(' expr ')'      { result = val[1] }
        | '-' expr  =UMINUS { result = -val[1] }
               
# これが一番アトミックなもの。
# IDENT は変数のように扱う。実際はenum かdefineかで定義される。

realprim : IDENT  { result = get_variables_value( val[0][2], val[0][0], val[0][1]) }
         | NUMBER { result = val[0][1] }
         | QSTR { result = val[0][1] }
 
end

---- header
---- inner = gen_inner.rb
---- footer = gen_maker.rb gen_maker_c.rb gen_maker_rb.rb gen_footer.rb 
