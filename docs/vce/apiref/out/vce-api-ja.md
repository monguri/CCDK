# VCE-SDK API リファレンスマニュアル

## 全カテゴリのリスト
<!-- make_categoryindexindex -->

- <a href="#array">array</a>
- <a href="#bin">bin</a>
- <a href="#core">core</a>
- <a href="#err">err</a>
- <a href="#log">log</a>
- <a href="#parser">parser</a>
- <a href="#pcallback">pcallback</a>
- <a href="#tcp">tcp</a>
- <a href="#text">text</a>
- <a href="#util">util</a>
- <a href="#watcher">watcher</a>

## 名前順の関数索引
<!-- make_nameindex -->

1. <a href="#ARRAY_SCAN">ARRAY_SCAN</a>
1. <a href="#ARRAY_SCAN_TYPE">ARRAY_SCAN_TYPE</a>
1. <a href="#ELEMENTOF">ELEMENTOF</a>
1. <a href="#FREE">FREE</a>
1. <a href="#GET_16BIT_INT">GET_16BIT_INT</a>
1. <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a>
1. <a href="#GET_32BIT_INT">GET_32BIT_INT</a>
1. <a href="#GET_32BIT_NATIVEINT">GET_32BIT_NATIVEINT</a>
1. <a href="#GET_64BIT_INT">GET_64BIT_INT</a>
1. <a href="#GET_64BIT_NATIVEINT">GET_64BIT_NATIVEINT</a>
1. <a href="#GET_8BIT_INT">GET_8BIT_INT</a>
1. <a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
1. <a href="#MALLOC">MALLOC</a>
1. <a href="#MAX">MAX</a>
1. <a href="#MIN">MIN</a>
1. <a href="#SET_16BIT_INT">SET_16BIT_INT</a>
1. <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a>
1. <a href="#SET_32BIT_INT">SET_32BIT_INT</a>
1. <a href="#SET_32BIT_NATIVEINT">SET_32BIT_NATIVEINT</a>
1. <a href="#SET_64BIT_INT">SET_64BIT_INT</a>
1. <a href="#SET_64BIT_NATIVEINT">SET_64BIT_NATIVEINT</a>
1. <a href="#SET_8BIT_INT">SET_8BIT_INT</a>
1. <a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
1. <a href="#STRERR">STRERR</a>
1. <a href="#vce_alloc_array_object">vce_alloc_array_object</a>
1. <a href="#vce_array_object_inuse">vce_array_object_inuse</a>
1. <a href="#vce_atoi">vce_atoi</a>
1. <a href="#vce_binary_pack">vce_binary_pack</a>
1. <a href="#vce_binary_pop_nb_i1">vce_binary_pop_nb_i1</a>
1. <a href="#vce_binary_pop_nb_i2">vce_binary_pop_nb_i2</a>
1. <a href="#vce_binary_pop_nb_i4">vce_binary_pop_nb_i4</a>
1. <a href="#vce_binary_pop_nb_i8">vce_binary_pop_nb_i8</a>
1. <a href="#vce_binary_pop_nb_ia1">vce_binary_pop_nb_ia1</a>
1. <a href="#vce_binary_pop_nb_ia2">vce_binary_pop_nb_ia2</a>
1. <a href="#vce_binary_pop_nb_ia4">vce_binary_pop_nb_ia4</a>
1. <a href="#vce_binary_pop_nb_ia8">vce_binary_pop_nb_ia8</a>
1. <a href="#vce_binary_pop_nb_stra">vce_binary_pop_nb_stra</a>
1. <a href="#vce_binary_push_nb_i1">vce_binary_push_nb_i1</a>
1. <a href="#vce_binary_push_nb_i2">vce_binary_push_nb_i2</a>
1. <a href="#vce_binary_push_nb_i4">vce_binary_push_nb_i4</a>
1. <a href="#vce_binary_push_nb_i8">vce_binary_push_nb_i8</a>
1. <a href="#vce_binary_push_nb_ia1">vce_binary_push_nb_ia1</a>
1. <a href="#vce_binary_push_nb_ia2">vce_binary_push_nb_ia2</a>
1. <a href="#vce_binary_push_nb_ia4">vce_binary_push_nb_ia4</a>
1. <a href="#vce_binary_push_nb_ia8">vce_binary_push_nb_ia8</a>
1. <a href="#vce_binary_push_nb_stra">vce_binary_push_nb_stra</a>
1. <a href="#vce_binary_unpack">vce_binary_unpack</a>
1. <a href="#vce_conn_break_heartbeat">vce_conn_break_heartbeat</a>
1. <a href="#vce_conn_clear">vce_conn_clear</a>
1. <a href="#vce_conn_close">vce_conn_close</a>
1. <a href="#vce_conn_close_tcpcontext_all">vce_conn_close_tcpcontext_all</a>
1. <a href="#vce_conn_get_buffer">vce_conn_get_buffer</a>
1. <a href="#vce_conn_get_index">vce_conn_get_index</a>
1. <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a>
1. <a href="#vce_conn_get_local_ipv4_addr">vce_conn_get_local_ipv4_addr</a>
1. <a href="#vce_conn_get_local_ipv4_addr_string">vce_conn_get_local_ipv4_addr_string</a>
1. <a href="#vce_conn_get_local_ipv6_addr">vce_conn_get_local_ipv6_addr</a>
1. <a href="#vce_conn_get_local_ipv6_addr_string">vce_conn_get_local_ipv6_addr_string</a>
1. <a href="#vce_conn_get_remote_addr_string">vce_conn_get_remote_addr_string</a>
1. <a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a>
1. <a href="#vce_conn_get_remote_ipv4_addr_string">vce_conn_get_remote_ipv4_addr_string</a>
1. <a href="#vce_conn_get_remote_ipv6_addr">vce_conn_get_remote_ipv6_addr</a>
1. <a href="#vce_conn_get_remote_ipv6_addr_string">vce_conn_get_remote_ipv6_addr_string</a>
1. <a href="#vce_conn_get_stat">vce_conn_get_stat</a>
1. <a href="#vce_conn_get_state_buffer">vce_conn_get_state_buffer</a>
1. <a href="#vce_conn_get_struct_from_index">vce_conn_get_struct_from_index</a>
1. <a href="#vce_conn_get_tcpcontext">vce_conn_get_tcpcontext</a>
1. <a href="#vce_conn_is_equal">vce_conn_is_equal</a>
1. <a href="#vce_conn_is_valid">vce_conn_is_valid</a>
1. <a href="#vce_conn_set_delay">vce_conn_set_delay</a>
1. <a href="#vce_conn_set_parser">vce_conn_set_parser</a>
1. <a href="#vce_conn_set_timeout">vce_conn_set_timeout</a>
1. <a href="#vce_conn_show_stat">vce_conn_show_stat</a>
1. <a href="#vce_conn_shrink_readbuf">vce_conn_shrink_readbuf</a>
1. <a href="#vce_conn_userdata_get_pointer">vce_conn_userdata_get_pointer</a>
1. <a href="#vce_conn_userdata_set_pointer">vce_conn_userdata_set_pointer</a>
1. <a href="#vce_conn_writable">vce_conn_writable</a>
1. <a href="#vce_conn_write">vce_conn_write</a>
1. <a href="#vce_conn_writed">vce_conn_writed</a>
1. <a href="#vce_dump_buffer">vce_dump_buffer</a>
1. <a href="#vce_end_all_array">vce_end_all_array</a>
1. <a href="#vce_end_array">vce_end_array</a>
1. <a href="#vce_errout">vce_errout</a>
1. <a href="#vce_extract_data_from_hex_text">vce_extract_data_from_hex_text</a>
1. <a href="#vce_finalize">vce_finalize</a>
1. <a href="#vce_free_array_object">vce_free_array_object</a>
1. <a href="#vce_free_array_object_all">vce_free_array_object_all</a>
1. <a href="#vce_get_array_maxnum">vce_get_array_maxnum</a>
1. <a href="#vce_get_array_member_size">vce_get_array_member_size</a>
1. <a href="#vce_get_array_object_index">vce_get_array_object_index</a>
1. <a href="#vce_get_array_object_last">vce_get_array_object_last</a>
1. <a href="#vce_get_array_object_next">vce_get_array_object_next</a>
1. <a href="#vce_get_array_object_pointer_by_index">vce_get_array_object_pointer_by_index</a>
1. <a href="#vce_get_array_object_pointer_by_index_only_used">vce_get_array_object_pointer_by_index_only_used</a>
1. <a href="#vce_get_array_object_top">vce_get_array_object_top</a>
1. <a href="#vce_get_array_usenum">vce_get_array_usenum</a>
1. <a href="#vce_get_current_utime">vce_get_current_utime</a>
1. <a href="#vce_get_ipv4_addr_by_name">vce_get_ipv4_addr_by_name</a>
1. <a href="#vce_get_last_error">vce_get_last_error</a>
1. <a href="#vce_get_netstat_string">vce_get_netstat_string</a>
1. <a href="#vce_get_stat">vce_get_stat</a>
1. <a href="#vce_get_tcp_packet_read_size">vce_get_tcp_packet_read_size</a>
1. <a href="#vce_get_tcp_packet_write_size">vce_get_tcp_packet_write_size</a>
1. <a href="#vce_heartbeat">vce_heartbeat</a>
1. <a href="#vce_if_included_in_array">vce_if_included_in_array</a>
1. <a href="#vce_init_array">vce_init_array</a>
1. <a href="#vce_init_limit_t">vce_init_limit_t</a>
1. <a href="#vce_initialize">vce_initialize</a>
1. <a href="#vce_initialize_limited">vce_initialize_limited</a>
1. <a href="#vce_limit_clear">vce_limit_clear</a>
1. <a href="#vce_mainloop">vce_mainloop</a>
1. <a href="#vce_make_binary_array_from_hex">vce_make_binary_array_from_hex</a>
1. <a href="#vce_make_binary_array_from_line">vce_make_binary_array_from_line</a>
1. <a href="#vce_make_hex_from_binary_array">vce_make_hex_from_binary_array</a>
1. <a href="#vce_make_hex_text_from_buffer">vce_make_hex_text_from_buffer</a>
1. <a href="#vce_protocol_acceptwatcher_deny">vce_protocol_acceptwatcher_deny</a>
1. <a href="#vce_protocol_acceptwatcher_noop">vce_protocol_acceptwatcher_noop</a>
1. <a href="#vce_protocol_closewatcher_noop">vce_protocol_closewatcher_noop</a>
1. <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a>
1. <a href="#vce_protocol_parser_bin32">vce_protocol_parser_bin32</a>
1. <a href="#vce_protocol_parser_text">vce_protocol_parser_text</a>
1. <a href="#vce_protocol_parser_through">vce_protocol_parser_through</a>
1. <a href="#vce_protocol_pcallback_dump">vce_protocol_pcallback_dump</a>
1. <a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a>
1. <a href="#vce_protocol_pcallback_echo_text">vce_protocol_pcallback_echo_text</a>
1. <a href="#vce_protocol_pcallback_noop">vce_protocol_pcallback_noop</a>
1. <a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a>
1. <a href="#vce_protocol_unparser_bin32">vce_protocol_unparser_bin32</a>
1. <a href="#vce_protocol_unparser_text">vce_protocol_unparser_text</a>
1. <a href="#vce_protocol_unparser_through">vce_protocol_unparser_through</a>
1. <a href="#vce_read_plain_text_file">vce_read_plain_text_file</a>
1. <a href="#vce_read_simple_config_file">vce_read_simple_config_file</a>
1. <a href="#vce_replace_malloc_funcs">vce_replace_malloc_funcs</a>
1. <a href="#vce_set_heartbeat_wait_flag">vce_set_heartbeat_wait_flag</a>
1. <a href="#vce_set_mainloop_callback">vce_set_mainloop_callback</a>
1. <a href="#vce_set_read_write_log_mode">vce_set_read_write_log_mode</a>
1. <a href="#vce_set_socket_library_ok">vce_set_socket_library_ok</a>
1. <a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>
1. <a href="#vce_show_array_usage">vce_show_array_usage</a>
1. <a href="#vce_snprintf">vce_snprintf</a>
1. <a href="#vce_strerror">vce_strerror</a>
1. <a href="#vce_strerror_close_reason">vce_strerror_close_reason</a>
1. <a href="#vce_tcpcontext_cleanup">vce_tcpcontext_cleanup</a>
1. <a href="#vce_tcpcontext_conn_iterate">vce_tcpcontext_conn_iterate</a>
1. <a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
1. <a href="#vce_tcpcontext_count_connections">vce_tcpcontext_count_connections</a>
1. <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
1. <a href="#vce_tcpcontext_enable_accept">vce_tcpcontext_enable_accept</a>
1. <a href="#vce_tcpcontext_get_all_connection">vce_tcpcontext_get_all_connection</a>
1. <a href="#vce_tcpcontext_get_stat">vce_tcpcontext_get_stat</a>
1. <a href="#vce_tcpcontext_protocol_set_maxlength">vce_tcpcontext_protocol_set_maxlength</a>
1. <a href="#vce_tcpcontext_set_accept_max">vce_tcpcontext_set_accept_max</a>
1. <a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a>
1. <a href="#vce_tcpcontext_set_conn_call_parser_per_heartbeat">vce_tcpcontext_set_conn_call_parser_per_heartbeat</a>
1. <a href="#vce_tcpcontext_set_conn_closewatcher">vce_tcpcontext_set_conn_closewatcher</a>
1. <a href="#vce_tcpcontext_set_conn_finalizer">vce_tcpcontext_set_conn_finalizer</a>
1. <a href="#vce_tcpcontext_set_conn_hiwater_acceptwatcher">vce_tcpcontext_set_conn_hiwater_acceptwatcher</a>
1. <a href="#vce_tcpcontext_set_conn_kickip_array">vce_tcpcontext_set_conn_kickip_array</a>
1. <a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
1. <a href="#vce_tcpcontext_set_equal_io_splitrate">vce_tcpcontext_set_equal_io_splitrate</a>
1. <a href="#vce_tcpcontext_timeout_control">vce_tcpcontext_timeout_control</a>
1. <a href="#vce_tcpcontext_userdata_get_pointer">vce_tcpcontext_userdata_get_pointer</a>
1. <a href="#vce_tcpcontext_userdata_set_pointer">vce_tcpcontext_userdata_set_pointer</a>
1. <a href="#vce_utime_diff">vce_utime_diff</a>

## 名前順のカテゴリ別索引
<!-- make_categoryindex -->
<a name="array"></a>
### array
<p>VCE内に配列を定義する。
配列は、構造体など任意のサイズのバッファの列として管理される。
arrayカテゴリの関数は、
「配列からの割りあて」「解放」「スキャン」を、
空き要素リストを利用することで高速に行なうために整備されている。
有限個の資源を割りあてたり解放したりを高速に行なうことは、
サーバプログラムに限らず多いが、
その部分を根本的に高速化する事を主眼に置いている。
パケットベクトライザやsearchカテゴリの関数では、
内部的にarrayカテゴリの関数を使っているが、
ユーザアプリケーションにおいても使うことができるように解放する。
</p>
Functions:

1. <a href="#ARRAY_SCAN">ARRAY_SCAN</a>
1. <a href="#ARRAY_SCAN_TYPE">ARRAY_SCAN_TYPE</a>
1. <a href="#vce_alloc_array_object">vce_alloc_array_object</a>
1. <a href="#vce_array_object_inuse">vce_array_object_inuse</a>
1. <a href="#vce_end_all_array">vce_end_all_array</a>
1. <a href="#vce_end_array">vce_end_array</a>
1. <a href="#vce_free_array_object">vce_free_array_object</a>
1. <a href="#vce_free_array_object_all">vce_free_array_object_all</a>
1. <a href="#vce_get_array_maxnum">vce_get_array_maxnum</a>
1. <a href="#vce_get_array_member_size">vce_get_array_member_size</a>
1. <a href="#vce_get_array_object_index">vce_get_array_object_index</a>
1. <a href="#vce_get_array_object_last">vce_get_array_object_last</a>
1. <a href="#vce_get_array_object_next">vce_get_array_object_next</a>
1. <a href="#vce_get_array_object_pointer_by_index">vce_get_array_object_pointer_by_index</a>
1. <a href="#vce_get_array_object_pointer_by_index_only_used">vce_get_array_object_pointer_by_index_only_used</a>
1. <a href="#vce_get_array_object_top">vce_get_array_object_top</a>
1. <a href="#vce_get_array_usenum">vce_get_array_usenum</a>
1. <a href="#vce_if_included_in_array">vce_if_included_in_array</a>
1. <a href="#vce_init_array">vce_init_array</a>
1. <a href="#vce_show_array_usage">vce_show_array_usage</a>

<a name="bin"></a>
### bin
<p>bin カテゴリの関数群は，データの pack/unpack を実装している．
データストリームに対してバイナリデータやテキストデータを
出力していく．
この関数群は通常，アプリケーションによって使われることは少ないが，
gen.rb スタブジェネレータの出力コードではこの関数群を基本的に使用している．
</p>
Functions:

1. <a href="#vce_binary_pack">vce_binary_pack</a>
1. <a href="#vce_binary_pop_nb_i1">vce_binary_pop_nb_i1</a>
1. <a href="#vce_binary_pop_nb_i2">vce_binary_pop_nb_i2</a>
1. <a href="#vce_binary_pop_nb_i4">vce_binary_pop_nb_i4</a>
1. <a href="#vce_binary_pop_nb_i8">vce_binary_pop_nb_i8</a>
1. <a href="#vce_binary_pop_nb_ia1">vce_binary_pop_nb_ia1</a>
1. <a href="#vce_binary_pop_nb_ia2">vce_binary_pop_nb_ia2</a>
1. <a href="#vce_binary_pop_nb_ia4">vce_binary_pop_nb_ia4</a>
1. <a href="#vce_binary_pop_nb_ia8">vce_binary_pop_nb_ia8</a>
1. <a href="#vce_binary_pop_nb_stra">vce_binary_pop_nb_stra</a>
1. <a href="#vce_binary_push_nb_i1">vce_binary_push_nb_i1</a>
1. <a href="#vce_binary_push_nb_i2">vce_binary_push_nb_i2</a>
1. <a href="#vce_binary_push_nb_i4">vce_binary_push_nb_i4</a>
1. <a href="#vce_binary_push_nb_i8">vce_binary_push_nb_i8</a>
1. <a href="#vce_binary_push_nb_ia1">vce_binary_push_nb_ia1</a>
1. <a href="#vce_binary_push_nb_ia2">vce_binary_push_nb_ia2</a>
1. <a href="#vce_binary_push_nb_ia4">vce_binary_push_nb_ia4</a>
1. <a href="#vce_binary_push_nb_ia8">vce_binary_push_nb_ia8</a>
1. <a href="#vce_binary_push_nb_stra">vce_binary_push_nb_stra</a>
1. <a href="#vce_binary_unpack">vce_binary_unpack</a>

<a name="core"></a>
### core
<p>coreカテゴリに含まれる関数群は、
VCEのライブラリを駆動するために必要な、
基本的な関数の集まりである。
ループを制御したり、VCE自体の初期化や解放を行なう。
Win32 環境においては、
vce_initialize 関数では、 Winsockの初期化もおこなう。
vce_errout_?? 関数では、VCEアプリケーションのログ出力の操作を行なう。
</p>
Functions:

1. <a href="#vce_conn_set_delay">vce_conn_set_delay</a>
1. <a href="#vce_errout">vce_errout</a>
1. <a href="#vce_finalize">vce_finalize</a>
1. <a href="#vce_heartbeat">vce_heartbeat</a>
1. <a href="#vce_init_limit_t">vce_init_limit_t</a>
1. <a href="#vce_initialize">vce_initialize</a>
1. <a href="#vce_initialize_limited">vce_initialize_limited</a>
1. <a href="#vce_limit_clear">vce_limit_clear</a>
1. <a href="#vce_mainloop">vce_mainloop</a>
1. <a href="#vce_set_heartbeat_wait_flag">vce_set_heartbeat_wait_flag</a>
1. <a href="#vce_set_mainloop_callback">vce_set_mainloop_callback</a>
1. <a href="#vce_set_read_write_log_mode">vce_set_read_write_log_mode</a>
1. <a href="#vce_set_socket_library_ok">vce_set_socket_library_ok</a>
1. <a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>

<a name="err"></a>
### err
<p>VCE内部のエラーコードに関する処理をする関数群。
基本的に vce_get_last_error してから その返り値を vce_strerror する。
</p>
Functions:

1. <a href="#vce_get_last_error">vce_get_last_error</a>
1. <a href="#vce_strerror">vce_strerror</a>
1. <a href="#vce_strerror_close_reason">vce_strerror_close_reason</a>

<a name="log"></a>
### log
<p>logカテゴリに含まれる関数群は、
VCEログフォーマットに基づいたログの出力のための関数の集まりである。
このAPIを使用して出力されたログは、VCE Admin Tool を使用することで
統合的に検索、保存ができる。
VCEログフォーマットについては、<a href="monitor.html">「VCEモニタリング」</a>を参照。
</p>
Functions:

1. <a href="#vce_get_netstat_string">vce_get_netstat_string</a>
1. <a href="#vce_get_stat">vce_get_stat</a>

<a name="parser"></a>
### parser
<p>parserカテゴリに属する関数群は、
conn_t コネクションからの入力を
レコード単位に分割し、分割されたレコードごとにコールバック関数を呼びだす。
VCE ではこのようにレコード単位のプロトコル処理を基本としている。
</p>
Functions:

1. <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a>
1. <a href="#vce_protocol_parser_bin32">vce_protocol_parser_bin32</a>
1. <a href="#vce_protocol_parser_text">vce_protocol_parser_text</a>
1. <a href="#vce_protocol_parser_through">vce_protocol_parser_through</a>
1. <a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a>
1. <a href="#vce_protocol_unparser_bin32">vce_protocol_unparser_bin32</a>
1. <a href="#vce_protocol_unparser_text">vce_protocol_unparser_text</a>
1. <a href="#vce_protocol_unparser_through">vce_protocol_unparser_through</a>

<a name="pcallback"></a>
### pcallback
<p>pcallback カテゴリに属する関数群は、
parser によってレコード単位に分割されたデータを処理するためのコールバック
関数である。通常のアプリケーションでは、
このコールバック関数の内容はアプリケーション開発者によって定義されるが、
エコーやダンプなど基本的な内容のコールバック関数はあらかじめ VCE
に内蔵されているため、デバッグの目的に使用することができる。
</p>
Functions:

1. <a href="#vce_protocol_pcallback_dump">vce_protocol_pcallback_dump</a>
1. <a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a>
1. <a href="#vce_protocol_pcallback_echo_text">vce_protocol_pcallback_echo_text</a>
1. <a href="#vce_protocol_pcallback_noop">vce_protocol_pcallback_noop</a>

<a name="tcp"></a>
### tcp
<p>tcpカテゴリでは、tcpcontext_t 型の操作を通して、
VCEの主ターゲットプロトコルであるTCPに関する基本機能を実装している。
Blowfish/Twofish/Rijndael を用いた暗号化や、
Diffie-Hellmanによる鍵交換、
パケットベクトライザ、圧縮など、通信に必要な基本的機能の集合である。
tcpカテゴリの関数の働きを理解するには、
VCEにおける
<a href="tcpcontext.html">TCPコネクション管理システムの仕組</a>
を理解することが必要である。
</p>
Functions:

1. <a href="#vce_conn_break_heartbeat">vce_conn_break_heartbeat</a>
1. <a href="#vce_conn_clear">vce_conn_clear</a>
1. <a href="#vce_conn_close">vce_conn_close</a>
1. <a href="#vce_conn_close_tcpcontext_all">vce_conn_close_tcpcontext_all</a>
1. <a href="#vce_conn_get_buffer">vce_conn_get_buffer</a>
1. <a href="#vce_conn_get_index">vce_conn_get_index</a>
1. <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a>
1. <a href="#vce_conn_get_local_ipv4_addr">vce_conn_get_local_ipv4_addr</a>
1. <a href="#vce_conn_get_local_ipv4_addr_string">vce_conn_get_local_ipv4_addr_string</a>
1. <a href="#vce_conn_get_local_ipv6_addr">vce_conn_get_local_ipv6_addr</a>
1. <a href="#vce_conn_get_local_ipv6_addr_string">vce_conn_get_local_ipv6_addr_string</a>
1. <a href="#vce_conn_get_remote_addr_string">vce_conn_get_remote_addr_string</a>
1. <a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a>
1. <a href="#vce_conn_get_remote_ipv4_addr_string">vce_conn_get_remote_ipv4_addr_string</a>
1. <a href="#vce_conn_get_remote_ipv6_addr">vce_conn_get_remote_ipv6_addr</a>
1. <a href="#vce_conn_get_remote_ipv6_addr_string">vce_conn_get_remote_ipv6_addr_string</a>
1. <a href="#vce_conn_get_stat">vce_conn_get_stat</a>
1. <a href="#vce_conn_get_state_buffer">vce_conn_get_state_buffer</a>
1. <a href="#vce_conn_get_struct_from_index">vce_conn_get_struct_from_index</a>
1. <a href="#vce_conn_get_tcpcontext">vce_conn_get_tcpcontext</a>
1. <a href="#vce_conn_is_equal">vce_conn_is_equal</a>
1. <a href="#vce_conn_is_valid">vce_conn_is_valid</a>
1. <a href="#vce_conn_set_parser">vce_conn_set_parser</a>
1. <a href="#vce_conn_set_timeout">vce_conn_set_timeout</a>
1. <a href="#vce_conn_show_stat">vce_conn_show_stat</a>
1. <a href="#vce_conn_shrink_readbuf">vce_conn_shrink_readbuf</a>
1. <a href="#vce_conn_userdata_get_pointer">vce_conn_userdata_get_pointer</a>
1. <a href="#vce_conn_userdata_set_pointer">vce_conn_userdata_set_pointer</a>
1. <a href="#vce_conn_writable">vce_conn_writable</a>
1. <a href="#vce_conn_write">vce_conn_write</a>
1. <a href="#vce_conn_writed">vce_conn_writed</a>
1. <a href="#vce_get_tcp_packet_read_size">vce_get_tcp_packet_read_size</a>
1. <a href="#vce_get_tcp_packet_write_size">vce_get_tcp_packet_write_size</a>
1. <a href="#vce_tcpcontext_cleanup">vce_tcpcontext_cleanup</a>
1. <a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
1. <a href="#vce_tcpcontext_count_connections">vce_tcpcontext_count_connections</a>
1. <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
1. <a href="#vce_tcpcontext_enable_accept">vce_tcpcontext_enable_accept</a>
1. <a href="#vce_tcpcontext_get_all_connection">vce_tcpcontext_get_all_connection</a>
1. <a href="#vce_tcpcontext_get_stat">vce_tcpcontext_get_stat</a>
1. <a href="#vce_tcpcontext_protocol_set_maxlength">vce_tcpcontext_protocol_set_maxlength</a>
1. <a href="#vce_tcpcontext_set_accept_max">vce_tcpcontext_set_accept_max</a>
1. <a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a>
1. <a href="#vce_tcpcontext_set_conn_call_parser_per_heartbeat">vce_tcpcontext_set_conn_call_parser_per_heartbeat</a>
1. <a href="#vce_tcpcontext_set_conn_closewatcher">vce_tcpcontext_set_conn_closewatcher</a>
1. <a href="#vce_tcpcontext_set_conn_finalizer">vce_tcpcontext_set_conn_finalizer</a>
1. <a href="#vce_tcpcontext_set_conn_hiwater_acceptwatcher">vce_tcpcontext_set_conn_hiwater_acceptwatcher</a>
1. <a href="#vce_tcpcontext_set_conn_kickip_array">vce_tcpcontext_set_conn_kickip_array</a>
1. <a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
1. <a href="#vce_tcpcontext_set_equal_io_splitrate">vce_tcpcontext_set_equal_io_splitrate</a>
1. <a href="#vce_tcpcontext_timeout_control">vce_tcpcontext_timeout_control</a>
1. <a href="#vce_tcpcontext_userdata_get_pointer">vce_tcpcontext_userdata_get_pointer</a>
1. <a href="#vce_tcpcontext_userdata_set_pointer">vce_tcpcontext_userdata_set_pointer</a>

