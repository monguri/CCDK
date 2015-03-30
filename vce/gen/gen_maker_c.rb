#
# gen_maker_c.rb
#
#
# Copyright (C) 2000-2005 Community Engine Inc. All rights reserved.
# For more information, please visit our website at www.ce-lab.net.
#

# c and cpp のソースを出力する実装のクラス

class Genmaker_c < Genmaker::Abstract
  Command_bits_type = { 1 => "unsigned char", 2 => "unsigned short",4 => "unsigned int" }
  Command_bits_getter = { 1 => "GET_8BIT_INT", 2 => "GET_16BIT_INT",4 => "GET_32BIT_INT"}
#  Command_bits_setter = { 1 =>"SET_8BIT_INT", 2 =>"SET_16BIT_INT", 4 => "SET_32BIT_INT"}
  Command_bits_setter = { 1 =>"_PUSH_I1", 2 =>"_PUSH_I2", 4 => "_PUSH_I4", 8 => "_PUSH_I8" }
  def initialize( gen, sv, cli, testsv, testcli, testrecvcli, use_const )
    super( gen, sv, cli, testsv, testcli, testrecvcli )
    if use_const
      @const_str = 'const'
    else
      @const_str = ''
    end
  end
  def extention
    "c"
  end
  def get_popper(type,vartype,name,num,subnum)
    data = {
      "single.char" => "_POP_I1",
      "single.short" => "_POP_I2",
      "single.int" => "_POP_I4",
      "single.int64" => "_POP_I8",
      "single.uchar" => "_POP_I1",
      "single.ushort" => "_POP_I2",
      "single.uint" => "_POP_I4",
      "single.float" => "_POP_F4",
      "array.char" => "_POP_IA1",
      "array.short" => "_POP_IA2",
      "array.int" => "_POP_IA4",
      "array.int64" => "_POP_IA8",
      "array.uchar" => "_POP_IA1",
      "array.ushort" => "_POP_IA2",
      "array.uint" => "_POP_IA4",
      "array.float" => "_POP_FA4",
      "array.char *" => "_POP_STRA" }
    r = data[ "#{type}.#{vartype}" ]
#    raise "bad type and vartype '#{type}.#{vartype}'" if( r == nil ) 
    if( r == nil ) then
      outwk = ""
      outwk += get_popper_struct( vartype, name, num, 0 )
      return outwk
#      return get_popper_struct( vartype, name )
    end

    if( type == "array" ) then
      if( vartype == "char *" ) then
        return "#{r}(#{name},#{name}_len,#{subnum},#{name}_i,#{name}_p);\n"
      else
        return "#{r}(#{name},#{name}_len);\n"
      end
    else
      return "#{r}(#{name});\n"
    end
  end

  def get_popper_struct( vartype,structname,nummax,nest,out = "",str_add = "" )
    if( @gen.struct["#{@gen.protocolname}_#{vartype}"] == nil )
      vartypewk = vartype
      vartype = vartypewk.upcase
      raise "bad type and vartype #{vartype}" if( @gen.struct["#{@gen.protocolname}_#{vartype}"] == nil )
    end

    data = {
      "single.char"   => "_POP_I1",
      "single.short"  => "_POP_I2",
      "single.int"    => "_POP_I4",
      "single.int64"  => "_POP_I8",
      "single.uchar"  => "_POP_I1",
      "single.ushort" => "_POP_I2",
      "single.uint"   => "_POP_I4",
      "single.float"  => "_POP_F4",
      "array.char"    => "_POP_IA1",
      "array.short"   => "_POP_IA2",
      "array.int"     => "_POP_IA4",
      "array.int64"   => "_POP_IA8",
      "array.uchar"   => "_POP_IA1",
      "array.ushort"  => "_POP_IA2",
      "array.uint"    => "_POP_IA4",
      "array.float"   => "_POP_FA4",
      "array.char *"  => "_POP_STRA",
      "array.stringarray"  => "_POP_STRA",
      "array.string"  => "_POP_IA1" }

    if ( str_add == "" ) then
      str_add = structname
    else
      str_add = "#{str_add}.#{structname}"
    end

    index = "i"
    space1 = "        "
    space2 = "    "
    if( nummax != nil )
      if( nest == 0 )
        out += "int i, j;\n"
        out += "    int lenwk;\n"
      else
        space1 += "    "
        space2 += "    "
        index = "j"
      end
      r = data["single.int"]
      out += "#{space2}#{r}(#{str_add}_len)\n"
      out += "#{space2}for(#{index} = 0; #{index} < #{str_add}_len; #{index}++)\n"
      out += "#{space2}{\n"
    end
    @gen.struct["#{@gen.protocolname}_#{vartype}"].each do |val|

      name = val['name']
      num = val['value'][0]

      r = data["#{val['type']}.#{val['vartype']}"]
      outwk = ""
      if( r == nil )
        str_add = "#{structname}[#{index}]"
        out += get_popper_struct( val['vartype'],name,num,1,outwk,str_add )
	    next
      end

      if( nummax == nil ) then
        if( val['type'] == :array ) then
          if( val['vartype'] == :string ) then
            out += "#{space1}lenwk = #{num};\n"
            out += "#{space1}#{r}(#{str_add}.#{name},lenwk);\n"
          elsif( val['vartype'] == :stringarray ) then
            out += "#{space1}#{r}(#{str_add}.#{name},#{str_add}.#{name}_len,#{val['value'][1]},#{name}_i,#{name}_p);\n"
          else
            out += "#{space1}#{str_add}.#{name}_len = #{num};\n"
            out += "#{space1}#{r}(#{str_add}.#{name},#{str_add}.#{name}_len);\n"
          end
        else
          out += "#{space1}#{r}(#{str_add}.#{name});\n"
        end
      else
        s_part = "#{str_add}[#{index}]"
        if( val['type'] == :array ) then
          if( val['vartype'] == :string ) then
            out += "#{space1}lenwk = #{num};\n"
            out += "#{space1}#{r}(#{s_part}.#{name},lenwk);\n"
          elsif( val['vartype'] == :stringarray ) then
            out += "#{space1}#{r}(#{s_part}.#{name},#{s_part}.#{name}_len,#{val['value'][1]},#{name}_i,#{name}_p);\n"
          else
            out += "#{space1}#{s_part}.#{name}_len = #{num};\n"
            out += "#{space1}#{r}(#{s_part}.#{name},#{s_part}.#{name}_len);\n"
          end
        else
          out += "#{space1}#{r}(#{s_part}.#{name});\n"
        end
      end
    end
    if( nummax != nil )
      out += "#{space2}}\n"
    end
    return out
  end

  def get_struct_length( vartype, len )
    if( @gen.struct["#{@gen.protocolname}_#{vartype}"] == nil )
      vartypewk = vartype
      vartype = vartypewk.upcase
      raise "bad type and vartype #{vartype}" if( @gen.struct["#{@gen.protocolname}_#{vartype}"] == nil )
    end

    datasize = {
      "single.char" => 1,
      "single.short" => 2,
      "single.int" => 4,
      "single.int64" => 8,
      "single.uchar" => 1,
      "single.ushort" => 2,
      "single.uint" => 4,
      "single.float" => 4,
      "array.char" => 1,
      "array.short" => 2,
      "array.int" => 4,
      "array.int64" => 8,
      "array.uint" => 4,
      "array.float" => 4,
      "array.uchar" => 1,
      "array.ushort" => 2,
      "array.char *" => 1 }
    @gen.struct["#{@gen.protocolname}_#{vartype}"].each do |val|
      vtype = val['type']
      vvartype = val['vartype']
      vnum = val['value'][0]
      vsubnum = val['value'][1]
      if( vvartype == :stringarray ) then
        vvartype = "char *"
      elsif( vvartype == :string ) then
        vvartype = "char"
      end
      lenwk = datasize["#{vtype}.#{vvartype}"]
      if( lenwk == nil )
        lenwk = 0
        if( vnum != nil )
          len += get_struct_length( vvartype, lenwk )*vnum
          len += 5
        else
          len += get_struct_length( vvartype, lenwk )
        end
