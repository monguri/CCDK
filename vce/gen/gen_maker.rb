#
# gen_maker.rb
#
#
# Copyright (C) 2000-2005 Community Engine Inc. All rights reserved.
# For more information, please visit our website at www.ce-lab.net.
#


#
# gen から出力されるソースを作る抽象クラス
# 
module Genmaker
  def create( source, gen, sv = true, cli = true, testsv = false, testcli = false, testrecvcli = false, use_const = true )
    case source
    when "rb"
      Genmaker_rb.new( gen, sv, cli, testsv, testcli, testrecvcli )
    when "c"
      Genmaker_c.new( gen, sv, cli, testsv, testcli, testrecvcli, use_const )
    when "cpp"
      Genmaker_cpp.new( gen, sv, cli, testsv, testcli, testrecvcli, use_const )
    else
      nil
    end
  end
  module_function :create
  class Abstract
    ToolName = "gen.rb CommunityEngine Inc. 2000-2005"
    def initialize( gen, sv, cli, testsv, testcli, testrecvcli )
      @gen = gen
      @sv = sv
      @cli = cli
      @testsv = testsv
      @testcli = testcli
      @testrecvcli = testrecvcli
      @server_cnt_protodecl = []
      @client_cnt_protodecl = []
      @server_cntfuncdef = []
      @client_cntfuncdef = []
      @server_cntvardef = []
      @server_connvarinit = []
      @server_connvardef = []
      @client_cntvardef = []
      @server_protodecl = []
      @client_protodecl = []
      @server_sendfuncdef = []
      @client_sendfuncdef = []
      @server_recvcasedef = []
      @client_recvcasedef = []
      @server_samplerecvfuncdef = []
      @client_samplerecvfuncdef = []
      @server_samplesendfuncdef = []
      @client_samplesendfuncdef = []
      @client_test_recv = []
      @header_funcenum = ""
      @client_ddvardef=[]
      @server_ddvardef=[]
      @client_ddfuncdef=[]
      @server_ddfuncdef=[]
      @client_ddfuncptype=[]
      @server_ddfuncptype=[]
    end
    # 出力用文字列作成。
    # 実際に作る文字列はサブクラスに任せる。
    def make
      idhash = {}
      @gen.c2s.each do |d|
        funcname = d['funcname']
        argdef = d['args']
        id = d['id']
        @header_funcenum += make_funcenum(funcname,id,"c2s")
        @server_cnt_protodecl.push( make_cnt_ptype( "recv", funcname ) + ";\n")
        @client_cnt_protodecl.push( make_cnt_ptype( "send", funcname ) + ";\n")
        @server_cntfuncdef.push( get_cnt_funcdef( "recv", funcname ))
        @client_cntfuncdef.push( get_cnt_funcdef( "send", funcname ))
        @server_cntvardef.push( get_cnt_vardef( "recv", funcname ))
        @server_connvardef.push( get_conn_vardef( funcname ))
        @server_connvarinit.push( get_conn_varinit( funcname ))
        @client_cntvardef.push( get_cnt_vardef( "send", funcname ))
        @server_protodecl.push( make_ptype( "recv", funcname, argdef) +";\n")
        @client_protodecl.push( make_ptype( "send", funcname, argdef, "conn") +";\n")
        @client_sendfuncdef.push( get_send_funcdef( funcname, argdef, id, 
                                                   "cli_sender", "conn"
                                                   ))
        @server_recvcasedef.push( get_recv_casedef( funcname, argdef, id, false ))
        @server_samplerecvfuncdef.push( get_sample_recv_funcdef( funcname, argdef ))
        @client_samplesendfuncdef.push( get_sample_send_funcdef( funcname, argdef ))
        @server_ddvardef.push(get_dd_vardef("recv",funcname))
        @client_ddvardef.push(get_dd_vardef("send",funcname))
        @server_ddfuncdef.push(get_dd_funcdef("recv",funcname))
        @client_ddfuncdef.push(get_dd_funcdef("send",funcname))
        @server_ddfuncptype.push(get_dd_funcptype("recv",funcname))
        @client_ddfuncptype.push(get_dd_funcptype("send",funcname))
      end

      @client_protodecl.push( "\n\n\n" )
      @server_protodecl.push( "\n\n\n" )

      @gen.s2c.each do |d|
        funcname = d['funcname']
        argdef = d['args']
        id = d['id']
        @header_funcenum += make_funcenum(funcname,id,"s2c")
        @server_cnt_protodecl.push( make_cnt_ptype( "send", funcname ) + ";\n")
        @client_cnt_protodecl.push( make_cnt_ptype( "recv", funcname ) + ";\n")
        @server_cntfuncdef.push( get_cnt_funcdef( "send", funcname ))
        @client_cntfuncdef.push( get_cnt_funcdef( "recv", funcname ))
        @server_cntvardef.push( get_cnt_vardef( "send", funcname ))
        @client_cntvardef.push( get_cnt_vardef( "recv", funcname ))
        @server_protodecl.push( make_ptype( "send", funcname, argdef)+";\n")
        @client_protodecl.push( make_ptype( "recv", funcname, argdef, "conn")+";\n")
        @server_sendfuncdef.push( get_send_funcdef( funcname, argdef, id, 
                                                   "sv_sender"
                                                   ))
        #@client_recvcasedef.push( get_recv_casedef( funcname, argdef, id, "conn" ))
        if @gen.cliclassmode == 0
            @client_recvcasedef.push( get_recv_casedef( funcname, argdef, id, true, "conn" ))
        else
            @client_recvcasedef.push( get_recv_casedef( funcname, argdef, id, false, "conn" ))
        end

        @client_samplerecvfuncdef.push( get_sample_recv_funcdef( funcname, argdef ))
        @server_samplesendfuncdef.push( get_sample_send_funcdef(funcname,argdef))
        @client_test_recv.push( get_recv( funcname, argdef))
        @server_ddvardef.push(get_dd_vardef("send",funcname))
        @client_ddvardef.push(get_dd_vardef("recv",funcname))
        @server_ddfuncdef.push(get_dd_funcdef("send",funcname))
        @client_ddfuncdef.push(get_dd_funcdef("recv",funcname))
        @server_ddfuncptype.push(get_dd_funcptype("send",funcname))
        @client_ddfuncptype.push(get_dd_funcptype("recv",funcname))
      end
      @sv_src = get_server_source
      @cli_src = get_client_source
      @sv_h = get_server_header
      @cli_h = get_client_header
      @sv_test_src = get_server_test_source
      @cli_test_src = get_client_test_source
      @cli_test_recv_src = get_client_test_recv_source
    end
    def save_file
      if @sv then
        if @sv_src != "" then
          name = "#{@gen.protocolname}_sv.#{extention}"
          f = File.open( name, "w")
          f.write( @sv_src)
          f.close
        end
        if @sv_h != "" then
          name = "#{@gen.protocolname}_sv.h"
          f = File.open( name, "w")
          f.write( @sv_h)
          f.close
        end        
      end
      if @cli then
        if @cli_src != "" then
          name = "#{@gen.protocolname}_cli.#{extention}"
          f = File.open( name, "w")
          f.write( @cli_src)
          f.close
        end
        if @cli_h != "" then
          name = "#{@gen.protocolname}_cli.h"
          f = File.open( name, "w")
          f.write( @cli_h)
          f.close
        end
      end
      if @testsv then
        if @sv_test_src != "" then
          name = "#{@gen.protocolname}_test_sv.#{extention}"
          f = File.open( name, "w")
          f.write( @sv_test_src )
          f.close
        end
      end
      if @testcli then
        if @cli_test_src != "" then
          name = "#{@gen.protocolname}_test_cli.#{extention}"
          f = File.open( name, "w")
          f.write( @cli_test_src)
          f.close
        end
      end
      if @testrecvcli then
        if @cli_test_recv_src != "" then
          name = "#{@gen.protocolname}_test_recv_cli.#{extention}"
          f = File.open( name, "w")
          f.write( @cli_test_recv_src)
          f.close
        end
      end
    end
    def extention
      ""
    end
    protected
    def make_funcenum(funcname,id,type)
      ""
    end
    def make_cnt_ptype( action, funcname)
      ""
    end
    def get_dd_vardef( action, msgname)
      ""
    end
    def get_dd_funcptype( action, msgname)
      ""
    end
    def get_dd_funcdef( action, msgname)
      ""
    end
    def get_cnt_funcdef( action, funcname)
    end
    def get_cnt_vardef( action, funcname)
    end
    def get_conn_vardef(funcname)
    end
    def get_conn_varinit(funcname)
    end
    def make_ptype( action, funcname, argdef, con = nil)
    end
    def get_send_funcdef( funcname, argdef, id, sender)
    end
    def get_recv_casedef( funcname, argdef, id, con = nil)
    end
    def get_server_source
      ""
    end
    def get_client_source
      ""
    end
    def get_server_header
      ""
    end
    def get_client_header
      ""
    end
    def get_server_test_source
      ""
    end
    def get_client_test_source
      ""
    end
    def get_client_test_recv_source
      ""
    end
    def get_recv( funcname, argdef)
    end
  end
end