<a name="text"></a>
### text
<p>text カテゴリの関数群は、
HTTPプロトコルのヘッダや，サーバの設定ファイルなど，
複雑な構造を持たないテキストを高速に処理するためにデザインされている。
したがって，日本語文字変換などの高度な機能は含まれていない．
特に HTTP 関係の関数は，VCE を用いてHTTPサーバを作成する場合には有効である．
</p>
Functions:

1. <a href="#vce_snprintf">vce_snprintf</a>

<a name="util"></a>
### util
<p>utilカテゴリの関数群は、
VCEアプリケーションの開発をしていく時に有用である。
特に暗号化ルーチンやハッシュのルーチンを使うための関数群などが有用である．
</p>
Functions:

1. <a href="#ELEMENTOF">ELEMENTOF</a>
1. <a href="#FREE">FREE</a>
1. <a href="#GET_16BIT_INT">GET_16BIT_INT</a>
1. <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a>
1. <a href="#GET_32BIT_INT">GET_32BIT_INT</a>
1. <a href="#GET_32BIT_NATIVEINT">GET_32BIT_NATIVEINT</a>
1. <a href="#GET_64BIT_INT">GET_64BIT_INT</a>
1. <a href="#GET_64BIT_NATIVEINT">GET_64BIT_NATIVEINT</a>
1. <a href="#GET_8BIT_INT">GET_8BIT_INT</a>
1. <a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
1. <a href="#MALLOC">MALLOC</a>
1. <a href="#MAX">MAX</a>
1. <a href="#MIN">MIN</a>
1. <a href="#SET_16BIT_INT">SET_16BIT_INT</a>
1. <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a>
1. <a href="#SET_32BIT_INT">SET_32BIT_INT</a>
1. <a href="#SET_32BIT_NATIVEINT">SET_32BIT_NATIVEINT</a>
1. <a href="#SET_64BIT_INT">SET_64BIT_INT</a>
1. <a href="#SET_64BIT_NATIVEINT">SET_64BIT_NATIVEINT</a>
1. <a href="#SET_8BIT_INT">SET_8BIT_INT</a>
1. <a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
1. <a href="#STRERR">STRERR</a>
1. <a href="#vce_atoi">vce_atoi</a>
1. <a href="#vce_dump_buffer">vce_dump_buffer</a>
1. <a href="#vce_extract_data_from_hex_text">vce_extract_data_from_hex_text</a>
1. <a href="#vce_get_current_utime">vce_get_current_utime</a>
1. <a href="#vce_get_ipv4_addr_by_name">vce_get_ipv4_addr_by_name</a>
1. <a href="#vce_make_binary_array_from_hex">vce_make_binary_array_from_hex</a>
1. <a href="#vce_make_binary_array_from_line">vce_make_binary_array_from_line</a>
1. <a href="#vce_make_hex_from_binary_array">vce_make_hex_from_binary_array</a>
1. <a href="#vce_make_hex_text_from_buffer">vce_make_hex_text_from_buffer</a>
1. <a href="#vce_read_plain_text_file">vce_read_plain_text_file</a>
1. <a href="#vce_read_simple_config_file">vce_read_simple_config_file</a>
1. <a href="#vce_replace_malloc_funcs">vce_replace_malloc_funcs</a>
1. <a href="#vce_utime_diff">vce_utime_diff</a>

<a name="watcher"></a>
### watcher
<p>watcher カテゴリの関数群は、conn_t を新規に受けいれ(accept)したり、閉じられたりしたときにそれを検知するための
コールバック関数群である。現在は acceptwatcher と closewatcher が存在する。
</p>
Functions:

1. <a href="#vce_protocol_acceptwatcher_deny">vce_protocol_acceptwatcher_deny</a>
1. <a href="#vce_protocol_acceptwatcher_noop">vce_protocol_acceptwatcher_noop</a>
1. <a href="#vce_protocol_closewatcher_noop">vce_protocol_closewatcher_noop</a>

## 全関数定義
<!-- make_funcdef start -->
<a name="ARRAY_SCAN"></a>
- <B>ARRAY_SCAN</B>

  概要 : VCEによって管理されている配列の全使用中要素をスキャンする

  カテゴリ : array

  関数プロトタイプ : ```ARRAY_SCAN( int arraydescriptor, void* pointer )``` 

  - arg 1 : ```int arraydescriptor```
    VCEの管理する配列にアクセスするための識別値。
この値は、 vce_init_array の返り値を保存しておいたものが使われる。
ちょうどUNIXにおけるファイルデスクリプタと同じように扱えばよい。

  - arg 2 : ```void *pointer```
    このポインター変数に配列の各要素のアドレスを代入する。

  返り値 : 本マクロは、関数のように使うのではなく、
ループの始まりとして使う(forのように)ために、返り値というものはない。

  詳細説明 : VCEの配列管理ルーチンを使う場合に、
全要素をスキャンする処理をしたい場合がある。そのためには、
vce_get_array_object_top 関数を用いて使用中リストから先頭の要素を取りだし、
次に vce_get_array_object_next 関数を用いてNULLを返すまで処理をくりかえす。
しかしその処理は繁雑なため、本マクロが用意されている。<BR>
注意点としては、本マクロによって取りだされる配列の要素は、
「使用中」つまり、使用中リストに入っているものだけである。
配列の最大サイズが1000個であったとしても使用中のものがなければ、
ループは1回もまわらない。

  使用例 : <pre>
// memory_ind によって指定されている配列のすべての使用中要素に処理をする
struct client *c;
ARRAY_SCAN( memory_ind, c ){
  do_something_to_the_structure( c );
}
</pre>

  See also : <a href="#vce_get_array_object_next">vce_get_array_object_next</a><a href="#vce_get_array_object_top">vce_get_array_object_top</a><a href="#vce_init_array">vce_init_array</a>
<a name="ARRAY_SCAN_TYPE"></a>
- <B>ARRAY_SCAN_TYPE</B>

  概要 : ARRAY_SCAN を C++ で使うための変種

  カテゴリ : array

  関数プロトタイプ : ```ARRAY_SCAN_TYPE( int arraydescriptor void *pointer, typedecl )``` 

  - arg 1 : ```int arraydescriptor```
    VCE の配列にアクセスするための識別値

  - arg 2 : ```void *pointer```
    このポインター変数に配列の各要素のアドレスを代入する。

  - arg 3 : ``` typedecl```
    ポインター変数の型を指定する。

  返り値 : なし。 使用方法は、 ARRAY_SCANと同じ。

  詳細説明 : ARRAY_SCAN は void のポインタをポインター変数 pointer に代入するが、
C++ においてはキャストが必要なためその処理がコンパイルエラーを発生する。
そのため、ARRAY_SCAN_TYPE マクロでは、
ポインタ変数の型をマクロに与えるようにしている。

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a>
<a name="ELEMENTOF"></a>
- <B>ELEMENTOF</B>

  概要 : 固定サイズの配列の要素数を返す(コンパイル時定数)。

  カテゴリ : util

  関数プロトタイプ : ```int ELEMENTOF(x)``` 

  - arg 1 : ```x```
    任意のC言語配列 (ポインタではない)

  返り値 : 配列の要素数

  詳細説明 : このマクロは実際には
<pre>
( sizeof(x) / sizeof((x)[0]) ) 
</pre>
と定義されている。mallocによって割りあてた配列のサイズは
コンパイル時にサイズが確定しないため、このマクロは使用できない。

  使用例 : <pre>
  int hoge[]= {1,2,3,4,5};
  a = ELEMENTOF(hoge);           // a には5が入る
</pre>


<a name="FREE"></a>
- <B>FREE</B>

  概要 : MALLOC関数で割りあてたメモリ領域を解放する。

  カテゴリ : util

  関数プロトタイプ : ```void FREE( void *p )``` 

  - arg 1 : ```void *p```
    解放するメモリ領域の先頭アドレス

  返り値 : なし

  詳細説明 : 標準C言語のfree関数をwrapする関数である。
単純に、free呼びだし記録をログするだけである。
vce_set_verbose_mode を1に設定すると、ログを出力するようになる。

  See also : <a href="#MALLOC">MALLOC</a><a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>
<a name="GET_16BIT_INT"></a>
- <B>GET_16BIT_INT</B>

  概要 : メモリ領域から16ビットの整数値を取りだす。

  カテゴリ : util

  関数プロトタイプ : ```unsigned short GET_16BIT_INT( char *p )``` 

  - arg 1 : ```char *p```
    取りだしたい値がネットワークバイトオーダで格納されているバッファの先頭
アドレス

  返り値 : 結果のunsigned short値

  詳細説明 : 内部でntohsを使用している。主にプロトコル処理に使われるが、
より一般的な目的のためには、 bin カテゴリの関数群を使うべきである。

  See also : <a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_16BIT_NATIVEINT"></a>
- <B>GET_16BIT_NATIVEINT</B>

  概要 : バッファから16ビット整数値を取りだす。

  カテゴリ : util

  関数プロトタイプ : ```short GET_16BIT_NATIVEINT( char *p )``` 

  返り値 : 取りだしたshort値

  詳細説明 : ntohs, htons などをつかわない、取りだしマクロである。

  See also : <a href="#GET_32BIT_NATIVEINT">GET_32BIT_NATIVEINT</a><a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
<a name="GET_32BIT_INT"></a>
- <B>GET_32BIT_INT</B>

  概要 : メモリ領域から32ビット整数値を取りだすマクロ

  カテゴリ : util

  関数プロトタイプ : ```unsigned int GET_32BIT_INT( char *p )``` 

  - arg 1 : ```char *p```
    取りだす元になるバッファの先頭アドレス

  返り値 : 取りだした値

  詳細説明 : 内部で ntohlを使用している。
このマクロはバイナリプロトコル解析用に使われるが、アプリケーションで
バイナリプロトコルを実装する場合には、このマクロではなく、
bin カテゴリの関数群を使うべきである。

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_32BIT_NATIVEINT"></a>
- <B>GET_32BIT_NATIVEINT</B>

  概要 : バッファから32ビット整数値を取りだす

  カテゴリ : util

  関数プロトタイプ : ```int GET_32BIT_NATIVEINT( char *p )``` 

  返り値 : 取りだしたint値

  詳細説明 : ntohl, htonl 等をつかわない取りだしマクロである。

  See also : <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a><a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
<a name="GET_64BIT_INT"></a>
- <B>GET_64BIT_INT</B>

  概要 : メモリ領域から64ビット整数値を取りだすマクロ

  カテゴリ : util

  関数プロトタイプ : ```VCEI64 GET_64BIT_INT( char *p )``` 

  - arg 1 : ```char *p```
    取りだす元になるバッファの先頭アドレス

  返り値 : 取りだした値

  詳細説明 : 内部で ntohlを使用している。
このマクロはバイナリプロトコル解析用に使われるが、アプリケーションで
バイナリプロトコルを実装する場合には、このマクロではなく、
bin カテゴリの関数群を使うべきである。

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_64BIT_NATIVEINT"></a>
- <B>GET_64BIT_NATIVEINT</B>

  概要 : バッファから64ビット整数値を取りだす

  カテゴリ : util

  関数プロトタイプ : ```int GET_64BIT_NATIVEINT( char *p )``` 

  返り値 : 取りだしたint値

  詳細説明 : ntohl, htonl 等をつかわない取りだしマクロである。

  See also : <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a><a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
<a name="GET_8BIT_INT"></a>
- <B>GET_8BIT_INT</B>

  概要 : メモリ領域から8ビットの整数値を取りだす

  カテゴリ : util

  関数プロトタイプ : ```unsigned char GET_8BIT_INT( char *b )``` 

  - arg 1 : ```char *b```
    取りだす値が格納されているバッファの先頭アドレス

  返り値 : 取りだした値

  詳細説明 : 単に値を取りだすだけ。32ビット、16ビット等のマクロとの整合性をとるために
定義されている。

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_8BIT_NATIVEINT"></a>
- <B>GET_8BIT_NATIVEINT</B>

  概要 : バッファから8ビット整数値を取りだす

  カテゴリ : util

  関数プロトタイプ : ```char GET_8BIT_NATIVEINT( char *p )``` 

  返り値 : 取りだした8ビット値

  詳細説明 : GET_32BIT_NATIVEINT,GET_16BIT_NATIVEINTなどと整合性のあるコードを書くため
だけに定義されている。

  See also : <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a><a href="#GET_32BIT_NATIVEINT">GET_32BIT_NATIVEINT</a>
<a name="MALLOC"></a>
- <B>MALLOC</B>

  概要 : malloc の wrapper. Cライブラリのmallocのラッパー

  カテゴリ : util

  関数プロトタイプ : ```void *MALLOC( size_t size )``` 

  - arg 1 : ```size_t size```
    割りあてるメモリのサイズ(バイト数)

  返り値 : 割りあてられたメモリ領域の先頭アドレス

  詳細説明 : 標準Cライブラリのmalloc()関数を呼びだし、mallocの返り値をそのまま
返す。
VCEでは、 malloc 関数はプログラム起動時に1回だけ呼びだして
大きなメモリ領域を割りあて、起動後は一切mallocせず、
cleanup時にすべてをfree()するという戦略を取っている。
これはmalloc関数の動作が遅いことや、
malloc関数の実装方法の違いによる挙動の変化を最小に抑えるためである。
MALLOC関数は、FREE関数と対で使用される。
vce_set_verbose_mode を1に設定すると、ログを出力するようになる。

  See also : <a href="#FREE">FREE</a><a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>
<a name="MAX"></a>
- <B>MAX</B>

  概要 : 2つの値を比較して大きい方の値を返す

  カテゴリ : util

  関数プロトタイプ : ```int MAX(int a, int b)``` 

  - arg 1 : ```int a```
    比較する片方の値。プロトタイプではintになっているが、
実際はマクロで定義されているので、比較演算子が使える型であればどんな型でも
使用することができる(移植性は高い)。

  - arg 2 : ```int b```
    比較するもう片方の値

  返り値 : 得られた値 ( 大きいほう )．

  詳細説明 : 以下のような定義になっている。char,short,int,long,long long ,float,double,VCEI64
とそれらの符号なし型に対応している。
<pre>
( (x) &gt; (y) ? (x)  (y) )
</pre>

  See also : <a href="#MIN">MIN</a>
<a name="MIN"></a>
- <B>MIN</B>

  概要 : 2つの値を比較して小さい方の値を返す

  カテゴリ : util

  関数プロトタイプ : ```int MIN(int a, int b )``` 

  - arg 1 : ```int a```
    比較する片方の値。プロトタイプではintになっているが、
実際はマクロで定義されているので、比較演算子が使える型であればどんな型でも
使用することができる(移植性は高い)。

  - arg 2 : ```int b```
    比較するもう片方の値

  返り値 : 結果の値

  詳細説明 : 以下のような定義になっている。char,short,int,long,long long,float,double,VCEI64
 とそれらの符号なし型に対応している。
<pre>
( (x) &lt; (y) ? (x)  (y) )
</pre>

  See also : <a href="#MAX">MAX</a>
<a name="SET_16BIT_INT"></a>
- <B>SET_16BIT_INT</B>

  概要 : メモリ領域に16ビットの整数値をネットワークバイトオーダでコピーする

  カテゴリ : util

  関数プロトタイプ : ```void SET_16BIT_INT( char *b, unsigned short i )``` 

  - arg 1 : ```char *b```
    コピーする先のバッファの先頭アドレス

  - arg 2 : ```unsigned short i```
    コピーする16ビットネイティブ値。

  返り値 : なし

  詳細説明 : 内部でhtonsを使用している。主にプロトコル処理に使われるが、
より一般的な目的のためには、 bin カテゴリの関数群を使うべきである。

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="SET_16BIT_NATIVEINT"></a>
- <B>SET_16BIT_NATIVEINT</B>

  概要 : 16ビット整数値を任意のバッファにコピーする

  カテゴリ : util

  関数プロトタイプ : ```void SET_16BIT_NATIVEINT( char *p, short i )``` 

  - arg 1 : ```char *p```
    コピーする先のバッファの先頭アドレス

  - arg 2 : ```short i```
    コピーする値

  返り値 : なし

  詳細説明 : ntohs, htons 等を使用しない。直接値をコピーする。
ポインタの型キャストをするためのマクロ。

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="SET_32BIT_INT"></a>
- <B>SET_32BIT_INT</B>

  概要 : メモリ領域に32ビットの整数値をネットワークバイトオーダでコピーする

  カテゴリ : util

  関数プロトタイプ : ```void SET_32BIT_INT( char *b, unsigned int i )``` 

  - arg 1 : ```char *b```
    値をコピーする先のメモリの先頭アドレス

  - arg 2 : ```unsigned int i```
    コピーしたい値(ネイティブ値)

  返り値 : なし

  詳細説明 : 内部で htonlを使用している。プロトコル解析用に使用されるが、
アプリケーションはプロトコル解析をする場合は、このマクロを使用
せずに bin カテゴリの関数群を使うべきである(そのほうが堅牢である。)

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="SET_32BIT_NATIVEINT"></a>
- <B>SET_32BIT_NATIVEINT</B>

  概要 : 32ビットの値を、任意のバッファにセットする

  カテゴリ : util

  関数プロトタイプ : ```void SET_32BIT_NATIVEINT( char *p, int i )``` 

  - arg 1 : ```char *p```
    コピーする先のバッファの先頭アドレス

  - arg 2 : ```int i```
    コピーする値

  返り値 : なし

  詳細説明 : htonl, ntohl等を使用せず、直接値をコピーする。
ポインタのキャストをするだけのマクロ。

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="SET_64BIT_INT"></a>
- <B>SET_64BIT_INT</B>

  概要 : メモリ領域に64ビットの整数値をネットワークバイトオーダでコピーする

  カテゴリ : util

  関数プロトタイプ : ```void SET_64BIT_INT( char *b, VCEI64 i )``` 

  - arg 1 : ```char *b```
    値をコピーする先のメモリの先頭アドレス

  - arg 2 : ```VCEI64 i```
    コピーしたい値(ネイティブ値)

  返り値 : なし

  詳細説明 : 内部で htonlを使用している。プロトコル解析用に使用されるが、
アプリケーションはプロトコル解析をする場合は、このマクロを使用
せずに bin カテゴリの関数群を使うべきである(そのほうが堅牢である。)

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="SET_64BIT_NATIVEINT"></a>
- <B>SET_64BIT_NATIVEINT</B>

  概要 : 64ビットの値を、任意のバッファにセットする

  カテゴリ : util

  関数プロトタイプ : ```void SET_64BIT_NATIVEINT( char *p, VCEI64 i )``` 

  - arg 1 : ```char *p```
    コピーする先のバッファの先頭アドレス

  - arg 2 : ```int i```
    コピーする値

  返り値 : なし

  詳細説明 : htonl, ntohl等を使用せず、直接値をコピーする。
ポインタのキャストをするだけのマクロ。

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="SET_8BIT_INT"></a>
- <B>SET_8BIT_INT</B>

  概要 : メモリ領域に8ビットの整数値をコピーする

  カテゴリ : util

  関数プロトタイプ : ```void SET_8BIT_INT( char *b, unsigned char i )``` 

  - arg 1 : ```char *b```
    コピーする先のバッファの先頭アドレス

  - arg 2 : ```unsigned char i```
    コピーする8ビット値

  返り値 : なし

  詳細説明 : 単にバッファにコピーするだけ。32ビット、16ビットなどのマクロとの整合性
をとって美しいコードを書くためだけに存在する。

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a>
<a name="SET_8BIT_NATIVEINT"></a>
- <B>SET_8BIT_NATIVEINT</B>

  概要 : 8ビットの整数値を任意のバッファにコピーする

  カテゴリ : util

  関数プロトタイプ : ```void SET_8BIT_NATIVEINT( char *p, char i )``` 

  - arg 1 : ```char *P```
    コピーする先のバッファの先頭アドレス

  - arg 2 : ```char i```
    コピーする値

  返り値 : なし

  詳細説明 : SET_16BIT_NATIVEINT,SET_32BIT_NATIVEINT との整合性をとってソースコードを
美しく書くためだけのマクロ。

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="STRERR"></a>
- <B>STRERR</B>

  概要 : VCEの最新エラーコードを文字列で得る

  カテゴリ : util

  関数プロトタイプ : ```char *STRERR``` 

  返り値 : 出力の文字列へのポインタ。

  詳細説明 : STRERRの定義は
<pre>
(vce_strerror( vce_get_last_error() ))
</pre>
である。

  See also : <a href="#vce_get_last_error">vce_get_last_error</a><a href="#vce_strerror">vce_strerror</a>
<a name="vce_alloc_array_object"></a>
- <B>vce_alloc_array_object</B>

  概要 : VCE配列の未使用要素を1個わりあてる

  カテゴリ : array

  関数プロトタイプ : ```void * vce_alloc_array_object( int index )``` 

  - arg 1 : ```int index```
    VCE配列を特定するための配列デスクリプタ

  返り値 : 割りあてられた配列要素の先頭アドレス。
配列の最大要素数まで要素を使いきっている場合(空きリストに何もない場合)は、
ヌルポインタを返す。
それ以外にもエラーの内容は vce_get_last_error で得ることができる。

  詳細説明 : VCE配列の空きリストを検索し、未使用要素がある場合はそのポインタを返す。
この関数は，あたらしく割りあてるバッファの中身に対して
何らかのデータを書きこむこと(ゼロ初期化等)は一切しない．

  See also : <a href="#vce_free_array_object">vce_free_array_object</a><a href="#vce_free_array_object_all">vce_free_array_object_all</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_array_object_inuse"></a>
- <B>vce_array_object_inuse</B>

  概要 : VCE配列の要素が使用中かどうかを調べる

  カテゴリ : array

  関数プロトタイプ : ```int vce_array_object_inuse( int index, void *p )``` 

  - arg 1 : ```int index```
    配列ディスクリプタ

  - arg 2 : ```void *p```
    配列要素をさすポインタ

  返り値 : 使用中なら1，そうでないなら0，
範囲外のポインタやindexの値が不正なときは負のエラーコード．

  詳細説明 : この関数を使うと，あるポインタが，
配列の中で使用中かどうかの状態を知ることができる．

  See also : <a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_free_array_object">vce_free_array_object</a>
<a name="vce_atoi"></a>
- <B>vce_atoi</B>

  概要 : 文字列を整数(int)に変換する。簡単な計算機能つき。

  カテゴリ : util

  関数プロトタイプ : ```int vce_atoi( char *p )``` 

  - arg 1 : ```char *p```
    変換する文字列。

  返り値 : 変換後の値。不正な入力の場合は一律に0を返す。

  詳細説明 : 単純な計算機能つきatoiルーチンである。
以下のような入力を受けつける。
<pre>
"12345"    →  12345
"-12345"   → -12345
"123+123"  →  246
"123-123"  →  0
"123+-123"  →  0
"-123-123" →  -246
"123*3"    →  369
"-123*3"   → -369
"-123*-3"  →  369
"123+2*2"  →  250  先に + が計算されていることに注意
"1+1+1+1+1"  →  5  いくつでもつなげることができる
"1+1+  1+1  +1"  →  5  空白文字(TAB,SPACE)は読みとばされる
</pre>
電卓の操作のように、演算子の結合強度とは無関係に、前の演算子から順に
計算していくことに注意。
内部ではlibcの atoi を使用している。
<BR>
入力が変換不可能な場合は、一律に0を返すが、そういう仕様だと0という値が
エラーなのか正しい値なのか判別できないため、変換できなかった場合は、
vce_get_last_error 関数を使って、VCE_EFORMAT を検出することで、
0が正しい出力なのかエラーなのかを判別することができるようになっている。
10進数専用である。

  知られているバグやTODO : 現在，この関数はまだ実験段階なため，
不安定(結果がおかしくなる場合がある)である．


