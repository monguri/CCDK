#
# gen_footer.rb
#
#
# Copyright (C) 2000-2005 Community Engine Inc. All rights reserved.
# For more information, please visit our website at www.ce-lab.net.
#

###########################################################################
# 使い方
###########################################################################
def pusage
  print "Usage: ruby gen.rb [Options] infile\n"
  print "--protocolname NAME\n"
  print "--serverconnection CONTYPE\n"
  print "--workbufsize SIZE\n"
  print "--version NUMBER\n"
  print "--identifier STRING\n"
  print "--nocpp\n"
  print "--noc\n"
  print "--noruby(--norb)\n"
  print "--nocli\n"
  print "--nosv\n"
  print "--output_test_sv\n"
  print "--output_test_cli\n"
  print "--output_test_recv_cli\n"
  print "--use_const\n"
  print "These options are overridden by command line options.\n"
end

begin
  gen = Gen.new
  infile = nil
  
  no_cpp_source = false
  no_c_source = false
  no_ruby_source = false
  no_sv_source = false
  no_cli_source = false
  output_test_sv = false
  output_test_cli = false
  output_test_recv_cli = false
  use_const = true
  
  ##### オプション解析
  if( ARGV.size < 1 ) then
    pusage()
    exit 0
  else
    while ARGV.size > 0 
      op = ARGV.shift
      if( op =~ /^--/ ) then
        arg = ARGV.shift
        if( arg == nil ) then
          pusage()
          exit 0
        end
        case op
        when "--protocolname"
          gen.protocolname = arg
        when "--serverconnection"
          gen.serverconnection = arg
        when "--workbufsize"
          gen.workbufsize = arg.to_i
        when "--version"
          gen.version = arg.to_i
        when "--identifier"
          gen.identifier = arg
          
        when "--nocpp"
          no_cpp_source = true
          ARGV.unshift(arg)
        when "--noc"
          no_c_source = true
          ARGV.unshift(arg)
        when "--noruby"
          no_ruby_source = true
          ARGV.unshift(arg)
        when "--norb"
          no_ruby_source = true
          ARGV.unshift(arg)
        when "--nocli"
          no_cli_source = true
          ARGV.unshift(arg)
        when "--nosv"
          no_sv_source = true
          ARGV.unshift(arg)
        when "--output_test_sv"
          output_test_sv = true
          ARGV.unshift(arg)
        when "--output_test_cli"
          output_test_cli = true
          ARGV.unshift(arg)
        when "--output_test_recv_cli"
          output_test_recv_cli = true
          ARGV.unshift(arg)
        when "--use_const"
          use_const = true
          ARGV.unshift(arg)
        else
          pusage
          exit 0
        end
      else
        infile = op
      end
    end
  end

  ##### パース開始
  File.open( infile ) do |f|
    gen.parse( f, infile)
  end
  if no_c_source == false then
    # 文字列作成
    g = Genmaker::create( "c", gen, !no_sv_source, !no_cli_source, 
                         output_test_sv, output_test_cli, output_test_recv_cli, use_const )
    g.make
    # 保存
    g.save_file
  end
  if no_cpp_source == false then
    # 文字列作成
    g = Genmaker::create( "cpp", gen, !no_sv_source, !no_cli_source,
                         output_test_sv, output_test_cli, output_test_recv_cli, use_const )
    g.make
    # 保存
    g.save_file
  end
  if no_ruby_source == false then
    # 文字列作成
    g = Genmaker::create( "rb", gen, !no_sv_source, !no_cli_source,
                         output_test_sv, output_test_cli, output_test_recv_cli, use_const )
    g.make
    # 保存
    g.save_file
  end
rescue Racc::ParseError, Gen::GenError, Errno::ENOENT
  raise ####
  $stderr.puts "#{File.basename $0}: #{$!}"
  exit 1
end
