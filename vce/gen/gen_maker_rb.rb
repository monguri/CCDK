#
# gen_maker_rb.rb
#
#
# Copyright (C) 2000-2005 Community Engine Inc. All rights reserved.
# For more information, please visit our website at www.ce-lab.net.
#


# ruby用ソースを出力する実装のクラス
class Genmaker_rb < Genmaker::Abstract
  Command_bits_getter = { 1 =>"pop_nb_i1!", 2 =>"pop_nb_i2!", 4 => "pop_nb_i4!"}
  Command_bits_setter = { 1 =>"push_nb_i1!", 2 =>"push_nb_i2!", 4 => "push_nb_i4!"}
  def initialize( gen, sv, cli, testsv, testcli, testrecvcli )
    super( gen, sv, cli, testsv, testcli, testrecvcli )
  end
  def extention
    "rb"
  end
  def get_popper(type,vartype,name,num)
    data = {
      "single.char" => "pop_nb_i1!",
      "single.uchar" => "pop_nb_i1!",
      "single.short" => "pop_nb_i2!",
      "single.ushort" => "pop_nb_i2!",
      "single.int" => "pop_nb_i4!",
      "single.uint" => "pop_nb_i4!",
      "single.int64" => "pop_nb_i8!",
      "array.char" => "pop_nb_ia1!",
      "array.uchar" => "pop_nb_ia1!",
      "array.short" => "pop_nb_ia2!",
      "array.ushort" => "pop_nb_ia2!",
      "array.int" => "pop_nb_ia4!",
      "array.uint" => "pop_nb_ia4!",
      "array.int64" => "pop_nb_ia8!",
      "array.char *" => "pop_nb_stra!" }
    r = data[ "#{type}.#{vartype}" ]
#    raise "bad type and vartype '#{type}.#{vartype}'" if( r == nil )
    return "#{name} = _data.#{r}(#{num})\n"
  end
  def get_pusher(type,vartype,name,num)
    data = {
      "single.char" => "push_nb_i1!",
      "single.uchar" => "push_nb_i1!",
      "single.short" => "push_nb_i2!",
      "single.ushort" => "push_nb_i2!",
      "single.int" => "push_nb_i4!",
      "single.uint" => "push_nb_i4!",
      "single.int64" => "push_nb_i8!",
      "array.char" => "push_nb_ia1!",
      "array.uchar" => "push_nb_ia1!",
      "array.short" => "push_nb_ia2!",
      "array.ushort" => "push_nb_ia2!",
      "array.int" => "push_nb_ia4!",
      "array.uint" => "push_nb_ia4!",
      "array.int64" => "push_nb_ia8!",
      "array.char *" => "push_nb_stra!" }
    r = data[ "#{type}.#{vartype}" ]