<a name="vce_binary_pack"></a>
- <B>vce_binary_pack</B>

  概要 : 構造体に保存されているデータをpackして、バイト列にする (古い)

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pack( struct bin_info *bi, int bn, char *outp, int len )``` 

  - arg 1 : ```struct bin_info *bi```
    bin_info構造体の配列の先頭アドレス

  - arg 2 : ```int bn```
    bin_info構造体の要素数

  - arg 3 : ```char *outp```
    出力バッファ

  - arg 4 : ```int len```
    出力バッファの最大長(バイト数)

  返り値 : 出力バッファに出力したバイト数

  詳細説明 : bin_info 構造体に保存されている状態のデータをPackし、一連のバイト列に
変換する。主にプロトコル処理で使われる。

  知られているバグやTODO : 現在は バイナリpush/pop 関数群によって，置きかえられている．


<a name="vce_binary_pop_nb_i1"></a>
- <B>vce_binary_pop_nb_i1</B>

  概要 : バッファから1バイト整数(char) を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_i1( char *in, int len, int ofs, char *out)``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだしはじめる場所の、バッファの先頭からのオフセット

  - arg 4 : ```char *out```
    取りだしたデータを格納するための char のポインタ

  返り値 : 1バイト取りだすことによって移動する、新しい ofs の値

  詳細説明 : vce_binary_push_nb_i1 関数で pack したデータを取りだす。
オフセットはつねに1進む。ただし、失敗した場合(データが足りないなど)は、
負のエラーコードを返す。

  See also : <a href="#vce_binary_push_nb_i1">vce_binary_push_nb_i1</a>
<a name="vce_binary_pop_nb_i2"></a>
- <B>vce_binary_pop_nb_i2</B>

  概要 : バッファから2バイト整数(short) を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_i2( char *in, int len, int ofs, short *out )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだしはじめる場所の、バッファの先頭からのオフセット

  - arg 4 : ```short *out```
    取りだしたデータを格納するための short のポインタ

  返り値 : 2バイト取りだすことによって移動する、新しい ofs の値

  詳細説明 : vce_binary_push_nb_i2 関数で pack したデータを取りだす。
オフセットはつねに2進む。ただし、失敗した場合(データが足りないなど)は、
負のエラーコードを返す。

  See also : <a href="#vce_binary_push_nb_i2">vce_binary_push_nb_i2</a>
<a name="vce_binary_pop_nb_i4"></a>
- <B>vce_binary_pop_nb_i4</B>

  概要 : バッファから4バイト整数(int) を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_i4( char *in, int len, int ofs, int *out )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだしはじめる場所の、バッファの先頭からのオフセット

  - arg 4 : ```int *out```
    取りだしたデータを格納するための int のポインタ

  返り値 : 4バイト取りだすことによって移動する、新しい ofs の値

  詳細説明 : vce_binary_push_nb_i4 関数で pack したデータを取りだす。
オフセットはつねに4進む。ただし、失敗した場合(データが足りないなど)は、
負のエラーコードを返す。

  See also : <a href="#vce_binary_push_nb_i4">vce_binary_push_nb_i4</a>
<a name="vce_binary_pop_nb_i8"></a>
- <B>vce_binary_pop_nb_i8</B>

  概要 : バッファから8バイト整数(VCEI64) を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_i8( char *in, int len, int ofs, VCEI64 *out )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだしはじめる場所の、バッファの先頭からのオフセット

  - arg 4 : ```VCEI64 *out```
    取りだしたデータを格納するための VCEI64 のポインタ

  返り値 : 8バイト取りだすことによって移動する、新しい ofs の値

  詳細説明 : vce_binary_push_nb_i8 関数で pack したデータを取りだす。
オフセットはつねに8進む。ただし、失敗した場合(データが足りないなど)は、
負のエラーコードを返す。

  See also : <a href="#vce_binary_push_nb_i8">vce_binary_push_nb_i8</a>
<a name="vce_binary_pop_nb_ia1"></a>
- <B>vce_binary_pop_nb_ia1</B>

  概要 : バッファから1バイト整数(char) の配列を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_ia1( char *src, int len, int ofs, char *out, int *outlen )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだす場所のバッファ先頭からのオフセット

  - arg 4 : ```char *out```
    取りだしたデータを格納する char 型の配列の先頭アドレス

  - arg 5 : ```int *outlen```
    値結果引数。引数として与えるときは、
out 引数で指定する配列の要素数を受けとり、
結果として、実際に埋めた要素数を返す。

  返り値 : 配列を取りだすことによって移動する、あたらしい ofs の値。
取りだしに失敗したら負のエラーコードを返す。

  詳細説明 : vce_binary_push_nb_ia1 関数で pack したデータを取りだす。
データが足りない場合や、取りだすための配列が小さすぎるなどの場合は、
中途半端に取りだすことはせず、失敗をあらわす負のエラーコードを返す。
これは VCE のバイナリ操作のポリシーとなっている。

  See also : <a href="#vce_binary_push_nb_ia1">vce_binary_push_nb_ia1</a>
<a name="vce_binary_pop_nb_ia2"></a>
- <B>vce_binary_pop_nb_ia2</B>

  概要 : バッファから2バイト整数(short) の配列を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_ia2( char *src, int len, int ofs, short *out, int *outlen )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだす場所のバッファ先頭からのオフセット

  - arg 4 : ```short *out```
    取りだしたデータを格納する short 型の配列の先頭アドレス

  - arg 5 : ```int *outlen```
    値結果引数。値として、 out 引数で指定する配列の要素数を受けとり、
結果として、実際に埋めた要素数を返す。

  返り値 : 配列を取りだすことによって移動する、あたらしい ofs の値。
取りだしに失敗したら負のエラーコードを返す。

  詳細説明 : vce_binary_push_nb_ia2 関数で pack したデータを取りだす。
データが足りない場合や、取りだすための配列が小さすぎるなどの場合は、
中途半端に取りだすことはせず、失敗をあらわす負のエラーコードを返す。
これは VCE のバイナリ操作のポリシーとなっている。
データはネットワークバイトオーダからネイティブのオーダーに戻して格納される。

  See also : <a href="#vce_binary_push_nb_ia2">vce_binary_push_nb_ia2</a>
<a name="vce_binary_pop_nb_ia4"></a>
- <B>vce_binary_pop_nb_ia4</B>

  概要 : バッファから4バイト整数(int) の配列を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_ia4( char *src, int len, int ofs, int *out, int *outlen )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだす場所のバッファ先頭からのオフセット

  - arg 4 : ```int *out```
    取りだしたデータを格納する int 型の配列の先頭アドレス

  - arg 5 : ```int *outlen```
    値結果引数。値として、 out 引数で指定する配列の要素数を受けとり、
結果として、実際に埋めた要素数を返す。

  返り値 : 配列を取りだすことによって移動する、あたらしい ofs の値。
取りだしに失敗したら負のエラーコードを返す。

  詳細説明 : vce_binary_push_nb_ia4 関数で pack したデータを取りだす。
データが足りない場合や、取りだすための配列が小さすぎるなどの場合は、
中途半端に取りだすことはせず、失敗をあらわす負のエラーコードを返す。
これは VCE のバイナリ操作のポリシーとなっている。
データはネットワークバイトオーダからネイティブのオーダーに戻して格納される。

  See also : <a href="#vce_binary_push_nb_ia4">vce_binary_push_nb_ia4</a>
<a name="vce_binary_pop_nb_ia8"></a>
- <B>vce_binary_pop_nb_ia8</B>

  概要 : バッファから8バイト整数(int) の配列を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_ia8( char *src, int len, int ofs, VCEI64 *out, int *outlen )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだす場所のバッファ先頭からのオフセット

  - arg 4 : ```VCEI64 *out```
    取りだしたデータを格納する int 型の配列の先頭アドレス

  - arg 5 : ```int *outlen```
    値結果引数。値として、 out 引数で指定する配列の要素数を受けとり、
結果として、実際に埋めた要素数を返す。

  返り値 : 配列を取りだすことによって移動する、あたらしい ofs の値。
取りだしに失敗したら負のエラーコードを返す。

  詳細説明 : vce_binary_push_nb_ia8 関数で pack したデータを取りだす。
データが足りない場合や、取りだすための配列が小さすぎるなどの場合は、
中途半端に取りだすことはせず、失敗をあらわす負のエラーコードを返す。
これは VCE のバイナリ操作のポリシーとなっている。
データはネットワークバイトオーダからネイティブのオーダーに戻して格納される。

  See also : <a href="#vce_binary_push_nb_ia8">vce_binary_push_nb_ia8</a>
<a name="vce_binary_pop_nb_stra"></a>
- <B>vce_binary_pop_nb_stra</B>

  概要 : バッファから文字列の配列を取りだす

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_pop_nb_stra( char *src, int len, int ofs, char **out, int *strnum, int eachmax )``` 

  - arg 1 : ```char *in```
    データを取りだすバッファの先頭アドレス

  - arg 2 : ```int len```
    データを取りだすバッファの長さ

  - arg 3 : ```int ofs```
    実際にデータを取りだす場所のバッファ先頭からのオフセット

  - arg 4 : ```char **out```
    取りだした文字列を格納するための、文字列へのポインタの配列の先頭アドレス

  - arg 5 : ```int *strnum```
    値結果引数。値として、 out 引数で指定する配列の要素数を受けとり、
結果として、実際に埋めた要素数を返す。

  - arg 6 : ```int eachmax```
    結果として出力する各C言語文字列の最大の長さを指定する。

  返り値 : 配列を取りだすことによって移動する、あたらしい ofs の値。
取りだしに失敗したら負のエラーコードを返す。

  詳細説明 : vce_binary_push_nb_stra 関数で pack したデータを取りだす。
データが足りない場合や、取りだすための配列が小さすぎるなどの場合は、
中途半端に取りだすことはせず、失敗をあらわす負のエラーコードを返す。
これは VCE のバイナリ操作のポリシーとなっている。
文字列は out 引数で指定される文字列配列にコピーされるため、
本関数を使用するアプリケーションによってコピー用のメモリ領域が
確保されている必要がある(サンプルコードを参照)。

  使用例 :   char *orig_data[] = { "foo", "bar" };
  char packed[1000];
  char buf[3][100];
  char *out[3] = { buf[0] , buf[1], buf[2] }; // for を使ってもよい
  int new_ofs,strnum,packed_len;
  packed_len = vce_binary_push_nb_stra( packed, sizeof(packed), 0, orig_data, 3, 100 );
  strnum = 3;
  new_ofs = vce_binary_pop_nb_stra( packed, packed_len, 0, out,&strnum, 100 );

  See also : <a href="#vce_binary_push_nb_stra">vce_binary_push_nb_stra</a>
<a name="vce_binary_push_nb_i1"></a>
- <B>vce_binary_push_nb_i1</B>

  概要 : 1バイト整数(char) をバッファにpushする

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_i1( char *out, int ofs, int maxlen, char c )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```char c```
    出力する元データ

  返り値 : 1バイト push することによって ofs が移動するので、
あたらしい ofs の値を返す。 この関数の場合は常に ofs + 1 である。
push できなかったときは、負のエラーコードを返す。

  詳細説明 : バイナリプロトコルを定義するときに使用されるバイナリ packer
用関数群のひとつ。gen.rb によって使用される。
対応する vce_binary_pop_nb_i1 関数で取りだすことができる。

  See also : <a href="#vce_binary_pop_nb_i1">vce_binary_pop_nb_i1</a>
<a name="vce_binary_push_nb_i2"></a>
- <B>vce_binary_push_nb_i2</B>

  概要 : 2バイト整数(short) をバッファにpushする

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_i2( char *out, int ofs, int maxlen, short s )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```short s```
    出力する元データ

  返り値 : 2バイト push することによって ofs が移動するので、
あたらしい ofs の値を返す。 この関数の場合は常に ofs + 2 である。
push できなかったときは、負のエラーコードを返す。

  詳細説明 : VCE のバイナリ packer のポリシー上、
2バイト以上のデータをバッファに push するときは、
絶対にデータを壊すことはしない。確実に全部のデータを push するか、
完全に失敗するかどちらかである。
対応する vce_binary_pop_nb_i2 関数で取りだすことができる。
データは、ネットワークバイトオーダで出力される。

  See also : <a href="#vce_binary_pop_nb_i2">vce_binary_pop_nb_i2</a>
<a name="vce_binary_push_nb_i4"></a>
- <B>vce_binary_push_nb_i4</B>

  概要 : 4バイト整数(int) をバッファにpushする

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_i4( char *out, int ofs, int maxlen, int i )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```int i```
    出力する元データ

  返り値 : 4バイト push することによって ofs が移動するので、
あたらしい ofs の値を返す。 この関数の場合は常に ofs + 4 である。
push できなかったときは、負のエラーコードを返す。

  詳細説明 : VCE のバイナリ packer のポリシー上、
4バイト以上のデータをバッファに push するときは、
絶対にデータを壊すことはしない。確実に全部のデータを push するか、
完全に失敗するかどちらかである。
対応する vce_binary_pop_nb_i4 関数で取りだすことができる。
データは、ネットワークバイトオーダで出力される。

  See also : <a href="#vce_binary_pop_nb_i4">vce_binary_pop_nb_i4</a>
<a name="vce_binary_push_nb_i8"></a>
- <B>vce_binary_push_nb_i8</B>

  概要 : 8バイト整数(VCEI64) をバッファにpushする

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_i8( char *out, int ofs, int maxlen, VCEI64 i )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```VCEI64 i```
    出力する元データ

  返り値 : 8バイト push することによって ofs が移動するので、
あたらしい ofs の値を返す。 この関数の場合は常に ofs + 8 である。
push できなかったときは、負のエラーコードを返す。

  詳細説明 : VCE のバイナリ packer のポリシー上、
8バイト以上のデータをバッファに push するときは、
絶対にデータを壊すことはしない。確実に全部のデータを push するか、
完全に失敗するかどちらかである。
対応する vce_binary_pop_nb_i8 関数で取りだすことができる。
データは、ネットワークバイトオーダで出力される。

  See also : <a href="#vce_binary_pop_nb_i8">vce_binary_pop_nb_i8</a>
<a name="vce_binary_push_nb_ia1"></a>
- <B>vce_binary_push_nb_ia1</B>

  概要 : 1バイト整数(char)の配列をバッファに push する

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_ia1( char *out, int ofs, int maxlen, char *ia, int num )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```char *ia```
    出力する1バイト整数(char)の配列の先頭アドレス

  - arg 5 : ```int num```
    出力する配列の要素数

  返り値 : 出力することによって移動した、あたらしいオフセットを返す。
出力に失敗した場合は負のエラーコードを返す。

  詳細説明 : char型の配列の中身を出力バッファに push する。
対応する vce_binary_pop_nb_ia1 関数で取りだすことができる。
出力バッファの長さが足りない場合は、データを壊さず、
負のエラーコード(VCE_EFULL)を返す。

  See also : <a href="#vce_binary_pop_nb_ia1">vce_binary_pop_nb_ia1</a>
<a name="vce_binary_push_nb_ia2"></a>
- <B>vce_binary_push_nb_ia2</B>

  概要 : 2バイト整数(short)の配列をバッファに push する

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_ia2( char *out, int ofs, int maxlen, short *ia, int num )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```short *ia```
    出力する2バイト整数(short)の配列の先頭アドレス

  - arg 5 : ```int num```
    出力する配列の要素数

  返り値 : 出力することによって移動した、あたらしいオフセットを返す。
出力に失敗した場合は負のエラーコードを返す。

  詳細説明 : short型の配列の中身を出力バッファに push する。
対応する vce_binary_pop_nb_ia2 関数で取りだすことができる。
データはすべてネットワークバイトオーダで保存される。
出力バッファの長さが足りない場合は、データを壊さず、
負のエラーコード(VCE_EFULL)を返す。

  See also : <a href="#vce_binary_pop_nb_ia2">vce_binary_pop_nb_ia2</a>
<a name="vce_binary_push_nb_ia4"></a>
- <B>vce_binary_push_nb_ia4</B>

  概要 : 4バイト整数(int)の配列をバッファに push する

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_ia4( char *out, int ofs, int maxlen, int *ia, int num )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```int *ia```
    出力する4バイト整数(int)の配列の先頭アドレス

  - arg 5 : ```int num```
    出力する配列の要素数

  返り値 : 出力することによって移動した、あたらしいオフセットを返す。
出力に失敗した場合は負のエラーコードを返す。

  詳細説明 : int型の配列の中身を出力バッファに push する。
対応する vce_binary_pop_nb_ia4 関数で取りだすことができる。
データはすべてネットワークバイトオーダで保存される。
出力バッファの長さが足りない場合は、データを壊さず、
負のエラーコード(VCE_EFULL)を返す。

  See also : <a href="#vce_binary_pop_nb_ia4">vce_binary_pop_nb_ia4</a>
<a name="vce_binary_push_nb_ia8"></a>
- <B>vce_binary_push_nb_ia8</B>

  概要 : 8バイト整数(VCEI64)の配列をバッファに push する

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_ia8( char *out, int ofs, int maxlen, VCEI64 *ia, int num )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```VCEI64 *ia```
    出力する8バイト整数(int)の配列の先頭アドレス

  - arg 5 : ```int num```
    出力する配列の要素数

  返り値 : 出力することによって移動した、あたらしいオフセットを返す。
出力に失敗した場合は負のエラーコードを返す。

  詳細説明 : int型の配列の中身を出力バッファに push する。
対応する vce_binary_pop_nb_ia8 関数で取りだすことができる。
データはすべてネットワークバイトオーダで保存される。
出力バッファの長さが足りない場合は、データを壊さず、
負のエラーコード(VCE_EFULL)を返す。

  See also : <a href="#vce_binary_pop_nb_ia8">vce_binary_pop_nb_ia8</a>
<a name="vce_binary_push_nb_stra"></a>
- <B>vce_binary_push_nb_stra</B>

  概要 : ヌル終端された文字列の配列をバッファに push する

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_push_nb_stra( char *out, int ofs, int maxlen, char **stra, int num, int eachmax )``` 

  - arg 1 : ```char *out```
    出力バッファの先頭アドレス

  - arg 2 : ```int ofs```
    実際に出力する場所の、バッファの先頭からのオフセット

  - arg 3 : ```int maxlen```
    出力バッファの長さ

  - arg 4 : ```char **stra```
    出力する元になる文字列へのポインタの配列。

  - arg 5 : ```int num```
    stra 引数で与える文字列へのポインタの配列の要素数。

  - arg 6 : ```int eachmax```
    stra 引数で与える各文字列の最大長さ。
文字列が一つでもこの長さに達するとエラーとなる。

  返り値 : 出力することによって移動した ofs の新しい値。
バッファが一杯になったり、その他の理由で push に失敗した場合は
負のエラーコードを返す。

  詳細説明 : 文字列をバイナリデータに pack し、バッファに追加する。
各文字列の最大文字数制限を可能にするために、
eachmax という引数が追加されている。
num が 0 のときは、 stra には NULL を指定することができる。

  See also : <a href="#vce_binary_pop_nb_stra">vce_binary_pop_nb_stra</a>
<a name="vce_binary_unpack"></a>
- <B>vce_binary_unpack</B>

  概要 : バッファのバイナリデータをunpackして構造体の配列にする(古い)

  カテゴリ : bin

  関数プロトタイプ : ```int vce_binary_unpack( struct bin_info *bi, int bn, char *inp, int len )``` 

  - arg 1 : ```struct bin_info *bi```
    bin_info構造体の配列の先頭アドレス

  - arg 2 : ```int bn```
    bin_info構造体の配列の要素数

  - arg 3 : ```char *inp```
    入力バッファの先頭アドレス

  - arg 4 : ```int len```
    入力バッファの長さ(バイト数)

  返り値 : 成功したら実際にunpackした長さを返す。これは lenより小さい可能性がある。
lenより大きいことはない。データが足りない場合は、
VCE_EDATASHORTを返す。

  詳細説明 : バイナリデータを、 bin_info 構造体の配列に指定されている通りに
unpackし、構造を持った状態に戻す。
主にプロトコル処理で使われる。

  知られているバグやTODO : 現在は バイナリpush/pop 関数群によって，置きかえられている．

  See also : <a href="#vce_binary_pack">vce_binary_pack</a>
<a name="vce_conn_break_heartbeat"></a>
- <B>vce_conn_break_heartbeat</B>

  概要 : コールバック関数内から、connのプロトコル処理を中止させる

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_break_heartbeat()``` 

  返り値 : 
  詳細説明 : conn_parserコールバック関数内で、この関数を呼ぶことでそのheartbeat内でのそのconnの
プロトコル処理を中止する。
同一heartbeat内で後続のパケットを処理したくない場合に使用する。たとえばマップの
切り替えの際にいったんプロトコルの処理を停止して、フェードアウト、マップの読み込み、
フェードインを行いたいときなどに利用する。
<BR>
これは、VCE-0.4.99以前のVCEでコールバック関数で０を返す場合に相当する。
現在、その仕様は変更されたため、このAPIが追加された。
<BR>
コールバック関数外でこの関数を呼んでも、全く無意味である。

  See also : <a href="#vce_tcpcontext_set_conn_call_parser_per_heartbeat">vce_tcpcontext_set_conn_call_parser_per_heartbeat</a>
<a name="vce_conn_clear"></a>
- <B>vce_conn_clear</B>

  概要 : conn_t型のインスタンスを初期化する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_clear( conn_t *c )``` 

  - arg 1 : ```conn_t *c```
    初期化するconn_tへのポインタ

  返り値 : なし

  詳細説明 : 初期化済みな conn_t を正式に作る唯一の方法である。 memset でゼロクリア
しても、正式な方法ではない。


<a name="vce_conn_close"></a>
- <B>vce_conn_close</B>

  概要 : TCPコネクションを閉じて解放する。

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_close( conn_t ct )``` 

  - arg 1 : ```conn_t ct```
    閉じたいコネクションの conn_t

  返り値 : なし

  詳細説明 : TCPコネクションを閉じる。実際には、次のheartbeatで close 処理をするための
フラグを立てるだけである。常に成功するが、すでに close フラグが立っている
コネクションに対して本関数を呼びだした場合は、 verbose モードでは
warning が出る。
このように vce_heartbeat を呼びださない限り、
実際にコネクションは閉じられないので注意が必要である。
VCEライブラリによってcloseされたコネクションは、アプリケーションが次に
write しようとしたときにエラーとして検出される。<BR>
また、資源を解放する前に、vce_tcpcontext_create時に指定している
closewatcherが呼びだされる。
Tips として， vce_conn_close した直後にタイムアウト値を通常よりも短く
設定しなおすことで，迅速な close 処理を期待できる．
そうしない場合，もしコネクションにデータが残っていたら，
デフォルトのタイムアウト時間を過ぎるまで，ずっとコネクションが残った
ままになるからである(サンプルコードを参照)．
引数が異常だった場合は VCE_EINVAL,
すでに閇じられているのに，さらに閇じようとした場合は VCE_EALREADY が，
vce_get_last_error で返される．

  使用例 : // クローズ後，短いタイムアウト値を設定
vce_conn_close( co );
vce_conn_set_timeout( co, 0 );

  See also : <a href="# vce_tcpcontext_connect"> vce_tcpcontext_connect</a><a href="# vce_tcpcontext_create"> vce_tcpcontext_create</a><a href="#vce_conn_writable">vce_conn_writable</a>
<a name="vce_conn_close_tcpcontext_all"></a>
- <B>vce_conn_close_tcpcontext_all</B>

  概要 : あるtcpが管理しているすべてのコネクションを切断する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_close_tcpcontext_all( tcpcontext_t tp )``` 

  - arg 1 : ```tcpcontext_t tp```
    切断対象となるコネクションを管理している tcpcontext_t

  返り値 : なし

  詳細説明 : すべてのコネクションを切断する。 closewatcher、 fainalizer は呼びだされる。
切断は「切断フラグ」を立てて次以降の vce_heartbeat を使って
実際の入出力をするため、本関数を呼びだした後は vce_heartbeat の呼びだしが
かならず必要である。
ゲームのサーバなどでは、サーバを正常に終了させるときには、
まず本関数の前に、全部のクライアントに対して shutdown の旨を伝え、
vce_tcpcontext_enable_accept 関数で新規の accept をブロックし、
そのあとこの関数を呼びだしてコネクションを閉じるという段階を
経るのが理想的である。
なお、本関数はサーバでもクライアントでも同様に動作する。
verbose モードのときは1本コネクションを切るごとにログを出力する(verbose).

  See also : <a href="#vce_tcpcontext_enable_accept">vce_tcpcontext_enable_accept</a>
<a name="vce_conn_get_buffer"></a>
- <B>vce_conn_get_buffer</B>

  概要 : conn_t の受信/送信バッファを得る

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_get_buffer( conn_t c, char **rb, int  *rblen, char **wb, int *wblen )``` 

  - arg 1 : ```conn_t c```
    バッファを取りだしたい conn_t

  - arg 2 : ```char **rb```
    読みこみバッファの先頭アドレスを格納したいポインタへのポインタ。
読みこみバッファの先頭アドレスを返す

  - arg 3 : ```int *rblen```
    読みこみバッファの長さを格納したい int 型の変数へのポインタ。
読みこみバッファの使用中の長さを返す。それは0以上の値を取る。

  - arg 4 : ```char **wb```
    書きこみバッファの先頭アドレスを格納したいポインタへのポインタ。
書きこみバッファの先頭アドレスを返す

  - arg 5 : ```int *wblen```
    書きこみバッファの長さを格納したい int 型の変数へのポインタ。
書きこみバッファの使用中の長さを返す。それは0以上の値を取る。

  返り値 : なし

  詳細説明 : オリジナルのプロトコルパーサを定義したいアプリケーションは
この関数を使って読みこみバッファを直接参照し、
独自の動作を定義することができる。
このようにして作った独自のプロトコルパーサは、
vce_tcpcontext_set_conn_parser 関数等をもちいて登録することができる。

  See also : <a href="#vce_conn_shrink_readbuf">vce_conn_shrink_readbuf</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_conn_get_index"></a>