#        next
      else
        if( vnum != nil )
          if( vsubnum != nil )
            len += lenwk*vnum*vsubnum
            len += 5*vnum
          else
            len += lenwk*vnum
            len += 5
          end
        else
          len += lenwk
        end
      end
      if( vvartype == "char" || vvartype == "char *" )
        len += 5
      end
    end
    return len
  end

  def get_pusher(type,vartype,name,num,subnum,outmax)
    data = {
      "single.char" => "_PUSH_I1",
      "single.short" => "_PUSH_I2",
      "single.int" => "_PUSH_I4",
      "single.int64" => "_PUSH_I8",
      "single.uchar" => "_PUSH_I1",
      "single.ushort" => "_PUSH_I2",
      "single.uint" => "_PUSH_I4",
      "single.float" => "_PUSH_F4",
      "array.char" => "_PUSH_IA1",
      "array.short" => "_PUSH_IA2",
      "array.int" => "_PUSH_IA4",
      "array.int64" => "_PUSH_IA8",
      "array.uint" => "_PUSH_IA4",
      "array.float" => "_PUSH_FA4",
      "array.uchar" => "_PUSH_IA1",
      "array.ushort" => "_PUSH_IA2",
      "array.char *" => "_PUSH_STRA" }
    r = data["#{type}.#{vartype}" ]
#    raise "bad type and vartype '#{type}.#{vartype}'" if( r == nil ) 
    if( r == nil ) then
      outwk = ""
      outwk += get_pusher_struct( vartype,name,outmax,num,0 )
      return outwk
#     return get_pusher_struct( vartype, name, outmax )
    end

    if( type == "array" ) then
      if( vartype == "char *" )then
        return "#{r}(#{name},#{name}_len,#{num},#{outmax},#{subnum});\n"
      else
        return "#{r}(#{name},#{name}_len,#{num},#{outmax});\n"
      end
    else
      return "#{r}(#{name},#{outmax});\n"
    end
  end

  def get_pusher_struct( vartype,structname,outmax,nummax,nest,out = "",str_add = "" )
    if( @gen.struct["#{@gen.protocolname}_#{vartype}"] == nil )
      vartypewk = vartype.to_s
      vartype = vartypewk.upcase
      raise "bad type and vartype #{vartype}" if( @gen.struct["#{@gen.protocolname}_#{vartype}"] == nil )
    end

    data = {
      "single.char"   => "_PUSH_I1",
      "single.short"  => "_PUSH_I2",
      "single.int"    => "_PUSH_I4",
      "single.int64"  => "_PUSH_I8",
      "single.uchar"  => "_PUSH_I1",
      "single.ushort" => "_PUSH_I2",
      "single.uint"   => "_PUSH_I4",
      "single.float"  => "_PUSH_F4",
      "array.char"    => "_PUSH_IA1",
      "array.short"   => "_PUSH_IA2",
      "array.int"     => "_PUSH_IA4",
      "array.int64"   => "_PUSH_IA8",
      "array.uchar"   => "_PUSH_IA1",
      "array.ushort"  => "_PUSH_IA2",
      "array.uint"    => "_PUSH_IA4",
      "array.float"   => "_PUSH_FA4",
      "array.char *"  => "_PUSH_STRA",
      "array.stringarray"  => "_PUSH_STRA",
      "array.string"  => "_PUSH_IA1" }

    if( str_add == "" ) then
      str_add = structname
    else
      str_add = "#{str_add}.#{structname}"
    end

    index = "i"
    space1 = "     "
    space2 = "  "
    if( nummax != nil ) then
      r = data["single.int"]
      if( nest == 0 )
        out += "int i, j;\n"
      else
        index = "j"
        space1 += "   "
        space2 += "   "
      end
      out += "#{space2}#{r}(#{str_add}_len,#{outmax})\n"
      out += "#{space2}for(#{index} = 0; #{index} < #{str_add}_len; #{index}++)\n"
      out += "#{space2}{\n"
    end
    @gen.struct["#{@gen.protocolname}_#{vartype}"].each do |val|
      name = val['name']
      num  = val['value'][0]

      r = data["#{val['type']}.#{val['vartype']}"]
      outwk = ""
      if( r == nil ) then
        str_add = "#{structname}[#{index}]"
        out += get_pusher_struct( val['vartype'],name,outmax,num,1,outwk,str_add )
	    next
      end

      if( nummax == nil ) then
        if( val['type'] == :array ) then
          if( val['vartype'] == :stringarray ) then
            out += "#{space1}#{r}(#{str_add}.#{name},#{str_add}.#{name}_len,#{num},#{outmax},#{val['value'][1]});\n"
          elsif( val['vartype'] == :string ) then
            out += "#{space1}#{r}(#{str_add}.#{name},strlen(#{str_add}.#{name})+1,#{num}+1,#{outmax});\n"
          else
            out += "#{space1}#{r}(#{str_add}.#{name},#{str_add}.#{name}_len,#{num},#{outmax});\n"
          end
        else
          if( val['vartype'] == :string ) then
            out += "#{space1}#{r}(#{str_add}.#{name},strlen(#{str_add}.#{name})+1,#{num}+1,#{outmax});\n"
          else
            out += "#{space1}#{r}(#{str_add}.#{name},#{outmax});\n"
          end
        end
      else
        s_part = "#{str_add}[#{index}]"
        if( val['type'] == :array ) then
          if( val['vartype'] == :stringarray ) then
            out += "#{space1}#{r}(#{s_part}.#{name},#{s_part}.#{name}_len,#{num},#{outmax},#{val['value'][1]});\n"
          elsif( val['vartype'] == :string ) then
            out += "#{space1}#{r}(#{s_part}.#{name},strlen(#{s_part}.#{name})+1,#{num}+1,#{outmax});\n"
          else
            out += "#{space1}#{r}(#{s_part}.#{name},#{s_part}.#{name}_len,#{num},#{outmax});\n"
          end
        else
          if( val['vartype'] == :string ) then
            out += "#{space1}#{r}(#{s_part}.#{name},strlen(#{s_part}.#{name})+1,#{num}+1,#{outmax});\n"
          else
            out += "#{space1}#{r}(#{s_part}.#{name},#{outmax});\n"
          end
        end
      end
    end
    if( nummax != nil ) then
      out += "#{space2}}\n"
    end
    return out
  end

  # C関数のプロトタイプを作る
  # ()の中はコンマでくぎった識別子定義の列である。
  # 識別子定義は、 TYPE NAME  または TYPE NAME [ NUM ] である。
  # Syntax error の場合は raiseする
  # Hashをつくって配列に入れる。
  # pname : プロトコル名
  # action: send/recv
  # iovar : circ_t または conn_t
  # argdef : parse_arglist のかえりち
  def make_ptype( action, name, argdef, con = nil)
    svcon = nil
    if con then
      svcon = con
    else
      svcon = @gen.serverconnection
    end
    if argdef.size == 0 then
      return "int #{@gen.protocolname}_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}_#{action}( #{svcon}_t _c )"
    else
      out = "int #{@gen.protocolname}_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}_#{action}( #{svcon}_t _c, "
      append = []

	not_struct = [ "char", "short", "int", "int64", "uchar", "ushort", "uint", "float", "string", "stringarray" ]

      argdef.each{ |i|

        if ( not_struct.index( i["vartype"].to_s ) == nil ) then
          usetype = shorttype2longtype( i["vartype"].to_s )
          if i["type"] == :single
            append.push( "#{@gen.protocolname}_#{usetype} #{i["name"]}" )
          else
            append.push( "#{@gen.protocolname}_#{usetype} *#{i["name"]}, "+
                           "int #{i["name"]}_len" )
          end
        elsif i["type"] == :single then
          usetype = i["vartype"].to_s
          usetype = shorttype2longtype(usetype)
          append.push( "#{usetype} #{i["name"]}" )
        else
          if i["vartype"] == :string then
            append.push( "#{@const_str} char *#{i["name"]}" )
          elsif i["vartype"] == :stringarray then
            append.push( "#{@const_str} char * #{@const_str} *#{i["name"]}, " +
                           "int #{i["name"]}_len" )
          else
            usetype = i["vartype"].to_s
            usetype = shorttype2longtype(usetype)
            append.push( "#{@const_str} #{usetype} *#{i["name"]}, " +
                           "int #{i["name"]}_len" )
          end
        end
      }
      return out + append.join(", ") + " )"
    end
  end

  #受信回数をカウントするための変数初期化
  def get_conn_varinit( msgname)
    limit="#{msgname}.limit"
    time="#{msgname}.time"
    if @gen.recvlimit[limit] &&  @gen.recvlimit[time]
      return "  #{@gen.protocolname}_t_#{msgname}[index].count=0;\n  #{@gen.protocolname}_t_#{msgname}[index].next=next;\n"
    else
      return ""
    end
  end

  #受信回数をカウントするための変数定義
  def get_conn_vardef( msgname)
    limit="#{msgname}.limit"
    time="#{msgname}.time"
    if @gen.recvlimit[limit] &&  @gen.recvlimit[time]
      return "static #{@gen.protocolname}_t #{@gen.protocolname}_t_#{msgname}[#{@gen.protocolname.upcase}_MAX_CONNECTION];\n"
    else
      return ""
    end
  end

  # DebugDisable変数出力
  def get_dd_vardef( action, msgname)
    return "static int #{@gen.protocolname}_#{msgname.to_s().gsub(/^.*?((\.)|(->))/,"")}_#{action}_debugout = 1;\n"
  end

  def get_dd_funcptype( action, msgname)
    return "void #{@gen.protocolname}_#{msgname.to_s().gsub(/^.*?((\.)|(->))/,"")}_#{action}_debugprint(int on_off);\n"
  end
  
  def get_dd_funcdef( action, msgname)
    out="void #{@gen.protocolname}_#{msgname.to_s().gsub(/^.*?((\.)|(->))/,"")}_#{action}_debugprint(int on_off)\n"
    out+="{\n  #{@gen.protocolname}_#{msgname.to_s().gsub(/^.*?((\.)|(->))/,"")}_#{action}_debugout=on_off;\n}\n"
    return out
  end

  # 数えるための変数出力
  def get_cnt_vardef( action, msgname)
    return "static double #{@gen.protocolname}_#{msgname.to_s.gsub(/^.*?((->)|(\.))/, "")}_#{action}_counter = 0;\n"
  end

  # 数えるための関数出力
  def get_cnt_funcdef( action, msgname )
    pt = make_cnt_ptype( action, msgname)
    out = "#{pt}\n"
    out+= "{\n"
    out+= "  return #{@gen.protocolname}_#{msgname.to_s.gsub(/^.*?((->)|(\.))/, "")}_#{action}_counter;\n"
    out+= "}\n"
  end

  # 回数カウント用の関数のプロトタイプを作る
  def make_cnt_ptype( action, name)
    return "double #{@gen.protocolname}_get_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}_#{action}_count( void )"
  end
  
  # C言語の送信用関数を出力する。
  # iovar: conn_t or circ_t
  # worksize: ワークバッファのサイズ(設定ファイルからよむ)
  # id : コマンドID
  def get_send_funcdef( name, argdef, id, sender, con = nil)
    svcon = nil
    if con then
      svcon = con
    else
      svcon = @gen.serverconnection
    end
    pr = make_ptype( "send", name, argdef, svcon)

    datasize = {
      "single.char" => 1,
      "single.short" => 2,
      "single.int" => 4,
      "single.int64" => 8,
      "single.uchar" => 1,
      "single.ushort" => 2,
      "single.uint" => 4,
      "single.float" => 4,
      "array.char" => 1,
      "array.short" => 2,
      "array.int" => 4,
      "array.int64" => 8,
      "array.uint" => 4,
      "array.float" => 4,
      "array.uchar" => 1,
      "array.ushort" => 2,
      "array.char *" => 1 }
    pushcode = ""
    format = ""
    pargs = ""
    str_stringtype = "";
    strwk = ""
    strmake = ""
    argsize=@gen.commandbits
    argdef.each{ |i|
      vtype = i["type"].to_s
      vnum = i["value"][0]
      vsubnum = i["value"][1]
      vname = i["name"].to_s

      if i['vartype'] == :string then
          vvartype = "char"
          str_stringtype += "  int #{vname}_len = strlen( #{vname} ) + 1;\n"
      elsif i['vartype'] == :stringarray then
          vvartype = "char *"
      else
          vvartype = i['vartype'].to_s
      end
      vvartype.downcase!

      pushcode += "  " + get_pusher( vtype,
                                    vvartype,vname,vnum,vsubnum,
                                    "sizeof(_work)" )

	# 構造体の場合
      if datasize["#{vtype}.#{vvartype}"] == nil then
        argsizewk = 0
        if vnum == nil then
          argsize += get_struct_length( "#{vvartype}", argsizewk )
        else
          argsize += get_struct_length( "#{vvartype}", argsizewk )*vnum
        end
	# debug_print atari ha source minaoshi de tewoiretai
#          strwk += "    struct #{vvartype} _#{vname}wk;\n";
#          format += ", #{vname}=%d"
#          pargs += ", #{vname}"
      elsif vtype == "single"
        if vvartype == "int64"
          format += ", #{vname}=%lld"
        elsif vvartype == "float"
          format += ", #{vname}=%g"
        else
          format += ", #{vname}=%d"
        end
        pargs += ", #{vname}"
        argsize += datasize["#{vtype}.#{vvartype}" ]
      else
        if vvartype == "char"
          format += ", #{vname}[%d]='%s'"
          pargs += ", #{vname}_len, _#{vname}wk"
          strwk += "    char _#{vname}wk[#{vnum.to_i + 1}];\n";
          strmake += "    _make_debug_print_str( _#{vname}wk, #{vnum.to_i + 1}, #{vname}, #{vname}_len);\n"
        else
          format += ", #{vname}[%d]"
          pargs += ", #{vname}_len"
        end
        if vsubnum
          argsize += datasize["#{vtype}.#{vvartype}" ]*vnum*vsubnum
          argsize += 5*vnum
        else
          argsize += datasize["#{vtype}.#{vvartype}" ]*vnum
          argsize += 5
        end
      end

    }
    commandbitssetter = Command_bits_setter[@gen.commandbits]
    out = "/****/\n"
    out+= "#{pr}\n"
    out+= "{\n"
    out+= "  /* Make bin_info array */\n"
    out+= "  char _work[#{argsize}];\n"
    out+= "  int _ofs = 0;\n"
    out+= str_stringtype
    out+= "  #{@gen.protocolname}_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}_send_counter += 1;\n"
    
    if con and @gen.serverconnection == :circ and @gen.vpr then
      out += "  _PUSH_I1( #{@gen.protocolid}, sizeof(_work));\n"
    end   