#    raise "bad type and vartype '#{type}.#{vartype}'" if( r == nil )
    if type == "single" then
      cast = ".to_i"
    elsif type == "array" && vartype == "char"
      cast = ".to_s"
    end
    return "_work.#{r}( #{name}#{cast} )\n"
  end

  # そのruby版。 iovar はいらないよ
  def make_ptype( action, name, argdef, con = nil)
    if argdef.size == 0 then
      return "#{@gen.protocolname}_#{name}_#{action}( _c )"
    else
      out = "#{@gen.protocolname}_#{name}_#{action}( _c, "
      append = []
      argdef.each{|i|
        append.push i["name"].to_s
      }
      return out + append.join( ", ") + " )"
    end
  end
  def get_cnt_vardef( action, msgname)
    return "$#{@gen.protocolname}_#{msgname}_#{action}_counter = 0\n"
  end
  def get_cnt_funcdef( action, msgname)
    out = "def #{@gen.protocolname}_get_#{msgname}_#{action}_count()\n"
    out+= "  return $#{@gen.protocolname}_#{msgname}_#{action}_counter\n"
    out+= "end\n"
  end
  def get_sample_recv_funcdef( name, argdef )
    "# ruby get_sample_recv_funcdef is not implemented now\n"
    out = "def " + make_ptype( "recv", name, argdef) + "\n"
    out += "  print '#{name} ('\n"
    argdef.each{ |i|
      out += "  print \"#{i["name"]}=\",#{i["name"]},\",\"\n"
    }
    out += "  print \" )\\n\" \n"
    out += "  0\n"
    out += "end\n"
    return out
  end
  def get_sample_send_funcdef(name,argdef)
    "# ruby get_sample_send_funcdef is not implemented now\n"
  end

  def get_send_funcdef( name, argdef, id, sender, con = nil)
    out = "def " + make_ptype( "send", name, argdef) + "\n"
    out += "  _work = \"\"\n"
    if con and @gen.serverconnection == :circ and @gen.vpr then
      out += "  _work.push_nb_i1!( #{@gen.protocolid})\n"
    end
    out+= "  _work." + Command_bits_setter[@gen.commandbits] +"(#{id})\n"
	argdef.each{ |i|
      vtype = i["type"].to_s
      vnum = i["value"][0]
      if i['vartype'] == :string then
        vvartype = "char *"
      elsif i['vartype'] == :stringarray then
        vvartype = "char *"
      else
        vvartype = i['vartype'].to_s
      end
      vvartype.downcase!
      vname = i["name"].to_s
      out+= "  " + get_pusher(vtype,vvartype,vname,vnum)
    }
    out+= "  return #{@gen.protocolname}_#{sender}(_c, _work )\n"
    out+= "end\n"
    return out
  end

  # そのruby版。
  def get_recv_casedef( name, argdef, id,isclient, con = nil)
    if( argdef.size == 0 ) then
      return "  when #{id}\n    ret = #{@gen.protocolname}_#{name}_recv(_c)\n"
    end

    retcode = "  when #{id}\n"
    popcode = ""
    args = []
    argdef.each{ |i|
      vtype = i["type"].to_s
      vnum = i["value"][0]
      if i['vartype'] == :string then
        vvartype = "char *"
      elsif i['vartype'] == :stringarray then
        vvartype = "char *"
      else
        vvartype = i['vartype'].to_s
      end
      vvartype.downcase!
      vname = i["name"].to_s
      
      popcode += "      " + get_popper(vtype,vvartype,vname,vnum)
      args.push( vname )
    }
    argstr = args.join(",")
    retcode += popcode
    retcode += "    $#{@gen.protocolname}_#{name}_recv_counter += 1\n"
    retcode += "    ret = #{@gen.protocolname}_#{name}_recv(_c, #{argstr} )\n"
    return retcode
  end
  def get_recv( name, argdef)
    if( argdef.size == 0 ) then
      retcode = "def #{@gen.protocolname}_#{name}_recv(_c)\n"
      retcode += "\t$#{@gen.protocolname}_recvdata.pusn( { 'proto' => \"#{@gen.protocolname}_#{name}_recv\", 'args' =>{\"conn\"=>_c}})\n"
      retcode += "\t0\n"
      retcode += "end\n"
      return retcode
    end
    retcode = ""
    args = []
    argdef.each{ |i|
      vname = i["name"]
      args.push( vname )
    }
    argstr = args.join(",")
    retcode += "def #{@gen.protocolname}_#{name}_recv(_c, #{argstr} )\n"
    retcode += "\t$#{@gen.protocolname}_recvdata.push( { 'proto' => \"#{@gen.protocolname}_#{name}_recv\", 'args' =>{ \"conn\"=>_c"
    args.each do |a|
      retcode += ",\"#{a}\"=>#{a}"
    end
    retcode += "}})\n"
    retcode += "\t0\n"
    retcode += "end\n"
    return retcode
  end

  # それのRuby版
  def get_server_source
    defines = make_define_defs
    enums = make_enum_defs
    out = "# Generated by #{ToolName}\n"
    out+= "require \"vce.so\"\n"
    out+= "\n\n"
    uprotoname = @gen.protocolname.upcase
    out += "#{defines}"
    out += "#{enums}"
    out+= "#{@server_cntvardef}\n"
    out+= "$#{@gen.protocolname}_recvdata = []\n"
    out+= "\n\n"
    out+= "$#{@gen.protocolname}_sv_proc = Proc.new {|_c,_data|\n"
    out+= "  ret = 0\n"
    out+= "  break if( _data.length < #{@gen.commandbits} )\n"
    out+= "  _command = _data.pop_nb_i#{@gen.commandbits}!\n"
    out+= "  case _command\n"
    out+= "#{@server_recvcasedef}\n"
    out+= "  else\n"
    out+= "    ret = #{@gen.protocolname}_sv_recv_error_callback(_c, \"gencommand\" )\n"
    out+= "  end\n"
    out+= "  ret\n"
    out+= "}\n"
    out+= "#{@server_sendfuncdef}\n"
    out+= "#{@server_cntfuncdef}\n"
    out+= "\n"
    out+= "def #{@gen.protocolname}_sv_get_version()\n"
    out+= "  return [ #{@gen.version} , #{@gen.subversion} ]\n"
    out+= "end\n\n"
    out+= "# End of generated code\n"
    return out
  end

  # そのruby版
  def get_client_source
    defines = make_define_defs
    enums = make_enum_defs
    out = "# Generated by #{ToolName}\n"
    out+= "require \"vce.so\"\n"
    out+= "\n\n"
    uprotoname = @gen.protocolname.upcase
    out += "#{defines}"
    out += "#{enums}"
    out+= "#{@client_cntvardef}\n"
    out+= "$#{@gen.protocolname}_recvdata = []\n"
    out+= "\n\n"
    out+= "$#{@gen.protocolname}_cli_proc = Proc.new { |_c,_data|\n"
    out+= "  ret = 0\n"
    out+= "  break if( _data.length < #{@gen.commandbits} )\n"
    out+= "  _command = _data.pop_nb_i#{@gen.commandbits}!\n"
    out+= "  case _command\n"
    out+= "#{@client_recvcasedef}\n"
    out+= "  else\n"
    out+= "    ret = #{@gen.protocolname}_cli_recv_error_callback(_c,\"gencommand\")\n"
    out+= "  end\n"
    out+= "  ret\n"
    out+= "}\n"
    out+= "#{@client_recvfuncdef}\n"
    out+= "#{@client_sendfuncdef}\n"
    out+= "#{@client_cntfuncdef}\n"
    out+= "\n"
    out+= "def #{@gen.protocolname}_cli_get_version()\n"
    out+= "  return [ #{@gen.version} , #{@gen.subversion} ]\n"
    out+= "end\n\n"
    out+= "# End of generated code\n"
    return out
  end
  def get_server_test_source
    out = "# Generated by #{ToolName}\n"
    out += "# server test code is not implemented now in ruby\n"
    out += "# End of generated code\n"
  end
  def get_client_test_source
    out = "# Generated by #{ToolName}\n"
    out += "# client test code is not implemented now in ruby\n"
    out += "# End of generated code\n"

    out += <<-EOT
    # Generated by #{ToolName}
    require 'vce.so'
    require '#{@gen.protocolname}_cli.rb'
    def #{@gen.protocolname}_cli_recv_error_callback( c, e )
      print "detected protocol error: #{'#{c}'}\n"
      -1
    end
    #{@client_samplerecvfuncdef}
    def test_main( host, port )
      context = TCPcontext.create( FALSE, nil, 0, 1000, 
                                  #{@gen.workbufsize}, #{@gen.workbufsize},
                                  60*60, 1, 8, 0, 0 )
      context.set_conn_parser( Conn::PARSER_BIN16, $#{@gen.protocolname}_cli_proc )

      conn = context.connect( host, port )

      if !conn.valid?
        print "cannnot connect.\n"
        exit 1
      end
      
      Vce.heartbeat while true

    end
    EOT
    return out
  end
  def get_client_test_recv_source
    out = "# Generated by #{ToolName}\n"
    out += "require \"vce.so\"\n"
    out += "\n\n"
    out += "#{@client_test_recv}\n"
    out += "def #{@gen.protocolname}_cli_sender( _c, _data)\n"
    out += "\t_c.unparser_bin16( _data)\n"
    out += "end\n"
    out+= "# End of generated code\n"
    return out
  end
  def make_define_defs
    out = ""
    uprotoname = @gen.protocolname.upcase
    @gen.define.each do |define, num|
      out += "#{uprotoname}_#{define} = #{num}\n"
    end
    out
  end

  # enum の配列から，C言語の typedef つき enum 定義を作りだす．
  # 文字列を返す．
  def make_enum_defs
    enumhash = {}
    out = ""
    @gen.enum.each do |key, e|
      symbol = key.to_s
      enumtype, val = e[0..1]
      out += 
        "#{@gen.protocolname.upcase}_#{symbol.to_s} = #{val.to_s}\n"
    end
    return out
  end
end