- <B>vce_conn_get_index</B>

  概要 : TCPコネクション(conn_t)のVCE内でのindexを求める

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_conn_get_index( conn_t c );``` 

  - arg 1 : ```conn_t c```
    インデックス値を求めたいコネクション

  返り値 : インデックス値。エラーの場合は負のエラーコードを返す

  詳細説明 : conn_t 構造体はVCE内部で1次元配列として管理されているので、
その配列へのインデックスはconn_tを指定するために一意なものとして利用できる。
したがって、「セッションID」のような用途に使える。

  See also : <a href="#vce_conn_get_struct_from_index">vce_conn_get_struct_from_index</a>
<a name="vce_conn_get_local_addr_string"></a>
- <B>vce_conn_get_local_addr_string</B>

  概要 : TCPコネクションのローカルアドレスとポートを文字列で得る

  カテゴリ : tcp

  関数プロトタイプ : ```char * vce_conn_get_local_addr_string( conn_t ct, char *s, int max )``` 

  - arg 1 : ```conn_t ct```
    アドレスを取得したいコネクション

  - arg 2 : ```char *s```
    結果文字列を格納するためのバッファ

  - arg 3 : ```int max```
    バッファのサイズ

  返り値 : ワーク領域(引数 s)をそのまま返す

  詳細説明 : conn_t のローカルアドレスを文字列で取得する。取得できる
アドレスのフォーマットは、
vce_conn_get_remote_addr_string 関数と同じである。

  See also : <a href="#vce_conn_get_remote_addr_string">vce_conn_get_remote_addr_string</a>
<a name="vce_conn_get_local_ipv4_addr"></a>
- <B>vce_conn_get_local_ipv4_addr</B>

  概要 : TCPコネクションのローカルIPv4アドレス(32bit)を得る

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_get_local_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p )``` 

  - arg 1 : ```conn_t ct```
    処理対象となるコネクション

  - arg 2 : ```unsigned int *a```
    32ビットのIPv4アドレス(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。

  - arg 3 : ```unsigned short *p```
    ポート番号(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。

  返り値 : なし

  詳細説明 : 出力はネットワークバイトオーダとなっているので、
必要に応じて、 ntohs, ntohl, などを使用して変換すること。

  See also : <a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a>
<a name="vce_conn_get_local_ipv4_addr_string"></a>
- <B>vce_conn_get_local_ipv4_addr_string</B>

  概要 : TCPコネクションのローカルIPv4アドレスとポートを文字列で得る

  カテゴリ : tcp

  関数プロトタイプ : ```char * vce_conn_get_local_ipv4_addr_string( conn_t ct, char *s, int max )``` 

  - arg 1 : ```conn_t ct```
    処理対象となるコネクション

  - arg 2 : ```char *s```
    出力先文字列の先頭アドレス

  - arg 3 : ```int max```
    出力先文字列の最大長さ

  返り値 : s のアドレスをそのまま返す

  詳細説明 : 本関数は IPv4 専用で、ソケットのこちら側の端点のアドレスを求める。
こちら側とは、本関数を呼びだしたプログラムが動作している側の端点である。
本関数は IPv4 専用なので、プロトコル独立をめざすために、本関数ではなく
vce_conn_get_local_addr_string 関数を使うことを推奨する。

  See also : <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a>
<a name="vce_conn_get_local_ipv6_addr"></a>
- <B>vce_conn_get_local_ipv6_addr</B>

  概要 : TCPコネクションのローカルIPv6アドレス(128bit)を得る

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_get_local_ipv6_addr( conn_t ct, char *a, unsigned short *p )``` 

  - arg 1 : ```conn_t ct```
    処理対象となるコネクション

  - arg 2 : ```char *a```
    128ビットのIPv6アドレス(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。
アドレスはネットワークバイトオーダで16バイトが、
そのままバッファに格納される。したがってこのバッファには16バイト以上の
メモリ領域を指定する必要がある。

  - arg 3 : ```unsigned short *p```
    ポート番号(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。

  返り値 : なし

  詳細説明 : vce_conn_get_remote_ipv4_addr 関数の IPv6版．

  See also : <a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a><a href="#vce_conn_get_remote_ipv6_addr">vce_conn_get_remote_ipv6_addr</a>
<a name="vce_conn_get_local_ipv6_addr_string"></a>
- <B>vce_conn_get_local_ipv6_addr_string</B>

  概要 : TCPコネクションのローカルIPv6アドレスとポートを文字列で得る

  カテゴリ : tcp

  関数プロトタイプ : ```char *vce_conn_get_local_ipv6_addr_string( conn_t ct, char *s, int max )``` 

  - arg 1 : ```conn_t ct```
    処理対象となる conn_t

  - arg 2 : ```char *s```
    出力先文字列の先頭アドレス

  - arg 3 : ```int max```
    出力先文字列の最大長さ

  返り値 : s のアドレスをそのまま返す, エラーの場合は  NULL を返す

  詳細説明 : TCP ソケットのローカルアドレスを文字列で得る。文字列の形式は、
vce_conn_get_remote_addr_string 関数と同じ。
この関数は  IPv6 専用でプロトコル独立でないため、
vce_conn_get_local_addr_string 関数の使用を推奨する。

  See also : <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a>
<a name="vce_conn_get_remote_addr_string"></a>
- <B>vce_conn_get_remote_addr_string</B>

  概要 : TCPコネクションのリモートピアのアドレスとポートを文字列で得る

  カテゴリ : tcp

  関数プロトタイプ : ```char *vce_conn_get_remote_addr_string( conn_t ct, char *s, int max )``` 

  - arg 1 : ```conn_t ct```
    アドレスを取得したいコネクション

  - arg 2 : ```char *s```
    結果文字列を格納するためのバッファ

  - arg 3 : ```int max```
    バッファのサイズ

  返り値 : ワーク領域(引数 s)をそのまま返す

  詳細説明 : プロトコル独立なアプリケーションにおいて、 conn_t のリモートピアのアドレスを
文字列で取得する。現在 VCE は ipv4 と ipv6 に対応しているが、
名前を逆引きせずに、 ipv4 では"192.168.0.11234" 、
ipv6 では "fe802d0b7fffec6f4cd.5678" といった感じで返す。
ipv4 では最後のポート番号を示すトークンが "" で区切られているのに対し、
ipv6 では "." で区切られていることに注意。
返された文字列がどのプロトコルのものかを判定する処理はアプリケーションに
任されている。

  See also : <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a><a href="#vce_conn_get_remote_ipv4_addr_string">vce_conn_get_remote_ipv4_addr_string</a>
<a name="vce_conn_get_remote_ipv4_addr"></a>
- <B>vce_conn_get_remote_ipv4_addr</B>

  概要 : TCPコネクションのリモートピアのIPv4アドレス(32bit)を得る

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_get_remote_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p )``` 

  - arg 1 : ```conn_t ct```
    処理対象となるコネクション

  - arg 2 : ```unsigned int *a```
    32ビットのIPv4アドレス(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。

  - arg 3 : ```unsigned short *p```
    ポート番号(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。

  返り値 : なし

  詳細説明 : 出力はネットワークバイトオーダとなっているので、
必要に応じて、 ntohs, ntohl, などを使用して変換すること。


<a name="vce_conn_get_remote_ipv4_addr_string"></a>
- <B>vce_conn_get_remote_ipv4_addr_string</B>

  概要 : TCPコネクションのリモートピアのIPv4アドレスとポートを文字列で得る

  カテゴリ : tcp

  関数プロトタイプ : ```char *vce_conn_get_remote_ipv4_addr_string( conn_t ct, char *s, int max )``` 

  - arg 1 : ```conn_t ct```
    処理対象となるコネクション

  - arg 2 : ```char *s```
    出力先文字列の先頭アドレス

  - arg 3 : ```int max```
    出力先文字列の最大長さ

  返り値 : s のアドレスをそのまま返す

  詳細説明 : IPアドレスをログ出力用などで、文字列に変換したい時が多いが、
この関数を使うと簡単に文字列を得ることができる。
この関数は IPv4 専用であるため IPv6 コネクションには対応していない。
プロトコル独立をめざすアプリケーションでは、
vce_conn_get_remote_addr 関数を用る。

  See also : <a href="#vce_conn_get_remote_addr">vce_conn_get_remote_addr</a><a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a>
<a name="vce_conn_get_remote_ipv6_addr"></a>
- <B>vce_conn_get_remote_ipv6_addr</B>

  概要 : TCPコネクションのリモートピアのIPv6アドレス(128bit)を得る

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_get_remote_ipv6_addr( conn_t ct, char *a, unsigned short *p )``` 

  - arg 1 : ```conn_t ct```
    処理対象となるコネクション

  - arg 2 : ```char *a```
    128ビットのIPv6アドレス(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。
アドレスはネットワークバイトオーダで16バイトが、
そのままバッファに格納される。したがってこのバッファには16バイト以上の
メモリ領域を指定する必要がある。

  - arg 3 : ```unsigned short *p```
    ポート番号(ネットワークバイトオーダ)
を返すためのポインタ。NULLを指定すると出力しない。

  返り値 : なし

  詳細説明 : 出力はネットワークバイトオーダとなっているので、
必要に応じて、 ntohs, ntohl, などを使用して変換すること。

  See also : <a href="#vce_conn_get_local_ipv6_addr">vce_conn_get_local_ipv6_addr</a>
<a name="vce_conn_get_remote_ipv6_addr_string"></a>
- <B>vce_conn_get_remote_ipv6_addr_string</B>

  概要 : TCPコネクションのリモートピアのIPv6アドレスとポートを文字列で得る

  カテゴリ : tcp

  関数プロトタイプ : ```char *vce_conn_get_remote_ipv6_addr_string( conn_t ct, char *s, int max )``` 

  - arg 1 : ```conn_t ct```
    処理対象となるコネクション

  - arg 2 : ```char *s```
    出力先文字列の先頭アドレス

  - arg 3 : ```int max```
    出力先文字列の最大長さ

  返り値 : s のアドレスをそのまま返す、エラーの場合は  NULL を返す

  詳細説明 : vce_conn_get_remote_ipv4_addr_string 関数の IPv6版．

  See also : <a href="#vce_conn_get_remote_addr">vce_conn_get_remote_addr</a><a href="#vce_conn_get_remote_ipv4_addr_string">vce_conn_get_remote_ipv4_addr_string</a><a href="#vce_conn_get_remote_ipv6_addr">vce_conn_get_remote_ipv6_addr</a>
<a name="vce_conn_get_stat"></a>
- <B>vce_conn_get_stat</B>

  概要 : conn_t の統計情報を取得する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_get_stat( conn_t ct, conn_stat_t *st )``` 

  - arg 1 : ```conn_t ct```
    情報を取得する対象となるコネクション(conn_t)

  - arg 2 : ```conn_stat_t *st```
    情報を取りだすために専用に用意されている conn_stat_t 型のインスタンスの
先頭アドレス

  返り値 : なし

  詳細説明 : TCPコネクションから統計情報を取りだす。
取りだすために conn_stat_t 構造体が定義されている。
以下はその構造体のメンバの説明である。
<ul>
<LI>recv_byte<BR>
そのコネクションで受信した総バイト数。
<LI>send_byte<BR>
そのコネクションで送信した総バイト数。
<LI>conn_write<BR>
そのコネクションに対して vce_conn_write した回数
<LI>recv_syscall, send_syscall<BR>
そのコネクションに対してrecv() システムコールを呼びだした回数と、
send_syscall を呼びだした回数。
</ul>

  See also : <a href="#vce_conn_is_valid">vce_conn_is_valid</a><a href="#vce_get_stat">vce_get_stat</a><a href="#vce_tcpcontext_get_stat">vce_tcpcontext_get_stat</a>
<a name="vce_conn_get_state_buffer"></a>
- <B>vce_conn_get_state_buffer</B>

  概要 : conn_tの状態管理バッファへのポインタを返す

  カテゴリ : tcp

  関数プロトタイプ : ```void * vce_conn_get_state_buffer( conn_t c, int *len );``` 

  - arg 1 : ```conn_t c```
    状態を取りだしたいコネクション

  - arg 2 : ```int *len```
    状態バッファの長さを返す。
NULL を指定すると何もしない

  返り値 : 値へのポインタ。状態のないプロトコルの場合NULLが返る

  詳細説明 : 状態のあるプロトコルの管理用バッファを返す。
vce_tcpcontext_create の呼びだし時に状態のあるプロトコルを指定(statebuf_size)
していれば、そのサイズの領域をもつバッファへのポインタを返す。

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_conn_get_struct_from_index"></a>
- <B>vce_conn_get_struct_from_index</B>

  概要 : TCPコネクションのindex値からconn_t構造体を得る。

  カテゴリ : tcp

  関数プロトタイプ : ```conn_t vce_conn_get_struct_from_index( int index );``` 

  - arg 1 : ```int index```
    インデックス値。前もって vce_conn_get_index 関数で得たindexを
つかって構造体に戻す。

  返り値 : conn_t構造体そのもの。

  詳細説明 : 本関数は「セッションID」から構造体を取りだしたいときなどに使用する。

  See also : <a href="#vce_conn_get_index">vce_conn_get_index</a>
<a name="vce_conn_get_tcpcontext"></a>
- <B>vce_conn_get_tcpcontext</B>

  概要 : conn_t から、そのコネクションが属する tcpcontext を取りだす

  カテゴリ : tcp

  関数プロトタイプ : ```tcpcontext_t vce_conn_get_tcpcontext( conn_t c )``` 

  - arg 1 : ```conn_t c```
    取りだしの対象となる conn_t

  返り値 : conn_t が属する tcpcontext_t

  詳細説明 : リモートにconnectするときや、新しいTCPのコネクションを受けいれた場合、
VCE内に conn_t が初期化されるが、その conn_t は、
かならず tcpcontext に関連づけられている。
したがって conn_t から tcpcontext_t を取りだすことが可能である。
この関数は主に VCE 内部で使用され、アプリケーションから使われることは少ない。

  See also : <a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
<a name="vce_conn_is_equal"></a>
- <B>vce_conn_is_equal</B>

  概要 : ふたつのTCPコネクション(conn_t)が同じか調べる

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_conn_is_equal( conn_t c1 , conn_t c2 )``` 

  - arg 1 : ```conn_t c1```
    調べる対象となるコネクションその1

  - arg 2 : ```conn_t c2```
    調べる対象となるコネクションその2

  返り値 : 等しい場合は1、等しくない場合は0を返す。

  詳細説明 : ふたつのコネクションが等しいかどうか調べる。
この二つのconn_tを使った書きこみと読みこみは全く同じ結果になる。
具体的には同じポインタとシリアル番号を持っているコネクションとなる。


<a name="vce_conn_is_valid"></a>
- <B>vce_conn_is_valid</B>

  概要 : TCPコネクション(conn_t)が壊れているかどうか調べる。

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_conn_is_valid( conn_t c )``` 

  - arg 1 : ```conn_t c```
    調査対象の conn_t

  返り値 : 無効なインスタンスなら0，有効なら1を返す．

  詳細説明 : VCE を使うアプリケーションでは，通常，VCEが返す conn_t を別のメモリ領域
に記憶しておいて，後でその接続を呼びだすために使うことが多い．
しかし，その時点では，その conn_t が指している VCE 内のオブジェクトは，
すでに解放されて再利用されている可能性がある．
本関数は，conn_t 型の serial メンバを使って，
すでにその conn_t が再利用されて存在しなくなっているかどうかを調べる．
また，本関数は， vce_tcpcontext_connect の返り値が正しいかどうかを調べる
ためにも使われる．
アプリケーションがあるコネクションに対して，
まだ書きこみができるかどうかを随時調べたい場合には，
常に vce_conn_writable 関数を使って調べるべきである．
ブロッキングモードの vce_tcpcontext_connect関数で返された conn_t を
本関数でテストする場合の詳細については，
<a href="connect.html">クライアントからの接続</a>を参照．

  See also : <a href="#vce_conn_writable">vce_conn_writable</a><a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
<a name="vce_conn_set_delay"></a>
- <B>vce_conn_set_delay</B>

  概要 : クライアント、サーバー間の通信の遅延んをシミュレートsる。

  カテゴリ : core

  関数プロトタイプ : ```void vce_conn_set_delay(conn_t ct,int delay_min,int delay_max)``` 

  - arg 1 : ```conn_t ct```
    遅延を設定する対象のコネクション

  - arg 2 : ```int delay_min```
    遅延させる最低の時間。単位はミリ秒

  - arg 3 : ```int delay_max```
    遅延させる最大の時間。単位はミリ秒

  返り値 : なし

  詳細説明 : 受信（若しくは送信）するときにmin〜maxまでの間で平均的に遅れを発生させる。
クライアント回線のラグタイムをシミュレートするときに使う。
一度設定すると遅延時間をゼロに設定することはできなくなる。

  知られているバグやTODO : バッファサイズが通常の送受信バッファと同じサイズで受信したパケットに細かく
時間等ヘッダが付加されるの上に遅延されるのでバッファが詰まりやすい。


<a name="vce_conn_set_parser"></a>
- <B>vce_conn_set_parser</B>

  概要 : conn_t ごとに動的にプロトコルパーサを設定する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_set_parser( conn_t ct, int (*parser)(conn_t), int (*pcallback)(conn_t,char*,int))``` 

  - arg 1 : ```conn_t ct```
    設定したい conn_t

  - arg 2 : ```int (*parser)(conn_t)```
    パーサー関数． vce_protocol_parser_bin16 など．

  - arg 3 : ```int (*pcallback)(conn_t c,char *d, int l )```
    パーサによって呼びだされるコールバック関数

  返り値 : なし

  詳細説明 : プロトコル処理の都合上，
コネクションごとに動的にパーサを変更したいことがある．
本関数を使うと，コネクションごとに，動的にパーサとコールバックの両方を
変更することができる．
プロトコルのコールバック関数の処理の中で本関数を使って関数を変更した場合，
次のパーサ呼びだしから，
その変更が適用される．
本関数は，たとえばプロトコルをデバッグモードに切りかえるときや
管理用関数に切りかえたいときなどにも使用できる．

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_protocol_parser_text">vce_protocol_parser_text</a><a href="#vce_protocol_parser_through">vce_protocol_parser_through</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_conn_set_timeout"></a>
- <B>vce_conn_set_timeout</B>

  概要 : conn_t ごとにタイムアウト時間を設定変更する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_set_timeout( conn_t c, int sec )``` 

  - arg 1 : ```conn_t c```
    設定を変更したい conn_t

  - arg 2 : ```int sec```
    新しいタイムアウト値(秒)

  返り値 : なし

  詳細説明 : デフォルトでは，各コネクションのタイムアウト値は，
vce_tcpcontext_create 関数のタイムアウト設定に準じるが，
本関数を用いて，コネクションごとのタイムアウトを自在に調整できる．
アプリケーションの実行中に特にセキュリティを高めたい状況などに
本関数を使って調整をするとよいだろう．

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_conn_show_stat"></a>
- <B>vce_conn_show_stat</B>

  概要 : 使用中のすべてのコネクションの状態を表示する。

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_show_stat( void )``` 

  返り値 : なし

  詳細説明 : <pre>
"=== SHOW CONNECTION STATISTICS ===\n"
</pre>
ではじまる、コネクションの個数と同じ行数の統計情報を出力する。
以下は、表示される内容の説明である。
<ul>
<LI><B>A</B><BR>
コネクション構造体(conn_t)のアドレス
<LI><B>Enc</B><BR>
暗号化しているなら1、そうでないなら0
<LI><B>IP</B><BR>
IPアドレスポート番号。ポート番号は10進数である。
<LI><B>Lst</B><BR>
最後にアクセスした時刻(time_t、システムタイム)
<LI><B>I</B><BR>
VCEの管理index
<LI><B>Sv</b><BR>
サーバコネクションなら1、クライアントコネクションなら0
<LI><B>ER</B><BR>
暗号化前の読みこみバッファのアドレス
<LI><B>EW</B><BR>
暗号化後の書きこみバッファのアドレス
<LI><B>R</B><BR>
復号後の読みこみバッファのアドレス
<LI><B>W</B><BR>
暗号化前の書きこみバッファのアドレス
<LI><B>St</B><BR>
暗号ネゴシエーション状態。
</ul>
注意点としては，サイレントモードでコンパイルされているVCEライブラリ
では，本関数は何も出力せず，VCE_ESUPPORT をラストエラーに設定する．

  知られているバグやTODO : 本関数は、標準エラー出力を利用するため、
Win32GUI環境において標準エラー出力が使えない場合は本関数は使用できない。


<a name="vce_conn_shrink_readbuf"></a>
- <B>vce_conn_shrink_readbuf</B>

  概要 : conn_t の読みこみバッファを縮ませる

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_conn_shrink_readbuf( conn_t ct, int len )``` 

  - arg 1 : ```conn_t ct```
    縮ませる読みこみバッファをもつ conn_t

  - arg 2 : ```int len```
    縮ませるながさ

  返り値 : 縮ませることができた長さを返す。
通常はlenがそのまま返る。

  詳細説明 : オリジナルのプロトコルパーサを定義する場合、
読みこみバッファの内容を処理した後、
vce_conn_shrink_readbufを使って読みこみバッファの内容を削る必要がある。


<a name="vce_conn_userdata_get_pointer"></a>
- <B>vce_conn_userdata_get_pointer</B>

  概要 : conn_tに関連付けたポインタを取り出す

  カテゴリ : tcp

  関数プロトタイプ : ```void *vce_conn_userdata_set_pointer(conn_t ct);``` 

  - arg 1 : ```conn_t ct```
    対象のconn_t

  返り値 : 
  詳細説明 : 

<a name="vce_conn_userdata_set_pointer"></a>
- <B>vce_conn_userdata_set_pointer</B>

  概要 : conn_tにポインタを関連付ける

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_conn_userdata_set_pointer(conn_t ct,void *p);``` 

  - arg 1 : ```conn_t ct```
    対象のconn_t

  - arg 2 : ```void *p```
    ポインタ

  返り値 : 
  詳細説明 : conn_tにある値を付加したいときに使う


<a name="vce_conn_writable"></a>
- <B>vce_conn_writable</B>

  概要 : TCPコネクションに書きこみが可能かどうかを調べる

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_conn_writable( conn_t ct );``` 

  - arg 1 : ```conn_t ct```
    書きこみ可能かどうか調べる対象となるTCPコネクションをあらわす conn_t。
ノンブロッキングのconnectをvce_tcpcontext_create するときに指定している
場合は、コネクションが完成したかどうかも調べることができる。
この関数はサーバーにおいてもクライアントにおいても使えるが、
クライアントで使うことのほうがほとんどである。

  返り値 : ct が有効でない場合は VCE_EINVAL をかえす。
ct がVCEの内部で初期化されている場合(つまり、コネクションがアプリケーション
の知らないところで切れている場合)は VCE_ECONNSERIAL を返す。
ct は有効だが、書きこみバッファに空きがないか、暗号鍵のネゴシエーション中
の場合はゼロを返す。
書きこみ可能な場合はプラスの値を返す。値の意味は、書きこみ可能なバイト数
である。

  詳細説明 : アプリケーションプログラムにおいて
TCPコネクションに何かを書きこみたいときは、この関数をつかって
書きこみ可能かどうかを調べてから書きこむこと。

  使用例 : <pre>
  // ひたすらソケットに書きこみ続けるプログラム
  tcpcontext_t t = vce_tcpontext_create( 0, ... );
  conn_t new_con = vce_tcpcontext_connect( t, "localhost" , 80 );
  while (1 ){
      vce_heartbeat();
      if( vce_conn_writable( new_con ) >= 4 ){
          vce_conn_write( new_con, "test" , 4 );
      } else {
          // Aから一定時間たったら，失敗を通知
      }
  }
</pre>

  See also : <a href="#vce_conn_is_valid">vce_conn_is_valid</a><a href="#vce_conn_write">vce_conn_write</a><a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
<a name="vce_conn_write"></a>
- <B>vce_conn_write</B>

  概要 : TCPコネクションにデータを生で書きこむ。

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_conn_write( conn_t ct, char *b, size_t len );``` 

  - arg 1 : ```conn_t ct```
    書きこむ対象となる conn_t

  - arg 2 : ```char *b```
    書きこむデータ．

  - arg 3 : ```size_t len```
    書きこむデータの長さ．

  返り値 : 1以上： 書きこみが成功した。<BR>
0  バッファがいっぱいになってしまっている。<BR>

  詳細説明 : 生データを直接送信する。直接送信するといっても、VCEの内部的には、
一旦TCPコネクション(conn_t)の内部に確保されている書きこみバッファに
溜めてからフラッシュされる。したがって、一度に書きこめる量の最大は、
vce_tcpcontext_create するときの書きこみバッファの長さによって決まる。

また、 vce_conn_write が負を返したら、もうそのコネクションは使えないので、
すみやかに vce_conn_close するべきである。<BR><BR>
<B>0が返ってくるなど、全部書きこめなかった場合の処理</B><BR>
vce_conn_write が0を返す場合は、
何らかの事情でソケットにデータが書きこめない状況になっている。
これは通常はクライアント側がそれ以上読みこめないことを意味する。
アプリケーションの内容がJPEGファイルなど大きなデータをやりとりする場合は、
0を返してもvce_conn_close せずに処理を続けるべきだが、
ゲームの操作パケットなど小さいデータの場合は、
クライアントに問題が発生していると解釈して vce_conn_close したほうがよい。

  使用例 :   // ゲームなど小さいパケットばかりを使う場合の vce_conn_close の使いかた
  if( vce_writable( ct ) > 0 ){
      int writel = vce_conn_write( ct, "hoge", 4 );
      if( writel < 4 ){
          vce_conn_close(ct);
      }
  }

  See also : <a href="#vce_conn_close">vce_conn_close</a><a href="#vce_conn_writable">vce_conn_writable</a>
<a name="vce_conn_writed"></a>
- <B>vce_conn_writed</B>

  概要 : connに書き込まれたデータがTCPコネクションに書き出されているかを調べる

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_conn_writed( conn_t c )``` 

  - arg 1 : ```conn_t c```
    調査対象の conn_t

  返り値 : バッファが全て書き出されていれば1, まだ書き出されていなければ0を返す．

  詳細説明 : vce_conn_write()をされていても、まだTCPのコネクションにデータが書き出されている訳ではなく実際にはconnの持つバッファーに書き込まれている。
VCEでは、vce_heartbeatを呼び出すことによって可能な限りデータを書き込む。実際にconnに書き込まれたデータが送信されてるかしらべるには、vce_conn_writed()を使用する必要がある。
特に、connをcloseする直前にデータを書き込む場合、vce_conn_writed()で調べてからcloseしないと実際には送信されていない可能性がある。

  See also : <a href="#vce_conn_valid">vce_conn_valid</a>
<a name="vce_dump_buffer"></a>
- <B>vce_dump_buffer</B>

  概要 : バイナリ配列をvce_erroutを用いてダンプする。

  カテゴリ : util

  関数プロトタイプ : ```void vce_dump_buffer( char *buf, int len )``` 

  - arg 1 : ```char *buf```
    ダンプしたいデータの先頭アドレス

  - arg 2 : ```int len```
    ダンプしたいデータの長さ

  返り値 : なし

  詳細説明 : vce_errout 関数を用いて、バイナリデータを含む配列の内容をすべてログする。
8バイトごとに区切って表示する非常に単純なものである。

  See also : <a href="#vce_errout">vce_errout</a>
<a name="vce_end_all_array"></a>
- <B>vce_end_all_array</B>

  概要 : 全てのVCE配列を解放する

  カテゴリ : array

  関数プロトタイプ : ```void vce_end_all_array( void )``` 

  返り値 : なし

  詳細説明 : すべてのVCE配列に対して vce_end_array を呼びだす。

  See also : <a href="#vce_init_array">vce_init_array</a>
<a name="vce_end_array"></a>
- <B>vce_end_array</B>

  概要 : VCE配列を解放する。

  カテゴリ : array

  関数プロトタイプ : ```int vce_end_array( int index )``` 

  - arg 1 : ```int index```
    配列を特定する配列デスクリプタ。
vce_init_array の返り値である。

  返り値 : 成功の場合は0、エラーだったら負のエラーコードを返す(vce.h)

  詳細説明 : 配列の要素ではなく、配列自体を解放することに注意。
また，すべて配列の要素は解放される．
vce_end_array を呼びだした後は、
その配列に関してはすべての操作が不可能となる。
vce_end_array 関数は内部で FREE 関数を呼びだしているので、
FREE 関数の呼びだし状況がログ出力される。

  See also : <a href="#FREE">FREE</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_errout"></a>
- <B>vce_errout</B>

  概要 : VCEのログ出力をする

  カテゴリ : core

  関数プロトタイプ : ```int vce_errout( const char *format, ... )``` 

  - arg 1 : ```char *format```
    フォーマット文字列。 printf のものと同じ

  - arg 2 : ```...```
    0個以上の引数列。 printf のものと同じ

  返り値 : なし

  詳細説明 : 文字列を標準エラー出力に表示する。ただし、
vce_errout_config 関数によってログ出力ディレクトリが指定されている場合は、
そのディレクトリにも出力し、そのログは自動的に rotate される。
標準エラー出力がない環境では，標準出力に出力される．

  See also : <a href="# vce_errout_set_another"> vce_errout_set_another</a><a href="# vce_verrout"> vce_verrout</a><a href="#vce_errout_config">vce_errout_config</a><a href="#vce_errout_v">vce_errout_v</a>
<a name="vce_extract_data_from_hex_text"></a>
- <B>vce_extract_data_from_hex_text</B>

  概要 : hextext 形式のASCIIテキストを、バイナリデータ配列に戻す

  カテゴリ : util

  関数プロトタイプ : ```int vce_extract_data_from_hex_text( const char *buf, int len, char *out, int outlen )``` 

  - arg 1 : ```char *buf```
    入力となるASCIIテキストの先頭アドレス

  - arg 2 : ```int len```
    入力テキストの長さ(バイト数)

  - arg 3 : ```char *out```
    出力バイナリ配列の先頭アドレス

  - arg 4 : ```int outlen```
    出力する最大のバイト数

  返り値 : テキストの中身が正当でない場合は VCE_EFORMAT を、
それ以外の何らかのエラー(バッファが足りないなど)の場合はそれに応じた
負のエラーコードを、完全に成功した場合は正の数(バイナリのバイト数)を返す。

  詳細説明 : hextext 形式のバッファを読みこみ、データの中身の正当性をチェックした上で、
バイナリ配列に読みこむ。

  See also : <a href="#vce_make_hex_text_from_buffer">vce_make_hex_text_from_buffer</a>
<a name="vce_finalize"></a>
- <B>vce_finalize</B>

  概要 : VCEの解放を行なう。

  カテゴリ : core

  関数プロトタイプ : ```int vce_finalize( void )``` 

  返り値 : 正常に終了できた場合は0、異常な場合は負のエラーコードを返す。

  詳細説明 : VCEが使用していたすべての資源を解放する。
vce_errout* を除いて，
この関数を呼びだした後のVCE関数の呼びだしはすべて未定義の動作となる。


<a name="vce_free_array_object"></a>
- <B>vce_free_array_object</B>

  概要 : VCE配列の要素を解放する

  カテゴリ : array

  関数プロトタイプ : ```int vce_free_array_object( int index , void *p )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  - arg 2 : ```void *p```
    解放したい配列の要素の先頭アドレス

  返り値 : 成功したら0、失敗したら負のエラーコードを返す

  詳細説明 : vce_free_array_object 関数は、 ARRAY_SCAN マクロ内で使用することができる。
この関数は，解放されるバッファの中身に対して何か書きこむことは一切しない．

  See also : <a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_free_array_object_all">vce_free_array_object_all</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_free_array_object_all"></a>
- <B>vce_free_array_object_all</B>

  概要 : 配列の全要素を解放する(配列自体は解放しない)

  カテゴリ : array

  関数プロトタイプ : ```void vce_free_array_object_all( int index )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  返り値 : なし

  詳細説明 : 1つの配列の中で使用中になっているすべての要素を解放する。

  知られているバグやTODO : 現在は1個1個解放しているため比較的遅い。
全体を一気に初期化することによって高速化する予定である(バージョン1以降)。

  See also : <a href="#vce_free_array_object">vce_free_array_object</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_maxnum"></a>
- <B>vce_get_array_maxnum</B>

  概要 : 配列の最大要素数を返す

  カテゴリ : array

  関数プロトタイプ : ```int vce_get_array_maxnum( int index )``` 

  - arg 1 : ```int index```
    情報を取得したい配列のindex

  返り値 : 配列のメンバの最大数．

  詳細説明 : 
  See also : <a href="#vce_get_array_member_size">vce_get_array_member_size</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_member_size"></a>
- <B>vce_get_array_member_size</B>

  概要 : 配列の各メンバのサイズを返す

  カテゴリ : array

  関数プロトタイプ : ```int vce_get_array_member_size( int index )``` 

  - arg 1 : ```int index```
    情報を取得したい配列の index

  返り値 : 配列のメンバのサイズ(vce_init_array の第一引数の値)．
引数が異常の場合は負のエラーコードを返す．

  詳細説明 : VCE の配列管理ルーチンが管理している配列のメンバのサイズを得る
vce_init_array の size 引数の値．

  See also : <a href="#vce_get_array_maxnum">vce_get_array_maxnum</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_object_index"></a>
- <B>vce_get_array_object_index</B>

  概要 : VCE配列要素が配列の何番目に位置しているかを得る

  カテゴリ : array

  関数プロトタイプ : ```int vce_get_array_object_index( int index , void *p )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  - arg 2 : ```void *p```
    インデックスを得たい要素の先頭アドレス

  返り値 : 引数が不正な場合はVCE_EINVALを、ポインタが適切な値でない場合は
VCE_EALIGNMENT を返す。
正常終了の場合は、0以上のインデックスを返す

  詳細説明 : vce_get_array_object_index 関数は、指定されたポインタが配列の
どの位置にあるか、ポインタの減算により計算し、インデックスを求める。


<a name="vce_get_array_object_last"></a>
- <B>vce_get_array_object_last</B>

  概要 : VCE配列の最後の要素を取りだす。

  カテゴリ : array

  関数プロトタイプ : ```void * vce_get_array_object_last( int index )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  返り値 : 最後の要素へのポインタ。要素がひとつも存在しない場合はNULLを返す

  詳細説明 : VCE配列の使用中のもののうち最後の要素へのポインタを得る。
vce_alloc_array_object は、常に使用中リンクの先頭に追加されるため、
vce_alloc_array_object と本関数をつかえば、 FIFOのようなことができる。
つまり、
先頭にのみ追加され、末尾からのみ取りだされるという配列を作ることができる。

  See also : <a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_get_array_object_next">vce_get_array_object_next</a><a href="#vce_get_array_object_top">vce_get_array_object_top</a>
<a name="vce_get_array_object_next"></a>
- <B>vce_get_array_object_next</B>

  概要 : VCE配列の使用中要素の次の要素を取りだす

  カテゴリ : array

  関数プロトタイプ : ```void * vce_get_array_object_next( int index , void *p )``` 

  - arg 1 : ```int index```
    配列を特定する配列デスクリプタ

  - arg 2 : ```void *p```
    vce_get_array_object_next は、
この引数で与えられたポインタの差す要素の次の使用中要素を返す。

  返り値 : 次の要素のポインタ

  詳細説明 : vce_get_array_object_next は、 ARRAY_SCAN マクロ中で使用されている。
通常のアプリケーションは、本関数を直接に使用するべきではない。
ARRAY_SCAN マクロを使用したほうが安全確実である。

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_get_array_object_top">vce_get_array_object_top</a>
<a name="vce_get_array_object_pointer_by_index"></a>
- <B>vce_get_array_object_pointer_by_index</B>

  概要 : VCE配列の要素をインデクスを指定して得る

  カテゴリ : array

  関数プロトタイプ : ```void *vce_get_array_object_pointer_by_index( int index, int objindex )``` 

  - arg 1 : ```int index```
    VCE配列を特定するための配列ディスクリプタ

  - arg 2 : ```int objindex```
    取りだしたい要素の配列中のindex

  返り値 : 取りだした要素を指すポインタ。

  詳細説明 : 通常、VCE配列の要素は ARRAY_SCAN もしくは、ポインタによってアクセスされるが、
本関数を使えばインデックスを使って要素にアクセスすることもできる．
NULLポインタを返す場合は、 vce_get_last_error を使ってエラーの内容を知る
ことができる。

  使用例 :   // 使用中、未使用にかかわらず配列の全要素を初期化する
  for(int i=0;;i++){
      sometype *t = vce_get_array_object_pointer_by_index( memind, i );
      if( t == NULL )break;
      t->someparam = somevalue;
  }

  See also : <a href="#vce_get_array_object_pointer_by_index_only_used">vce_get_array_object_pointer_by_index_only_used</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_object_pointer_by_index_only_used"></a>
- <B>vce_get_array_object_pointer_by_index_only_used</B>

  概要 : VCE配列の指定したインデクスを持つ要素を得る(使用中の要素のみ)

  カテゴリ : array

  関数プロトタイプ : ```void * vce_get_array_object_pointer_by_index_only_used( int index, int objindex )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  - arg 2 : ```int objindex```
    取りだしたい要素の配列中のインデックス。

  返り値 : 取りだした要素をさすポインタ。要素が使用中でない場合はNULLポインタを返す

  詳細説明 : vce_get_array_object_pointer_by_index 関数とほぼ同じだが、
現在使用のものだけを返す。

  See also : <a href="#vce_get_array_object_pointer_by_index">vce_get_array_object_pointer_by_index</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_object_top"></a>
- <B>vce_get_array_object_top</B>

  概要 : 

  カテゴリ : array

  関数プロトタイプ : ```void * vce_get_array_object_top( int index )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  返り値 : 使用中の要素をさすポインタ。
使用中の要素がない場合はヌルポインタを返す

  詳細説明 : vce_get_array_object_top は、 ARRAY_SCAN マクロの内部で使用される。

ARRAY_SCAN マクロは、配列の要素のうち使用中のものすべてをスキャンする
ために実装されているが、本関数はそのうち先頭のものを取りだす。
通常のアプリケーションは、 ARRAY_SCAN マクロを直接使用するほうが便利な
場合が多い。

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_get_array_object_next">vce_get_array_object_next</a>
<a name="vce_get_array_usenum"></a>
- <B>vce_get_array_usenum</B>

  概要 : VCE配列の要素のうちいくつが使用中になっているかを数える

  カテゴリ : array

  関数プロトタイプ : ```int vce_get_array_usenum( int index )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  返り値 : 使用中の要素の数。

  詳細説明 : 配列全体をスキャンして数えることなく、使用中の数を返す。
スキャンしないので非常に高速である。

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_current_utime"></a>
- <B>vce_get_current_utime</B>

  概要 : 現在時刻を VCEI64型で得る

  カテゴリ : util

  関数プロトタイプ : ```VCEI64 vce_get_current_utime( void )``` 

  返り値 : 現在時刻。
UNIX環境においては、 gettimeofday  関数により得られた
timeval 構造体の値を VCEI64 に変換した値を返す。
Win32環境においては、 GetSystemTime 関数により得られた
SYSTEMTIME 構造体の値を VCEI64 に変換した値を返す。

  詳細説明 : VCEI64に変換される元になるtimevalの値は、 gettimeofday() が返す値を
変換して得られるものである。
VCEはこの関数が返す値を、vce_heartbeat が呼びだされるごとに更新する。

  See also : <a href="#vce_set_internal_timer">vce_set_internal_timer</a>
<a name="vce_get_ipv4_addr_by_name"></a>
- <B>vce_get_ipv4_addr_by_name</B>

  概要 : ホスト名から IPv4アドレス(ネットワークバイトオーダ)を得る

  カテゴリ : util

  関数プロトタイプ : ```int vce_get_ipv4_addr_by_name( unsigned int *a, const char *s );``` 

  - arg 1 : ```unsigned int *a```
    IPv4アドレスのポインタ。出力に使われる。
出力はネットワークバイトオーダのままである。in_addr 構造体の
s_addr メンバそのもの。

  - arg 2 : ```char *s```
    ホスト名。"192.168.1.2" や "www.vce-lab.net" などが指定できる。

  返り値 : 成功したら0、失敗したら負のエラーコードを返す

  詳細説明 : UNIXの場合は inet_aton 、 gethostbyname の順に呼びだす。
Win32の場合は、inet_addr, gethostbyname の順に呼びだす。
PlanetWeb の場合は，現在は DNS解決に対応していない．


<a name="vce_get_last_error"></a>
- <B>vce_get_last_error</B>

  概要 : VCE内で最後に起こったエラー番号を取得する。

  カテゴリ : err

  関数プロトタイプ : ```int vce_get_last_error(void);``` 

  返り値 : エラーコードの値。

  詳細説明 : この関数で取得されるエラー番号はすべて vce.h に定義されている。
それでエラーの内容を知ることができる他に、ログとして残したい場合は、
vce_strerror を利用することができる。
ただし、
vce_strerror の返す文字列の内容は将来変更されないとは限らないため、
その出力文字列をパースして処理に利用しないほうがよい。
vce.h で定義されているエラーコードは、
将来にわたって変更されることはない。(削除される場合は欠番となる。)

  使用例 : <pre>
// vce_tcpcontext_create はよくエラーが発生する関数である。
tcpcontext_t t = vce_tcpcontext_create( .... );
if( !t ){
    vce_errout( "Cannot create tcpcontext! %s\n",
    vce_strerror( vce_get_last_error() ) );
}
</pre>

  See also : <a href="#vce_strerror">vce_strerror</a>
<a name="vce_get_netstat_string"></a>
- <B>vce_get_netstat_string</B>

  概要 : VCE が管理しているすべての接続情報を文字列で取得する。

  カテゴリ : log

  関数プロトタイプ : ```void vce_get_netstat_string( char *buf, int maxlen )``` 

  - arg 1 : ```char *buf```
    出力先文字列

  - arg 2 : ```int maxlen```
    出力する最大の長さ

  返り値 : バッファが余ったら0、埋まったら負(VCE_EFULL)を返す

  詳細説明 : VCE が管理しているすべてのコネクションに関する情報を文字列で取りだす。
UNIXでいうところの、 netstat コマンドの出力に相当する内容となっている。
各コネクションの情報は "PARAM=VALUE" をコンマで区切ってならべた内容で、
1行あたり1コネクション(ソケット)となる。
行の基本種類は "conn", "listen_conn", の2種類がある。
"conn" の場合に表示される情報が最も種類が多い。
<ul>
<LI>"type=conn" の場合の情報<BR>
type=conn は、通常のコネクションをあらわす。
<ul>
<LI>r=NUM  受信バッファの長さ(暗号デコード済み)
<LI>w=NUM  送信バッファの長さ(暗号エンコードまだ)
<LI>er=NUM  受信バッファの長さ(暗号デコードまだ)
<LI>ew=NUM  送信バッファの長さ(暗号エンコード済み)
<LI>rem=STR  リモートアドレス。 vce_conn_get_remote_addr_string の出力。
<LI>loc=STR  ローカルアドレス。 vce_conn_get_local_addr_string の出力。
<LI>fd=NUM  OS の socket fd.
<LI>s=NUM  VCE内のシリアル番号
<LI>last=NUM  最後にアクセスがあった時刻
<LI>timeo=NUM  タイムアウトまでの時間
<LI>nego=NUM  暗号ネゴシエーション状態
</ul>
<LI>"type=listen_conn" の場合<BR>
これらのタイプは、接続待ち状態の tcpcontext あたり1個、表示される。
ほかのホストとつながっているコネクションをあらわしているわけではない。
<UL>
<LI>loc=STR  ローカルアドレス。ソケットを bind しているアドレス
<LI>fd=NUM  ソケットの File Descriptor
</UL>
</ul>
アプリケーションは出力バッファのためのメモリを確保し、
本関数に与えなければならないが、そのためには1コネクションあたり
1コネクションあたり最大200バイト使うので，
最大コネクションに応じたサイズのバッファを渡す必要がある．

  See also : <a href="#vce_get_stat">vce_get_stat</a>
<a name="vce_get_stat"></a>
- <B>vce_get_stat</B>

  概要 : VCE 全体の動作状況記録を取得する

  カテゴリ : log

  関数プロトタイプ : ```void vce_get_stat( vce_stat_t *v )``` 

  - arg 1 : ```vce_stat_t *v```
    記録を格納する vce_stat_t 構造体へのポインタ

  返り値 : なし

  詳細説明 : 本関数は、 vce_stat_t 構造体にVCE 全体の統計情報を格納する。
構造体メンバの意味は以下の通り。
<ul>
<LI>time_t boot_time<BR>
vce_initialize の起動時刻(time_t)
<LI>VCEI64 recv_byte,send_byte<BR>
読みこみ/書きこみ総バイト数
<LI>VCEI64 send_syscall, send_syscall_e<BR>
send() システムコールの呼びだし回数。 _e は、エラー発生回数
<LI>VCEI64 recv_syscall, recv_syscall_e<BR>
recv() システムコールの呼びだし回数。 _e は、エラー発生回数
<LI>VCEI64 accept_syscall, accept_syscall_e<BR>
accept() システムコールの呼びだし回数。 _e は、エラー発生回数
<LI>VCEI64 connect_syscall, connect_syscall_e<BR>
connect() システムコールの呼びだし回数。 _e は、エラー発生回数
<LI>conn_free, conn_alloc, conn_close, conn_write<BR>
VCE の各関数の呼びだし回数
<LI>keyex<BR>
DiffieHellman 鍵交換を使って鍵を交換した総回数。
鍵交換の負荷試験等に使う。
<LI>tcpcontext_create,tcpcontext_cleanup,tcpcontext_connect<BR>
各関数の呼びだし回数。成功したときだけ回数としてカウントされることに注意。
<LI>conn_timeout<BR>
コネクション(conn_t)がタイムアウトした回数
<LI>log_count<BR>
vce_errout や vce_errout0 を呼びだした回数。
</ul>

  See also : <a href="#vce_conn_get_stat">vce_conn_get_stat</a><a href="#vce_tcpcontext_get_stat">vce_tcpcontext_get_stat</a>
<a name="vce_get_tcp_packet_read_size"></a>
- <B>vce_get_tcp_packet_read_size</B>

  概要 : 読み込みデータの圧縮時のサイズと展開時のサイズを取得する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_get_tcp_packet_read_size(int *original, int *processing)``` 

  - arg 1 : ```int *original```
    展開したデータサイズを返すためのバッファの先頭アドレス。

  - arg 2 : ```int *processing```
    圧縮したデータサイズを返すためのバッファの先頭アドレス。

  返り値 : なし

  詳細説明 : 読み込みデータの圧縮時、展開時のデータサイズを取得できる。コールバック関数で
参照する。コールバック関数以外で使用するとたえず0になる。

  See also : <a href="#vce_get_tcp_packet_read_size">vce_get_tcp_packet_read_size</a>
<a name="vce_get_tcp_packet_write_size"></a>
- <B>vce_get_tcp_packet_write_size</B>

  概要 : 書きこみデータの圧縮時のサイズと展開時のサイズを取得する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_get_tcp_packet_write_size(int *original, int *processing)``` 

  - arg 1 : ```int *original```
    展開したデータサイズを返すためのバッファの先頭アドレス。

  - arg 2 : ```int *processing```
    圧縮したデータサイズを返すためのバッファの先頭アドレス。

  返り値 : なし

  詳細説明 : 書きこみデータの圧縮時、展開時のデータサイズを取得できる。コールバック関数で
参照する。コールバック関数以外で使用するとたえず0になる。

  See also : <a href="#vce_get_tcp_packet_read_size">vce_get_tcp_packet_read_size</a>
<a name="vce_heartbeat"></a>
- <B>vce_heartbeat</B>

  概要 : VCEを能動的に呼びだし、I/O処理をさせる。

  カテゴリ : core

  関数プロトタイプ : ```void vce_heartbeat( void )``` 

  返り値 : なし

  詳細説明 : VCEのI/O処理ルーチンを1回動かす。vce_mainloopではこの関数をずっと
呼びだし続けている。vce_mainloopではなくこの関数を使うことで、
より柔軟なユーザーメインルーチンを作ることができる。
この関数によってVCEをドライブする場合は、vce_set_mainloop_callback
関数で指定した関数は呼びだされないことに注意。
デフォルトでは、vce_heartbeat は呼びだしたらすぐにreturnするが、
このままサーバを起動すると、CPU時間を目一杯使用することになる。
vce_set_heartbeat_wait_flag 関数を使ってsleep時間を調整すれば、
この状況を回避できる。
もちろんCPU時間を一杯まで使わないようにする調整は、
アプリケーションの側で行なってもよく、
そのほうがアプリケーションごとに最適なCPU時間の利用ができる。

  使用例 : <pre>
  #include "vce.h"
  int main()
  {
      while(1){
          user_function();
          vce_heartbeat();
      }
  }
</pre>

  See also : <a href="#vce_mainloop">vce_mainloop</a><a href="#vce_set_heartbeat_wait_flag">vce_set_heartbeat_wait_flag</a><a href="#vce_set_mainloop_callback">vce_set_mainloop_callback</a>
<a name="vce_if_included_in_array"></a>
- <B>vce_if_included_in_array</B>

  概要 : 配列のある要素が、正しく配列に含まれてるかどうかしらべる

  カテゴリ : array

  関数プロトタイプ : ```int vce_if_included_in_array( int index, void *p )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  - arg 2 : ```void *p```
    調べたい要素をさすポインタ

  返り値 : 指定した配列に含まれているなら1、そうでないなら0を返す
引数が不正な場合は負のエラーコードを返す。

  詳細説明 : void *p で指定される要素が、 index で指定される配列に含まれている
かどうかを調べる。<BR>
配列要素が正しく配列に含まれているかどうかを調べるには、
まず p から配列の先頭アドレスを引き、その結果を配列要素のサイズ
で割った余りを得る。その余りが0でない場合は、要素が正しく配置されて
いないことがわかる。
さらに、わりきれる場合でも、
商が0以上配列の要素数-1 の範囲を越えていたら、
範囲外に配置されているためエラーとなる。

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_get_array_object_index">vce_get_array_object_index</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_init_array"></a>
- <B>vce_init_array</B>

  概要 : 新規にVCEの配列を初期化する。

  カテゴリ : array

  関数プロトタイプ : ```int vce_init_array ( size_t size , int num , char *nm )``` 

  - arg 1 : ```size_t size```
    配列の要素のサイズ(バイト数)

  - arg 2 : ```int num```
    配列の要素の個数

  - arg 3 : ```char *nm```
    配列の名前。名前を指定しておくと、VCE内で問題が生じたときに
ログに名前が出力されるのでデバッグの助けとなる。

  返り値 : 返り値： 成功したら0以上の配列ID。
このIDは今後のアクセスに使用する。この値をUNIXのファイルにならって、
配列デスクリプタと呼ぶ。失敗したらvce.h に定義されている負の値を返す。

  詳細説明 : 配列に必要なメモリを割りあてて配列をゼロクリアし、
使用中リストも同時に初期化する。
VCEの配列は、配列の初期化、空き要素の検索、解放を、
空きリストを実装することによって高速に実現できるように実装されている。
vce_init_array は、
概算で(要素のサイズ+20)×要素の個数 バイトのメモリを消費する。<BR>
vce_init_array が返すint値は、UNIXファイルの file descriptor のような
もので、今後の配列へのアクセスに使用する。<BR><BR>
VCE配列はVCEの処理の基盤ルーチンとして使用されている。<BR>
また、 vce_init_array 関数は内部で MALLOC 関数を使用している.

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#MALLOC">MALLOC</a><a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_end_array">vce_end_array</a><a href="#vce_free_array_object">vce_free_array_object</a><a href="#vce_free_array_object_all">vce_free_array_object_all</a>
<a name="vce_init_limit_t"></a>
- <B>vce_init_limit_t</B>

  概要 : vce_limit_t 構造体をデフォルト値に初期化する

  カテゴリ : core

  関数プロトタイプ : ``` void vce_init_limit_t( vce_limit_t *t )``` 

  返り値 : なし

  詳細説明 : vce_initialize_limited 関数に与える構造体引数である vce_limit_t を
正式に初期化する関数である。この構造体を使う場合はかならず
この関数を使って初期化しなければならない。

  See also : <a href="#vce_initialize_limited">vce_initialize_limited</a>
<a name="vce_initialize"></a>
- <B>vce_initialize</B>

  概要 : VCEを初期化する。

  カテゴリ : core

  関数プロトタイプ : ```int vce_initialize( void )``` 

  返り値 : 正常に初期化できた場合は0、そうでない場合は負のエラーコード(vce.h)。

  詳細説明 : VCEの関数を呼びだす前に必ず呼びださなければならない初期化関数である。
VCEの内部用メモリはこの関数で確保される．
またWindows環境においては、Winsockの初期化も同時に行なう。
UNIX 用では SIGPIPE をブロックする。

  使用例 : <pre>
// OS がソケットライブラリを提供していない場合のコード
int main()
{
    vce_initialize();

    // load inet libraries
    // load device dependent modules ..
    // Dialing ...

    while( wait_for_socket_init() );

    vce_set_socket_library_ok(1);

    t = vce_tcpcontext_create( ... );
    while(1){
        vce_heartbeat();
    }
}
</pre>

  See also : <a href="#vce_finalize">vce_finalize</a><a href="#vce_set_socket_library_ok">vce_set_socket_library_ok</a>
<a name="vce_initialize_limited"></a>
- <B>vce_initialize_limited</B>

  概要 : 限られたメモリ使用量で VCE を初期化する

  カテゴリ : core

  関数プロトタイプ : ```int vce_initialize_limited( vce_limit_t *lim )``` 

  - arg 1 : ```vce_limit_t *lim```
    設定情報を含んだ vce_limit_t 構造体へのポインタ．

  返り値 : 正常に初期化できた場合は0、そうでない場合は負のエラーコード(vce.h)。

  詳細説明 : vce_initialize と同じだが、 vce_limit_t 構造体を用いて、
メモリ使用量をチューニングできる。特にメモリ容量を限界までチューニング
したい環境において使用される。
vce_limit_t の各メンバはそれぞれ
<pre>
int max_tcpcontext  tcpcontext_t の最大個数
int max_taskgroup  taskgroup_t の最大個数
int max_conn  全体の conn_t の最大個数
int max_search  全体の検索エンジンの最大個数
int max_array  全体の配列エンジンの最大個数
</pre>
となっていて、0以上の値を指定することで設定可能。
-1 を指定するとデフォルト値を使用する。
すべての値をデフォルト値に設定するために
vce_init_limit_t 関数が用意されているのでそれを使用すること。
<BR>
max_array の最低値に関しては，VCE内部でも配列エンジンを使っているので
注意が必要である．VCEは内部で以下のように配列エンジンを使用する．
<ul>
<LI>conn,task処理用に2個，常時使用
<LI>tcpcontext は1個あたり4〜5個
<LI>switchcontext1個あたり3個
<LI>モニタリングクライアントは2個
<LI>モニタリングサーバーは5個 (うちtcpcontextが4個)
<LI>検索エンジンは1個あたり1個
<LI>taskgroup は1個
</ul>
これらのVCEのサービスは，配列が足りなくなると VCE_EARRAYを返す．
したがってVCEの各サービスの初期化関数が VCE_EARRAY を返したときは，
max_array の上限に注目してみるとよい．
また， max_array を1増やすごとに72バイトのメモリが確保される．
Linux/Win32環境では， max_array にデフォルト値の -1 を設定したときは
256が設定される．
<BR>
メモリを節約するという目的とは別に、デフォルトの最大値をもっと大きな値に
したいという場合にも本関数を使用できる。
典型的なのが、デフォルトの最大同時接続数1000 を、
もっと大きな値に変更する場合である。
その目的のためにも本関数を使用することができる。
ただし、ほとんどの linux/freeBSD  OS において、
カーネルの設定やユーザープロセス空間の limit によって最大接続数が
1024 以下に抑えられていることに注意が必要である。
この限界値を越えるには、カーネルの設定変更や
再コンパイル，シェルの設定変更が必要である。
Linux のチューニングについては <a href="linuxtune.html">こちら</a>を参照．

  使用例 : <pre>
int main(){
    // ゲームクライアント向けに共有メモリや検索エンジンを使わなくする
    vce_limit_t lim;
    lim.max_tcpcontext = 1;
    lim.max_taskgroup = -1;
    lim.max_conn = 1;
    lim.max_search = 0;
    lim.max_array = 0;
    lim.sendbuf_work_size = -1;
    lim.recvbuf_work_size = -1;
    vce_initialize_limited( &lim );
    vce_finalize();
}
</pre>

  See also : <a href="#vce_init_limit_t">vce_init_limit_t</a><a href="#vce_initialize">vce_initialize</a>
<a name="vce_limit_clear"></a>
- <B>vce_limit_clear</B>

  概要 : vce_limit_t型の構造体の初期化をする(-1のデフォルト値で初期化)

  カテゴリ : core

  関数プロトタイプ : ```void vce_limit_clear( vce_limit_t *t )``` 

  返り値 : なし

  詳細説明 : vce_initialize_limited 関数の引数として与えられるvce_limit_t型の
構造体の全部のメンバーに対して、デフォルト値である -1 を設定する。
この関数を使って vce_limit_t 型を初期化して vce_initialize_limited 関数を
呼び出すと、完全にデフォルトの設定が採用される。


  See also : <a href="#vce_initialize_limited">vce_initialize_limited</a>
<a name="vce_mainloop"></a>
- <B>vce_mainloop</B>

  概要 : VCEのメインループ関数。

  カテゴリ : core

  関数プロトタイプ : ```int vce_mainloop(void)``` 

  返り値 : なし

  詳細説明 : この関数を呼びだすことにより、CPUをVCEに渡す。
この関数から戻ることはない。vce_set_mainloop_callback関数によって
コールバック関数が定義されている場合は、
この関数の中から永久的にその関数が呼びだされ続ける。
またその関数が0以外を返した場合は、vce_mainloopはその関数が返した値を
そのまま返し、終了する。

  See also : <a href="#vce_set_mainloop_callback">vce_set_mainloop_callback</a>
<a name="vce_make_binary_array_from_hex"></a>
- <B>vce_make_binary_array_from_hex</B>

  概要 : 16進数文字列を変換して、バイナリデータを含む配列を作る。

  カテゴリ : util

  関数プロトタイプ : ```void vce_make_binary_array_from_hex( char *out, int outlen, const char *hex )``` 

  - arg 1 : ```char *out```
    バイナリデータ出力先の先頭アドレス

  - arg 2 : ```int outlen```
    入力データの長さ(偶数でない場合は、0をうしろに単に足したものを出力する)

  - arg 3 : ```char *hex```
    入力データ。

  返り値 : なし

  詳細説明 : "788ab0d8ce8df6" のような文字列から、バイナリデータの配列を作る。
2文字で1バイトを生成するため、奇数の文字数のデータが指定されたときには、
最後に0を単純に足したものを生成して出力する。
通常は、偶数文字数のテキストを指定して呼びだすこと。
vce_make_hex_from_binary_array の逆関数．

  See also : <a href="#vce_make_hex_from_binary_array">vce_make_hex_from_binary_array</a>
<a name="vce_make_binary_array_from_line"></a>
- <B>vce_make_binary_array_from_line</B>

  概要 : ASCIIテキストの1行からバイナリデータの配列を出力する

  カテゴリ : util

  関数プロトタイプ : ```void vce_make_binary_array_from_line( const char *line, int linelen, char *out, int *outlen, int *uselen )``` 

  - arg 1 : ```char *line```
    入力行

  - arg 2 : ```int linelen```
    入力行の長さ。

  - arg 3 : ```char *out```
    出力バッファ

  - arg 4 : ```int *outlen```
    出力バッファの長さ。値結果引数で、まず 最大長さを与えて呼びだし、
関数が返る時には、実際に使用した長さを代入して返す。

  - arg 5 : ```int *uselen```
    実際にテキストの行を読んだ長さを返す。

  返り値 : なし

  詳細説明 : "\r\n" と "\n" のどちらでおわってるかわからない行から
バイナリ配列をつくる。
成功した場合は、実際に配列を埋めた長さを outlen で返し、
入力行を実際に読んだ長さを uselen で返す。


<a name="vce_make_hex_from_binary_array"></a>
- <B>vce_make_hex_from_binary_array</B>

  概要 : バイナリデータ配列から，単一のhex の文字列を作る

  カテゴリ : util

  関数プロトタイプ : ```int vce_make_hex_from_binary_array( char *out, int outlen, const char *buf,int len, int folding)``` 

  - arg 1 : ```char *out```
    出力先バッファの先頭アドレス

  - arg 2 : ```int outlen```
    出力先バッファの長さ

  - arg 3 : ```char *buf```
    入力バッファの先頭アドレス

  - arg 4 : ```int len```
    入力バッファの長さ

  - arg 5 : ```int folding```
    32文字(入力の16バイト)ごとに折りかえすかどうかのフラグ．
折りかえすなら1，そうでないなら0．
折りかえさない場合は，どんなに入力が長くても1個の，
改行を含まない文字列になる．
また folding が 1 のときは，文字列の末尾に改行記号が UNIX 方式で入る．

  返り値 : 出力先がいっぱいになった場合は、 VCE_EFULLを返す。
そうでない場合は出力の文字数を返す(ヌル文字は含まない)

  詳細説明 : 変換結果は、1バイトが2文字になるので，成功した場合は，
出力は常に入力の2倍の文字数になる．
たとえば "abc" は "616263" となる．
この関数は vce_make_hex_text_from_buffer 関数のベース関数である．

  See also : <a href="#hextext">hextext</a><a href="#vce_make_hex_text_from_buffer">vce_make_hex_text_from_buffer</a>
<a name="vce_make_hex_text_from_buffer"></a>
- <B>vce_make_hex_text_from_buffer</B>

  概要 : バイナリデータ配列から、 hextext 形式のASCIIテキストを出力する。

  カテゴリ : util

  関数プロトタイプ : ```int vce_make_hex_text_from_buffer( const char *buf , int len , char *out , int outlen )``` 

  - arg 1 : ```char *buf```
    入力となるバイナリデータの先頭アドレス

  - arg 2 : ```int len```
    入力データの長さ

  - arg 3 : ```char *out```
    出力先の先頭アドレス

  - arg 4 : ```int outlen```
    出力する最大長さ(バイト数)

  返り値 : 出力先がいっぱいになった場合は、 VCE_EFULLを返す。
そうでない場合は出力した文字数を返す(ヌル文字は含まない)

  詳細説明 : 変換結果は、1バイトが2文字になる。
先頭のヘッダは、そのバッファをデコードするために必要な情報が記述されている。
中身の正当性をチェックするために、SHA-1によるチェックサムの値と、
長さが含まれている。読みこみルーチンではこれらすべての値が正しいことを
確認する。
変換した文字列は，
vce_make_binary_array_from_hex 関数で元に戻すことができる．

  See also : <a href="#hextext">hextext</a><a href="#vce_extract_data_from_hex_text">vce_extract_data_from_hex_text</a><a href="#vce_make_binary_array_from_hex">vce_make_binary_array_from_hex</a>
<a name="vce_protocol_acceptwatcher_deny"></a>
- <B>vce_protocol_acceptwatcher_deny</B>

  概要 : すべてのコネクションを拒否するTCP(conn_t)のaccept監視関数

  カテゴリ : watcher

  関数プロトタイプ : ```int vce_protocol_acceptwatcher_deny( conn_t c )``` 

  - arg 1 : ```conn_t c```
    サーバの tcpcontext が新規に accept した(受けいれた)コネクションを
あらわす conn_t

  返り値 : この関数は常に-1を返す。

  詳細説明 : この関数は vce_tcpcontext_create の引数に指定される。
この関数を指定すると、すべてのコネクションを拒否するため
クライアントが接続できなくなる。
したがってデバッグ用と言える。

  See also : <a href="#vce_protocol_acceptwatcher_noop">vce_protocol_acceptwatcher_noop</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_acceptwatcher_noop"></a>
- <B>vce_protocol_acceptwatcher_noop</B>

  概要 : すべてのコネクションを受けいれる TCP(conn_t)のaccept 監視関数

  カテゴリ : watcher

  関数プロトタイプ : ```int vce_protocol_acceptwatcher_noop( conn_t c )``` 

  - arg 1 : ```conn_t c```
    サーバの tcpcontext が新規に accept した(受けいれた)コネクションを
あらわす conn_t

  返り値 : この関数は常に0を返すので、すべてのコネクションを受けいれる。

  詳細説明 : この関数は vce_tcpcontext_create の引数に指定される。
0を返すとデフォルトの動作と同じであるため、
NULL を指定したのと同じことになる。

  See also : <a href="#vce_protocol_acceptwatcher_deny">vce_protocol_acceptwatcher_deny</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_closewatcher_noop"></a>
- <B>vce_protocol_closewatcher_noop</B>

  概要 : 何もしない、コネクション close 監視関数

  カテゴリ : watcher

  関数プロトタイプ : ```int vce_protocol_closewatcher_noop( conn_t c )``` 

  - arg 1 : ```conn_t c```
    閉じられようとしているコネクション(閉じる直前)

  返り値 : この関数は常に0を返す。

  詳細説明 : vce_tcpcontext_create の引数に指定される close監視関数のひとつである。
実際には何の処理もしないため、NULL を指定するのと同じ結果になる。
ただし、
明示的に指定することによって、プログラムソースが読みやすくなるという利点が
ある。

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_parser_bin16"></a>
- <B>vce_protocol_parser_bin16</B>

  概要 : bin16 プロトコルのレコードを取りだしてコールバック関数を呼びだす

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_parser_bin16( conn_t c )``` 

  - arg 1 : ```conn_t ct```
    レコードがきているかどうか検査する対象のコネクション構造体。

  返り値 : データがまだ足りない場合は0、レコードがみつかってコールバックを
呼びだせたら、コールバックの返り値をそのまま返す。

  詳細説明 : vce_protocol_parser_bin16 関数は、conn_t 用のレコード検出関数である。
bin16 と呼ばれるプロトコルのレコードを取りだす。
レコードを検出するたびに、
vce_tcpcontext_create 関数の呼びだし時に指定しているコールバック関数を
呼びだす。
VCEのアプリケーションにおいては、アプリケーションの特性上、
<B>小さいパケットを多く処理する</b>ことが多いので，
bin16プロトコルを使うことが多くなるだろう．
<BR><BR>
<B>bin16プロトコルの内容</B><BR>
bin16プロトコルを使う場合、
ソケットを流れる1レコードは以下のようなフォーマットになっている。
C言語風に書けば以下のようなコードになる．
<pre>
struct packet
{
unsigned short content_length;
char buf[content_length];
}
</pre>
となる。つまり10バイトのデータを送ると、(10 + sizeof(unsigned short)) で
12バイトのデータが送信されることになる。
<BR><BR>
<B>コールバック関数の定義</B><BR>
コールバック関数の定義は
<pre>
int callback( conn_t *c, char *data, int len )
</pre>
である。<code>char *data</code>にレコードの内容
<code>buf[content_length]</code>
へのポインタが、<code>int len</code>
に <code>content_length </code>が代入される。
<code>conn_t *c </code>には、入力元を特定できるコネクションが代入される。
<BR><BR>


  See also : <a href="#vce_protocol_parser_bin32">vce_protocol_parser_bin32</a><a href="#vce_protocol_parser_text">vce_protocol_parser_text</a><a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_parser_bin32"></a>
- <B>vce_protocol_parser_bin32</B>

  概要 : bin32プロトコルのレコードを取りだしてコールバック関数を呼びだす

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_parser_bin32( conn_t c )``` 

  - arg 1 : ```conn_t ct```
    レコード検査をする対象となるコネクション構造体(conn_t)

  返り値 : データがまだ足りない場合は0、レコードがみつかってコールバックを呼びだせ
たら、コールバックの返り値をそのまま返す。

  詳細説明 : 本関数は、 conn_t 用のレコード検出関数であり、32ビットまでのレコード長に
対応している。実際にはそれほど長いデータレコードを使用することは
性能上問題の原因にしかならないので、
BIN32DATA_MAX までの長さしか検出できない。
それより長いレコードが入力されようとした場合、
それはサーバーに対するクラッキング行為であるとして
プロトコルエラーを返す(VCEはその場合コネクションを切断する)
BIN32DATA_MAX は vce.h で定義されている。

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_protocol_unparser_bin32">vce_protocol_unparser_bin32</a>
<a name="vce_protocol_parser_text"></a>
- <B>vce_protocol_parser_text</B>

  概要 : プロトコルを1行単位で取りだしてコールバック関数を呼びだす

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_parser_text( conn_t c )``` 

  - arg 1 : ```conn_t c```
    レコード取りだし対象となるコネクション

  返り値 : データがまだ足りない場合は0、レコードがみつかってコールバックを
呼びだせたら、コールバックの返り値をそのまま返す。

  詳細説明 : 行単位のレコードをテキスト行解析により取りだす。
テキストプロトコルの場合は、暗号化をしない場合、tcpdump などのプログラム
により、
悪意がなくてもプロトコルの中身が解析されてしまうので注意が必要である。
改行のデリミタとなる文字列は "\n" と "\r\n" の2種である。
また、 コールバックに入力されるデータはヌル終端されている C 言語の文字列
* ではない * 。 そのため、 vce_makecstr 関数などを用いて、
C言語の文字列に変換する必要がある。

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a>
<a name="vce_protocol_parser_through"></a>
- <B>vce_protocol_parser_through</B>

  概要 : レコード境界を切らずにコールバックを呼びだすプロトコルパーサ

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_parser_through( conn_t ct )``` 

  - arg 1 : ```conn_t ct```
    データを受けとるTCPコネクション(conn_t)

  返り値 : コールバック関数の返り値をそのまま返す。
したがって、コールバック関数が負の値を返した場合はVCEによって自動的に
接続が切断される。

  詳細説明 : 各種プロトコルの中には、
レコードという考えかたがないものもある。
そのようなプロトコルのために、データ処理を一切せずに、
ソケットからの入力データをそのままコールバック関数に渡すパーサが必要である。
vce_protocol_parser_through はまさにそのために使用される。

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_protocol_unparser_through">vce_protocol_unparser_through</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_dump"></a>
- <B>vce_protocol_pcallback_dump</B>

  概要 : 普通のTCPコネクション用の、データをダンプするコールバック

  カテゴリ : pcallback

  関数プロトタイプ : ```int vce_protocol_pcallback_dump( conn_t ct, char *data, int len )``` 

  - arg 1 : ```conn_t ct```
    入出力対象となるTCPコネクション。

  - arg 2 : ```char *data```
    入力データへの先頭アドレス

  - arg 3 : ```int len```
    入力データの長さ(バイト数)

  返り値 : 送信しないので常に0を返す

  詳細説明 : conn_tに入力されたデータをすべて vce_dump_buffer 関数を使って
ダンプする。アプリケーションのデバッグ用に作られた関数である。
<BR>
この関数は「プロトコルコールバック関数」である．

  See also : <a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a><a href="#vce_protocol_pcallback_noop">vce_protocol_pcallback_noop</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_echo_bin16"></a>
- <B>vce_protocol_pcallback_echo_bin16</B>

  概要 : conn_t上のbin16プロトコル用の、エコー・コールバック関数

  カテゴリ : pcallback

  関数プロトタイプ : ```int vce_protocol_pcallback_echo_bin16( conn_t ct, char *data, int len )``` 

  - arg 1 : ```conn_t ct```
    エコーする対象となるコネクション。

  - arg 2 : ```char *data```
    受信データの先頭アドレス

  - arg 3 : ```int len```
    受信データの長さ(バイト数)

  返り値 : 入出力に失敗すると負のエラーコード(vce.h)を、成功すると
送信バイト数を返す。

  詳細説明 : vce_tcpcontext_set_conn_parser 関数の呼びだし時に指定する，
プロトコルコールバック関数である。

本関数は、デフォルトでVCEに附属している
コールバック関数で、入力された文字列を単純に出力にエコーバックする。

本関数を使うためには、 vce_tcpcontext_set_conn_parser の呼びだし時に、
vce_protocol_parser_bin16 関数をプロトコルパーサとして登録しておく
必要がある。<BR>

実際のアプリケーションにおいては、独自のコールバック関数を
定義してクライアントからの入力を処理するが、本関数はテストのために
使用することができる。<BR>

  See also : <a href="#vce_protocol_pcallback_dump">vce_protocol_pcallback_dump</a><a href="#vce_protocol_pcallback_noop">vce_protocol_pcallback_noop</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_echo_text"></a>
- <B>vce_protocol_pcallback_echo_text</B>

  概要 : conn_t 上の行指向テキストプロトコル用のエコーコールバック関数

  カテゴリ : pcallback

  関数プロトタイプ : ```int vce_protocol_pcallback_echo_text(conn_t ct, char *data, int len )``` 

  - arg 1 : ```conn_t ct```
    入力を受けるコネクション

  - arg 2 : ```char *data```
    入力データの先頭アドレス

  - arg 3 : ```int len```
    入力データの長さ

  返り値 : 入出力に失敗すると負のエラーコード、成功すると送信バイト数を返す

  詳細説明 : 入力をそのまま出力にコピーして text プロトコルで書きだす。

  See also : <a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a><a href="#vce_protocol_unparser_text">vce_protocol_unparser_text</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_noop"></a>
- <B>vce_protocol_pcallback_noop</B>

  概要 : 普通のTCPコネクション用の、何もしないプロトコルコールバック関数

  カテゴリ : pcallback

  関数プロトタイプ : ```int vce_protocol_pcallback_noop( conn_t ct ,char *data , int len )``` 

  - arg 1 : ```conn_t ct```
    入出力対象となるコネクション.

  - arg 2 : ```char *data```
    入力データの先頭アドレス

  - arg 3 : ```int len```
    入力データの長さ(バイト数)

  返り値 : 送信しないので常に0を返す

  詳細説明 : 本関数は vce_tcpcontext_set_conn_parser の呼びだし時に指定する
プロトコルコールバック関数である．
本関数は単にデータを捨てて何もしない．
<BR>
アプリケーションは実際には本関数を使用することはなく、
独自のプロトコルコールバック関数を定義して入力データの処理をすることになる。
サーバーを一時的に「殺す」ために使える．
<BR>

  See also : <a href="#vce_protocol_pcallback_dump">vce_protocol_pcallback_dump</a><a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_unparser_bin16"></a>
- <B>vce_protocol_unparser_bin16</B>

  概要 : bin16 プロトコルのレコードを、コネクションに対して書きこむ

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_unparser_bin16( conn_t ct, char *data , int len  )``` 

  - arg 1 : ```conn_t ct```
    書きこみ対象のコネクション

  - arg 2 : ```char *data```
    処理すべきデータへのポインタ

  - arg 3 : ```int len```
    処理すべきデータの長さ

  返り値 : 成功したら書きこめたバイト数を返し、
失敗したら負のエラーコードを返す。
レコードに必要な情報を同時に送信するので、書きこめたバイト数は、
書きこもうとしたバイト数より2バイト多い。
レコードの内容については、 vce_protocol_parser_bin16 を参照。

  詳細説明 : 本関数は、 conn_t に対して，
bin16プロトコルのレコードを送りだすためのフォーマッタ関数である．
つまり，データに常に2バイトのヘッダをくっつけて書きだす．
<B>送信バイト数</B><BR><BR>
bin16プロトコルは、All or Nothing な送信をする。つまり、
20バイト送ろうとして、送信バッファに残り10バイトしかなかったので
10バイトしか送れなかったということはなく、負のエラーコードか22か、
どちらかの返り値しかない。
これは、不完全なレコードを送ることをしない、
というVCEのポリシーの現れである。

  使用例 : <pre>
  // エコーサーバを実装するコールバック関数の例
  int callback( conn_t ct, char *data, int len )
  {
      return vce_protocol_unparser_bin16( ct,data,len );
  }
</pre>

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_unparser_bin32"></a>
- <B>vce_protocol_unparser_bin32</B>

  概要 : BIN32プロトコルのレコードをひとつ、コネクション(conn_t)に書きこむ

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_unparser_bin32( conn_t ct, char *data, int len )``` 

  - arg 1 : ```conn_t ct```
    書きこみ対象のコネクション

  - arg 2 : ```char *data```
    書きこむデータレコードの内容をさすポインタ

  - arg 3 : ```int len```
    書きこむデータレコードの長さ(バイト)

  返り値 : 成功したら書きこめたバイト数を返し、
失敗したら負のエラーコードを返す。
レコードに必要な情報を同時に送信するので、書きこめたバイト数は、
書きこもうとしたバイト数より4バイト多い。

  詳細説明 : BIN32プロトコルは、BIN16の限界である64キロバイトより大きいデータレコードを
送りたいときに使用されるアンパーサである。
BIN32によって大きいデータを送信できるが、定数 BIN32DATA_MAX で規定されている
データ長よりも長いデータは送信できない。

  See also : <a href="#vce_protocol_parser_bin32">vce_protocol_parser_bin32</a><a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a>
<a name="vce_protocol_unparser_text"></a>
- <B>vce_protocol_unparser_text</B>

  概要 : テキストプロトコルのレコード(1行)をコネクションに書きこむ

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_unparser_text( conn_t ct, char *data, int len )``` 

  - arg 1 : ```conn_t ct```
    書きこむ対象となるコネクション

  - arg 2 : ```char *data```
    書きこむデータへのポインタ

  - arg 3 : ```int len```
    書きこむデータの長さ

  返り値 : 成功したらデータの長さプラス1，失敗したら負のエラーコード．

  詳細説明 : 改行記号である"\n" や "\r"もエスケープなどの処理を一切せずに
そのまま書きこむので注意が必要である。
また、データの末尾に "\n" を追加して送信するので、
送信バイト数は、成功の場合 len よりも1多い値となる。

  See also : <a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_unparser_through"></a>
- <B>vce_protocol_unparser_through</B>

  概要 : TCPコネクションにデータをそのまま書き出す

  カテゴリ : parser

  関数プロトタイプ : ```int vce_protocol_unparser_through( conn_t ct, char *data, int len)``` 

  - arg 1 : ```conn_t ct```
    データを出力するコネクション

  - arg 2 : ```char *data```
    出力するデータの先頭アドレス

  - arg 3 : ```int len```
    出力するデータの長さ(バイト数)

  返り値 : 書きこめたデータの長さ。エラーの場合は負のエラーコード

  詳細説明 : 本関数は，何の処理もせずにデータをconn_tに書きこむ．

  See also : <a href="#vce_protocol_parser_through">vce_protocol_parser_through</a><a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_read_plain_text_file"></a>
- <B>vce_read_plain_text_file</B>

  概要 : プレインテキストファイルを読みこむ

  カテゴリ : util

  関数プロトタイプ : ```int vce_read_plain_text_file( const char *filename, int (*callback)(char*,in,char*))``` 

  - arg 1 : ```char *filename```
    読みこむファイル名

  - arg 2 : ```int (*callback) (char *filename,int lineno,char *line )```
    引数処理のためのコールバック関数

  返り値 : ファイルが読みこめない場合 VCE_EACCESSFILE を返す。
成功したら0を返す。またコールバック関数が負を返したら、
その値をそのまま返す。

  詳細説明 : 入力テキストファイルの各行を読みこむごとにコールバック関数を呼びだし、
実際の入力データの処理はそのコールバック関数で実行する。
本関数は行番号などデバッグに役立つ情報を付加してコールバック関数を呼びだし、
コールバック関数が負を返したら処理を中断する。
vce_read_simple_config_file 関数をさらに単純にしたものである。
なお、空行は読みとばされる。

  See also : <a href="#vce_read_simple_config_file">vce_read_simple_config_file</a>
<a name="vce_read_simple_config_file"></a>
- <B>vce_read_simple_config_file</B>

  概要 : 単純なテキスト設定ファイルをコールバック関数を使って読みこむ

  カテゴリ : util

  関数プロトタイプ : ```int vce_read_simple_config_file( const char *filename, int ( *callback ) ( char *,int,char *,char *) )``` 

  - arg 1 : ```char *filename```
    読みこむファイル名

  - arg 2 : ```int (*callback) (char *filename,int lineno,char *param, char *value)```
    ファイルの中身を処理するためのコールバック関数

  返り値 : ファイルが読みこめない場合 VCE_EACCESSFILE を返す。
成功したら0を返す。またコールバック関数が負を返したら、
その値をそのまま返す。

  詳細説明 : vce_read_simple_config_file は入力ファイルを1行づつ読みこみ、
各行に
<pre>
PARAMNAME=VALUE
</pre>
という形式(イコール'='でパラメータと値を並べたもの)を発見するごとに
指定されたコールバック関数を呼びだす。
イコールの前後では空白文字は存在できない．
またPARAMNAME は必ず行頭からはじまらなければならない．
文字列のエスケープには対応していないので，
改行をデータ中に入れることはできない．
コールバック関数のプロトタイプは
<pre>
int (*callback)(char *filename, int lineno, char *param, char *value )
</pre>
であり、 filename は設定ファイル名、 lineno は入力ファイルの中の行番号、
char *param はパラメータ名、 char *value は設定値である。
value に改行記号は含まれない。
また、 "\r\n" で終わる行も "\n" で終わる行も同じように読みこむことができる。
<BR>
1行の長さを最大32キロバイトと仮定している。
それを越える長さの行があった場合は、
越える分については読みこまれない。
また、コールバック関数が負を返すと、
本関数も負を返す。返り値は、コールバック関数が返した値と同じである。
本関数は，標準入出力(stdioのFILE構造体)をそのまま使用するので，
標準入出力が使用できない環境では動作しない．

  See also : <a href="#swp">swp</a><a href="#vce_copy_cstring_upto">vce_copy_cstring_upto</a><a href="#vp">vp</a>
<a name="vce_replace_malloc_funcs"></a>
- <B>vce_replace_malloc_funcs</B>

  概要 : VCE が使うmalloc関数を置きかえる

  カテゴリ : util

  関数プロトタイプ : ```void vce_replace_malloc_funcs( void*(*a)(size_t), void*(*r)(void*,size_t), void(*f)(void*))``` 

  - arg 1 : ```void * (*a)(size_t)```
    メモリ割りあて関数へのポインタ。NULLを指定すると置きかえない。

  - arg 2 : ```void*(*a)(void*,size_t)```
    メモリ再割りあて関数へのポインタ。NULLを指定すると置きかえない。

  - arg 3 : ```void (*f)(void*)```
    メモリ解放関数へのポインタ。NULLを指定すると置きかえない。

  返り値 : なし

  詳細説明 : VCEがメモリ割りあて/解放に使う関数を置きかえる。
アプリケーションによっては、メモリ管理を一元化したい場合や、
メモリ関係の性能監視のために malloc/free 関数を再定義したい場合がある。
本関数ではそのような場合に関数ポインタを指定することで
置きかえることができる。
デフォルトでは、 割りあて関数は malloc, 解放関数は free となっている。
本関数は、 vce_initialize 関数より前に呼びだすことが可能である。


<a name="vce_set_heartbeat_wait_flag"></a>
- <B>vce_set_heartbeat_wait_flag</B>

  概要 : vce_heartbeat の sleep時間 調節機構をon/off する

  カテゴリ : core

  関数プロトタイプ : ```void vce_set_heartbeat_wait_flag( int flag )``` 

  - arg 1 : ```int flag```
    0なら調節機構を off,1 なら on になる。

  返り値 : なし

  詳細説明 : vce_heartbeat の sleep 時間調整機構を操作する。
flag に1を設定すると、vce_heartbeat は、
最高100ミリ秒、
ネットワークからの入力がない場合 select で待つようになる。
デフォルトでこの機能は off である
(なぜなら、ちゃんとしたアプリケーションならその機構をアプリケーションの
側で持っていることが多いから)。
このループ速度調整機能は，最低速度を100ミリ秒としているが，
現在の実装では，実際には数十分かけてその速度に落ちつくことになる．
つまり，VCEは急激にループ速度を変更することはせず，
パケットを受けるとループ速度を2倍にし，
パケットを受けないと非常にゆっくりとしたペースで速度を落としていく．

  See also : <a href="#vce_heartbeat">vce_heartbeat</a>
<a name="vce_set_mainloop_callback"></a>
- <B>vce_set_mainloop_callback</B>

  概要 : vce_mainloopから呼びだすコールバック関数を設定する。

  カテゴリ : core

  関数プロトタイプ : ```void vce_set_mainloop_callback( int (*f)(void) )``` 

  - arg 1 : ```int (*f)(void)```
    コールバック関数へのポインタ

  返り値 : 戻り値はない。常に成功する。

  詳細説明 : vce_mainloopから定期的に呼びだされるコールバック関数。
vce_mainloopを呼びだすと通常永久ループに入るが、
vce_mainloopを利用しつつもアプリケーションで並行に処理をしたい場合は
この関数を使用する。VCEが通常の負荷の状態のときは、
約10ミリ秒に1回以上のタイミングで呼びだされることになる。
<BR>
また、コールバック関数が0以外を返すとvce_mainloopが終了する。

  使用例 : <pre>
  #include "vce.h"
  int callbk( void )
  {
      printf( "callback function is called.\n" );
  }
  int main( int argc, char **argv )
  {
      // 何らかのコード
      vce_set_mainloop_callback( callbk );
      vce_mainloop();
  }
</pre>

  See also : <a href="#vce_heartbeat">vce_heartbeat</a><a href="#vce_mainloop">vce_mainloop</a>
<a name="vce_set_read_write_log_mode"></a>
- <B>vce_set_read_write_log_mode</B>

  概要 : VCEによるread/writeシステムコールの使用をログするかを設定する

  カテゴリ : core

  関数プロトタイプ : ```void vce_set_read_write_log_mode( int mode )``` 

  - arg 1 : ```int mode```
    1ならログする、0ならログしない。

  返り値 : なし

  詳細説明 : ログ出力をするように設定すると、 vce_errout と同じストリームに対して、
何番(ディスクリプタ)のストリームに対して何バイト出力したかの値と、
実際のデータのダンプ(16進数)を出力する。
この出力はVCEのバージョンによって変化するかもしれないため、
あくまで人間が目視でデバッグするために使うのが望ましい。

  See also : <a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>
<a name="vce_set_socket_library_ok"></a>
- <B>vce_set_socket_library_ok</B>

  概要 : VCE の下層の socket ライブラリが初期化できたことを VCE に通知する。

  カテゴリ : core

  関数プロトタイプ : ```void vce_set_socket_library_ok( int flag )``` 

  - arg 1 : ```int flag```
    初期化フラグ。初期化できていたら1、そうでないなら0。

  返り値 : なし

  詳細説明 : VCE は socket ライブラリに依存しているが、
UNIX 以外のアーキテクチャの場合、socket ライブラリはアプリケーションの
初期化時、 vce_initialize や vce_tcpcontext_create
の呼びだし時には初期化されていない可能性がある。
ところがこれらの関数(入出力はしないがメモリ確保をする関数)はできるだけ
プログラムの呼びだし時に行っておきたい。
本関数を使うことによって、アプリケーションがメインループに入った後に、
入出力をするようにできる。
具体的には、 flag が0の時は、 vce_heartbeat は何もしない。また
send/recv/accept/bind/listen/connect/socket/shutdown/close
などといった処理はすべて呼びださない。
なお POSIX(Linux,FreeBSD) 環境においては、
このフラグは最初から1に設定されているので、
本関数を呼びだす必要はない。
Win32 環境においては、
VCE 内部で winsock の初期化が成功したら自動的に1 に設定される。
VCE が内部的に保存しているこのフラグの値は、
vce_initialize の呼びだし後に意味をもつので、
アプリケーションはまず vce_initialize を呼びださなければならない。

  See also : <a href="#vce_initialize">vce_initialize</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_set_verbose_mode"></a>
- <B>vce_set_verbose_mode</B>

  概要 : verboseモード(うるさいモード)の設定をする

  カテゴリ : core

  関数プロトタイプ : ```void vce_set_verbose_mode( int mode )``` 

  - arg 1 : ```int mode```
    1以上なら verboseモードとなる。 0なら通常モード。
-1なら、「絶対に出力しない」モード。

  返り値 : なし

  詳細説明 : verbose モードの設定は、動的に変更できる。
この関数は、 vce_initialize 関数の出力もverboseにできるように、
vce_initialize 関数の呼びだし前に呼びだすことができるようにできている。<BR>
モードを1にするとVCEライブラリの中に埋めこまれている、
冗長なメッセージも出力されるため、
遅い回線を通してエラーメッセージを見るときは注意が必要である。

  知られているバグやTODO : TODO verbose モードの仕様は、
アプリケーションとVCE自体の出力を自由に調整できるように、
柔軟に設定をできるようにしていく予定である。
現在はmodeの値は0か1のみが使える。


<a name="vce_show_array_usage"></a>
- <B>vce_show_array_usage</B>

  概要 : VCE配列の状態をすべて出力する。

  カテゴリ : array

  関数プロトタイプ : ```int vce_show_array_usage( int index , int show_all )``` 

  - arg 1 : ```int index```
    配列を特定するための配列デスクリプタ

  - arg 2 : ```int show_all```
    各要素についても情報を表示するなら1、そうでないなら0。
0のほうが出力される文字数はかなり少ない。

  返り値 : 現在使用中の要素数を返す

  詳細説明 : デバッグ用の関数。配列を指定し、その配列の管理している要素についての
情報をログに対して出力する。
<BR>
注意： エラー出力を抑える設定でビルドされている VCE ライブラリを
リンクしている場合は，本関数は VCE_ESUPPORT を返して何も出力しない．

  知られているバグやTODO : 本関数は、標準エラー出力を使用して出力するため、
標準エラー出力の利用できないWin32GUI環境の場合、
本関数の呼びだしは無意味となる。

  See also : <a href="#vce_init_array">vce_init_array</a>
<a name="vce_snprintf"></a>
- <B>vce_snprintf</B>

  概要 : libc の snprintf の wrapper

  カテゴリ : text

  関数プロトタイプ : ```void vce_snprintf( char *out, int len, const char *format, ... )``` 

  - arg 1 : ```char *out```
    文字列を出力するバッファの先頭アドレス

  - arg 2 : ```int len```
    バッファの長さ

  - arg 3 : ```char *format```
    フォーマット文字列

  返り値 : なし

  詳細説明 : UNIX のlibc(glibc) に含まれている snprintf は、
UNIX 以外の環境では、異なるインターフェイスを持っていたり、
そもそも存在しなかったりする。 snprintf はバッファオーバーフロー攻撃を
防ぐためには必要不可欠な関数なので、 VCE ではこれらのプラットフォームの
コードを安全にするために、 vce_snprintf を使うことを推奨する。

  知られているバグやTODO : linux,win32 以外の環境においてはこの関数は
sprintf と同等の機能しか持っていない．
(バッファ管理のミスによりバッファーオーバーフロー攻撃される可能性がある)。
そのためアプリケーション側で対処する必要がある．


<a name="vce_strerror"></a>
- <B>vce_strerror</B>

  概要 : VCEエラーコードを文字列に変換する。

  カテゴリ : err

  関数プロトタイプ : ```char *vce_strerror( int ecode );``` 

  - arg 1 : ```int ecode```
    エラーコード。 vce.h で定義されている。

  返り値 : 文字列へのポインタ。

  詳細説明 : vce.h に定義されているエラーコードを，同様に定義されている
文字列に変換する．
サイレントモードでコンパイルされているVCEの場合は，
本関数は空の文字列を返すし，LAST_ERROR に VCE_ESUPPORTを設定する．

  See also : <a href="#vce_get_last_error">vce_get_last_error</a>
<a name="vce_strerror_close_reason"></a>
- <B>vce_strerror_close_reason</B>

  概要 : VCEエラーコード(CLOSE_REASON)を文字列に変換する。

  カテゴリ : err

  関数プロトタイプ : ```char *vce_strerror_close_reason( CLOSE_REASON reason );``` 

  - arg 1 : ```CLOSE_REASON reason```
    CLOSE_REASON エラーコード。 vce.h で定義されている。

  返り値 : 文字列へのポインタ。

  詳細説明 : vce.h に定義されているエラーコード(CLOSE_REASON)を，同様に定義されている
文字列に変換する．
サイレントモードでコンパイルされているVCEの場合は，
本関数は空の文字列を返す．


<a name="vce_tcpcontext_cleanup"></a>
- <B>vce_tcpcontext_cleanup</B>

  概要 : TCPコンテキストを解放する。

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_cleanup( tcpcontext_t tp )``` 

  - arg 1 : ```tcpcontext_t tp```
    解放するTCPコンテキストへのポインタ。 vce_tcpcontext_createの返り値である。
サーバーコンテキストもクライアントコンテキストも同様に解放できる。

  返り値 : なし

  詳細説明 : VCEライブラリ中に保存されているTCPコンテキストの構造体を1個解放する。
VCEライブラリが管理できる tcpcontext 構造体の数は制限があるので、
vce_tcpcontext_cleanup 関数で解放せずに vce_tcpcontext_create を
くりかえすと、資源が足りなくなり VCE_EFULL を返すようになる。

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_conn_iterate"></a>
- <B>vce_tcpcontext_conn_iterate</B>

  概要 : tcpcontext が保持しているすべてのconn_tに対して関数で処理する

  カテゴリ : 

  関数プロトタイプ : ```int vce_tcpcontext_conn_iterate( tcpcontext_t tt, int (*f)(conn_t c))``` 

  - arg 1 : ```tcpcontext_t tt```
    処理したい tcpcontext_t

  - arg 2 : ```int (*f)(conn_t c)```
    各要素に対して呼びだされるコールバック関数

  返り値 : 引数が不正などの場合は負のエラーコード、正常終了の場合はゼロを返す

  詳細説明 : コールバック関数の引数には、コネクション(conn_t)の各要素が与えられる。
コールバック関数が負を返すとループを途中で終了する。
0以上の値を返すとループを継続する．

  See also : <a href="#vce_tcpcontext_get_all_connection">vce_tcpcontext_get_all_connection</a>
<a name="vce_tcpcontext_connect"></a>
- <B>vce_tcpcontext_connect</B>

  概要 : リモートにあるVCEサーバに接続し、TCPコネクションを1個確立する。

  カテゴリ : tcp

  関数プロトタイプ : ```conn_t vce_tcpcontext_connect( tcpcontext_t tp, const char *hostname, unsigned short port );``` 

  - arg 1 : ```tcpcontext_t tp```
    設定情報を格納しているTCPコンテキスト。

  - arg 2 : ```char *hname```
    どのホストに接続するのか、IPアドレスを名前か番号で指定する。

  - arg 3 : ```unsigned short port```
    上記で指定したホストのどのポートに接続するのかを指定する。

  返り値 : 成功なら新しくTCPコンテキストの中に割りあてられたコネクション管理
構造体(conn_t)を返す。
失敗なら無効なconn_tを返す。
無効かどうかを知るには vce_conn_is_valid 関数を使用する。
エラーの内容を得るには、
vce_get_last_error を使う。

  詳細説明 : 言うまでもなくconnectはクライアントソケットにだけ許された機能なので、
クライアントコンテキストの場合のみ利用可能である。
また vce_tcpcontext_connect 関数は、内部で conn_t を1個割りあてて初期化
するときに tcpcontext_t から、parser と callback の情報をコピーするので、
vce_tcpcontext_connect の呼びだし以前に vce_tcpcontext_set_parser を
呼びだしておく必要がある。
なお，クライアントから connect をするときには，
tcpcontext がノンブロッキングモードに設定されている場合と，
そうでない場合で成功確認方法が異なる．
これについては<a href="connect.html">クライアントからの接続</a>
を参照．

  使用例 : <pre>
  t = vce_tcpcontext_create( 0, ... );
  conn_t connection = vce_tcpcontext_connect( t,  "www.ce-lab.net", 80 );
</pre>

  See also : <a href="#vce_conn_is_valid">vce_conn_is_valid</a><a href="#vce_conn_writable">vce_conn_writable</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_count_connections"></a>
- <B>vce_tcpcontext_count_connections</B>

  概要 : tcpcontext に属するコネクションの数を数える

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_tcpcontext_count_connections( tcpcontext_t t, int *conn )``` 

  - arg 1 : ```tcpcontext_t t```
    数を調査したい対象となる tcpcontext

  - arg 2 : ```int *conn```
    conn_t コネクションの数を返すためのバッファの先頭アドレス．
NULL を指定すると，無視される．

  返り値 : 正常終了ならばゼロ，そうでないならば負のエラーコードを返す．

  詳細説明 : 1個の tcpcontext が管理しているコネクションの数を数える．

  See also : <a href="#vce_tcpcontext_get_all_connection">vce_tcpcontext_get_all_connection</a>
<a name="vce_tcpcontext_create"></a>
- <B>vce_tcpcontext_create</B>

  概要 : TCPコンテキストを初期化する。

  カテゴリ : tcp

  関数プロトタイプ : ```tcpcontext_t vce_tcpcontext_create( int flag, const char *bindaddr, unsigned short port, int maxcon, size_t rblen, size_t wblen, int timeout, VCE_BLOCK_CIPHER cipher, int shkeylen , int nonblock_connect, int nodelay, size_t statebuf_size )``` 

  - arg 1 : ```int flag```
    TCPcontext の基本的性質を設定するフラグ。
1にするとIPv4のサーバーコンテキスト、0にするとクライアントコンテキストになる。

  - arg 2 : ```char *bindaddr```
    ソケットを bindするIPアドレス。クライアントの場合もサーバーの場合も、
通常は "0.0.0.0"を指定すれば十分である。
特定のアドレスからのみ接続を受けいれたい場合は、IPアドレスを指定する。
例： "192.168.1.11"

  - arg 3 : ``` unsigned short port```
    ソケットをbindするポート番号。
1024より小さくするためにはroot権限が必要である(UNIX)。
VCEを用いたアプリケーションの場合は、
7000よりも大きい適当な番号にしておけば問題ない。

  - arg 4 : ```int maxcon```
    最大接続数。VCEはOSの限界までの接続数をサポートするが、
この引数によってVCEが接続を許す本数をそれより小さい本数に制限する
ことができる。この制限は、アクセス不能攻撃を防ぐためには有効である。
ちなみに、OSの限界値は、Linuxでは1000本程度、
win32ではメモリ次第もしくは64本である。
どちらもある程度チューニングが可能である。<BR>
ただし、チューニングして非常に多くのコネクション(2000本以上とか)を
1マシンで同時に使うのは性能やセキュリティの面で薦められない。<BR>
この引数の限界は存在しないが、 VCE は vce_initialize 時に、
前もって最大のコネクション数を決めてから各 tcpcontext_t に割りふるように
なっているので、たとえば maxcon に 1200 を指定しても 1000 本のコネクション
しか割りあてられない(Linuxでのデフォルト限界値は1000)。
この場合は、 vce_initialize_limited 関数を使用して、
最大接続限界をそれより大きな値にしてやることが必要である。

  - arg 5 : ```size_t rblen```
    ネットワークからの読みこみバッファの最大長。
この最大長は、1個のTCPコネクションの読みこみバッファの長さである。

  - arg 6 : ```size_t wblen```
    書きこみバッファの数。

  - arg 7 : ```int timeout```
    接続のタイムアウト時間(秒)。
一定時間、あるTCPコネクションに対して書きこみも読みこみもしなかった
場合、自動的にコネクションを切断する(shutdown/close).
これをタイムアウトという。タイムアウトした後にそのコネクションに
書きこみしようとした場合は、エラーが返る。

  - arg 8 : ```VCE_BLOCK_CIPHER cipher```
    暗号化コネクションを利用したい場合は、
VCE_BLOCK_CIPHER_BLOWFISH,VCE_BLOCK_CIPHER_RIJNDAEL,VCE_BLOCK_CIPHER_TWOFISH
のいずれかの値を指定する。利用しない場合は、
VCE_BLOCK_CIPHER_NONE を指定する。
暗号強度と性能に関しては<a href="bench.html">こちら</a>を参照.

  - arg 9 : ```int shkeylen```
    共有鍵の長さ。鍵交換の結果、サーバとクライアントがコーディングキーとして
使う鍵の長さを指定する。この鍵が長いほど、
暗号解読攻撃に対する耐性が強い。<BR>
VCE_BLOCK_CIPHER_BLOWFISH を使う場合は、4以上56以下の値を指定する。<BR>
チャットやゲームアプリケーションなどでは8を指定すれば十分である。<BR>
VCE_BLOCK_CIPHER_RIJNDAEL を使う場合は、16,24,32 のいずれかを指定する。<BR>
チャットやゲームアプリケーションなどでは16を指定すれば十分である。<BR>
VCE_BLOCK_CIPHER_TWOFISH を使う場合は、16,24,32 のいずれかを指定する。<BR>
チャットやゲームアプリケーションなどでは16を指定すれば十分である。  <BR>
デコードとエンコードのための時間は、キーの長さの1乗に比例して長くなる。<BR>


  - arg 10 : ```int nonblock_connect```
    nonblock_connect は、クライアントコンテキスト専用で、
新しくconnect()システムコールを用いて接続を構築するときに、
TCPコネクションが完成するまでブロックするかどうかを指定する。
1だとブロックしない(nonblock)、0だとブロックする。
ブロックするようにすれば、
アプリケーションのプログラムを多少単純にすることができる。
ただし，VCEのアプリケーション開発においては，
「ノンブロッキング接続」が推奨される．
ゲームクライアントなどのアプリケーションにおいては，
確実にノンブロッキングモードを使用するべきである．
この理由については，<a href="connect.html">クライアントの接続について</a>
が参考になるだろう．

  - arg 11 : ```nodelay```
    ソケットに対してTCP_NODELAY オプションを使うかどうかを指定する。
nodelayを1にすると TCP_NODELAY オプションをつけ、0にすると付けない。
TCP_NODELAYオプションによって、OSがTCPパケットをネットワークに送りこむ
までの溜め時間が短かくなる。(Negelアルゴリズムのキャンセル)
ただし、小さなパケットを連続で送る場合は、
ネットワーク利用効率が下がるので注意が必要である。
特に小さなパケットを高速にやりとりしたい場合以外は、0にするべきである。

  - arg 12 : ```size_t statebuf_size```
    状態をもつプロトコルの場合、この引数に0より大きい値を指定し、
状態管理のための領域をVCEに管理させることができる。
vce_conn_get_state 関数を使用することにより、
状態管理領域へのポインタを取得することができる。

  返り値 : 成功したら TCPコンテキストへのポインタを返す。
失敗したらヌルポインタを返す。

  詳細説明 : TCPコンテキストの実体をVCE内部に(128個まで)初期化し、
通信に必要なすべての初期化を行なう。
この関数が返す tcpcontext_t 型は、今後の処理
(現在は vce_tcpcontext_cleanupのみ)で使用する。
VCE は vce_tcpcontext_connect など新規コネクションを初期化するような
処理をするときに tcpcontext_t の設定をコピーして使用するため、
vce_tcpcontext_connect の後に vce_tcpcontext_set_??? のような関数を
使って設定を変更しても、
connect で得られたコネクションには設定が反映されない。
したがってコーディング時には、できるだけ tcpcontext の設定は
vce_tcpcontext_create の直後に集中させるようにすることが大切である。
またブロック暗号を使用する場合は、
8バイトや16バイトといったブロックの長さに丸めて通信されるので、
短かいデータを送信する場合は、限界性能に微妙に影響が出る場合がある。
ただし TCP のヘッダが40バイトあることを考えると、
その部分に凝るのはそれほど意味があるとは思えない。
<BR>
<B>送受信バッファを小さくするときの注意</B><BR>
メモリが少ない環境において，使用メモリを極限まで節約するために，
tcpcontext の「受信バッファ量」と「送信バッファ量」
を小さくしたいことは多い．
ところが，このふたつの量を小さくしていくと，
様々な問題が起こり得る．
「送信バッファ」に関しては，
1回のプロトコル送信で送信したい量よりも小さくすると，
その送信が失敗するので，アプリケーションが1回のプロトコルで送りたい
量を下回らないようにする必要がある．
「受信バッファ」に関しても同様だが，
暗号を使う場合に独特の注意点がある．
それは，VCEは，heartbeatが呼びだされてから次の heartbeat
が呼びだされるまでの間に conn_write された
データに関しては，ひとつにまとめて暗号化することがある点だ．
たとえば，次のheartbeat呼びだしまでの期間に，
サーバーが1KBのデータを20回送ると， 20KBが1個の塊として暗号化され，
クライアントの読みこみバッファが10KBしかなかったとすると，
そのバッファを使って暗号を解読することができなくなる．
暗号解読は読みこみバッファの空きを使って処理されるからである．
ちなみに，暗号化の最大パックサイズは32KBバイトなので，
受信側の読み込みバッファが32KB+8以上あれば，
どんな場合でも間違いなく暗号を解読できる．
送信する速度と，
受信側の読みこみバッファの量は，関係があるのである．
したがって，「バルク転送をしたい場合は，
受信側に十分な(32KB以上の)読みこみバッファを用意せよ．」
ということになる．

  使用例 : <pre>
  #include "vce.h"

  int my_callback( conn_t ct, char *data , int len )
  {
      データ処理。
      if( 正常修了 ) return 0;  else return -1;
  }

  int main( int argc, char **argv )
  {
      tcpcontext_t *t = vcetcpcontext_create(
      1,      // サーバ
      6667,   // ポート 6667
      10,     // 最大接続数
      1024, 1024,  // 読み書きバッファー長
      60 * 60,   // 1時間で接続タイムアウト
      VCE_BLOCK_CIPHER_BLOWFISH,   // 暗号を使用
      8,         // 8バイト(64ビット)の鍵を使用
      0,         // ブロッキング
      0,         // NODELAY は指定しない
      0          // 状態のないプロトコル
      );
      ...
  }
</pre>

  See also : <a href="#vce_conn_get_state">vce_conn_get_state</a><a href="#vce_initialize">vce_initialize</a><a href="#vce_initialize_limited">vce_initialize_limited</a><a href="#vce_tcpcontext_cleanup">vce_tcpcontext_cleanup</a><a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a><a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a><a href="#vce_tcpcontext_set_conn_closewatcher">vce_tcpcontext_set_conn_closewatcher</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_tcpcontext_enable_accept"></a>
- <B>vce_tcpcontext_enable_accept</B>

  概要 : 新規に accept しないようにする

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_enable_accept( tcpcontext_t tp, int flag )``` 

  - arg 1 : ```tcpcontext_t tp```
    操作対象となるTCPcontext

  - arg 2 : ```int flag```
    1にすると今後も新規に accept する。
0にすると今後は accept しない。

  返り値 : なし

  詳細説明 : サーバを人為的に終了させるときなどに、
新たなユーザがログインしてこないように、
新規に accept しないようにしたいことがある。
本関数はそのために使用する。
verbose モードのときはログを出力する(verbose mode only)。

  See also : <a href="#vce_tcpcontext_close_all_conn">vce_tcpcontext_close_all_conn</a>
<a name="vce_tcpcontext_get_all_connection"></a>
- <B>vce_tcpcontext_get_all_connection</B>

  概要 : tcpcontext に属するすべてのコネクションを得る

  カテゴリ : tcp

  関数プロトタイプ : ```int vce_tcpcontext_get_all_connection( tcpcontext_t t , conn_t *a, int max);``` 

  - arg 1 : ```tcpcontext_t t```
    処理対象のtcpcontext

  - arg 2 : ```conn_t *a```
    配列を出力する先頭アドレス

  - arg 3 : ```int max```
    配列の最大要素数

  返り値 : 配列を埋めた数を返す(0以上の値)。

  詳細説明 : ひとつのtcpcontext に属するコネクションを配列にコピーして出力する。

  See also : <a href="#vce_tcpcontext_count_connections">vce_tcpcontext_count_connections</a>
<a name="vce_tcpcontext_get_stat"></a>
- <B>vce_tcpcontext_get_stat</B>

  概要 : tcpcontext の統計情報を取得する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_get_stat( tcpcontext_t tp, tcpcontext_stat_t *s )``` 

  - arg 1 : ```tcpcontext_t tp```
    情報を取得する tcpcontext

  - arg 2 : ```tcpcontext_stat_t *s```
    情報を格納するための構造体(tcpcontext_stat_t)の先頭アドレス

  返り値 : なし

  詳細説明 : TCPコンテキストが内部的に管理している統計情報を取得する。
この情報はデバッグやログなど幅広く活用される。
以下はtcpcontext_stat_t構造体メンバの説明である。
<ul>
<LI>current_conn<BR>
現在活動中のコネクションの数。 
<LI>recv_byte, send_byte<BR>
合計の送受信バイト数
<LI>recv_syscall, recv_syscall_e<BR>
recv()システムコールの呼びだし回数。 _e はエラー呼びだしの回数
<LI>accept_syscall, accept_syscall_e, send_syscall, send_syscall_e,
connect_syscall, connect_syscall_e<BR>
各システムコールの呼びだし回数。
<LI>conn_write<BR>
vce_conn_write の呼びだし回数
<LI>conn_timeout<BR>
conn_t がタイムアウトした回数。
<LI>tcpcontext_connect<BR>
vce_tcpcontext_connect が成功した回数。
</ul>

  See also : <a href="#vce_conn_get_stat">vce_conn_get_stat</a><a href="#vce_get_stat">vce_get_stat</a>
<a name="vce_tcpcontext_protocol_set_maxlength"></a>
- <B>vce_tcpcontext_protocol_set_maxlength</B>

  概要 : パーサーが分割する最大の長さを設定する。

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_protocol_set_maxlength(tcpcontext_t ct,int maxlength,int(*errcall)(conn_t ct))``` 

  - arg 1 : ```tcpcontext_t t```
    設定情報を格納しているTCPコンテキスト。

  - arg 2 : ```int max_length```
    分割する最大のレコード長。

  - arg 3 : ```int(*errcall)(conn_t ct))```
    制限に達した時に呼ばれるコールバック関数。負の値を返せば接続を拒否できる。
NULLの場合は呼ばれず接続を拒否する。

  返り値 : 無し

  詳細説明 : 　ストリームからレコード単位に分割するときに
先頭に格納されてる長さの情報を受信したときにチェックする。
プログラムがクラックされ、異常に長いレコードを連続で受信し、バッファや帯域を
圧迫させる行為を防ぐ事が出来る。

  知られているバグやTODO : TODO 現在は16bitパーサーでしかチェックしていない。


<a name="vce_tcpcontext_set_accept_max"></a>
- <B>vce_tcpcontext_set_accept_max</B>

  概要 : 一分間あたりの接続数を制限する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_accept_max(tcpcontext_t t,int con_max,int (*accept_warning)(tcpcontext_t t))``` 

  - arg 1 : ```tcpcontext_t t```
    設定情報を格納しているTCPコンテキスト。

  - arg 2 : ```int con_max```
    一分間で許容する最大の接続数

  - arg 3 : ```int (*accept_warning)(tcpcontext_t t)```
    制限に達した時に呼ばれるコールバック関数。負の値を返せば接続を拒否できる。
NULLの場合は呼ばれず接続を拒否する。

  返り値 : 無し

  詳細説明 : DDoS対策として接続数を制限するときに使う関数。
接続が来てVCE内のあらゆる処理をする前に判断されるので
低負荷でブロックする事ができる。（conn構造体も作られない）
設定した制限値が10だとすれば10本までは接続を通し、
その後は6秒毎に一本ずつ許可数が増えていくようになっている。
con_maxにゼロを設定すれば許可無しとなる。

  使用例 : <pre>
  //一分間で10本の接続を許可する
  vce_tcpcontext_set_accept_max(t,10,0);
</pre>


<a name="vce_tcpcontext_set_conn_acceptwatcher"></a>
- <B>vce_tcpcontext_set_conn_acceptwatcher</B>

  概要 : TCPコンテキストに対して、指定されたaccept監視関数を使うように設定する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_conn_acceptwatcher( tcpcontext_t tp, int (*aw)(conn_t) )``` 

  - arg 1 : ```tcpcontext_t tp```
    設定対象となるTCPコンテキスト

  - arg 2 : ```int (*aw)(conn_t c)```
    accept監視関数。conn_t cには、新規に受けいれられようとしている
コネクションが入る。

  返り値 : なし

  詳細説明 : サーバーコンテキストが新しい接続を受けいれたときに、
この関数が1回呼びだされる。
アプリケーション開発者はこの関数を置きかえることによって、
接続を受けいれた場合にログを出力したり、アドレス制限をかけたりできる。
このコールバック関数が負を返すと、
VCEは接続受けいれ拒否と判断し、closeする。
暗号化コネクションを使用しているときは、暗号ネゴシエーションが終了してから、
acceptwatcher が呼びだされる。

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_closewatcher">vce_tcpcontext_set_conn_closewatcher</a>
<a name="vce_tcpcontext_set_conn_call_parser_per_heartbeat"></a>
- <B>vce_tcpcontext_set_conn_call_parser_per_heartbeat</B>

  概要 : 1回の heartbeat で各コネクションのパーサが呼びだされる回数を調整する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_conn_call_parser_per_heartbeat( tcpcontext_t tt, int v )``` 

  - arg 1 : ```tcpcontext_t tt```
    設定対象の tcpcontext_t

  - arg 2 : ```int v```
    回数(0以上)．負を指定したときの動作は不定．

  返り値 : 
  詳細説明 : デフォルトの状態では、プロトコル・パーサは、 vce_heartbeat 関数の中で、
ネットワークからの入力を確認して1レコード分の情報がそろっている事が
確認されると、1回だけコールバック関数を呼びだす。
本関数を使ってその最大回数を制御することができる．
引数 v で指定した回数まで， 1回の heartbeat で複数回のコールバックが
呼びだされるようになる．
本関数は，クライアントおよびサーバーの性能チューンにおいてまず
注目される点である．

  See also : <a href="#vce_heartbeat">vce_heartbeat</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_tcpcontext_set_conn_closewatcher"></a>
- <B>vce_tcpcontext_set_conn_closewatcher</B>

  概要 : TCPコンテキストに対して、指定されたclose監視関数を使うように設定する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_conn_closewatcher( tcpcontext_t tp, int (*cw)(conn_t,CLOSE_REASON) )``` 

  - arg 1 : ```tcpcontext_t tp```
    設定対象となるTCPコンテキスト

  - arg 2 : ```int (*cw)(conn_t c, CLOSE_REASON reason)```
    close 監視関数。conn_t c には、閉じられようとしているコネクションが入る。
reason には， CLOSE_REASON 列挙体で定義されている定数が代入される．

  返り値 : なし

  詳細説明 : 何らかの理由で接続がcloseされてしまったときに1回だけ呼びだされる関数。
VCEではこのように呼びだされる関数は close watcher と呼ばれる。
アプリケーション開発者がこの関数本体を定義する
ことによって、ソケットが閉じられたことをログしたりできる。
close watcher は呼びだされるときの原因に応じて reason 引数に，
何が原因だったのかをあらわす定数が代入される．
アプリケーションではこの値をみて，closeの原因を推定できる．
reason の内容は，以下の通りである．
以下ではそれぞれを
「リモート型」と「ローカル型」に分けて，
問題を迅速に切りわけられるようにした．

<ul>
<LI>CLOSE_REASON_NONE (-1)<BR>
VCEが内部的に使用する．これが返されるのは， VCE のバグが考えられる．

<LI>CLOSE_REASON_UNKNOWN (0)<BR>
原因不明．基本的に返されることはない．
返された場合は，VCEのバグが考えられる．

<LI>CLOSE_REASON_REMOTE (1)<BR>
リモートピアによってコネクションが切断されたため，
書きこみも読みこみもできなくなった．
CLOSE_REASON_REMOTE は，リモート型の中で，特に分類できなかった場合の
generic な理由のときに返される．

<LI>CLOSE_REASON_APPLICATION (2)<BR>
アプリケーションによって， vce_conn_close などが呼びだされた．
「ローカル型」の典型的なクローズ理由である．

<LI>CLOSE_REASON_TIMEOUT (3)<BR>
タイムアウト時間になるまで，送受信が行われなかったため，
切断された．タイムアウトの場合は，リモートが原因なのか，
ローカルが原因なのか，判別はつかない．

<LI>CLOSE_REASON_DECODER (4)<BR>
暗号デコーディング関数の内部でエラーが起きた．
相手から送られてきたデータのフォーマットが異常であるか，
データレコードが必要としている分のデータが届かない間にコネクションが
利用不可能になってしまった場合に起こる．
つまり，このエラーは，「リモート型」である．
このエラーは，コネクション初期化時の暗号ネゴシエーションが終わり，
データの交換が始まってから起こる．

<LI>CLOSE_REASON_ENCODER (5)<BR>
暗号エンコーディング関数の内部でエラーが起きた．
このエラーは，コネクション初期化時の暗号ネゴシエーションが終わり，
データの交換が始まってから起こる．
VCE は暗号化用に特別なメモリを使わないこともあり，この理由は
「リモート型」である．


<LI>CLOSE_REASON_PARSER (6)<BR>
プロトコルパーサー関数が負の値を返したので，
コネクションを切断した．
これは，ローカル型である．ローカルのパーサー関数の返り値が負であった．

<LI>CLOSE_REASON_INTERNAL (7)<BR>
VCE の内部的な問題により，コネクションを閉じた．
VCEの内部メモリが足りない場合や，エラーチェックに
失敗した場合や，VCEのバグが考えられる．
ローカル型である．

<LI>CLOSE_REASON_FULL (8)<BR>
SWPを使っている場合に，SWPへ送る送信バッファが一杯になっている場合に
この値になる．SWPへ送る送信バッファが一杯ということは，
SWPのサーバーからの受信バッファも一杯になっている可能性が高い．
SWPのバッファー容量を大きくするか，
相手むけ回線の容量が一杯になっていることを疑うべきである．
リモートホストのバッファが一杯になっていることから，
「リモート型」と言える．

</ul>

<BR><BR>
現在、コールバック関数の返り値は無視される。
close watcher は，すでに完成しているコネクションに対してだけ呼びだされる．
言いかえれば，暗号化コネクションを使用しているときに、
暗号ネゴシエーションが終了する前にコネクションが切断された場合、
close watcher は呼びだされない．
その場合でも、 fainalizer は呼びだされる。
<BR>
なお，close watcher の引数はVCE バージョン 0.4.73 から追加されたが，
過去のバージョンの close watcher を渡してもコンパイラ警告が出るだけで
問題は起きない．

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a>
<a name="vce_tcpcontext_set_conn_finalizer"></a>
- <B>vce_tcpcontext_set_conn_finalizer</B>

  概要 : TCPコンテキストに対して、コネクションのファイナライザを指定する。

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_conn_finalizer( tcpcontext_t tp , void *finalizer(conn_t) )``` 

  - arg 1 : ```tcpcontext_t tp```
    ファイナライザを指定するTCPコンテキストのポインタ

  - arg 2 : ```void *finalizer(conn_t to_be_finalized )```
    ファイナライザ関数へのポインタ。 to_be_finalized は、
解放されようとしているコネクションをあらわす。

  返り値 : なし

  詳細説明 : TCPコンテキストが管理しているTCPコネクションが解放されようとしているときに
1回だけ呼びだされるファイナライザを指定する。
これは、Rubyなど高級言語でTCPのコネクションをガベージコレクタに追跡
させたいときなどに有用である。vce_tcpcontext_create 関数を呼びだして
tcpコンテキストを初期化した後に呼びだすこと。
この関数は主にRubyやJavaなど、他の言語用のwrapperライブラリのために
用意されている。アプリケーションからは、closewatcher を使うので十分である。
注意点としては、暗号化コネクションを使用しているときに、
暗号ネゴシエーションが終了する前にコネクションが切断された場合に、
closewatcher は呼びだされないが、 finalizer は呼びだされる点である。

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_set_conn_hiwater_acceptwatcher"></a>
- <B>vce_tcpcontext_set_conn_hiwater_acceptwatcher</B>

  概要 : TCPコンテキストに，接続数が多いとき用のaccept監視関数をセットする

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_conn_hiwater_acceptwatcher( tcpcontext_t tp, int water, int (*aw)(conn_t,int))``` 

  - arg 1 : ```tcpcontext_t tp```
    設定対象となるTCPコンテキスト

  - arg 2 : ```int water```
    高水位を指定する値．この値以上の数の同時接続が，
ひとつのTCPcontextに対して存在している場合は，
通常の acceptwatcher ではなく，
本関数で設定する専用のacceptwatcherを呼びだすようにする．

  - arg 3 : ```int (*aw)(conn_t c,int num)```
    設定する監視関数(高水位接続監視関数)．通常のものとは異なり，
現在何個の接続が存在しているのかを num で受けとることができる．
あらかじめ設定されている最大接続数と比較することで，
システムにあとどれぐらいの余裕があるのかを知ることができる．

  返り値 : なし

  詳細説明 : サーバーコンテキストが新しい接続を受けいれたときに，
同時接続数がある数以上の場合に，
指定した接続監視関数を呼びだすように設定する．
VCEでは，この数のことを「高水位設定値」"high water"と呼んでいる．
この機能を使うことによって，サーバーが混雑しているときに，
ユーザーが単に接続できないようになるのではなく，
「現在混雑しています．」などといったメッセージを送信することが可能となる．
たとえば，絶対的最大数が1000に設定されているゲームサーバーの場合は，
900あたりにこの値(water)を設定しておき，
900本目以降の接続に関してはここで設定した専用の監視関数を使うことで，
独自のプロトコルシーケンスを発行することができる．
高水位接続監視関数が呼びだされた場合は，
通常の接続監視関数は呼びだされない.
また高水位接続監視関数の返り値は，通常の接続監視関数の返り値と同様に
扱われる．つまり，負を返すと接続を拒否する．

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a>
<a name="vce_tcpcontext_set_conn_kickip_array"></a>
- <B>vce_tcpcontext_set_conn_kickip_array</B>

  概要 : 接続を拒否するIPアドレスの配列を設定する。

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_conn_kickip_array(tcpcontext_t tp,unsigned int *null_terminated_ipaddr_array)``` 

  - arg 1 : ```tcpcontext_t t```
    設定情報を格納しているTCPコンテキスト。

  - arg 2 : ```unsigned int *null_terminated_ipaddr_array```
    ０終端されたIPアドレスへのリスト。

  返り値 : 無し

  詳細説明 : 拒否するIPアドレスをひとつずつ大量に設定したいときに使う。
配列はunsigned intのそのままIPv4アドレスで、配列の先頭のアドレスを渡すだけで
0.0.0.0がくるまで全部とチェックする。Accept後他の処理が入る前にすぐチェックされるので
低負荷で蹴る事が出来る。


<a name="vce_tcpcontext_set_conn_parser"></a>
- <B>vce_tcpcontext_set_conn_parser</B>

  概要 : TCPコンテキストに対して、TCPコネクション(conn_t)用のパーサを設定する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_conn_parser( tcpcontext_t tp, int (*parser)(conn_t),int (*pcallback)(conn_t,char*,int))``` 

  - arg 1 : ```tcpcontext_t tp```
    設定対象となる TCPコンテキスト

  - arg 2 : ```int (*parser)(conn_t c )```
    パーサ関数へのポインタ

  - arg 3 : ```int (*pcallback)(conn_t c,char *data, int len )```
    パーサ関数がレコードを取りだしたときに、そのレコードを与えてよびだす
コールバック関数

  返り値 : なし

  詳細説明 : 通常のTCPコネクション(conn_t)からの入力をパースしてレコードを取りだす
パーサ関数を指定する。VCEでは、
レコード境界を判定してレコードを取りだす方法を挿しかえることができるように、
関数へのポインタを設定できるようになっている。
VCEでは、標準的な方法でレコード境界を判定するためのデフォルトパーサとして、
<pre>
vce_protocol_parser_bin16            標準的なbin16パーサ
vce_protocol_parser_text             改行記号をレコード境界とするパーサ
vce_protocol_parser_through          何も処理せず、そのまま渡すパーサ
</pre>
以上の2つのパーサを実装しているので、通常のアプリケーションでは、
これらのパーサを利用すればよい。
また、 pcallback はパーサによって呼びだされるコールバック関数で、
引数として data, len を用いてレコードの中身(レコード境界を除く)
を与える。これも単純なものはVCEに標準添付されていて、
<pre>
vce_protocol_pcallback_echo_bin16    bin16でエコーするコールバック
vce_protocol_pcallback_echo_text     改行レコードでエコーするコールバック
vce_protocol_pcallback_noop          データを捨てるコールバック
vce_protocol_pcallback_dump          データを表示するコールバック
</pre>
が利用できる。
通常はユーザーがアプリケーションごとにコールバック関数を定義し、
その関数でデータを適切に処理する。
コールバック関数が負を返したら、VCEはプロトコルエラーと判断し、
TCPコネクションを自動的に切断する。
コールバック関数がゼロ以上を返すと，正常終了と見なすが，
vce_tcpcontext_set_conn_call_parser_per_heartbeat 関数を使って
1回の heartbeat あたりの最大コールバック呼びだし回数を変更している場合，
ゼロとそれ以上の値では意味が異なる．
詳細は  vce_tcpcontext_set_conn_call_parser_per_heartbeat
関数のリファレンスを参照．
<BR><BR>
また、パーサを自前で定義するようなアプリケーションの場合
(bin16でもbin32でもtextでもなく、まったく新しいプロトコルを定義したい場合)
はパーサ関数を自前で定義してこの関数でパーサとして設定することになる。
その場合はコールバックを使用することができないため、
<pre>
vce_tcpcontext_set_conn_parser( t, parser, NULL );
</pre>
のようなコーディングをすることになる。


  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_call_parser_per_heartbeat">vce_tcpcontext_set_conn_call_parser_per_heartbeat</a>
<a name="vce_tcpcontext_set_equal_io_splitrate"></a>
- <B>vce_tcpcontext_set_equal_io_splitrate</B>

  概要 : 1回の heartbeat でネットワークへの送信をするコネクション数を調整する

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_set_equal_io_splitrate( tcpcontext_t tt, int v )``` 

  - arg 1 : ```tcpcontext_t tt```
    設定対象となる TCPコンテキスト

  - arg 2 : ```int v```
    何回に分けて書きこむかの値(デフォルトは1)

  返り値 : なし

  詳細説明 : vce_heartbeat では，
VCE が確保している書きこみバッファにデータがたまっている場合は
ネットワークへのデータ送信を試みる．
デフォルトでは，1回の vce_heartbeat
内で全てのデータをフラッシュしようとするが，
送信したい量が1回に数百KB?数MBに達する場合などは，
送信データが OS の送信用メモリ
(Linuxの場合は，TCP用に確保されているメモリページ)を溢れさせて，
一部のコネクションの送信パフォーマンスが著しく低下してしまう場合がある．
本関数を使って，
複数回の heartbeat でコネクションをフラッシュするように調整し，
この問題を回避することができる．
ただし，1回の vce_heartbeat にかかる時間が長い場合は，
あるクライアントからみた round-trip query time は長くなる可能性がある．
本関数を使わずに，Linux自体をチューンする解決策もある．
それに関しては <a href="linuxtune.html">linuxtune.html</a> を参照.


<a name="vce_tcpcontext_timeout_control"></a>
- <B>vce_tcpcontext_timeout_control</B>

  概要 : TCPコンテキストのタイムアウト動作方式を設定する。

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_timeout_control( tcpcontext_t tp, int recv_reset, int send_reset )``` 

  - arg 1 : ```tcpcontext_t t```
    設定したいTCPコンテキスト

  - arg 2 : ```int recv_reset```
    クライアントから受信したときにタイムアウトカウンタを初期化するかどうか
のフラグ。通常は1にしておく。

  - arg 3 : ```int send_reset```
    クライアントへ送信が成功したときにタイムアウトカウンタを初期化するかどうか
のフラグ。デフォルトはゼロで、アプリケーションによっては1にする場合もある。

  返り値 : なし

  詳細説明 : VCE は、TCP セッションにおいて一定時間アクセスがないとタイムアウトさせて
closewatcher を呼びだす機能を持っている。
何らかのデータを送信したり受信したときにタイムアウトのためのカウンタを
初期化するが、
この関数では、送信/受信 成功のときに実際にタイムアウトカウンタをゼロに
戻すかどうかの設定ができる。
VCE はデフォルト状態では、recv_reset=1, send_reset=0 となっている。
つまり、送信に成功しても、タイムアウトカウンタをリセットしない。
この事により、クライアントからは、タイムアウト時間内に最低1個は、
パケットが送られて来ないとタイムアウトしてしまう。
VCE がターゲットとしているリアルタイムアプリケーションにおいては、
このような動作がデフォルトであるほうが自然である。
本関数は、滅多に使われることはない。

  使用例 :   vce_tcpcontext_timeout_control( t, 1, 1 );

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_userdata_get_pointer"></a>
- <B>vce_tcpcontext_userdata_get_pointer</B>

  概要 : tcpcontext_tに関連付けたポインタを取り出す

  カテゴリ : tcp

  関数プロトタイプ : ```void *vce_tcpcontext_userdata_set_pointer(tcpcontext_t ct);``` 

  - arg 1 : ```tcpcontext_t ct```
    対象のtcpcontext_t

  返り値 : 
  詳細説明 : 

<a name="vce_tcpcontext_userdata_set_pointer"></a>
- <B>vce_tcpcontext_userdata_set_pointer</B>

  概要 : tcpcontext_tにポインタを関連付ける

  カテゴリ : tcp

  関数プロトタイプ : ```void vce_tcpcontext_userdata_set_pointer(tcpcontext_t ct,void *p);``` 

  - arg 1 : ```tcpcontext_t ct```
    対象のtcpcontext_t

  - arg 2 : ```void *p```
    ポインタ

  返り値 : 
  詳細説明 : tcpcontext_tにある値を付加したいときに使う


<a name="vce_utime_diff"></a>
- <B>vce_utime_diff</B>

  概要 : struct timeval 型の時刻の差分を VCEI64 型で求める

  カテゴリ : util

  関数プロトタイプ : `````` 

  - arg 1 : ```struct timeval *before```
    差分を求める時刻のうち、前のもの。

  - arg 2 : ```struct timeval *after```
    差分を求める時刻のうち、後のもの。

  返り値 : 
  詳細説明 : 時刻の差分をマイクロ秒に換算し、VCEI64 型に変換して返す。
この関数は BSD カーネルの time_diff 関数とまったく同じだが、
32ビットマシンで42億マイクロ秒(420秒)を越える時間を返せるように、
VCEI64型としている。


<!-- make_funcdef end -->
<BR><BR>
Copyright 2000-2005 Community Engine Inc. All rights reserved.