#    out+= "  #{commandbitssetter}(_work, #{id} );\n"
    ft=""
    if con
      ft="c2s"
    else
      ft="s2c"
    end
    
    edef="#{@gen.protocolname}_#{ft}_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}"
    out+= "  #{commandbitssetter}( #{edef.upcase}, sizeof( _work));\n"
    out+= "#{pushcode}\n"
    if @gen.ifdef["#{name}"]
      out+= "#ifdef #{@gen.ifdef["#{name}"]}\n"
    end
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "  if(#{@gen.protocolname}_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}_send_debugout)\n"
    out+= "  {\n"
    out+= "    char _addr[256];\n"
    out+= "    int _retsend;\n"
    out+= strwk
    out+= strmake
    out+= "    #{@gen.printf_func}( \"#{@gen.protocolname}_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}_send( [%s]#{format} )\\n\" , vce_#{svcon}_get_remote_addr_string( _c, _addr, sizeof(_addr) ) #{pargs} );\n"
    out+= "    _retsend=#{@gen.protocolname}_#{sender}( _c, _work, _ofs);\n"
    out+= "    if(_retsend<0){\n"
    out+= "      vce_errout(\"protocol error : #{@gen.protocolname}_#{name.to_s.gsub(/^.*?((->)|(\.))/, "")}_send code : %d\\n\",_retsend);\n"
    out+= "    }\n"
    out+= "    return _retsend;\n"
    out+= "  }\n"
    out+= "  else\n"
    out+= "    return #{@gen.protocolname}_#{sender}( _c, _work, _ofs);\n"
    out+= "#else\n"
    out+= "  return #{@gen.protocolname}_#{sender}( _c, _work, _ofs);\n"
    out+= "#endif\n"
    if @gen.ifdef["#{name}"]
      out+= "#else\n"
      out+= "  return 0;\n"
      out+= "#endif\n"
    end
    out+= "}\n"
    return out
  end

  # 関数のIDにあわせたenumを作る。
  def make_funcenum( funcname, id,type)
    en = "  #{@gen.protocolname}_#{type}_#{funcname.to_s().gsub(/.*?((\.)|(->))/,"")}=#{id},\n"
#    STDERR.print en.upcase
    return en.upcase
  end
  
  #
  # 受信用スイッチのcaseを出力する(C言語用)
  #
  def get_recv_casedef( name, argdef, id, isclient, con=nil)

    name2 = ""

    if isclient == false
        if name.to_s.scan(/\./) != []
            name2 = name.to_s.gsub(/\./, ".#{@gen.protocolname}_")
        elsif name.to_s.scan(/->/) != []
            name2 = name.to_s.gsub(/->/, "->#{@gen.protocolname}_")
        else
            name2 = "#{@gen.protocolname}_#{name}"
    	end
	else
		if name.to_s.scan(/\./) != []
            name2 = name.to_s.gsub(/.*?\./, "#{@gen.protocolname}_")
        elsif name.to_s.scan(/->/) != []
            name2 = name.to_s.gsub(/.*?->/, "#{@gen.protocolname}_")
        else
            name2 = "#{@gen.protocolname}_#{name}"
    	end
	end

    if( argdef.size == 0 ) then
      out = "  case #{id} :\n"
      out+= "#ifdef GEN_DEBUG_PRINT\n"
      out+= "    #{@gen.printf_func}( \"#{name2}_recv()\\n\" );\n"
      out+= "#endif\n"
      out+= "    _ret = #{name2}_recv( _c );\n"
      out+= "    break;\n"
      return out
    end
    if con then
      svcon = con
    else
      svcon = @gen.serverconnection
    end

    datasize = {
      "single.char" => 1,
      "single.short" => 2,
      "single.int" => 4,
      "single.int64" => 8,
      "single.uchar" => 1,
      "single.ushort" => 2,
      "single.uint" => 4,
      "single.float" => 4,
      "array.char" => 1,
      "array.short" => 2,
      "array.int" => 4,
      "array.int64" => 8,
      "array.uint" => 4,
      "array.float" => 4,
      "array.uchar" => 1,
      "array.ushort" => 2,
      "array.char *" => 1 }
    vardecls = ""
    lensets = ""
    args = []
    popcode = ""
    format = ""
    pargs = ""
    strwk = ""
    strmake = ""
    argsize=@gen.commandbits
    argdef.each{ |i|
      vtype = i["type"].to_s
      vnum = i["value"][0]
      vsubnum = i["value"][1]

      if i['vartype'] == :string then
          vvartype = "char"
      elsif i['vartype'] == :stringarray then
          vvartype = "char *"
      else
          vvartype = i["vartype"].to_s
      end
      vvartype.downcase!
      vname = i["name"].to_s

      popcode += "    " + get_popper( vtype,vvartype,vname,vnum,vsubnum )

      if datasize["#{vtype}.#{vvartype}"] == nil then
        # 構造体の場合
        vallist = ""
        if vtype == "array"
          vardecls += "    #{@gen.protocolname}_#{vvartype} #{vname}[#{vnum}];\n"
          vardecls += "    int #{vname}_len = #{vnum};"
          vallist += "#{vname}, #{vname}_len"
        else
          vardecls += "    #{@gen.protocolname}_#{vvartype} #{vname};\n"
          vallist += "#{vname}"
        end
        argsizewk = 0
        if vnum == nil then
          argsize += get_struct_length( "#{vvartype}", argsizewk )
        else
          argsize += get_struct_length( "#{vvartype}", argsizewk )*vnum
          argsize += 5
        end
#        pargs += ",#{vname}"
        args.push(vallist)		# xxx_xxx_recvに追加される

      elsif( vtype == "single" ) then
        if vvartype == "int64" 
          format += ", #{vname}=%lld"
        elsif vvartype == "float"
          format += ", #{vname}=%g"
        else
          format += ", #{vname}=%d"
        end
        argsize += datasize["#{vtype}.#{vvartype}" ]
        vvartype = shorttype2longtype(vvartype)
        vardecls += "    #{vvartype} #{vname};\n"
        pargs += ",#{vname}"
        args.push(vname)
      else
        if( vvartype == "char *") then
          vardecls += "    char #{vname}[#{vnum}][#{vsubnum}];\n"
          vardecls += "    int #{vname}_len = #{vnum};\n"
          vardecls += "    char *#{vname}_p[#{vnum}];\n"
          vardecls += "    int #{vname}_i;\n"
          format += ", #{vname}[%d]"
          pargs += ",#{vname}_len"
          args.push("#{vname}_p,#{vname}_len" )
          argsize += datasize["#{vtype}.#{vvartype}" ] * vnum * vsubnum
          argsize += 5 * vnum
        else
          argsize += datasize["#{vtype}.#{vvartype}" ] * vnum
          argsize += 5
          vvartype = shorttype2longtype(vvartype)
          vardecls += "    #{vvartype} #{vname}[#{vnum}];\n"
          vardecls += "    int #{vname}_len = #{vnum};\n"
          if vvartype == "char"
            format += ", #{vname}[%d]='%s'"
            pargs += ", #{vname}_len, _#{vname}wk"
            strwk += "    char _#{vname}wk[#{vnum.to_i + 1}];\n";
            strmake += "    _make_debug_print_str( _#{vname}wk, #{vnum.to_i + 1}, #{vname}, #{vname}_len);\n"
          else
            format += ", #{vname}[%d]"
            pargs += ", #{vname}_len"
          end

          if i['vartype'] == :string then
            args.push(vname)
          else
            args.push(vname,vname+"_len" )
          end
        end
      end
    }
    
    unless con
#      STDERR.print "server recv protocolsize: #{argsize}\n" 
      if(argsize>@gen.sizeofargs)
        @gen.sizeofargs = argsize
      end
    end
    
    argstr = args.join( ",")
    
    ft=""
    if con
      ft="s2c"
    else
      ft="c2s"
    end

    edef="#{@gen.protocolname}_#{ft}_#{name.to_s().gsub(/.*?((\.)|(->))/,"")}"
    out = "  case  #{edef.upcase} :/* record length : #{argsize} */\n"
    out+= "  {\n"
    out+= "#{vardecls}\n"
    

    # unless con
    #   limit="#{name}.limit"
    #   time="#{name}.time"
    #   if @gen.recvlimit[limit] &&  @gen.recvlimit[time]
    #     counttime=@gen.recvlimit[time] / @gen.recvlimit[limit]
    #     out+="    /* too many call check */\n"
    #     out+="    if(_con_index>=0&&-1==#{@gen.protocolname}_manycall_check(&#{@gen.protocolname}_t_#{name}[_con_index],#{@gen.recvlimit[limit]},#{counttime}000))\n"
    #     out+="    {\n"
    #     out+="      int _eret=#{@gen.protocolname}_toomany_recv_warning(_c,#{id});\n"
    #     out+="#ifdef GEN_DEBUG_PRINT\n"
    #     out+="      vce_errout(\"too many call #{name}\\n\");\n"
    #     out+="#endif\n"
    #     out+="      if(_eret<0)\n"
    #     out+="        return _eret;\n"
    #     out+="    }\n"
    #   end
    # end
    
    unless con
      out+= "    /* protocol length check */\n"
      out+= "    if(#{argsize}<_len){\n"
      out+= "      int _eret=#{@gen.protocolname}_toolong_recv_warning(_c,#{id},_len);\n"
      out+= "#ifdef GEN_DEBUG_LEN_PRINT\n"
      out+= "      vce_errout(\"invalid length : recv%dbytes #{name2}_recv\\n\",_len);\n"
      out+= "#endif\n"
      out+= "      if(_eret<0)\n"
      out+= "        return _eret;\n"
      out+= "    }\n\n"
    end
    
    out+= "#{popcode}\n"
    out+= "    #{@gen.protocolname}_#{name.to_s().gsub(/^.*?((\.)|(->))/,"")}_recv_counter += 1;\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "    if(#{@gen.protocolname}_#{name.to_s().gsub(/^.*?((\.)|(->))/,"")}_recv_debugout)\n"
    out+= "    {\n"
    out+= "      char _addr[256];\n"
    out+= strwk
    out+= strmake
    out+= "      #{@gen.printf_func}( \"#{name2}_recv( [%s]#{format} )\\n\", vce_#{svcon}_get_remote_addr_string( _c, _addr, sizeof(_addr) ) #{pargs} );\n" 
    out+= "    }\n"
    out+= "#endif\n"

    if @gen.ifdef["#{name}"]
      out+= "#ifdef #{@gen.ifdef["#{name}"]}\n"
    end
    out+= "    _ret = #{name2}_recv( _c, #{argstr});\n"
    if @gen.ifdef["#{name}"]
      out+= "#else\n"
      out+= "    _ret=0;\n"
      out+= "#endif\n"
    end
    out+= "    break;\n"
    out+= "  }\n"
    return out
  end

  # ソースコード全体を出力する
  # con : 'conn' or 'circ'
  # prototypes : C言語的に正しいプロトタイプ宣言のあつまりであること
  def make_define_defs
    uprotoname = @gen.protocolname.upcase
    out = ""
    @gen.define.each do |define, num|
      out += "#undef #{uprotoname}_#{define}\n"
      out += "#define #{uprotoname}_#{define} #{num}\n"
    end
    out+="\n"
    @gen.static.each do |static, num|
      base = @gen.static_base[static].upcase
      out += "#ifndef #{base}_#{static}\n"
      out += "#define #{base}_#{static} #{num}\n"
      out += "#endif\n"
    end
    if @gen.protocolid then
      out += "#undef #{uprotoname}_PROTOCOL_ID\n"
      out += "#define #{uprotoname}_PROTOCOL_ID #{@gen.protocolid}\n"
    end
    out
  end

  # enum の配列から，C言語の typedef つき enum 定義を作りだす．
  # 文字列を返す．
  def make_enum_defs
      enumhash = {}
      enums = []
      out = ""


      @gen.enum.each do |key, e|
          symbol = key.to_s
          enumtype, val,seq = e[0..2]

          o = "_SEQ_#{seq}___ #{@gen.protocolname.upcase}_#{symbol.to_s} = #{val.to_s}\n"
          if enumtype.nil? then
              enums.push( o)
          else
              enumhash[enumtype] = [] if enumhash[enumtype].nil?
              enumhash[enumtype].push( o.gsub( /\n/,"") )
          end
      end
      enumhash.keys.each do |k|
          out += "#ifndef _#{@gen.protocolname.upcase}_#{k}_ENUMDEF_\n"
          out += "#define _#{@gen.protocolname.upcase}_#{k}_ENUMDEF_\n"
          out += "typedef enum {\n"
          enumhash[k].sort.each { |line|
              line.gsub!( /_SEQ_[0-9]+___/,"")
              out += line + ",\n"
          }
          out += "\n} #{@gen.protocolname.upcase}_#{k};\n"
          out += "#endif\n\n"
      end
      enums.each do |d|
          out += d
      end
      return out
  end

  def make_struct_defs
	not_struct = [ "char", "short", "int", "int64", "uchar", "ushort", "uint", "float" ]

	out = ""

#	@gen.struct.each do |key,val|
	@gen.structname.each do |key|
      structname = key
      val = @gen.struct[key.to_s]

      out += "typedef struct _#{structname} {\n"

      val.each do |arg|
		str_len = ""

        vartype = arg['vartype']
        if vartype == :string || vartype == :stringarray then
          vartype = :char
		end
        # 構造体名が検出された場合、@gen.protocolname_を付ける
		if ( not_struct.index( vartype.to_s ) == nil ) then
          out += "#{@gen.protocolname}_"
		end
        vartype = shorttype2longtype( vartype )

        out += "    "
        out += "#{vartype} #{arg['name']}"
        out += "[#{arg['value'][0]}]" if arg['value'][0]
        out += "[#{arg['value'][1]}]" if arg['value'][1]
        out += ";\n"

		if arg['type'] == :array && arg['vartype'] != :string then
#        if arg['type'] == :array then
			out += "    int #{arg['name']}_len;\n"
		end
		if arg['vartype'] == :stringarray then
			out += "    char *#{arg['name']}_p;\n"
			out += "    int #{arg['name']}_i;\n"
		end

          end

          out += "} #{structname};\n"
      end

      return out
  end

  def make_funcenum_defs
    k="FUNCID"
    out = "#ifndef _#{@gen.protocolname.upcase}_#{k}_ENUMDEF_\n"
    out+= "#define _#{@gen.protocolname.upcase}_#{k}_ENUMDEF_\n"
    out+= "typedef enum _#{@gen.protocolname.upcase}_#{k}{\n"
    out+= @header_funcenum
    out+= "  #{@gen.protocolname.upcase}_IDMAX=#{@gen.idmax}\n"
    out+= "} #{@gen.protocolname.upcase}_#{k};\n"
    out+= "#endif\n\n"
    return out
  end

  def get_server_header
    uprotoname = @gen.protocolname.upcase
    defines = make_define_defs
    enums = make_enum_defs
    enums+= make_funcenum_defs
    structs = make_struct_defs
    svcon = @gen.serverconnection.to_s
    out = "/* Generated by #{ToolName} */\n"
    out+= "#ifndef _#{uprotoname}_SV_H_\n"
    out+= "#define _#{uprotoname}_SV_H_\n"
    out+= "#include \"vce.h\"\n"
    out += "#{@gen.sh.join('\n')}\n"
    out += "#{defines}"
    out += "#{enums}"
    out += "#{structs}\n\n"
    out+= "#ifdef __cplusplus\n"
    out+= "extern \"C\" {\n"
    out+= "#endif\n\n"
    out+= "#define #{uprotoname}_MAX_RECV_RECORD_LENGTH #{@gen.sizeofargs}\n"
    out+= "#define #{uprotoname}_MAX_CONNECTION 1024\n"
    out+= "\n"
    out+= "int #{@gen.protocolname}_new(#{svcon}_t c);\n"
    out+= "int #{@gen.protocolname}_del(#{svcon}_t c);\n"
    out+= "int #{@gen.protocolname}_toomany_recv_warning( #{svcon}_t c,int proto_id);\n"
    out+= "int #{@gen.protocolname}_toolong_recv_warning( #{svcon}_t c,int proto_id,int length);\n\n"
    out+= "int #{@gen.protocolname}_sv_pcallback( #{svcon}_t c,char *data,int len );\n"
    out+= "int #{@gen.protocolname}_sv_recv_error_callback( #{svcon}_t c,int e );\n"
    out+= "\n#{@server_cnt_protodecl.join('')}\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "\n#{@server_ddfuncptype.join('')}\n"
    out+= "#endif\n"
    out+= "\n#{@server_protodecl.join('')}\n"
    out+= "unsigned int #{@gen.protocolname}_sv_get_version( unsigned int *subv );\n"
    out+= "int #{@gen.protocolname}_sv_sender( #{svcon}_t c, char *data, int len );\n"
    out+= "#{svcon}_t  #{@gen.protocolname}_sv_get_current_#{svcon}( void );\n"
    out+= "#ifdef __cplusplus\n"
    out+= "};\n"
    out+= "#endif\n"
    out+= "#endif\n"
    return out
  end
  def get_client_header
    uprotoname = @gen.protocolname.upcase
    defines = make_define_defs
    enums = make_enum_defs
    enums+= make_funcenum_defs
    structs = make_struct_defs
    out = "/* Generated by #{ToolName} */\n"
    out+= "#ifndef _#{uprotoname}_CLI_H_\n"
    out+= "#define _#{uprotoname}_CLI_H_\n"
    out+= "#include \"vce.h\"\n"
    out+= "#{@gen.ch.join('\n')}\n"
    out+= "#ifdef __cplusplus\n"
    out+= "extern \"C\" {\n"
    out+= "#endif\n"
    out+= "#define #{uprotoname}_MAX_CONNECTION 1024\n"
    out+= "\n"
    out += "#{defines}\n\n"
    out += "#{enums}\n\n"
    out += "#{structs}\n\n"
    out+= "int #{@gen.protocolname}_cli_pcallback( conn_t c,char *data,int len );\n"
    out+= "int #{@gen.protocolname}_cli_recv_error_callback( conn_t c, int e );\n"
    out+= "\n#{@client_cnt_protodecl.join('')}\n\n\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "\n#{@client_ddfuncptype.join('')}\n"
    out+= "#endif\n"
    out+= "\n#{@client_protodecl.join('')}\n\n\n"
    out+= "unsigned int #{@gen.protocolname}_cli_get_version( unsigned int *subv );\n"
    out+= "int #{@gen.protocolname}_cli_sender(conn_t c, char *data, int len );\n"
    out+= "conn_t #{@gen.protocolname}_cli_get_current_conn( void );\n"
    out+= "#ifdef __cplusplus\n"
    out+= "};\n"
    out+= "#endif\n"
    out+= "#endif\n"
    return out
  end

  # cntfuncdefs : 数える用関数の列。
  # sendfuncdefs: 送信用関数の列。C言語的に正しいこと。
  # recvcasedefs : switch の中の case の列。datatop を先頭とすること
  def get_server_source
    uprotoname = @gen.protocolname.upcase
    commandbitstype = Command_bits_type[@gen.commandbits]
    commandbitsgetter = Command_bits_getter[@gen.commandbits]
    svcon = @gen.serverconnection.to_s
    out = "/* Generated by #{ToolName} */\n"
    out+= "#define _#{uprotoname}_SV_C_\n"
    out+= "#include \"#{@gen.protocolname}_sv.h\"\n"
    out+= "\n\n"
    out+= "typedef struct #{@gen.protocolname}_t_\n"
    out+= "{\n"
    out+= "  int count;\n"
    out+= "  VCEI64 next;\n"
    out+= "}#{@gen.protocolname}_t;\n"
    out+= "\n"
    out+= "static #{svcon}_t #{@gen.protocolname}_conns[#{uprotoname}_MAX_CONNECTION];\n"
    out+= "static int #{@gen.protocolname}_uninit=1;\n\n"
    out+= "#{@server_connvardef.join('')}\n"
    out+= "\n\n"
    out+= "#{@server_cntvardef.join('')}\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "#{@server_ddvardef.join('')}\n"
    out+= "#endif\n"
    out+= "\n\n"

    out+= "int #{@gen.protocolname}_get_using_index(#{svcon}_t c)\n"
    out+= "{\n"
    out+= "  int i;\n"
    out+= "  if(#{@gen.protocolname}_uninit)\n"
    out+= "  {\n"
    out+= "        for(i=0;i<#{uprotoname}_MAX_CONNECTION;i++)\n"
    out+= "    {\n"
    out+= "      #{@gen.protocolname}_conns[i].p=0;\n"
    out+= "      #{@gen.protocolname}_conns[i].serial=0;\n"
    out+= "    }\n"
    out+= "    #{@gen.protocolname}_uninit=0;\n"
    out+= "  }\n"
    out+= "  for(i=0;i<#{uprotoname}_MAX_CONNECTION;i++)\n"
    out+= "  {\n"
    out+= "    if(vce_#{svcon}_is_equal(c,#{@gen.protocolname}_conns[i]))\n"
    out+= "      return i;\n"
    out+= "  }\n"
    out+= "  return -1;\n"
    out+= "}\n"
    out+= "\n"
    
    out+= "int #{@gen.protocolname}_get_free_index()\n"
    out+= "{\n"
    out+= "  int i;\n"
    out+= "  if(#{@gen.protocolname}_uninit)\n"
    out+= "  {\n"
    out+= "    for(i=0;i<#{uprotoname}_MAX_CONNECTION;i++)\n"
    out+= "    {\n"
    out+= "      #{@gen.protocolname}_conns[i].p=0;\n"
    out+= "      #{@gen.protocolname}_conns[i].serial=0;\n"
    out+= "    }\n"
    out+= "    #{@gen.protocolname}_uninit=0;\n"
    out+= "  }\n"
    out+= "  for(i=0;i<#{uprotoname}_MAX_CONNECTION;i++)\n"
    out+= "  {\n"
    out+= "    if(#{@gen.protocolname}_conns[i].p==0&&#{@gen.protocolname}_conns[i].serial==0)\n"
    out+= "      return i;\n"
    out+= "  }\n"
    out+= "  return -1;\n"
    out+= "}\n"
    out+= "\n"
    
    out+= "int #{@gen.protocolname}_new(#{svcon}_t c)\n"
    out+= "{\n"
    out+= "  int index;\n"
    out+= "  VCEI64 next;\n"
    out+= "  index=#{@gen.protocolname}_get_free_index();\n"
    out+= "  if(index==-1)return -1;\n"
    out+= "  #{@gen.protocolname}_conns[index].p=c.p;\n"
    out+= "  #{@gen.protocolname}_conns[index].serial=c.serial;\n"
    out+= "  next=vce_get_current_utime();\n"
    out+= "#{@server_connvarinit.join('')}\n"
    out+= "  return 0;\n"
    out+= "}\n"
    out+= "\n"
    
    out+= "int #{@gen.protocolname}_del(#{svcon}_t c)\n"
    out+= "{\n"
    out+= "  int index;\n"
    out+= "  index=#{@gen.protocolname}_get_using_index(c);\n"
    out+= "  if(index==-1)return -1;\n"
    out+= "  #{@gen.protocolname}_conns[index].p=0;\n"
    out+= "  #{@gen.protocolname}_conns[index].serial=0;\n"
    out+= "  return 0;\n"
    out+= "}\n"
    out+= "\n"
    
    out+= "int #{@gen.protocolname}_manycall_check(#{@gen.protocolname}_t *many,int limit,VCEI64 time)\n"
    out+= "{\n"
    out+= "  VCEI64 currenttime=vce_get_current_utime();\n"
    out+= "  many->count++;\n"
    out+= "  while(many->next<currenttime)\n"
    out+= "  {\n"
    out+= "    many->count--;\n"
    out+= "    if(many->count==0)\n"
    out+= "    {\n"
    out+= "      many->next=currenttime+time;\n"
    out+= "      break;\n"
    out+= "    }\n"
    out+= "    many->next+=time;\n"
    out+= "  }\n"
    out+= "  if(many->count>limit)\n"
    out+= "  {\n"
    out+= "    many->count=limit;\n"
    out+= "    return -1;\n"
    out+= "  }\n"
    out+= "  return 0;\n"
    out+= "}\n"
    out+= "#define _SHORTCHECK if( _ofs<0  ){ if( _ofs != VCE_ETOOSHORT ){ return #{@gen.protocolname}_sv_recv_error_callback(_c, _ofs); } else { return 0; }}\n"


    out+= "#define _POP_I8(i) _ofs = vce_binary_pop_nb_i8(_data,_len,_ofs, (VCEI64*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_I4(i) _ofs = vce_binary_pop_nb_i4(_data,_len,_ofs, (int*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_I2(i) _ofs = vce_binary_pop_nb_i2(_data,_len,_ofs, (short*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_I1(i) _ofs = vce_binary_pop_nb_i1(_data,_len,_ofs, (char*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_F4(i) _ofs = vce_binary_pop_nb_i4(_data,_len,_ofs, (int*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_IA8(ia,ialen) _ofs = vce_binary_pop_nb_ia8(_data,_len,_ofs,(VCEI64*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_IA4(ia,ialen) _ofs = vce_binary_pop_nb_ia4(_data,_len,_ofs,(int*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_IA2(ia,ialen) _ofs = vce_binary_pop_nb_ia2(_data,_len,_ofs,(short*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_IA1(ia,ialen) _ofs = vce_binary_pop_nb_ia1(_data,_len,_ofs,(char*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_FA4(ia,ialen) _ofs = vce_binary_pop_nb_ia4(_data,_len,_ofs,(int*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_STRA(sa,salen,eachmax,i,p) for(i=0;i<salen;i++){p[i]=sa[i];} _ofs = vce_binary_pop_nb_stra(_data,_len,_ofs,p,&salen,eachmax); _SHORTCHECK;\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "static void _make_debug_print_str( char *out, int outlen, char *in, int inlen )\n"
    out+= "{\n"
    out+= "  int i;\n"
    out+= "  int is_bin = 0;\n"
    out+= "  for( i=0; i<inlen; i++ ){\n"
    out+= "    if( in[i] < 0x20 || in[i] > 0x7E ){\n"
    out+= "      is_bin = 1;\n"
    out+= "      break;\n"
    out+= "    }\n"
    out+= "  }\n"
    out+= "  if( is_bin ){ \n"
    out+= "    vce_snprintf( out, outlen, \"(%d bytes)\", inlen ); \n"
    out+= "  }else{\n"
    out+= "    vce_makecstr( out, outlen, in, inlen );\n"
    out+= "  }\n"
    out+= "}\n"
    out+= "#endif //GEN_DEBUG_PRINT\n"
    out+= "static #{svcon}_t #{@gen.protocolname}_sv_current_#{svcon};\n"
    out+= "int #{@gen.protocolname}_sv_pcallback( #{svcon}_t _c, char *_data, int _len)\n"
    out+= "{\n"
    out+= "  int _ofs = #{@gen.commandbits};\n"
    out+= "  int _ret;\n"
# 回数を数えるのがおもすぎる。
#    out+= "  int _con_index;\n"
    out+= "  #{commandbitstype} _command;\n"
    out+= "  if( _len < #{@gen.commandbits} ) return 0;\n"
    out+= "  #{@gen.protocolname}_sv_current_#{svcon} = _c;\n"
#    out+= "  _con_index=#{@gen.protocolname}_get_using_index(_c);\n"
    out+= "  _command = #{commandbitsgetter}(_data);\n"
    out+= "  switch( _command ){\n"
    out+= "#{@server_recvcasedef.join('')}\n"
    out+= "  default: \n"
    out+= "    return #{@gen.protocolname}_sv_recv_error_callback(_c, VCE_EGENCOMMAND );\n"
    out+= "  }\n"
    out+= "  vce_#{svcon}_clear( &#{@gen.protocolname}_sv_current_#{svcon} );\n"
    out+= "  return _ret;\n"
    out+= "}\n\n"
    out+= "#define _OFSCHECK if( _ofs<0 ) return _ofs;\n"
    out+= "#define _LENCHECK(l,max) if( (l) > (max) ) return VCE_EFULL;\n"
      out+= "#define _PUSH_STRA(a,alen,maxalen,outmax,eachmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_stra(_work,_ofs,outmax,(const char*const*)a,alen,eachmax); _OFSCHECK;\n"

    out+= "#define _PUSH_IA1(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia1(_work,_ofs, outmax, a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_IA2(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia2(_work,_ofs, outmax, a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_IA4(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia4(_work,_ofs, outmax, a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_IA8(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia8(_work,_ofs, outmax, a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_FA4(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia4(_work,_ofs, outmax, (int *)a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_I1(i,outmax) _ofs = vce_binary_push_nb_i1(_work,_ofs,outmax,(char)i); _OFSCHECK;\n"
    out+= "#define _PUSH_I2(i,outmax) _ofs = vce_binary_push_nb_i2(_work,_ofs,outmax,(short)i); _OFSCHECK;\n"
    out+= "#define _PUSH_I4(i,outmax) _ofs = vce_binary_push_nb_i4(_work,_ofs,outmax,(int)i); _OFSCHECK;\n"
    out+= "#define _PUSH_I8(i,outmax) _ofs = vce_binary_push_nb_i8(_work,_ofs,outmax,(VCEI64)i); _OFSCHECK;\n"
    out+= "#define _PUSH_F4(i,outmax) _ofs = vce_binary_push_nb_i4(_work,_ofs,outmax,*(int *)&i); _OFSCHECK;\n"

    out+= "#{@server_sendfuncdef.join('')}\n\n\n"
    out+= "#{@server_cntfuncdef.join('')}\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "#{@server_ddfuncdef.join('')}"
    out+= "#endif\n"
    out+= "unsigned int #{@gen.protocolname}_sv_get_version( unsigned int *subv )\n"
    out+= "{\n"
    out+= "  if(subv) *subv = #{@gen.subversion};\n"
    out+= "  return (unsigned int)#{@gen.version};\n"
    out+= "}\n"
    out+= "#{svcon}_t #{@gen.protocolname}_sv_get_current_#{svcon}( void )\n"
    out+= "{\n"
    out+= "  return #{@gen.protocolname}_sv_current_#{svcon};\n"
    out+= "}\n"
    out+= "/* End of generated code */\n"
    return out
  end
  def get_client_source
    uprotoname = @gen.protocolname.upcase
    commandbitstype = Command_bits_type[@gen.commandbits]
    commandbitsgetter = Command_bits_getter[@gen.commandbits]
    out = "/* Generated by #{ToolName} */\n"
    out+= "#define _#{uprotoname}_CLI_C_\n"
    out+= "#include \"#{@gen.protocolname}_cli.h\"\n"
    out+= "\n\n"
    out+= "#{@client_cntvardef.join('')}\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "#{@client_ddvardef.join('')}\n"
    out+= "#endif\n"
    out+= "\n\n"
    out+= "#define _SHORTCHECK if( _ofs<0  ){ if( _ofs != VCE_ETOOSHORT ){ return #{@gen.protocolname}_cli_recv_error_callback(_c, _ofs); } else { return 0; }}\n"
    out+= "#define _POP_I8(i) _ofs = vce_binary_pop_nb_i8(_data,_len,_ofs, (VCEI64*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_I4(i) _ofs = vce_binary_pop_nb_i4(_data,_len,_ofs, (int*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_I2(i) _ofs = vce_binary_pop_nb_i2(_data,_len,_ofs, (short*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_I1(i) _ofs = vce_binary_pop_nb_i1(_data,_len,_ofs, (char*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_F4(i) _ofs = vce_binary_pop_nb_i4(_data,_len,_ofs, (int*)&i); _SHORTCHECK;\n"
    out+= "#define _POP_IA8(ia,ialen) _ofs = vce_binary_pop_nb_ia8(_data,_len,_ofs,(VCEI64*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_IA4(ia,ialen) _ofs = vce_binary_pop_nb_ia4(_data,_len,_ofs,(int*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_IA2(ia,ialen) _ofs = vce_binary_pop_nb_ia2(_data,_len,_ofs,(short*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_IA1(ia,ialen) _ofs = vce_binary_pop_nb_ia1(_data,_len,_ofs,(char*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_FA4(ia,ialen) _ofs = vce_binary_pop_nb_ia4(_data,_len,_ofs,(int*)ia,&ialen); _SHORTCHECK;\n"
    out+= "#define _POP_STRA(sa,salen,eachmax,i,p) for(i=0;i<salen;i++){p[i]=sa[i];} _ofs = vce_binary_pop_nb_stra(_data,_len,_ofs,p,&salen,eachmax); _SHORTCHECK;\n"	
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "static void _make_debug_print_str( char *out, int outlen, char *in, int inlen )\n"
    out+= "{\n"
    out+= "  int i;\n"
    out+= "  int is_bin = 0;\n"
    out+= "  for( i=0; i<inlen; i++ ){\n"
    out+= "    if( in[i] < 0x20 || in[i] > 0x7E ){\n"
    out+= "      is_bin = 1;\n"
    out+= "      break;\n"
    out+= "    }\n"
    out+= "  }\n"
    out+= "  if( is_bin ){ \n"
    out+= "    vce_snprintf( out, outlen, \"(%d bytes)\", inlen ); \n"
    out+= "  }else{\n"
    out+= "    vce_makecstr( out, outlen, in, inlen );\n"
    out+= "  }\n"
    out+= "}\n"
    out+= "#endif //GEN_DEBUG_PRINT\n"
    out+= "static conn_t #{@gen.protocolname}_cli_current_conn;\n"
    out+= "int #{@gen.protocolname}_cli_pcallback( conn_t _c, char *_data, int _len)\n"
    out+= "{\n"
    out+= "  int _ofs = #{@gen.commandbits};\n"
    out+= "  int _ret;\n"
    out+= "  #{commandbitstype} _command;\n"
    out+= "  if( _len < #{@gen.commandbits} ) return 0;\n"
    out+= "  #{@gen.protocolname}_cli_current_conn = _c;\n"
    out+= "  _command = #{commandbitsgetter}(_data);\n"
    out+= "  switch( _command ){\n"
    out+= "#{@client_recvcasedef.join('')}\n"
    out+= "  default:\n"
    out+= "    _ret = #{@gen.protocolname}_cli_recv_error_callback(_c,VCE_EGENCOMMAND);\n"
    out+= "  }\n"
    out+= "  vce_conn_clear( &#{@gen.protocolname}_cli_current_conn );\n"
    out+= "  return _ret;\n"
    out+= "}\n\n"
    out+= "#define _OFSCHECK if( _ofs<0 ) return _ofs;\n"
    out+= "#define _LENCHECK(l,max) if( (l) > (max) ) return VCE_EFULL;\n"
    out+= "#define _PUSH_STRA(a,alen,maxalen,outmax,eachmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_stra(_work,_ofs,outmax,(const char*const*)a,alen,eachmax)\n"

    out+= "#define _PUSH_IA1(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia1(_work,_ofs, outmax, (char*)a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_IA2(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia2(_work,_ofs, outmax, (short*)a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_IA4(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia4(_work,_ofs, outmax, (int*)a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_IA8(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia8(_work,_ofs, outmax, (VCEI64*)a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_FA4(a,alen,maxalen,outmax) _LENCHECK(alen,maxalen); _ofs = vce_binary_push_nb_ia4(_work,_ofs, outmax, (int*)a, alen ); _OFSCHECK;\n"
    out+= "#define _PUSH_I1(i,outmax) _ofs = vce_binary_push_nb_i1(_work,_ofs,outmax,(char)i); _OFSCHECK;\n"
    out+= "#define _PUSH_I2(i,outmax) _ofs = vce_binary_push_nb_i2(_work,_ofs,outmax,(short)i); _OFSCHECK;\n"
    out+= "#define _PUSH_I4(i,outmax) _ofs = vce_binary_push_nb_i4(_work,_ofs,outmax,(int)i); _OFSCHECK;\n"
    out+= "#define _PUSH_I8(i,outmax) _ofs = vce_binary_push_nb_i8(_work,_ofs,outmax,(VCEI64)i); _OFSCHECK;\n"
    out+= "#define _PUSH_F4(i,outmax) _ofs = vce_binary_push_nb_i4(_work,_ofs,outmax,*(int *)&i); _OFSCHECK;\n"



    out+= "#{@client_sendfuncdef.join('')}\n"
    out+= "#{@client_cntfuncdef.join('')}\n"
    out+= "#ifdef GEN_DEBUG_PRINT\n"
    out+= "#{@client_ddfuncdef.join('')}\n"
    out+= "#endif\n"
    out+= "unsigned int #{@gen.protocolname}_cli_get_version( unsigned int *subv )\n"
    out+= "{\n"
    out+= "  if(subv)*subv= #{@gen.subversion};\n"
    out+= "  return (unsigned int)#{@gen.version};\n"
    out+= "}\n"
    out+= "conn_t #{@gen.protocolname}_cli_get_current_conn( void )\n"
    out+= "{\n"
    out+= " return #{@gen.protocolname}_cli_current_conn;\n"
    out+= "}\n"
    out+= "/* End of generated code */\n"
    return out
  end
  
  def get_server_test_source
    out = "/* Generated by #{ToolName} */\n"
    out+= "/* Sorry, now server test source is not implemented. */\n"
    out+= "/* End of generated code */\n"
  end

  # 試しのデータを何となく送ってみる関数を適当に製作する
  #
  def get_sample_send_funcdef( name, argdef )
    if( argdef.size == 0 ) then
      return "#{@gen.protocolname}_#{name}_send( _c );\n"
    end
    out = "#{@gen.protocolname}_#{name}_send( _c, "
    out_args_ary = []
    argdef.each { |i|
      vtype = i["type"].to_s
      # single 変数だったら，1を，配列だったら NULL,0 を．
      if( vtype == "single" ) then
        out_args_ary.push( "1" )
      else
        out_args_ary.push( "NULL,0" )
      end
    }
    out += out_args_ary.join(",") + ");\n"
  end

  # C言語の受信用関数を出力する．
  # テストプログラム用．
  def get_sample_recv_funcdef( name, argdef )
    pr = make_ptype( "recv", name, argdef, nil )
    out = "/****/\n"
    out+= "#{pr}\n"
    out+= "{\n"
    out+= "    vce_errout( \"received #{name} from server\\n\" );\n"
    out+= "    return 0;\n"
    out+= "}\n"
  end

  def get_client_test_source
    uprotoname = @gen.protocolname.upcase
    lprotoname = @gen.protocolname
    out = "/* Generated by #{ToolName} */\n"
    out+= "#define _#{uprotoname}_CLI_TEST_C_\n"
    out+= "#include \"#{@gen.protocolname}_cli.h\"\n"
    out+= "\n\n"
    out+= "unsigned short portnum = 12345;\n"
    out+= "char *host = \"localhost\";\n"
    out+= "VCE_BLOCK_CIPHER cipher = VCE_BLOCK_CIPHER_NONE;\n"
    out+= "conn_t _c;\n"
    out+= "tcpcontext_t tcp;\n"
    out+= "int sent = 0;\n"
    out+= "\n"
    out+= "int #{lprotoname}_cli_sender( conn_t _c, char *data, int len )\n"
    out+= "{\n"
    out+= "    /* unparser: you may have to replace */\n"
    out+= "    return vce_protocol_unparser_bin32(_c,data,len);\n"
    out+= "}\n"
    out+= "int #{lprotoname}_cli_recv_error_callback( conn_t _c, int e )\n"
    out+= "{\n"
    out+= "    vce_errout( \"detected protocol error: %d\\n\",e);\n"
    out+= "    return -1;\n"
    out+= "}\n"
    out+= "#{@client_samplerecvfuncdef}\n"
    out+= "int main( int argc, char **argv )\n"
    out+= "{\n"
    out+= "    vce_initialize();\n"
    out+= "    vce_set_verbose_mode(0);\n"
    out+= "    if( argc != 3 ){\n"
    out+= "        vce_errout( \"Usage: #{lprotoname}_testcli host port\\n\" );\n"
    out+= "        return 1;\n"
    out+= "    }\n"
    out+= "    host = argv[1];\n"
    out+= "    portnum = (unsigned short) atoi( argv[2] );\n"
    out+= "    tcp = vce_tcpcontext_create( 0, \n"
    out+= "                                 NULL, 0, 1,\n"
    out+= "                                 #{@gen.workbufsize},\n"
    out+= "                                 #{@gen.workbufsize},\n"
    out+= "                                 9999999,\n"
    out+= "                                 VCE_BLOCK_CIPHER_NONE,0,\n"
    out+= "                                 0,0,0 );\n"
    out+= "    if( !tcp ){\n"
    out+= "        vce_errout( \"failed to create tcpcontext: %s\\n\", STRERR);\n"
    out+= "        return 1;\n"
    out+= "    }\n"
    out+= "    /* Here, you may want to replace bin32 parser */\n"
    out+= "    vce_tcpcontext_set_conn_parser( tcp,\n"
    out+= "                                    vce_protocol_parser_bin32,\n"
    out+= "                                    #{lprotoname}_cli_pcallback);\n"
    out+= "    _c = vce_tcpcontext_connect( tcp, host, portnum );\n"
    out+= "    if( vce_conn_is_valid(_c) == 0 ){\n"
    out+= "        vce_errout( \"failed to connect to server:%s\\n\",STRERR);\n"
    out+= "        return 1;\n"
    out+= "    }\n"
    out+= "    while(1){\n"
    out+= "        vce_heartbeat();\n"
    out+= "        if( vce_conn_is_valid(_c) == 0 ){\n"
    out+= "            vce_errout( \"connection lost\\n\" );\n"
    out+= "            exit(1);\n"
    out+= "        }\n"
    out+= "        if( vce_conn_writable(_c)>0 && sent == 0 ){\n"
    out+= "            /* Here you put your own protocol calls */\n"
    out+= "            #{@client_samplesendfuncdef[0]}\n"
    out+= "            sent = 1;\n"
    out+= "        }\n"
    out+= "    }\n"
    out+= "    /* not reached */\n"
    out+= "    return 0;\n"
    out+= "}\n"
    out+= "/* End of generated code */\n"
  end

  def shorttype2longtype(type)
      type = type.to_s
      if( type == "uchar" ) then
          return "unsigned char"
      elsif( type == "ushort" ) then
          return "unsigned short"
      elsif( type == "uint" ) then
          return "unsigned int"
      elsif( type == "int64" ) then
          return "VCEI64"
      else
          return type
      end
  end

end

# cpp 用クラス
class Genmaker_cpp < Genmaker_c
  def initialize( gen, sv, cli, testsv, testcli, testrecvcli, use_const )
    super( gen, sv, cli, testsv, testcli, testrecvcli, use_const )
  end
  def extention
    "cpp"
  end
end

