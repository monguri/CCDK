# VCE-SDK API Reference Manual

## Categories
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

## Function index by name
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

## Category index by name
<!-- make_categoryindex -->
<a name="array"></a>
### array
<p></p>
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
<p></p>
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
<p> Core functions are basic functions for VCE applications.
Major functionality is controlling application's main loop,
VCE initialization, and cleaning up.
  In Win32 environment, winsock initialization is done in
vce_initialize function.
vce_errout_?? functions are designed to output application error log
to file or stdout.
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
<p></p>
Functions:
1. <a href="#vce_get_last_error">vce_get_last_error</a>
1. <a href="#vce_strerror">vce_strerror</a>
1. <a href="#vce_strerror_close_reason">vce_strerror_close_reason</a>

<a name="log"></a>
### log
<p>PENDING
</p>
Functions:
1. <a href="#vce_get_netstat_string">vce_get_netstat_string</a>
1. <a href="#vce_get_stat">vce_get_stat</a>

<a name="parser"></a>
### parser
<p></p>
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
<p></p>
Functions:
1. <a href="#vce_protocol_pcallback_dump">vce_protocol_pcallback_dump</a>
1. <a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a>
1. <a href="#vce_protocol_pcallback_echo_text">vce_protocol_pcallback_echo_text</a>
1. <a href="#vce_protocol_pcallback_noop">vce_protocol_pcallback_noop</a>

<a name="tcp"></a>
### tcp
<p></p>
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
<p></p>
Functions:
1. <a href="#vce_snprintf">vce_snprintf</a>

<a name="util"></a>
### util
<p></p>
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
<p></p>
Functions:
1. <a href="#vce_protocol_acceptwatcher_deny">vce_protocol_acceptwatcher_deny</a>
1. <a href="#vce_protocol_acceptwatcher_noop">vce_protocol_acceptwatcher_noop</a>
1. <a href="#vce_protocol_closewatcher_noop">vce_protocol_closewatcher_noop</a>

## Definition of all functions
<!-- make_funcdef start -->
<a name="ARRAY_SCAN"></a>
- <B>ARRAY_SCAN</B>
Summary : Scan all in-use elements stored in VCE's array.
Category : array
Prototype : ```ARRAY_SCAN( int arraydescriptor, void* pointer )``` 
  - arg 1 : ```int arraydescriptor```
    PENDING

  - arg 2 : ```void *pointer```
    Set address of each array entry to this pointer.

  Return value : This macro returns no value, since this is not used as a function
but as a loop (like C's for statement). 

  Description : When you want to scan all elements in an VCE array,
you can use vce_get_array_object_top function.
First of all, fetch the top element from the in-use list.
And afterwards, use the vce_get_array_object_next function repeatedly,
until it returns NULL.
This macro is made available to avoid complication of such process.
Note that this macro fetches allocated array elements
only-those elements in the in-use list.
Even if 1000 is given as the maximum array size,
it will never repeat the loop if no elements is found.

  Example : <pre>
// Process all allocated elements in an array specified by "memory_ind" 
struct client *c;
ARRAY_SCAN( memory_ind, c ){
  do_something_to_the_structure( c );
}
</pre>

  See also : <a href="#vce_get_array_object_next">vce_get_array_object_next</a><a href="#vce_get_array_object_top">vce_get_array_object_top</a><a href="#vce_init_array">vce_init_array</a>
<a name="ARRAY_SCAN_TYPE"></a>
- <B>ARRAY_SCAN_TYPE</B>
Summary : A variety of ARRAY_SCAN macro fot use in C++ language
Category : array
Prototype : ```ARRAY_SCAN_TYPE( int arraydescriptor void *pointer, typedecl )``` 
  - arg 1 : ```int arraydescriptor```
    Array descriptor of VCE array.

  - arg 2 : ```void *pointer```
    Set address of each array entry to this pointer.

  - arg 3 : ``` typedecl```
    Type of the pointer.

  Return value : None.

  Description : ARRAY_SCAN assigns a void pointer to the pointer variable "pointer".
This leads a compilation error however in C++,
because C++ requires casting when assignning void pointer.
Consequently, the ARRAY_SCAN_TYPE macro is given the pointer variable type. 

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a>
<a name="ELEMENTOF"></a>
- <B>ELEMENTOF</B>
Summary : Get number of elements of a fixed-size array.
Category : util
Prototype : ```int ELEMENTOF(x)``` 
  - arg 1 : ```x```
    Any C array. (Not pointer)

  Return value : Number of elements of the array.

  Description : This macro is actually defined as
<pre>
( sizeof(x) / sizeof((x)[0]) )
</pre>     
 This macro cannot be used for an array allocated by malloc,
 because the size of elements is not determined upon compilation. 

  Example : <pre>
  int hoge[]= {1,2,3,4,5};
  a = ELEMENTOF(hoge);           // numer 5 is in a
</pre>


<a name="FREE"></a>
- <B>FREE</B>
Summary : Release a memory block allocated with MALLOC function.
Category : util
Prototype : ```void FREE( void *p )``` 
  - arg 1 : ```void *p```
    Top address of a memry block which will be freed.

  Return value : None

  Description : This function wrap the standard C free function.
It simply logs invocation records of free.
It prints log message when vce_set_verbose_mode 1.

  See also : <a href="#MALLOC">MALLOC</a><a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>
<a name="GET_16BIT_INT"></a>
- <B>GET_16BIT_INT</B>
Summary : Get 16 bit integer value from buffer
Category : util
Prototype : ```unsigned short GET_16BIT_INT( char *p )``` 
  - arg 1 : ```char *p```
    Top address of source data buffer.

  Return value : Got value (unsigned short)

  Description : ntohs is used internally.
It is mainly used for protocol processing,
though the function group in the bin category should
rather be used for more general purposes.
For the MIPS machine architecture (“PlayStation(R)2”),
VCE implements this macro as a function. 

  See also : <a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_16BIT_NATIVEINT"></a>
- <B>GET_16BIT_NATIVEINT</B>
Summary : Get 16bit integer value from any buffer
Category : util
Prototype : ```short GET_16BIT_NATIVEINT( char *p )``` 
  Return value : Got short value.

  Description :  It does not use ntohs, htons nor others.
A value is copied directly.
For MIPS architecture (“PlayStation(R)2” ),
VCE  implements this macro as a function. 

  See also : <a href="#GET_32BIT_NATIVEINT">GET_32BIT_NATIVEINT</a><a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
<a name="GET_32BIT_INT"></a>
- <B>GET_32BIT_INT</B>
Summary : A macro to get 32bit value from memory buffer.
Category : util
Prototype : ```unsigned int GET_32BIT_INT( char *p )``` 
  - arg 1 : ```char *p```
    Top address of source data.

  Return value : Got value(int)

  Description : ntohl is used internally.
This macro is used for binary protocol analysis, however,
if the binary protocol is implemented within an application,
the bin category function group should be used instead.
For the MIPS machine architecture (“PlayStation(R)2”)
VCE implements this macro as a function. 

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_32BIT_NATIVEINT"></a>
- <B>GET_32BIT_NATIVEINT</B>
Summary : Get 32bit integer value from buffer
Category : util
Prototype : ```int GET_32BIT_NATIVEINT( char *p )``` 
  Return value : Got int value.

  Description : This is a data-fetch macro not using ntohl, htonl nor others.
For MIPS machine architecture (“PlayStation(R)2” ),
VCE implements this macro as a function. 

  See also : <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a><a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
<a name="GET_64BIT_INT"></a>
- <B>GET_64BIT_INT</B>
Summary : A macro to get 64bit value from memory buffer.
Category : util
Prototype : ```VCEI64 GET_64BIT_INT( char *p )``` 
  - arg 1 : ```char *p```
    Top address of source data.

  Return value : Got value(int)

  Description : ntohl is used internally.
This macro is used for binary protocol analysis, however,
if the binary protocol is implemented within an application,
the bin category function group should be used instead.
For the MIPS machine architecture (“PlayStation(R)2”)
VCE implements this macro as a function. 

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_64BIT_NATIVEINT"></a>
- <B>GET_64BIT_NATIVEINT</B>
Summary : Get 64bit integer value from buffer
Category : util
Prototype : ```int GET_64BIT_NATIVEINT( char *p )``` 
  Return value : Got int value.

  Description : This is a data-fetch macro not using ntohl, htonl nor others.
For MIPS machine architecture (“PlayStation(R)2” ),
VCE implements this macro as a function. 

  See also : <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a><a href="#GET_8BIT_NATIVEINT">GET_8BIT_NATIVEINT</a>
<a name="GET_8BIT_INT"></a>
- <B>GET_8BIT_INT</B>
Summary : Get 8-bit integer from buffer
Category : util
Prototype : ```unsigned char GET_8BIT_INT( char *b )``` 
  - arg 1 : ```char *b```
    Top address of source data buffer.

  Return value : Got value (unsigned char)

  Description :  This simply fetches a value.
 It is defined to maintain consistency with 32 and 16 bit macro.

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="GET_8BIT_NATIVEINT"></a>
- <B>GET_8BIT_NATIVEINT</B>
Summary : Get 8bit integer value from buffer
Category : util
Prototype : ```char GET_8BIT_NATIVEINT( char *p )``` 
  Return value : Got 8bit value

  Description : This is defined merely for writing codes consistent with GET_32BIT_NATIVEINT,
GET_16BIT_NATIVEINT and others. 

  See also : <a href="#GET_16BIT_NATIVEINT">GET_16BIT_NATIVEINT</a><a href="#GET_32BIT_NATIVEINT">GET_32BIT_NATIVEINT</a>
<a name="MALLOC"></a>
- <B>MALLOC</B>
Summary : A wrapper function for C library malloc().
Category : util
Prototype : ```void *MALLOC( size_t size )``` 
  - arg 1 : ```size_t size```
    Size of allocated memory ( in bytes)

  Return value : Top address of allocated memory block.

  Description : This calls the malloc() function of the standard C library,
and returns a returned value of malloc as is.
VCE invokes the malloc function only once upon a startup of a program
to allocate a large memory space as possible as it can,
afterwards, it free()s everything upon a cleanup,
not using malloc funcs at all, according to its strategy.
This is because the malloc function is too slow,
or for minimizing variation of behavior due to the
difference in implementation method of the malloc function.
The MALLOC function is used pairing up with the FREE function.
It prints log message when vce_set_verbose_mode 1.

  See also : <a href="#FREE">FREE</a><a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>
<a name="MAX"></a>
- <B>MAX</B>
Summary : Compare 2 integer values and return bigger one.
Category : util
Prototype : ```int MAX(int a, int b)``` 
  - arg 1 : ```int a```
    First parameter being compared.
Although "int" type is used in this macro's prototype,
but because this is macro, so you can make use of this macro
for any types which accepts integer-comparison operator.

  - arg 2 : ```int b```
    Another parameter being compared.

  Return value : Got value ( bigger one )

  Description :  This is defined as follows.
 It corresponds to the char, short, int, long, long long, float, double, and VCEI64
 types along with their unsigned types. 
<pre>
   ( (x) > (y) ? (x)  (y) )
</pre>   

  See also : <a href="#MIN">MIN</a>
<a name="MIN"></a>
- <B>MIN</B>
Summary : Compare 2 integer values and return bigger one.
Category : util
Prototype : ```int MIN(int a, int b )``` 
  - arg 1 : ```int a```
    First parameter being compared.
Although "int" type is used in this macro's prototype,
but because this is macro, so you can make use of this macro
for any types which accepts integer-comparison operator.

  - arg 2 : ```int b```
    Another parameter being compared.

  Return value : Result value.

  Description : This is defined as follows.
It corresponds to the char, short, int, long, long long, float, double, and VCEI64
types along with their unsigned types. 
<Pre>
( (x) < (y) ? (x)  (y) )
</pre>


  See also : <a href="#MAX">MAX</a>
<a name="SET_16BIT_INT"></a>
- <B>SET_16BIT_INT</B>
Summary : Copy 16-bit integer to buffer in network byte-order.
Category : util
Prototype : ```void SET_16BIT_INT( char *b, unsigned short i )``` 
  - arg 1 : ```char *b```
    Top address of destination buffer.

  - arg 2 : ```unsigned short i```
    Native unsignes short value being copied.

  Return value : None

  Description : htons is used internally.
It is mainly used for protocol processing,
though the function group in the bin category should rather be used for
more general purposes.
For the MIPS architecture (“PlayStation(R)2” ),
VCE implements this macro as a function. 

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="SET_16BIT_NATIVEINT"></a>
- <B>SET_16BIT_NATIVEINT</B>
Summary : Copy 16-bit integer value to any buffer
Category : util
Prototype : ```void SET_16BIT_NATIVEINT( char *p, short i )``` 
  - arg 1 : ```char *p```
    Top address of destination buffer.

  - arg 2 : ```short i```
    Native value being copied.

  Return value : None

  Description : This macro is not using ntohs, htons nor others inside it.
For MIPS machine architecture(“PlayStation(R)2”),
VCE implements this macro as a function. 

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="SET_32BIT_INT"></a>
- <B>SET_32BIT_INT</B>
Summary : Copy 32-bit integer to buffer in network byte-order.
Category : util
Prototype : ```void SET_32BIT_INT( char *b, unsigned int i )``` 
  - arg 1 : ```char *b```
    Top address of input data.

  - arg 2 : ```unsigned int i```
    Native int value being copied.

  Return value : None

  Description : htonl is used internally.
For MIPS architecture (“PlayStation(R)2” ),
VCE  implements this macro as a function.
It can be used for protocol analysis,
but you should rather use the function group in the bin
category for protocol analysis( they make it robust ).

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="SET_32BIT_NATIVEINT"></a>
- <B>SET_32BIT_NATIVEINT</B>
Summary : copy 32bit integer value to any buffer
Category : util
Prototype : ```void SET_32BIT_NATIVEINT( char *p, int i )``` 
  - arg 1 : ```char *p```
    Top address of destination buffer.

  - arg 2 : ```int i```
    Native value being copied.

  Return value : None

  Description :  Copy values directly to output buffer without doing htonl, nor htons.
For MIPS machine architecture (“PlayStation(R)2” ),
VCE implements this macro as a function. 

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="SET_64BIT_INT"></a>
- <B>SET_64BIT_INT</B>
Summary : Copy 32-bit integer to buffer in network byte-order.
Category : util
Prototype : ```void SET_64BIT_INT( char *b, VCEI64 i )``` 
  - arg 1 : ```char *b```
    Top address of input data.

  - arg 2 : ```VCEI64 i```
    Native int value being copied.

  Return value : None

  Description : htonl is used internally.
For MIPS architecture (“PlayStation(R)2” ),
VCE  implements this macro as a function.
It can be used for protocol analysis,
but you should rather use the function group in the bin
category for protocol analysis( they make it robust ).

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a><a href="#SET_8BIT_INT">SET_8BIT_INT</a>
<a name="SET_64BIT_NATIVEINT"></a>
- <B>SET_64BIT_NATIVEINT</B>
Summary : copy 64bit integer value to any buffer
Category : util
Prototype : ```void SET_64BIT_NATIVEINT( char *p, VCEI64 i )``` 
  - arg 1 : ```char *p```
    Top address of destination buffer.

  - arg 2 : ```int i```
    Native value being copied.

  Return value : None

  Description :  Copy values directly to output buffer without doing htonl, nor htons.
For MIPS machine architecture (“PlayStation(R)2” ),
VCE implements this macro as a function. 

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="SET_8BIT_INT"></a>
- <B>SET_8BIT_INT</B>
Summary : Copy 8-bit integer to buffer
Category : util
Prototype : ```void SET_8BIT_INT( char *b, unsigned char i )``` 
  - arg 1 : ```char *b```
    Top address of destination buffer.

  - arg 2 : ```unsigned char i```
    unsigned char value being copied.

  Return value : None

  Description :  This only copies onto a buffer, being available for the purpose
of writing well-formed codes,
maintaining consistency with 32 and 16 bit macro or others. 

  See also : <a href="#GET_16BIT_INT">GET_16BIT_INT</a><a href="#GET_32BIT_INT">GET_32BIT_INT</a><a href="#GET_8BIT_INT">GET_8BIT_INT</a><a href="#SET_16BIT_INT">SET_16BIT_INT</a><a href="#SET_32BIT_INT">SET_32BIT_INT</a>
<a name="SET_8BIT_NATIVEINT"></a>
- <B>SET_8BIT_NATIVEINT</B>
Summary : Copy 8bit integer value to any buffer
Category : util
Prototype : ```void SET_8BIT_NATIVEINT( char *p, char i )``` 
  - arg 1 : ```char *P```
    Top address of destiniation buffer.

  - arg 2 : ```char i```
    Native value being copied.

  Return value : None

  Description : This macro is only for writing well-formed codes,
maintaining consistency with SET_16BIT_NATIVEINT,SET_32BIT_NATIVEINT. 

  See also : <a href="#SET_16BIT_NATIVEINT">SET_16BIT_NATIVEINT</a><a href="#SET_8BIT_NATIVEINT">SET_8BIT_NATIVEINT</a>
<a name="STRERR"></a>
- <B>STRERR</B>
Summary : Get string of latest VCE error
Category : util
Prototype : ```char *STRERR``` 
  Return value : Pointer to string explaining the error code.

  Description : STRERR macro is defined as
<pre>
(vce_strerror( vce_get_last_error() ))
</pre>

  See also : <a href="#vce_get_last_error">vce_get_last_error</a><a href="#vce_strerror">vce_strerror</a>
<a name="vce_alloc_array_object"></a>
- <B>vce_alloc_array_object</B>
Summary : Allocate an unused element of a VCE array.
Category : array
Prototype : ```void * vce_alloc_array_object( int index )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE array.

  Return value : The top address of an allocated array element.
The null pointer is returned in case that all the element is
already used.
Error code can be obtained in vce_get_last_error function.

  Description : Search through empty list of VCE array and
then return a pointer if there is any available element.
This function never write data onto the contents of a newly allocated
memory.

  See also : <a href="#vce_free_array_object">vce_free_array_object</a><a href="#vce_free_array_object_all">vce_free_array_object_all</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_array_object_inuse"></a>
- <B>vce_array_object_inuse</B>
Summary : Know a VCE array object is currently used or not
Category : array
Prototype : ```int vce_array_object_inuse( int index, void *p )``` 
  - arg 1 : ```int index```
    Integer discriptor value to specify VCE array

  - arg 2 : ```void *p```
    Pointer to an VCE array object

  Return value : Returns 1 if the object is currently used,
otherwize zero. Returns minus error code if given arguments
are invalid ( for example index is inefficient, or pointer is
out of range )

  Description : You know if an array object is used(not freed) in an VCE array.

  See also : <a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_free_array_object">vce_free_array_object</a>
<a name="vce_atoi"></a>
- <B>vce_atoi</B>
Summary : Convert C string into a int value with simple calcuration.
Category : util
Prototype : ```int vce_atoi( char *p )``` 
  - arg 1 : ```char *p```
    Top address of string being converted.

  Return value : Converted value. If bad input, returns 0 in any case.

  Description : The atoi routine with the simple computation function.
The following inputs are accepted
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
"123+2*2"  →  250  Note that "+" is determined first.
"1+1+1+1+1"  →  5  Any number of linking is allowed.
"1+1+  1+1  +1"  →  5  Blank characters (TAB, SPACE) are skipped in reading.
</pre>
Dedicated to decimal numbers.
Note that operators are determined from left to right regardless of
connection weight of operators, like an operation of calculators.
atoi of libc is used internally.
If it returns "0" across the board when the conversion of an input
is not possible, the figure "0" cannot be determined whether
an error or valid value.
Therefore, in case of conversion failure,
it is enabled to use the vce_get_last_error function to detect
VCE_EFORMAT, in order to determine such "0".

  Bugs/TODO : This function is still at the experimental stage,
so it may be not performing stably-sometimes results make no sense.


<a name="vce_binary_pack"></a>
- <B>vce_binary_pack</B>
Summary : Make a byte array from an array of structure. (obsolete)
Category : bin
Prototype : ```int vce_binary_pack( struct bin_info *bi, int bn, char *outp, int len )``` 
  - arg 1 : ```struct bin_info *bi```
    Top address of an array of bin_info structure

  - arg 2 : ```int bn```
    Number of elements of bin_info structure array

  - arg 3 : ```char *outp```
    Output buffer

  - arg 4 : ```int len```
    Length of output buffer ( in bytes)

  Return value : Number of bytes written in output buffer

  Description : It Packs data stored in the bin_info structure and converts it
to a series of byte strings. This is mainly used for
protocol processing.

  Bugs/TODO : Now this function is already replaced with binary push/pop functions.


<a name="vce_binary_pop_nb_i1"></a>
- <B>vce_binary_pop_nb_i1</B>
Summary : Pop a 1-byte integer(char) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_i1( char *in, int len, int ofs, char *out)``` 
  - arg 1 : ```char *in```
    Top address of input buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```char *out```
    char pointer to store poped data.

  Return value : The new ofs value that moves through fetching one byte.

  Description : This fetches data packed by vce_binary_push_nb_i1function.
An offset advances by 1 all the time; however, it
returns a negative error code in case of failure (such as data shortage).

  See also : <a href="#vce_binary_push_nb_i1">vce_binary_push_nb_i1</a>
<a name="vce_binary_pop_nb_i2"></a>
- <B>vce_binary_pop_nb_i2</B>
Summary : Pop a 2-byte integer(short) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_i2( char *in, int len, int ofs, short *out )``` 
  - arg 1 : ```char *in```
    Top address of input buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```short *out```
    short pointer to store poped data.

  Return value : The new ofs value that moves through fetching 2 bytes.

  Description : This fetches data packed with vce_binary_push_nb_i2 function.
An offset advances by 2 all the time; however, it
returns a negative error code in case of failure (such as data shortage).

  See also : <a href="#vce_binary_push_nb_i2">vce_binary_push_nb_i2</a>
<a name="vce_binary_pop_nb_i4"></a>
- <B>vce_binary_pop_nb_i4</B>
Summary : Pop a 4-byte integer(int) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_i4( char *in, int len, int ofs, int *out )``` 
  - arg 1 : ```char *in```
    Top address of input buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```int *out```
    int pointer to store poped data.

  Return value : The new ofs value that moves through fetching 4 bytes.

  Description : This fetches data packed with vce_binary_push_nb_i4 function.
An offset advances by 4 all the time; however, it
returns a negative error code in case of failure (such as data shortage).

  See also : <a href="#vce_binary_push_nb_i4">vce_binary_push_nb_i4</a>
<a name="vce_binary_pop_nb_i8"></a>
- <B>vce_binary_pop_nb_i8</B>
Summary : Pop a 8-byte integer(int) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_i8( char *in, int len, int ofs, VCEI64 *out )``` 
  - arg 1 : ```char *in```
    Top address of input buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```VCEI64 *out```
    int pointer to store poped data.

  Return value : The new ofs value that moves through fetching 8 bytes.

  Description : This fetches data packed with vce_binary_push_nb_i8 function.
An offset advances by 8 all the time; however, it
returns a negative error code in case of failure (such as data shortage).

  See also : <a href="#vce_binary_push_nb_i8">vce_binary_push_nb_i8</a>
<a name="vce_binary_pop_nb_ia1"></a>
- <B>vce_binary_pop_nb_ia1</B>
Summary : Pop an array of 1-byte integer(char) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_ia1( char *src, int len, int ofs, char *out, int *outlen )``` 
  - arg 1 : ```char *in```
    Top address of input data buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```char *out```
    Top address of char array to store poped data

  - arg 5 : ```int *outlen```
    value-result parameter. This parameter must contain number of elements
of an array "out" when calling, and returns number of elements
actually filled into "out".

  Return value : The new ofs value that moves through fetching an array.
It returns a negative error code as fetching fails.

  Description : This fetches data packed with vce_binary_push_nb_ia1 function.
In case of data shortage, or that an array used
for fetching is too small, it returns a negative error code
indicating failure instead of fetching halfway. This is VCE's
policy on binary operation.

  See also : <a href="#vce_binary_push_nb_ia1">vce_binary_push_nb_ia1</a>
<a name="vce_binary_pop_nb_ia2"></a>
- <B>vce_binary_pop_nb_ia2</B>
Summary : Pop an array of 2-byte integer(short) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_ia2( char *src, int len, int ofs, short *out, int *outlen )``` 
  - arg 1 : ```char *in```
    Top address of input buffer.

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```short *out```
    pointer to short array to save poped data.

  - arg 5 : ```int *outlen```
    value-result parameter. This parameter must contain number of elements
of an array "out" when calling, and returns number of elements
actually filled into "out".

  Return value : The new ofs value that moves through fetching an array.
It returns a negative error code as fetching fails.

  Description : This fetches data packed with vce_binary_push_nb_ia2 function.
In case of data shortage, or that an array used
for fetching is too small, it returns a negative error code
indicating failure instead of fetching halfway. This is VCE's
policy on binary operation.
After being changed its order from network byte to native, data is stored.

  See also : <a href="#vce_binary_push_nb_ia2">vce_binary_push_nb_ia2</a>
<a name="vce_binary_pop_nb_ia4"></a>
- <B>vce_binary_pop_nb_ia4</B>
Summary : Pop an array of 4-byte integer(int) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_ia4( char *src, int len, int ofs, int *out, int *outlen )``` 
  - arg 1 : ```char *in```
    Top address of input buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```int *out```
    Top address of int array to store poped data

  - arg 5 : ```int *outlen```
    value-result parameter. This parameter must contain number of elements
of an array "out" when calling, and returns number of elements
actually filled into "out".

  Return value : The new ofs value that moves through fetching an array.
It returns a negative error code as fetching fails.

  Description : This fetches data packed with vce_binary_push_nb_ia4 function.
In case of data shortage, or that an array used
for fetching is too small, it returns a negative
error code indicating failure instead of fetching halfway.
This is VCE's policy on binary operation.
Having been changed its order from network byte to native, data is stored.

  See also : <a href="#vce_binary_push_nb_ia4">vce_binary_push_nb_ia4</a>
<a name="vce_binary_pop_nb_ia8"></a>
- <B>vce_binary_pop_nb_ia8</B>
Summary : Pop an array of 8-byte integer(int) from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_ia8( char *src, int len, int ofs, VCEI64 *out, int *outlen )``` 
  - arg 1 : ```char *in```
    Top address of input buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```VCEI64 *out```
    Top address of int array to store poped data

  - arg 5 : ```int *outlen```
    value-result parameter. This parameter must contain number of elements
of an array "out" when calling, and returns number of elements
actually filled into "out".

  Return value : The new ofs value that moves through fetching an array.
It returns a negative error code as fetching fails.

  Description : This fetches data packed with vce_binary_push_nb_ia8 function.
In case of data shortage, or that an array used
for fetching is too small, it returns a negative
error code indicating failure instead of fetching halfway.
This is VCE's policy on binary operation.
Having been changed its order from network byte to native, data is stored.

  See also : <a href="#vce_binary_push_nb_ia8">vce_binary_push_nb_ia8</a>
<a name="vce_binary_pop_nb_stra"></a>
- <B>vce_binary_pop_nb_stra</B>
Summary : Pop an array of strings from a buffer
Category : bin
Prototype : ```int vce_binary_pop_nb_stra( char *src, int len, int ofs, char **out, int *strnum, int eachmax )``` 
  - arg 1 : ```char *in```
    Top address of input buffer

  - arg 2 : ```int len```
    Length of input data buffer

  - arg 3 : ```int ofs```
    Number of offset bytes from the beginning of the input buffer

  - arg 4 : ```char **out```
    Top address of an array of pointer to char.

  - arg 5 : ```int *strnum```
    value-result parameter. This parameter must contain number of elements
of an array "out" when calling, and returns number of elements
actually filled into "out".

  - arg 6 : ```int eachmax```
    Max length of each strings saved in "out".

  Return value : The new ofs value that moves through fetching an array.
It returns a negative error code as fetching fails.

  Description : This fetches data packed with vce_binary_push_nb_stra function.
In case of data shortage, or that an array used for fetching is too
small, it returns a negative error code indicating failure instead
of fetching halfway.
This is VCE's policy on binary operation.
Since character strings are copied onto the character string array
designated by the out argument, memory space for copying must be
allocated by the application using this function.(refer to sample codes)

  Example :   char *orig_data[] = { "foo", "bar" };
  char packed[1000];
  char buf[3][100];
  char *out[3] = { buf[0] , buf[1], buf[2] }; // you can use C's "for" here
  int new_ofs,strnum,packed_len;
  packed_len = vce_binary_push_nb_stra( packed, sizeof(packed), 0, orig_data, 3, 100 );
  strnum = 3;
  new_ofs = vce_binary_pop_nb_stra( packed, packed_len, 0, out,&strnum, 100 );

  See also : <a href="#vce_binary_push_nb_stra">vce_binary_push_nb_stra</a>
<a name="vce_binary_push_nb_i1"></a>
- <B>vce_binary_push_nb_i1</B>
Summary : Push 1-byte integer(char) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_i1( char *out, int ofs, int maxlen, char c )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```char c```
    Source data which will be written into output buffer

  Return value : New offset value. This value is changed by pushing 1 byte.
In this function, new value is always ofs + 1.
Returns minus error indicator value when any error.

  Description : This is one of function groups for binary packer that is used as
defining binary protocol. This is used by gen.rb protocol generator.
You can fetch data by the corresponding vce_binary_pop_nb_i1function.

  See also : <a href="#vce_binary_pop_nb_i1">vce_binary_pop_nb_i1</a>
<a name="vce_binary_push_nb_i2"></a>
- <B>vce_binary_push_nb_i2</B>
Summary : Push 2-byte integer(short) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_i2( char *out, int ofs, int maxlen, short s )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```short s```
    Source data to be pushed

  Return value : This returns the new ofs value resulted from a movement of
ofs through pushing 2 bytes.
This particular function returns ofs + 2 all the time.
When it fails to push, it returns a negative error code.

  Description : In compliance with VCE's binary packer policy,
it will never destroy data as pushing data of 2 bytes or larger into a
buffer.
It will either push entire data certainly or fail completely.
You can fetch data by corresponding
vce_binary_pop_nb_i2 function.
Data is output on the network byte order.

  See also : <a href="#vce_binary_pop_nb_i2">vce_binary_pop_nb_i2</a>
<a name="vce_binary_push_nb_i4"></a>
- <B>vce_binary_push_nb_i4</B>
Summary : Push 4-byte integer(int) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_i4( char *out, int ofs, int maxlen, int i )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```int i```
    Source data to be pushed

  Return value : This function returns the new ofs value resulted
from a movement of ofs through pushing 4 bytes.
This particular function returns ofs + 4 all the time.
When it fails to push, it returns a negative error code.

  Description : In compliance with VCE's binary packer policy,
it will never destroy data as pushing data of 4 bytes or larger into a
buffer.
It will either push entire data certainly or fail completely.
You can fetch data by corresponding
vce_binary_pop_nb_I4 function.
Data is output on the network in byte order.

  See also : <a href="#vce_binary_pop_nb_i4">vce_binary_pop_nb_i4</a>
<a name="vce_binary_push_nb_i8"></a>
- <B>vce_binary_push_nb_i8</B>
Summary : Push 8-byte integer(VCEI64) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_i8( char *out, int ofs, int maxlen, VCEI64 i )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```VCEI64 i```
    Source data to be pushed

  Return value : This function returns the new ofs value resulted
from a movement of ofs through pushing 8 bytes.
This particular function returns ofs + 8 all the time.
When it fails to push, it returns a negative error code.

  Description : In compliance with VCE's binary packer policy,
it will never destroy data as pushing data of 8 bytes or larger into a
buffer.
It will either push entire data certainly or fail completely.
You can fetch data by corresponding
vce_binary_pop_nb_i8 function.
Data is output on the network in byte order.

  See also : <a href="#vce_binary_pop_nb_i8">vce_binary_pop_nb_i8</a>
<a name="vce_binary_push_nb_ia1"></a>
- <B>vce_binary_push_nb_ia1</B>
Summary : Push an array of 1-byte integer(char) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_ia1( char *out, int ofs, int maxlen, char *ia, int num )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```char *ia```
    Top address of an array of char(1byte integer) type

  - arg 5 : ```int num```
    Number of elements being pushed

  Return value : Return new offset value.
Return minus error code when failed to push.

  Description : This pushes the contents of a char type array into the output buffer.
You can fetch data by corresponding
vce_binary_pop_nb_ia1 function.
When length of the output buffer is shorter than needed,
it returns a negative error code
(VCE_EFULL), instead of destroying it.

  See also : <a href="#vce_binary_pop_nb_ia1">vce_binary_pop_nb_ia1</a>
<a name="vce_binary_push_nb_ia2"></a>
- <B>vce_binary_push_nb_ia2</B>
Summary : Push an array of 2-byte integer(short) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_ia2( char *out, int ofs, int maxlen, short *ia, int num )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```short *ia```
    Top address of an array of short(2byte integer) type

  - arg 5 : ```int num```
    Number of elements being pushed

  Return value : This returns the new offset which has moved through outputting.
In case of output failure, it returns a negative error code.

  Description : This pushes the contents of a short type array into the output buffer.
You can fetch data by corresponding
vce_binary_pop_nb_ia2 function.
All data is saved in network byte order.
When length of the output buffer is
short, it returns a negative error code (VCE_EFULL),
instead of destroying it.

  See also : <a href="#vce_binary_pop_nb_ia2">vce_binary_pop_nb_ia2</a>
<a name="vce_binary_push_nb_ia4"></a>
- <B>vce_binary_push_nb_ia4</B>
Summary : Push an array of 4-byte integer(int) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_ia4( char *out, int ofs, int maxlen, int *ia, int num )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```int *ia```
    Top address of an array of int(4byte integer) type

  - arg 5 : ```int num```
    Number of elements being pushed

  Return value : This returns the new offset which has moved through outputting.
In case of output failure, it returns a negative error code.

  Description : This pushes the contents of an int type array into the output buffer.
You can fetch data by corresponding vce_binary_pop_nb_ia4 function.
All data is saved in network byte order.
When length of the output buffer is short,
it returns a negative error code (VCE_EFULL), instead of destroying it.

  See also : <a href="#vce_binary_pop_nb_ia4">vce_binary_pop_nb_ia4</a>
<a name="vce_binary_push_nb_ia8"></a>
- <B>vce_binary_push_nb_ia8</B>
Summary : Push an array of 8-byte integer(VCEI64) to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_ia8( char *out, int ofs, int maxlen, VCEI64 *ia, int num )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```VCEI64 *ia```
    Top address of an array of int(4byte integer) type

  - arg 5 : ```int num```
    Number of elements being pushed

  Return value : This returns the new offset which has moved through outputting.
In case of output failure, it returns a negative error code.

  Description : This pushes the contents of an int type array into the output buffer.
You can fetch data by corresponding vce_binary_pop_nb_ia8 function.
All data is saved in network byte order.
When length of the output buffer is short,
it returns a negative error code (VCE_EFULL), instead of destroying it.

  See also : <a href="#vce_binary_pop_nb_ia8">vce_binary_pop_nb_ia8</a>
<a name="vce_binary_push_nb_stra"></a>
- <B>vce_binary_push_nb_stra</B>
Summary : Push null-terminated string array to a buffer
Category : bin
Prototype : ```int vce_binary_push_nb_stra( char *out, int ofs, int maxlen, char **stra, int num, int eachmax )``` 
  - arg 1 : ```char *out```
    Top address of output buffer

  - arg 2 : ```int ofs```
    Number of offset bytes from the beginning of the output buffer

  - arg 3 : ```int maxlen```
    Length of output buffer

  - arg 4 : ```char **stra```
    An array of string pointers, which will be pushed into output buffer

  - arg 5 : ```int num```
    Number of pointers contained in **stra argument

  - arg 6 : ```int eachmax```
    Max length of each strings contained in **stra argument.
If length of even one string goes longer than this value,
this function will return error code.

  Return value : The new ofs value which has moved through outputting.
When it fails to push because a buffer is full or otherwise,
it returns a negative error code.

  Description : This packs a character string into binary data,
and adds it to a buffer.
The argument eachmax is added in order to
enable a restriction on the maximum number of letters of each
character string. When num is 0, NULL can be designated as stra.

  See also : <a href="#vce_binary_pop_nb_stra">vce_binary_pop_nb_stra</a>
<a name="vce_binary_unpack"></a>
- <B>vce_binary_unpack</B>
Summary : Unpack binary char array into an array of struct.(obsolete)
Category : bin
Prototype : ```int vce_binary_unpack( struct bin_info *bi, int bn, char *inp, int len )``` 
  - arg 1 : ```struct bin_info *bi```
    Top address of an array of bin_info structure

  - arg 2 : ```int bn```
    Number of elements of bin_info structure array

  - arg 3 : ```char *inp```
    Top address of input buffer

  - arg 4 : ```int len```
    Length of input buffer (in bytes)

  Return value : Return length of processed data if successful.
This can be smaller than parameter "len", but never bigger than "len".
Returns VCE_EDATASHORT when input data is too short.

  Description : This unpacks binary data as specified by an array of the bin_info structure,
and brings it back to the structured state.
It is mainly used for protocol processing.

  Bugs/TODO : This function is already replaced with binary push/pop functions.

  See also : <a href="#vce_binary_pack">vce_binary_pack</a>
<a name="vce_conn_break_heartbeat"></a>
- <B>vce_conn_break_heartbeat</B>
Summary : PENDING
Category : tcp
Prototype : ```void vce_conn_break_heartbeat()``` 
  Return value : 
  Description : PENDING

  See also : <a href="#vce_tcpcontext_set_conn_call_parser_per_heartbeat">vce_tcpcontext_set_conn_call_parser_per_heartbeat</a>
<a name="vce_conn_clear"></a>
- <B>vce_conn_clear</B>
Summary : Initialize conn_t instance
Category : tcp
Prototype : ```void vce_conn_clear( conn_t *c )``` 
  - arg 1 : ```conn_t *c```
    pointer to a conn_t

  Return value : None

  Description : This is only way to correctly create an initialized conn_t.
Zero-clear with memset is not formal.


<a name="vce_conn_close"></a>
- <B>vce_conn_close</B>
Summary : Close and release one TCP connection.
Category : tcp
Prototype : ```void vce_conn_close( conn_t ct )``` 
  - arg 1 : ```conn_t ct```
    A TCP connection (conn_t) to be closed.

  Return value : None

  Description : This closes a TCP connection.
What it actually does is just to put up the flag for the closing in
next heartbeat.
It succeeds all the time, however, when this function is invoked
for the connection with the close flag up, a warning is
given in the verbose mode.
Note that a connection will not actually be closed,
unless vce_heartbeat is called.
The connection closed by the VCE library will be detected
as an error as an application attempts to write next time.
Moreover, the closewatcher designated upon vce_tcpcontext_create
is called before releasing resources.
By resetting the time-out value shorter than a normal value
right after vce_conn_close, speedy close processing would be expected.
If not doing so, a connection will remain until the default time-out
duration-time passes, should there left some data within a connection.
(refer to sample codes) vce_get_last_error returns
VCE_EINVAL and VCE_EALREADY,
in case that an argument was abnormal and that additional
close is attempted when it was already closed, respectively.

  Example : // Set shorter time-out duration after closing conn_t
vce_conn_close( co );
vce_conn_set_timeout( co, 0 );

  See also : <a href="# vce_tcpcontext_connect"> vce_tcpcontext_connect</a><a href="# vce_tcpcontext_create"> vce_tcpcontext_create</a><a href="#vce_conn_writable">vce_conn_writable</a>
<a name="vce_conn_close_tcpcontext_all"></a>
- <B>vce_conn_close_tcpcontext_all</B>
Summary : Close all connections maintained by a tcpcontext.
Category : tcp
Prototype : ```void vce_conn_close_tcpcontext_all( tcpcontext_t tp )``` 
  - arg 1 : ```tcpcontext_t tp```
    Target tcpcontext, which contains one or more conn_t
which will be closed by calling this function.

  Return value : None

  Description : This disconnects all connections parented by a TCPcontext.
Closewatcher and fainalizer are invoked afterwords.
You have to call vce_heartbeat after calling this function
to finish I/O. That is because actual disconnection will be done
in next vce_heartbeat (see vce_conn_close section).
A online-game server, for instance, in ideal case it informs all the
clients of its intention of shutdown first of all,
then blocks a new accept with vce_tcpcontext_enable_accept
function, and lastly closes a connection through invoking this function,
in order to properly terminate the server.
This function behaves the same on a server and client.
In the verbose mode, a log is output upon every disconnection.

  See also : <a href="#vce_tcpcontext_enable_accept">vce_tcpcontext_enable_accept</a>
<a name="vce_conn_get_buffer"></a>
- <B>vce_conn_get_buffer</B>
Summary : Get conn_t's read/write buffer.
Category : tcp
Prototype : ```void vce_conn_get_buffer( conn_t c, char **rb, int  *rblen, char **wb, int *wblen )``` 
  - arg 1 : ```conn_t c```
    target conn_t

  - arg 2 : ```char **rb```
    This parameter returns pointer to read buffer.

  - arg 3 : ```int *rblen```
    This parameter returns length of read buffer.
You can get how many bytes of data can be read from this conn_t.

  - arg 4 : ```char **wb```
    This parameter returns pointer to write buffer.

  - arg 5 : ```int *wblen```
    This parameter returns length of write buffer.
You can get how many bytes of data can be written into this conn_t.

  Return value : None

  Description : If your application needs an original protocol parser,
you can define it by directly refering to the read/write buffer.
Such original protocol parser can be registered
by vce_tcpcontext_set_conn_parser function.

  See also : <a href="#vce_conn_shrink_readbuf">vce_conn_shrink_readbuf</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_conn_get_index"></a>
- <B>vce_conn_get_index</B>
Summary : Get index number of conn_t in VCE library.
Category : tcp
Prototype : ```int vce_conn_get_index( conn_t c );``` 
  - arg 1 : ```conn_t c```
    target conn_t. retrieve index from this conn_t.

  Return value : Index number. Return minus value when error.

  Description : Index number can be uniquely used to specify conn_t,
because the conn_t structure is maintained as a one-dimensional
array inside VCE.
Therefore, it may be used for the purposes such as the "session ID"
in your application.

  See also : <a href="#vce_conn_get_struct_from_index">vce_conn_get_struct_from_index</a>
<a name="vce_conn_get_local_addr_string"></a>
- <B>vce_conn_get_local_addr_string</B>
Summary : Get local address and port number from conn_t by string
Category : tcp
Prototype : ```char * vce_conn_get_local_addr_string( conn_t ct, char *s, int max )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *s```
    Top address of output buffer

  - arg 3 : ```int max```
    Length of output buffer

  Return value : Return buffer "s" as it is.

  Description : This obtains local address of conn_t in a character string.
The address format allowed is the same as
vce_conn_get_remote_addr_string function's.

  See also : <a href="#vce_conn_get_remote_addr_string">vce_conn_get_remote_addr_string</a>
<a name="vce_conn_get_local_ipv4_addr"></a>
- <B>vce_conn_get_local_ipv4_addr</B>
Summary : Get 32-bit IPv4 local address from a TCP connection
Category : tcp
Prototype : ```void vce_conn_get_local_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```unsigned int *a```
    Pointer to 32bit integer(int) IP address.
Output data is network byte-ordered.
Ignore this parameter if NULL is set.

  - arg 3 : ```unsigned short *p```
    Pointer to 16bit integer(short) port number.
Output data is network byte-ordered.
Ignore this parameter if NULL is set.

  Return value : None

  Description : Output data is in the network byte order.
It should be converted using ntohs, ntohl or others as you need.

  See also : <a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a>
<a name="vce_conn_get_local_ipv4_addr_string"></a>
- <B>vce_conn_get_local_ipv4_addr_string</B>
Summary : Get Ipv4 local peer address from a TCP connectin as a string
Category : tcp
Prototype : ```char * vce_conn_get_local_ipv4_addr_string( conn_t ct, char *s, int max )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *s```
    Top address of output buffer

  - arg 3 : ```int max```
    Length of output buffer

  Return value : Return parameter "s" as it is

  Description : This function is dedicated to IPv4 and determines an address
of the end point on this side of the socket.
"This side" means that the end point on the side where the program
that invoked this function is running.
Since this function is dedicated to IPv4,
it is recommended to use vce_conn_get_local_addr_string
function rather than this function,
because we should persue protocol independency in our applications.

  See also : <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a>
<a name="vce_conn_get_local_ipv6_addr"></a>
- <B>vce_conn_get_local_ipv6_addr</B>
Summary : Get 128-bit IPv6 local address from a TCP connection
Category : tcp
Prototype : ```void vce_conn_get_local_ipv6_addr( conn_t ct, char *a, unsigned short *p )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *a```
    Pointer to char array, which will contain 16bytes of IPv6 address.
Ignore this parameter if NULL is set.
Output data is network byte-ordered. You have to allocate more than 16bytes
for this parameter.

  - arg 3 : ```unsigned short *p```
    Pointer to 16bit integer(short).
Ignore this parameter if NULL is set.

  Return value : None

  Description : This function is IPv6 version of vce_conn_get_remote_ipv4_addr function.

  See also : <a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a><a href="#vce_conn_get_remote_ipv6_addr">vce_conn_get_remote_ipv6_addr</a>
<a name="vce_conn_get_local_ipv6_addr_string"></a>
- <B>vce_conn_get_local_ipv6_addr_string</B>
Summary : Get Ipv6 local address from a TCP connectin as a string
Category : tcp
Prototype : ```char *vce_conn_get_local_ipv6_addr_string( conn_t ct, char *s, int max )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *s```
    Top address of output buffer

  - arg 3 : ```int max```
    Length of output buffer

  Return value : Return parameter "s" as it is, or NULL when error.

  Description : This gets local address of a conn_t in a character string,
in the format same as vce_conn_get_remote_addr_string's.
Since this function is dedicated to IPv6 and protocol dependent,
it is recommended to use vce_conn_get_local_addr_string function instead.

  See also : <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a>
<a name="vce_conn_get_remote_addr_string"></a>
- <B>vce_conn_get_remote_addr_string</B>
Summary : Get remote peer address and port number from conn_t by string
Category : tcp
Prototype : ```char *vce_conn_get_remote_addr_string( conn_t ct, char *s, int max )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *s```
    Top address of output buffer.

  - arg 3 : ```int max```
    Length of output buffer

  Return value : Return buffer "s" as it is.

  Description : This gets remote peer address of conn_t in
a protocol independent application in a character string.
VCE is compatible with ipv4 and ipv6 at the moment,
and returns like "192.168.0.11234" for IPV4,
or "fe802d0b7fffec6f4cd.5678" for IPv6.
It does not resolve DNS name.
Note that the token indicating the last port number is
divided by "" for ipv4,
whereas "." is used for ipv6.
The process to determine to which protocol a returned character
string belongs is left to an application.

  See also : <a href="#vce_conn_get_local_addr_string">vce_conn_get_local_addr_string</a><a href="#vce_conn_get_remote_ipv4_addr_string">vce_conn_get_remote_ipv4_addr_string</a>
<a name="vce_conn_get_remote_ipv4_addr"></a>
- <B>vce_conn_get_remote_ipv4_addr</B>
Summary : Get 32-bit IPv4 remote peer address from a TCP connection
Category : tcp
Prototype : ```void vce_conn_get_remote_ipv4_addr( conn_t ct, unsigned int *a, unsigned short *p )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```unsigned int *a```
    Pointer to return 32bit integer(int) IP address.
Output data will be network byte-ordered.
Ignore this parameter if NULL is set.

  - arg 3 : ```unsigned short *p```
    Pointer to return port number. Output data is network byte-ordered.
Ignore this parameter if NULL is set.

  Return value : None

  Description : Output data is in network byte order,
so you use ntohs(), or ntohl() if you need them.


<a name="vce_conn_get_remote_ipv4_addr_string"></a>
- <B>vce_conn_get_remote_ipv4_addr_string</B>
Summary : Get Ipv4 remote peer address from a TCP connectin as a string
Category : tcp
Prototype : ```char *vce_conn_get_remote_ipv4_addr_string( conn_t ct, char *s, int max )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *s```
    Top address of output buffer.

  - arg 3 : ```int max```
    Length of output buffer

  Return value : Return parameter "s" as it is

  Description : Converting IPv4 address into string is often demanded
for purposes such as logging.
In the “PlayStation(R)2”development environment,
designate over 50 bytes as "s", the output buffer.
This is because current "PlayStation(R)2” library does not have snprintf.
Since this function is dedicated to IPv4, it is not compatible
with the IPv6 connection.
An application pursuing protocol independency should use
vce_conn_get_remote_addr function.

  See also : <a href="#vce_conn_get_remote_addr">vce_conn_get_remote_addr</a><a href="#vce_conn_get_remote_ipv4_addr">vce_conn_get_remote_ipv4_addr</a>
<a name="vce_conn_get_remote_ipv6_addr"></a>
- <B>vce_conn_get_remote_ipv6_addr</B>
Summary : Get 128-bit IPv6 remote peer address from a TCP connection
Category : tcp
Prototype : ```void vce_conn_get_remote_ipv6_addr( conn_t ct, char *a, unsigned short *p )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *a```
    Pointer to char array, which will contain 16bytes of IPv6 address.
Ignore this parameter if NULL is set.
Output data is network byte-ordered. You have to allocate more than 16bytes
for this parameter.

  - arg 3 : ```unsigned short *p```
    Pointer to 16bit integer(short) port number.
Ignore this parameter if NULL is set.

  Return value : None

  Description : Output data is in network byte order.
You use ntohs(), or ntohl() functions in case you need them.

  See also : <a href="#vce_conn_get_local_ipv6_addr">vce_conn_get_local_ipv6_addr</a>
<a name="vce_conn_get_remote_ipv6_addr_string"></a>
- <B>vce_conn_get_remote_ipv6_addr_string</B>
Summary : Get Ipv6 remote peer address from a TCP connectin as a string
Category : tcp
Prototype : ```char *vce_conn_get_remote_ipv6_addr_string( conn_t ct, char *s, int max )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```char *s```
    Top address of output buffer

  - arg 3 : ```int max```
    Length of output buffer

  Return value : Return parameter "s" as it is, or NULL when error.

  Description : This function is IPv6 version of vce_conn_get_remote_ipv4_addr_string
function.

  See also : <a href="#vce_conn_get_remote_addr">vce_conn_get_remote_addr</a><a href="#vce_conn_get_remote_ipv4_addr_string">vce_conn_get_remote_ipv4_addr_string</a><a href="#vce_conn_get_remote_ipv6_addr">vce_conn_get_remote_ipv6_addr</a>
<a name="vce_conn_get_stat"></a>
- <B>vce_conn_get_stat</B>
Summary : Get conn_t's statistics information
Category : tcp
Prototype : ```void vce_conn_get_stat( conn_t ct, conn_stat_t *st )``` 
  - arg 1 : ```conn_t ct```
    source conn_t

  - arg 2 : ```conn_stat_t *st```
    Top address of an instance of conn_stat_t structure

  Return value : None

  Description : This fetches statistical information from TCP connection.
The conn_stat_t structure is defined for such extraction.
Description of the structure members are as follows

<UL>
<LI>recv_byte<BR>
Total bytes received by this connection.
<LI>send_byte<BR>
Total bytes transmitted by this connection.
<LI>conn_write<BR>
Number of times vce_conn_write is made toward this connection.
<LI>recv_syscall, send_syscall
Number of times the recv()system call and send_syscall
are invoked toward this connection.
</ul>

  See also : <a href="#vce_conn_is_valid">vce_conn_is_valid</a><a href="#vce_get_stat">vce_get_stat</a><a href="#vce_tcpcontext_get_stat">vce_tcpcontext_get_stat</a>
<a name="vce_conn_get_state_buffer"></a>
- <B>vce_conn_get_state_buffer</B>
Summary : Get pointer to conn_t's state buffer.
Category : tcp
Prototype : ```void * vce_conn_get_state_buffer( conn_t c, int *len );``` 
  - arg 1 : ```conn_t c```
    source conn_t

  - arg 2 : ```int *len```
    Return length of state buffer.
Do nothing if NULL is specified.

  Return value : Pointer to state buffer.
Returns NULL if stateless protocol.

  Description : This returns protocol state buffer attached to a conn_t.
If the protocol with the state is designated (statebuf_size) upon
invocation of vce_tcpcontext_create,
this returns a pointer to the buffer having the region of that size.

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_conn_get_struct_from_index"></a>
- <B>vce_conn_get_struct_from_index</B>
Summary : Get conn_t struct from index number.
Category : tcp
Prototype : ```conn_t vce_conn_get_struct_from_index( int index );``` 
  - arg 1 : ```int index```
    Index of the conn_t. You can get conn_t by specifying index
number which is got by using vce_conn_get_index function.

  Return value : retrieved conn_t

  Description : You can use this function when you want to get conn_t
from "session ID" in your application.

  See also : <a href="#vce_conn_get_index">vce_conn_get_index</a>
<a name="vce_conn_get_tcpcontext"></a>
- <B>vce_conn_get_tcpcontext</B>
Summary : get tcpcontext_t from a conn_t
Category : tcp
Prototype : ```tcpcontext_t vce_conn_get_tcpcontext( conn_t c )``` 
  - arg 1 : ```conn_t c```
    target conn_t

  Return value : instance of tcpcontext_t, owner of parameter "c"

  Description : When connecting to a remote computer or accepting new TCP,
conn_t is initialized within VCE.
Such conn_t is always associated with tcpcontext.
Therefore, tcpcontext can be extracted from conn_t.
This function is mainly used within VCE internally,
but seldom be used from an application.

  See also : <a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
<a name="vce_conn_is_equal"></a>
- <B>vce_conn_is_equal</B>
Summary : Check if two conn_t instances are the same
Category : tcp
Prototype : ```int vce_conn_is_equal( conn_t c1 , conn_t c2 )``` 
  - arg 1 : ```conn_t c1```
    first target

  - arg 2 : ```conn_t c2```
    second target

  Return value : Returns 1 if equal. 0 if not.

  Description : This checks if two connections are the same.
Writing and reading using those two conn_t's will lead definitely the
same results.
In concrete, it will be the connection having the same
pointer and serial number.


<a name="vce_conn_is_valid"></a>
- <B>vce_conn_is_valid</B>
Summary : Check if a TCP connection ( conn_t ) is broken or not.
Category : tcp
Prototype : ```int vce_conn_is_valid( conn_t c )``` 
  - arg 1 : ```conn_t c```
    target conn_t

  Return value : Returns 1 if valid, or 0 if not valid.

  Description : VCEed applications often store conn_t's returned from VCE
in a different memory region and use it afterwards for calling
the connection again.
However, at the point of time, the object within VCE
that is referred by such conn_t may possibly have released and reused.
This function checks if such conn_t has reused and is no longer
existing, using the serial number of the conn_t type.
This function is also used to check if the returned value from
vce_tcpcontext_connect is correct or not.
If you want to check you can write data into the conn_t,
you must use vce_conn_writable function all the time, not this function.

  See also : <a href="#vce_conn_writable">vce_conn_writable</a><a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
<a name="vce_conn_set_delay"></a>
- <B>vce_conn_set_delay</B>
Summary : pending
Category : core
Prototype : ```void vce_conn_set_delay(conn_t ct,int delay_min,int delay_max)``` 
  - arg 1 : ```conn_t ct```
    pending

  - arg 2 : ```int delay_min```
    pending

  - arg 3 : ```int delay_max```
    pending

  Return value : None

  Description : pending

  Bugs/TODO : pending


<a name="vce_conn_set_parser"></a>
- <B>vce_conn_set_parser</B>
Summary : Set protocl parser and callback function per conn_t basis
Category : tcp
Prototype : ```void vce_conn_set_parser( conn_t ct, int (*parser)(conn_t), int (*pcallback)(conn_t,char*,int))``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  - arg 2 : ```int (*parser)(conn_t)```
    parser function to be set. For example, vce_protocol_parser_bin16, and
so on.

  - arg 3 : ```int (*pcallback)(conn_t c,char *d, int l )```
    Callback function. This function will be called by the protocol parser.

  Return value : None

  Description : In some application, you may want to use
different parsers in each connection.
This function can change both parser and callback function dinamically.

If you change any callback function inside protocol callback function,
new callback function will be used after next parser call.

This function may be used for switching a protocol to
the debug mode, or to the control function, as well.

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_protocol_parser_text">vce_protocol_parser_text</a><a href="#vce_protocol_parser_through">vce_protocol_parser_through</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_conn_set_timeout"></a>
- <B>vce_conn_set_timeout</B>
Summary : Change each conn_t's timeout length
Category : tcp
Prototype : ```void vce_conn_set_timeout( conn_t c, int sec )``` 
  - arg 1 : ```conn_t c```
    target conn_t

  - arg 2 : ```int sec```
    new timeout value in seconds

  Return value : None

  Description : By default, time-out durations of respective connections
comply with the time-out setting of the vce_tcpcontext_create function.
The time-out duration depending on each connection can be adjusted without
restriction through using this function.
You can make use of this function in your application
if you want special high security in some situation.

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_conn_show_stat"></a>
- <B>vce_conn_show_stat</B>
Summary : Show stats of all active connections.
Category : tcp
Prototype : ```void vce_conn_show_stat( void )``` 
  Return value : None

  Description : This outputs statistical information of the same number
of lines as it of connection, starting with
<pre>
"=== SHOW CONNECTION STATISTICS ===\n".
</pre>
Descriptions of the contents to be displayed are as follows

<UL>
<LI>A<BR>
Address of the connection structure (conn_t)
<LI>Enc<BR>
1 if encrypted, otherwise 0
<LI>IP<BR>
IP address port number. The port number is in the decimal.
<LI>Lst<BR>
Last accessed time (time_t, system time)
<LI>I<BR>
VCE control index
<LI>Sv<BR>
1 for server connections, 0 for client connections.
<LI>ER<BR>
Read buffer address before encryption
<LI>EW<BR>
Write buffer address after encryption
<LI>R<BR>
Read buffer address after decryption
<LI>W<BR>
Write buffer address before encryption
<LI>St<BR>
Negotiating on encryption
</ul>
Note that this function outputs nothing with the VCE library
compiled in the silent mode, and sets up
VCE_ESUPPORT as the last error.

  Bugs/TODO : Since this function uses standard error for output,
this function cannot be used in case standard error output is
unavailable in Win32GUI environment.


<a name="vce_conn_shrink_readbuf"></a>
- <B>vce_conn_shrink_readbuf</B>
Summary : shrink conn_t's read buffer
Category : tcp
Prototype : ```int vce_conn_shrink_readbuf( conn_t ct, int len )``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  - arg 2 : ```int len```
    Length to shrink

  Return value : Shrinked length. When success, this will be same as parameter "len".

  Description : When defining an original protocol parser in your application,
the contents of the read buffer must be deleted using
vce_conn_shrink_readbuf, after processing the contents of the read buffer.


<a name="vce_conn_userdata_get_pointer"></a>
- <B>vce_conn_userdata_get_pointer</B>
Summary : 
Category : tcp
Prototype : ```void *vce_conn_userdata_set_pointer(conn_t ct);``` 
  - arg 1 : ```conn_t ct```
    
  Return value : 
  Description : 

<a name="vce_conn_userdata_set_pointer"></a>
- <B>vce_conn_userdata_set_pointer</B>
Summary : 
Category : tcp
Prototype : ```void vce_conn_userdata_set_pointer(conn_t ct,void *p);``` 
  - arg 1 : ```conn_t ct```
    
  - arg 2 : ```void *p```
    
  Return value : 
  Description : 

<a name="vce_conn_writable"></a>
- <B>vce_conn_writable</B>
Summary : Check if a TCP connection is ready to use (write).
Category : tcp
Prototype : ```int vce_conn_writable( conn_t ct );``` 
  - arg 1 : ```conn_t ct```
    A conn_t variable to be checked. If you're using nonblocking connect()
option on vce_tcpcontext_create, you can check if TCP socket is
established by calling this function. vce_conn_writable can be used
in both server programs and client programs, but it's commonly used in
client programs.

  Return value : Returns VCE_EINVAL if ct is not valid.
Returns VCE_ECONNSERIAL if ct is not usable any more
( the connection is cleared inside vce library. )
Returns 0 if connection is active but there are no buffer space/under
key negotiation.
Returns >0 if writable. The value means how many bytes you can write into
the socket.

  Description : Use this function to check if writing is allowed,
when writing something into conn_t in your application.

  Example :   // This program keeps writing in conn_t continuously
  tcpcontext_t t = vce_tcpontext_create( 0, ... );
  conn_t new_con = vce_tcpcontext_connect( t, "localhost" , 80 );
  while (1 ){
      vce_heartbeat();
      if( vce_conn_writable( new_con ) >= 4 ){
          vce_conn_write( new_con, "test" , 4 );
      } else {
          // Fail. too long time after starting connect().
      }
  }


  See also : <a href="#vce_conn_is_valid">vce_conn_is_valid</a><a href="#vce_conn_write">vce_conn_write</a><a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a>
<a name="vce_conn_write"></a>
- <B>vce_conn_write</B>
Summary : Write raw data into a TCP connection.
Category : tcp
Prototype : ```int vce_conn_write( conn_t ct, char *b, size_t len );``` 
  - arg 1 : ```conn_t ct```
    target conn_t to write

  - arg 2 : ```char *b```
    Pointer to data.

  - arg 3 : ```size_t len```
    Length of written data.

  Return value : Larger than 1 successful<BR>
0  Buffer full<BR>

  Description : This directly transmits raw data.
Here direct transmission means that,
data is stored in the write buffer allocated inside conn_t
for a while, then is flushed in next vce_heartbeat().
Consequently, the maximum amount allowed to write at a time
will depend on length of write buffer upon vce_tcpcontext_create.

Moreover, once vce_conn_write returns a negative value,
the connection is no longer available. In this case you should
immediately call vce_conn_close against the conn_t.
<BR><BR>

<B>In cases it fails to write  returning 0 for example</B><BR>

In case vce_conn_write returns 0,
any data cannot be written into a socket for some reason.
This usually means that the client side can no longer read (down).
When the contents of an application sends or receives
large data such as JPEG files, a process must go on
without calling vce_conn_close,
even if it returns 0.
However, if small data such as game operation packets is used,
it should be deemed that some problem is occurring to a client
and calling vce_conn_close is perferable.

  Example :   // how to use vce_conn_close in cases like online games
  // always small packets are transmitted
  if( vce_writable( ct ) > 0 ){
      int writel = vce_conn_write( ct, "hoge", 4 );
      if( writel < 4 ){
          vce_conn_close(ct);
      }
  }


  See also : <a href="#vce_conn_close">vce_conn_close</a><a href="#vce_conn_writable">vce_conn_writable</a>
<a name="vce_conn_writed"></a>
- <B>vce_conn_writed</B>
Summary : 
Category : tcp
Prototype : ```int vce_conn_writed( conn_t c )``` 
  - arg 1 : ```conn_t c```
    target conn_t

  Return value : 
  Description : 
  See also : <a href="#vce_conn_valid">vce_conn_valid</a>
<a name="vce_dump_buffer"></a>
- <B>vce_dump_buffer</B>
Summary : Dump binary data array using vce_errout.
Category : util
Prototype : ```void vce_dump_buffer( char *buf, int len )``` 
  - arg 1 : ```char *buf```
    Top address of data being dumped

  - arg 2 : ```int len```
    Length of data being dumped

  Return value : None

  Description : This logs all the array contents including binary data using
the vce_errout function.
This is so simple that displays dividing every 8 bytes in the buffer.

  See also : <a href="#vce_errout">vce_errout</a>
<a name="vce_end_all_array"></a>
- <B>vce_end_all_array</B>
Summary : Release all VCE array.
Category : array
Prototype : ```void vce_end_all_array( void )``` 
  Return value : None

  Description : Call vce_end_array against all VCE arrays maintained by VCE.

  See also : <a href="#vce_init_array">vce_init_array</a>
<a name="vce_end_array"></a>
- <B>vce_end_array</B>
Summary : Release a VCE array.
Category : array
Prototype : ```int vce_end_array( int index )``` 
  - arg 1 : ```int index```
    Array descriptor, which is formerly returned by vce_init_array.

  Return value : 
  Description : Note that this releases an array itself, and not its elements.
All elements in the array will be released.
After invocation of vce_end_array, all the operations
concerning the array become unavailable.
vce_end_array function calls the FREE function inside it.

  See also : <a href="#FREE">FREE</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_errout"></a>
- <B>vce_errout</B>
Summary : Log output for VCE application
Category : core
Prototype : ```int vce_errout( const char *format, ... )``` 
  - arg 1 : ```char *format```
    Format string. Same as "printf" libc function.

  - arg 2 : ```...```
    Argument list. Same as "printf" function.
No argument is also acceptable.

  Return value : None

  Description : 
  See also : <a href="# vce_errout_set_another"> vce_errout_set_another</a><a href="# vce_verrout"> vce_verrout</a><a href="#vce_errout_config">vce_errout_config</a><a href="#vce_errout_v">vce_errout_v</a>
<a name="vce_extract_data_from_hex_text"></a>
- <B>vce_extract_data_from_hex_text</B>
Summary : Convert hextext format ASCII text into a binary data array.
Category : util
Prototype : ```int vce_extract_data_from_hex_text( const char *buf, int len, char *out, int outlen )``` 
  - arg 1 : ```char *buf```
    Top address of input ASCII text string.

  - arg 2 : ```int len```
    Length of input text string ( in bytes )

  - arg 3 : ```char *out```
    Top address of destination binary data buffer.

  - arg 4 : ```int outlen```
    Size of destination binary data buffer.

  Return value : This returns VCE_EFORMAT if source text is not well formatted.
This also returns  negative error code when other errors.
Positive number (binary bytes) for complete success.

  Description : This reads hextext format buffer into a binary array
after checking validity of contents of "buf".

  See also : <a href="#vce_make_hex_text_from_buffer">vce_make_hex_text_from_buffer</a>
<a name="vce_finalize"></a>
- <B>vce_finalize</B>
Summary : Release all resources used by VCE.
Category : core
Prototype : ```int vce_finalize( void )``` 
  Return value : Returns 0 if successful. Otherwise minus error indicator value.

  Description : This releases all the resources used by VCE.
All VCE function invocation after calling this function will be an
undefined action except vce_errout*.


<a name="vce_free_array_object"></a>
- <B>vce_free_array_object</B>
Summary : Free an element of a VCE array.
Category : array
Prototype : ```int vce_free_array_object( int index , void *p )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE array.

  - arg 2 : ```void *p```
    Top address of an element in the array.

  Return value : Returns 0 if successful. Otherwise negative error code.

  Description : vce_free_array_object function can be used within the ARRAY_SCAN macro.
This function never write anything onto the contents of the buffer
being released.

  See also : <a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_free_array_object_all">vce_free_array_object_all</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_free_array_object_all"></a>
- <B>vce_free_array_object_all</B>
Summary : Free all elements in an array
Category : array
Prototype : ```void vce_free_array_object_all( int index )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE array.

  Return value : NOne

  Description : Free all used elements in an array.

  Bugs/TODO : This is comparatively slow, because it releases one by one at the moment.
Speeding up through simultaneous entire
initialization is planned (version 1 and later).

  See also : <a href="#vce_free_array_object">vce_free_array_object</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_maxnum"></a>
- <B>vce_get_array_maxnum</B>
Summary : Get max number of array elements
Category : array
Prototype : ```int vce_get_array_maxnum( int index )``` 
  - arg 1 : ```int index```
    Array descriptor of target VCE array

  Return value : Max number of elements in the array.

  Description : This function returns max number of elemnts in the array.
Same as vce_init_array's "num" parameter.

  See also : <a href="#vce_get_array_member_size">vce_get_array_member_size</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_member_size"></a>
- <B>vce_get_array_member_size</B>
Summary : Get size of each members of an array
Category : array
Prototype : ```int vce_get_array_member_size( int index )``` 
  - arg 1 : ```int index```
    Array descriptor of target VCE array

  Return value : Array member size (the first argument value of vce_init_array)．
Return a negative error code, in case of invalid argument.

  Description : This is the value of the size argument of vce_init_array
function that gets the size of the array controlled by the VCE array
control routine.

  See also : <a href="#vce_get_array_maxnum">vce_get_array_maxnum</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_object_index"></a>
- <B>vce_get_array_object_index</B>
Summary : Get index number of an element in an VCE array.
Category : array
Prototype : ```int vce_get_array_object_index( int index , void *p )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array.

  - arg 2 : ```void *p```
    Pointer to an element in the array.

  Return value : Return VCE_EINVAL, if an argument is invalid.
If a pointer is not a suitable value, return VCE_EALIGNMENT.
Return 0 or more as index, in case of success.

  Description : The vce_get_array_object_index function determines an index through
subtracting the designated pointer from an array's top pointer.


<a name="vce_get_array_object_last"></a>
- <B>vce_get_array_object_last</B>
Summary : Get last element of VCE array.
Category : array
Prototype : ```void * vce_get_array_object_last( int index )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array.

  Return value : Pointer to the last element of the array.
Returns NULL if no element is available.

  Description : This obtains the pointer to the last element among the VCE arrays in use.
Since vce_alloc_array_object is always added to the head of the link in use,
FIFO-like processing can be done by using vce_alloc_array_object and this
function, in other words, the array that only allows addition to the head
and extraction from the tail.

  See also : <a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_get_array_object_next">vce_get_array_object_next</a><a href="#vce_get_array_object_top">vce_get_array_object_top</a>
<a name="vce_get_array_object_next"></a>
- <B>vce_get_array_object_next</B>
Summary : Get an VCE array element succeedinng given elemnt
Category : array
Prototype : ```void * vce_get_array_object_next( int index , void *p )``` 
  - arg 1 : ```int index```
    Array descriptor of the VCE's array.

  - arg 2 : ```void *p```
    vce_get_array_object_next returns an element in the array
next to the element specified by parameter "p".

  Return value : Pointer to next element.
Null pointer if next element is not found.

  Description : vce_get_array_object_next is used within the ARRAY_SCAN macro.
Regular applications should not use this function directly.
The ARRAY_SCAN macro is safer and sure to use.

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_get_array_object_top">vce_get_array_object_top</a>
<a name="vce_get_array_object_pointer_by_index"></a>
- <B>vce_get_array_object_pointer_by_index</B>
Summary : Get a VCE array element by index number
Category : array
Prototype : ```void *vce_get_array_object_pointer_by_index( int index, int objindex )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array

  - arg 2 : ```int objindex```
    Index of the element which you want to get.

  Return value : Pointer to the element.

  Description : Normally, VCE elements are accessed with ARRAY_SCAN or a pointer;
but you can also access the element by specifying index of it
by this function.
As returning a NULL pointer,
the contents of an error may be known by using vce_get_last_error.

  Example :   // Initialize all elements of array without checking if they're used
  for(int i=0;;i++){
      sometype *t = vce_get_array_object_pointer_by_index( memind, i );
      if( t == NULL )break;
      t->someparam = somevalue;
  }

  See also : <a href="#vce_get_array_object_pointer_by_index_only_used">vce_get_array_object_pointer_by_index_only_used</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_object_pointer_by_index_only_used"></a>
- <B>vce_get_array_object_pointer_by_index_only_used</B>
Summary : Get a VCE array element by index number, which are being used
Category : array
Prototype : ```void * vce_get_array_object_pointer_by_index_only_used( int index, int objindex )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array

  - arg 2 : ```int objindex```
    Index number of the element which you want to get.

  Return value : Pointer to the element. Returns NULL pointer if the element is not used
currently.

  Description : Almost same as vce_get_array_object_pointer_by_index,
but you can select used elements using this function.

  See also : <a href="#vce_get_array_object_pointer_by_index">vce_get_array_object_pointer_by_index</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_array_object_top"></a>
- <B>vce_get_array_object_top</B>
Summary : 
Category : array
Prototype : ```void * vce_get_array_object_top( int index )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array.

  Return value : Pointer to an element in the array.
Null pointer if there is no allocated element in the array.

  Description : vce_get_array_object_top is used inside the ARRAY_SCAN macro.
The ARRAY_SCAN macro is implemented for scanning all the array
elements in use, and this function fetches the head of those elements.
It is often useful for normal
applications to directly use the ARRAY_SCAN macro, not this function.

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_get_array_object_next">vce_get_array_object_next</a>
<a name="vce_get_array_usenum"></a>
- <B>vce_get_array_usenum</B>
Summary : Count how many
Category : array
Prototype : ```int vce_get_array_usenum( int index )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array.

  Return value : Number of currently used elements in an array.

  Description : Get number of elements currently in-use, without scanning
through the array.
This function is really fast because it does not scan the array.

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_get_current_utime"></a>
- <B>vce_get_current_utime</B>
Summary : Get current time by VCEI64 data type
Category : util
Prototype : ```VCEI64 vce_get_current_utime( void )``` 
  Return value : The current time.
In UNIX environment, this function will convert "timeval" structure
into VCEI64 type.
In this case, "timeval" is got by gettimeofday function.
In Win32 environment, this function will convert "SYSTEMTIME"
into VCEI64 type.
In this case, "SYSTEMTIME" is got by GetSystemTime function.

  Description : The source value of timeval
is a value obtained by converting returned value from
gettimeofday().
VCE renews the return value each time vce_heartbeat is invoked.

  See also : <a href="#vce_set_internal_timer">vce_set_internal_timer</a>
<a name="vce_get_ipv4_addr_by_name"></a>
- <B>vce_get_ipv4_addr_by_name</B>
Summary : Get network byte order IPv4 address from host name string
Category : util
Prototype : ```int vce_get_ipv4_addr_by_name( unsigned int *a, const char *s );``` 
  - arg 1 : ```unsigned int *a```
    Pointer to output IPv4 network byte-order address.
equivalent to in_addr.s_addr.

  - arg 2 : ```char *s```
    Hostname. "192.168.1.2" and "www.vce-lab.net" are acceptable.

  Return value : Returns 0 if successful. Otherwise minus error indicator value.

  Description : In UNIX systems, inet_aton(), and gethostbyname() are called sequently.
In Win32 systems, inet_addr(), and gethostbyname() are called sequently.
In PlanetWeb, this is not compatible with DNS resolving.


<a name="vce_get_last_error"></a>
- <B>vce_get_last_error</B>
Summary : Get last error code occured inside VCE library.
Category : err
Prototype : ```int vce_get_last_error(void);``` 
  Return value : Error code.

  Description : The error numbers obtained through by this function are
all defined in vce.h.
Accordingly, details of such error can be known,
or vce_strerror can be used to record it to a log.
However, the contents of string returned by
vce_strerror may possibly be modified in the future,
such output string should not be parsed and used for
further processing.
The error codes defined in vce.h will not be modified.
(becomes a missing number if deleted)

  Example : <pre>
// vce_tcpcontext_create often meets errors...
tcpcontext_t t = vce_tcpcontext_create( .... );
if( !t ){
    vce_errout( "Cannot create tcpcontext! %s\n",
    vce_strerror( vce_get_last_error() ) );
}
</pre>

  See also : <a href="#vce_strerror">vce_strerror</a>
<a name="vce_get_netstat_string"></a>
- <B>vce_get_netstat_string</B>
Summary : Get all connection information maintained by VCE in string format
Category : log
Prototype : ```void vce_get_netstat_string( char *buf, int maxlen )``` 
  - arg 1 : ```char *buf```
    Top address of destination string buffer.

  - arg 2 : ```int maxlen```
    Size of destination string buffer.

  Return value : Returns zero if buffer is not filled up.
Otherwise(if filled) returns VCE_EFULL.

  Description : This fetches information regarding all connections administrated
by VCE in a string buffer.
This looks like output of the UNIX netstat command.
Information of respective connections are "PARAM=VALUE" separated
with commas, and one line represents one connection (socket).
Basic 2 types of lines are "conn" and "listen_conn".
Types of information displayed in "conn" is the most various. 　

<UL>
<LI>In cases of "type=conn"<BR>
"type=conn" represents a normal connection.
<UL>
<LI>r=NUM<BR>
Length of recv buffer (plain)
<LI>w=NUM<BR>
Length of send buffer (plain)
<LI>er=NUM<BR>
Length of recv buffer (encoded)
<LI>ew=NUM<BR>
Length of send buffer (encoded)
<LI>rem=STR<BR>
Remote address, output of vce_conn_get_remote_addr_string
<LI>loc=STR<BR>
Local address, output of vce_conn_get_local_addr_string
<LI>fd=NUM<BR>
Socket fd of operating system.
<LI>s=NUM<BR>
Serial number of conn_t within VCE
<LI>last=NUM<BR>
Date of last access
<LI>timeo=NUM<BR>
Remaining time till timeout
<LI>nego=NUM<BR>
Cipher negotiation state
</ul>

<LI>In case of "type=listen_conn"<BR>
One each of these types are displayed for respective
waiting tcpcontexts, though not representing
connections connected with other hosts.
<ul>
<LI>loc=STR<BR>
Local address, binding a socket.
<LI>fd=NUM File Descriptor of a socket.
</ul>
</ul>
　An application needs to allocate memory for output buffer and
give it to this function.
Please note that you have to allocate relatively big output buffer
because this function uses 200 bytes for each line at most.

  See also : <a href="#vce_get_stat">vce_get_stat</a>
<a name="vce_get_stat"></a>
- <B>vce_get_stat</B>
Summary : Get overall VCE activity statistics information.
Category : log
Prototype : ```void vce_get_stat( vce_stat_t *v )``` 
  - arg 1 : ```vce_stat_t *v```
    Pointer to vce_stat_t which contains statistics information.

  Return value : None

  Description : This function stores entire VCE statistical information in
vce_stat_t structure.
Meanings of structure members are as follows 　
<UL>
<LI>time_t boot_time<BR>
　Startup time of vce_initialize (time_t)
<LI>VCEI64 recv_byte,send_byte<BR>
Total write/read bytes
<LI>VCEI64 send_syscall, send_syscall_e<BR>
Number of invocation of the system call send(),
"_e" represents error occurrence.
<LI>VCEI64 recv_syscall, recv_syscall_e<BR>
Number of invocation of system call recv(),
"_e" represents error occurrence.
<LI>VCEI64 accept_syscall, accept_syscall_e<BR>
Number of invocation of system call accept(),
"_e" represents error occurrence.
<LI>VCEI64 connect_syscall, connect_syscall_e<BR>
Number of invocation of system call connect(),
"_e" represents error occurrence.
<LI>conn_free, conn_alloc, conn_close, conn_write<BR>
Number of invocation of respective VCE functions
<LI>keyex<BR>
Total number of key exchanges using DiffieHellman
key exchange. This is used for load test of key exchanging or others.
<LI>tcpcontext_create,tcpcontext_cleanup,tcpcontext_connect<BR>
Number of invocation of respective functions.
Note that only successful invocation is counted.
<LI>conn_timeout<BR>
Number of connections (conn_t) that met timeout.
<LI>log_count<BR>
Number of invocation of vce_errout or vce_errout0.
</ul>

  See also : <a href="#vce_conn_get_stat">vce_conn_get_stat</a><a href="#vce_tcpcontext_get_stat">vce_tcpcontext_get_stat</a>
<a name="vce_get_tcp_packet_read_size"></a>
- <B>vce_get_tcp_packet_read_size</B>
Summary : PENDING
Category : tcp
Prototype : ```void vce_get_tcp_packet_read_size(int *original, int *processing)``` 
  - arg 1 : ```int *original```
    PENDING

  - arg 2 : ```int *processing```
    PENDING

  Return value : PENDING

  Description : PENDING

  See also : <a href="#vce_get_tcp_packet_read_size">vce_get_tcp_packet_read_size</a>
<a name="vce_get_tcp_packet_write_size"></a>
- <B>vce_get_tcp_packet_write_size</B>
Summary : PENDING
Category : tcp
Prototype : ```void vce_get_tcp_packet_write_size(int *original, int *processing)``` 
  - arg 1 : ```int *original```
    PENDING

  - arg 2 : ```int *processing```
    PENDING

  Return value : None

  Description : PENDING

  See also : <a href="#vce_get_tcp_packet_read_size">vce_get_tcp_packet_read_size</a>
<a name="vce_heartbeat"></a>
- <B>vce_heartbeat</B>
Summary : 
Category : core
Prototype : ```void vce_heartbeat( void )``` 
  Return value : None

  Description : This runs VCE I/O routine once, to flush all incoming/outgoing data.
vce_mainloop function keeps calling this function.
More flexible user main routines can be made using
this function instead of vce_mainloop.
Note that the functions designated by the
vce_set_mainloop_callback function will not be called as
driving VCE with this function.
By default, vce_heartbeat returns straight after it invocation,
however, starting up a server as is will cause full usage of the CPU time.
This situation can be avoided through adjusting the sleep
time using the vce_set_heartbeat_wait_flag function.
Of course, the adjustment to avoid full usage of the CPU time may
also be done on the application side,
and in fact, that will enable best suited CPU time usage
depending on your application.

  Example : <pre>
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
Summary : Test if given element is correctly included in a VCE array.
Category : array
Prototype : ```int vce_if_included_in_array( int index, void *p )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array.

  - arg 2 : ```void *p```
    Pointer to an element in the array.

  Return value : Return 1, if it is included in the specified array.
If not,return 0. In case of invalid argument, return error code.

  Description : This checks if the element designated by void *p is included
in the array.
To check if array elements are included in an array properly,
subtract the head address from p first, then divide the
difference by the size of array elements to obtain the remainder.
When the remainder is not 0, the elements are not
arranged properly.
Even if the remainder is 0, as the quotient is not in the range from 0
to the number of array
elements negative 1, the elements are arranged outside the range-an error.

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#vce_get_array_object_index">vce_get_array_object_index</a><a href="#vce_init_array">vce_init_array</a>
<a name="vce_init_array"></a>
- <B>vce_init_array</B>
Summary : Initialize a new VCE array.
Category : array
Prototype : ```int vce_init_array ( size_t size , int num , char *nm )``` 
  - arg 1 : ```size_t size```
    Size of each elements in the array. Byte count.

  - arg 2 : ```int num```
    Number of lements of the array.

  - arg 3 : ```char *nm```
    Name of the array. This name will help your debugging
because VCE will print out this name when any problem is occured.

  Return value : 
  Description : This zero-clears an array through allocating necessary memory for the array,
and initializes the in-use list at the same time.
VCE arrays are implemented for realizing high-speed array initialization,
searching freelist and releasing buffer through implementing the empty list.
vce_init_array consumes memory roughly estimated as (element size plus 20)
times (number of elements) in bytes.
The int value returned by vce_init_array is like UNIX files' file descriptor,
that is used for later access to arrays.
The VCE array is used as a basic routine of VCE processing.
vce_init_array function uses the MALLOC function internally.

  See also : <a href="#ARRAY_SCAN">ARRAY_SCAN</a><a href="#MALLOC">MALLOC</a><a href="#vce_alloc_array_object">vce_alloc_array_object</a><a href="#vce_end_array">vce_end_array</a><a href="#vce_free_array_object">vce_free_array_object</a><a href="#vce_free_array_object_all">vce_free_array_object_all</a>
<a name="vce_init_limit_t"></a>
- <B>vce_init_limit_t</B>
Summary : Initialize vce_limit_t structure with default value.
Category : core
Prototype : ``` void vce_init_limit_t( vce_limit_t *t )``` 
  Return value : None

  Description : It's always correct way to use vce_init_limit_t function when
you use vce_initialize_limited function.

  See also : <a href="#vce_initialize_limited">vce_initialize_limited</a>
<a name="vce_initialize"></a>
- <B>vce_initialize</B>
Summary : Initialize VCE.
Category : core
Prototype : ```int vce_initialize( void )``` 
  Return value : Returns 0 if successful. Otherwise minus error indicator (see vce.h).

  Description : You have to call this function before calling VCE functions.
Required memory will be allocated inside this function.
This initializes Winsock in Windows environment.
For UNIX, it blocks SIGPIPE.
With regard to VCE for “PlayStation(R)2” ,
invoke this function before initialization of a network by an application,
then invoke ce_set_socket_library_ok(1) at the point the socket library
is initialized. (refer to samples)

  Example : // When no socket library is provided by operating system
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

  See also : <a href="#vce_finalize">vce_finalize</a><a href="#vce_set_socket_library_ok">vce_set_socket_library_ok</a>
<a name="vce_initialize_limited"></a>
- <B>vce_initialize_limited</B>
Summary : Initialize VCE with limited memory configuration
Category : core
Prototype : ```int vce_initialize_limited( vce_limit_t *lim )``` 
  - arg 1 : ```vce_limit_t *lim```
    Pointer to vce_limit_t containing limit information.

  Return value : Returns 0 if successful. Otherwise minus error indicator value (vce.h).

  Description : This is the same as vce_initialize,
though it allows tuning of memory consumption using
vce_limit_t structure.
You have to use vce_init_limit_t function to initialize
vce_limit_t structure with default values before passing it to
vce_initialize_limited function.
In particular, this is used in some situation where ultimate
tuning of memory capacity is demanded.
<PRE>
int max_tcpcontext     Max number of tcpcontext_t
int max_taskgroup      Max number of taskgroup_t
int max_conn           Max number of entire conn_t
int max_search  Max number of the entire search engine
int max_array   Max number of VCE arrays
int sendbuf_work_size  Size of work memory for sending
int recvbuf_work_size  Size of work memory for receiving
</pre>

They can be set with values 0 or larger.
Set -1 to use default value.
<BR>
Please note that you will have to pay attention to minimum
value of max_array. That is because VCE uses array engine inside it
<ul>
<LI>Always 2 arrays are occupied by VCE itself for conn,task
<LI>tcpcontext uses 4 or 5 per 1
<LI>switchcontext uses 3 per 1
<LI>monitoring client uses 2 per 1
<LI>monitoring server uses 5 (4 of them are for tcpcontext ) per 1
<LI>search engine uses 1 per 1
<LI>taskgroup uses 1 per 1
</ul>
These VCE services will return VCE_EARRAY if array is not enough.
So, you may increase max_array if you meet VCE_EARRAY error code.
In addition, when you increase max_array for 1,
it requires 72 bytes of memory accordingly.
In Linux/win32 environment, max_array defaults to 256.
<BR>
<BR>
This function can also be used for the purpose of enlarging the
maximum default value, as well as saving memory
for larger scale applications.
A typical case may change default maximum number of simultaneous
connections of 1000 to larger value.
This function can be used for such purpose, provided that,
attention must be paid to keeping the maximum number of connections
below 1024 by the kernel settings or the limit of the
user process space among most of linux/freeBSD OS's.
To exceed this limit, in most of the cases,
modification of the kernel settings or recompilation is required.
Please look at <a href="linuxtune.html>here</a> for detail tuning of Linux.

  Example : <pre>
int main(){
    // Don't use shared memory and search engine for game clients
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
Summary : Initialize vce_limit_t structure (Clear with default value -1 )
Category : core
Prototype : ```void vce_limit_clear( vce_limit_t *t )``` 
  Return value : None

  Description : This function initializes all member of vce_limit_t structre  with
default value -1. By calling vce_initialize_limited function with
vce_limit_t structure initialized by vce_limit_clear,
vce uses default settings in every configuration.

  See also : <a href="#vce_initialize_limited">vce_initialize_limited</a>
<a name="vce_mainloop"></a>
- <B>vce_mainloop</B>
Summary : 
Category : core
Prototype : ```int vce_mainloop(void)``` 
  Return value : None

  Description : By calling this function, CPU will be occupied by VCE.
This function will never return.
When vce_set_mainloop_callback function defines a callback function,
the defined function will be permanently called from
within this function.
If the function returns the value other than 0,
vce_mainloop returns the value sent back from that function
and will terminate.

  See also : <a href="#vce_set_mainloop_callback">vce_set_mainloop_callback</a>
<a name="vce_make_binary_array_from_hex"></a>
- <B>vce_make_binary_array_from_hex</B>
Summary : Convert hex text into binary data array.
Category : util
Prototype : ```void vce_make_binary_array_from_hex( char *out, int outlen, const char *hex )``` 
  - arg 1 : ```char *out```
    Top address of destination buffer. Binary data will be filled
to this buffer.

  - arg 2 : ```int outlen```
    Length of input string.
If this is not even number, it adds 0 value at the end of input string,
and keep processesing going.

  - arg 3 : ```char *hex```
    Input data string.

  Return value : None

  Description : This creates an array of binary data from a string
such as "788ab0d8ce8df6".
Since one byte is created by two letters,
when data of an odd-numbered characters is designated,
it generates binary data having simply added 0 at the end,
then outputs.
In general, designate even-numbered characters for outputting.
An inverse function is vce_make_hex_from_binary_array

  See also : <a href="#vce_make_hex_from_binary_array">vce_make_hex_from_binary_array</a>
<a name="vce_make_binary_array_from_line"></a>
- <B>vce_make_binary_array_from_line</B>
Summary : Convert 1 line of ASCII text into a binary data array.
Category : util
Prototype : ```void vce_make_binary_array_from_line( const char *line, int linelen, char *out, int *outlen, int *uselen )``` 
  - arg 1 : ```char *line```
    Top address of input line

  - arg 2 : ```int linelen```
    Length of input line

  - arg 3 : ```char *out```
    Output buffer

  - arg 4 : ```int *outlen```
    Length of output buffer. This is value-result parameter.
Firstly it have to contain max length of output buffer,
and then this function fills this parameter with
how many bytes are used actually.

  - arg 5 : ```int *uselen```
    Returns how many bytes actually read from input text.

  Return value : None

  Description : This creates a binary array from a text line.
You can specify a text line in some loose format,
for example it can be terminated by "\r\n" or "\n".
When successful, it returns actual embedded length of the array
stored in "outlen", and actual read length of input
line is stored in "uselen" argument.


<a name="vce_make_hex_from_binary_array"></a>
- <B>vce_make_hex_from_binary_array</B>
Summary : Make a hex string from a binary array
Category : util
Prototype : ```int vce_make_hex_from_binary_array( char *out, int outlen, const char *buf,int len, int folding)``` 
  - arg 1 : ```char *out```
    Top address of output string buffer.

  - arg 2 : ```int outlen```
    Length of output string buffer.

  - arg 3 : ```char *buf```
    Top address of input binary data.

  - arg 4 : ```int len```
    Length of input binary data.

  - arg 5 : ```int folding```
    A flag to decide whether folding every 32 characters
(16 bytes of input) or net. Set 1 for folding, otherwise 0.
In case of folding=0, output string will become a single line without
any carriage return, even though the input length comes to be
particularly long. When fold=1, a "\n" code is added
to the end of output string according to the UNIX way.

  Return value : Returns VCE_EFULL if output buffer is filled up.
Otherwise returns how many bytes are filled.
(null terminator character is not included)

  Description : Since one byte becomes two characters after conversion,
successful results will always lead the output to have
twice as many characters as input characters do.
For instance, "abc" will become "616263". This function is
used by vce_make_hex_text_from_buffer internally.

  See also : <a href="#hextext">hextext</a><a href="#vce_make_hex_text_from_buffer">vce_make_hex_text_from_buffer</a>
<a name="vce_make_hex_text_from_buffer"></a>
- <B>vce_make_hex_text_from_buffer</B>
Summary : Make hextext format ASCII text from a binary data array.
Category : util
Prototype : ```int vce_make_hex_text_from_buffer( const char *buf , int len , char *out , int outlen )``` 
  - arg 1 : ```char *buf```
    Top address of input binary data.

  - arg 2 : ```int len```
    Length of input binary data.

  - arg 3 : ```char *out```
    Top address of output string buffer.

  - arg 4 : ```int outlen```
    Size of output string buffer.

  Return value : Returns VCE_EFULL if outout buffer is filled up.
Otherwise returns how many bytes are filled. ( null terminator
character is not included).

  Description : One byte becomes two characters after conversion.
Necessary information to decode its buffer is described in
leading data header.
For proving its contents, a check-sum value by SHA-1 and
length of content are contained.
When reading, this function checks all these information
is correct.
Converted string can be restored with
vce_make_binary_array_from_hex function.

  See also : <a href="#hextext">hextext</a><a href="#vce_extract_data_from_hex_text">vce_extract_data_from_hex_text</a><a href="#vce_make_binary_array_from_hex">vce_make_binary_array_from_hex</a>
<a name="vce_protocol_acceptwatcher_deny"></a>
- <B>vce_protocol_acceptwatcher_deny</B>
Summary : accept watcher for TCP conn_t which denies all connection.
Category : watcher
Prototype : ```int vce_protocol_acceptwatcher_deny( conn_t c )``` 
  - arg 1 : ```conn_t c```
    An instance of conn_t, which is newly accepted by a server tcpcontext_t.

  Return value : This function always returns -1, so no new connections are accepted.

  Description : This function is passed to vce_tcpcontext_create function
as its argument.
When this function is set in a TCPcontext, all connections
are rejected and any client cannot connect to the server.
This function is for debugging.

  See also : <a href="#vce_protocol_acceptwatcher_noop">vce_protocol_acceptwatcher_noop</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_acceptwatcher_noop"></a>
- <B>vce_protocol_acceptwatcher_noop</B>
Summary : accept() watcher for TCP conn_t which accepts all connection.
Category : watcher
Prototype : ```int vce_protocol_acceptwatcher_noop( conn_t c )``` 
  - arg 1 : ```conn_t c```
    An instance of conn_t, which is newly accepted by a server tcpcontext_t.

  Return value : Always returns zero, so automatically all new connections are
accepted without any limitation.

  Description : 
  See also : <a href="#vce_protocol_acceptwatcher_deny">vce_protocol_acceptwatcher_deny</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_closewatcher_noop"></a>
- <B>vce_protocol_closewatcher_noop</B>
Summary : TCP connection close watcher which does nothing
Category : watcher
Prototype : ```int vce_protocol_closewatcher_noop( conn_t c )``` 
  - arg 1 : ```conn_t c```
    An instance of conn_t which will be closed by this function call.

  Return value : This function always returns zero.

  Description : This callback function can be set in TCPcontext.
This function do not perform anything, so all request for new
TCP connection from clients are accepted.
You can use "NULL" instead of this function, but you'd better
use this function because your source code will be more cleaner.

  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_parser_bin16"></a>
- <B>vce_protocol_parser_bin16</B>
Summary : Get a bin16 record and call callback function.
Category : parser
Prototype : ```int vce_protocol_parser_bin16( conn_t c )``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  Return value : Returns zero if received data is not enough.
Returns return value of callback function as it is,
if data record is complete and could call protocol callback function.

  Description : vce_protocol_parser_bin16 function detects and fetches data record
from raw data sent to a conn_t.
It fetches a protocol record that is named bin16.
Each time a record is detected, a callback function is called.
The callback function is set when vce_tcpcontext_create.

<BR>
In VCE application, you may want to use bin16 protocol
in almost all cases, because VCE is very good at processing
"many small packets".
<BR>
<BR>
<B> Content of bin16 protocol</B><BR>
One record passed through a socket is formatted as follows.
Here you will see C-like virtual code
<pre>
struct packet
{
unsigned short content_length;
char buf[content_length];
}
</pre>

This means that 10-byte data brings about 12-byte of
actual data sent (10 + sizeof(unsigned short)).
<BR><BR>
<B>Callback function definition</B><BR>
Definition of a callback function is
<PRE>
int callback( conn_t *c, char *data, int len )
</pRE>
<code>conn_t *c</code> is for target connection,
and <code>char *data</code> is for pointer to the buffer,
<code>int len</code> is length of the input buffer.


  See also : <a href="#vce_protocol_parser_bin32">vce_protocol_parser_bin32</a><a href="#vce_protocol_parser_text">vce_protocol_parser_text</a><a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_parser_bin32"></a>
- <B>vce_protocol_parser_bin32</B>
Summary : Get a bin32 record and call callback function
Category : parser
Prototype : ```int vce_protocol_parser_bin32( conn_t c )``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  Return value : Returns zero if received data is not completed.
Returns return value of protocol callback function
if data record is completed, and could call protocol callback function.

  Description : This function is designed for finding a record from received data
by a conn_t, and is applicable up to the 32-bit(4G) record length.
Since such long data record would just become the cause of quality
problem actually, detection is possible up to the length of
BIN32DATA_MAX.
When input record is longer than BIN32DATA_MAX,
that record is judged as a server-cracking, and
protocol error will be returned.
VCE shuts down the connection in this case.
BIN32DATA_MAX is defined within vce.h.

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_protocol_unparser_bin32">vce_protocol_unparser_bin32</a>
<a name="vce_protocol_parser_text"></a>
- <B>vce_protocol_parser_text</B>
Summary : Get each line from stream and call protocol callback function
Category : parser
Prototype : ```int vce_protocol_parser_text( conn_t c )``` 
  - arg 1 : ```conn_t c```
    target conn_t

  Return value : Returns zero if received data is not completed.
Returns return value of protocol callback function
if data record is completed, and could call protocol callback function.

  Description : This function fetches a line from received data by a conn_t,
by text parsing.
You should note that third person between your server and
clients will probably/accidentaly see content of the packets if you don't
use encryption. Text protocol is the most easy protocol to be
inspected by some sniffering program like "tcpdump".
<BR>
There are two types of delimiter characters for breaking line,
which are "\n" and "\r\n".
Also, input data to protocol callback function is NOT a C character
string with NULL-termination.
Therefore, data must be converted to the C string by using
vce_makecstr function.

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a>
<a name="vce_protocol_parser_through"></a>
- <B>vce_protocol_parser_through</B>
Summary : A protocol parser for calling callback without reading records.
Category : parser
Prototype : ```int vce_protocol_parser_through( conn_t ct )``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  Return value : It returns callback function's reeturn value as it is.
Therefore the connection is shut down automatically when the callback
function returns negative value.

  Description : Some protocols do not have a concept of record.
This parser function is designed for use of these cases.
This function does not perform any processing before
passing the input data to protocol callback function.

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_protocol_unparser_through">vce_protocol_unparser_through</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_dump"></a>
- <B>vce_protocol_pcallback_dump</B>
Summary : Protocol callback function for dumping data input from TCP connection
Category : pcallback
Prototype : ```int vce_protocol_pcallback_dump( conn_t ct, char *data, int len )``` 
  - arg 1 : ```conn_t ct```
    Processing conn_t. 

  - arg 2 : ```char *data```
    Top address of received data.

  - arg 3 : ```int len```
    Length of received data.

  Return value : Always returns zero because this function tramsmits nothing.

  Description : This function dumps all input data received by conn_t.
This function is prepared for
the purpose of debugging.
This function is called as a "protocol callback function".

  See also : <a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a><a href="#vce_protocol_pcallback_noop">vce_protocol_pcallback_noop</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_echo_bin16"></a>
- <B>vce_protocol_pcallback_echo_bin16</B>
Summary : Echo callback function for normal TCP bin16 protocol
Category : pcallback
Prototype : ```int vce_protocol_pcallback_echo_bin16( conn_t ct, char *data, int len )``` 
  - arg 1 : ```conn_t ct```
    Processing conn_t. 

  - arg 2 : ```char *data```
    Top address of received data

  - arg 3 : ```int len```
    Length of received data

  Return value : Returns minus value if error occured.
Returns larger than zero if transmit is successful.

  Description : This function is a protocol callback function,
which is specified when calling
vce_tcpcontext_set_conn_parser function.
This function echoes input data into output buffer as it is.
To use this function, you have to have bin16 parser by
vce_tcpcontext_set_conn_parser, and vce_protocol_parser_bin16.
<BR>
In actual application, you should use your original protocol
callback function, but you may be able to use this echo function
for your debugging.

  See also : <a href="#vce_protocol_pcallback_dump">vce_protocol_pcallback_dump</a><a href="#vce_protocol_pcallback_noop">vce_protocol_pcallback_noop</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_echo_text"></a>
- <B>vce_protocol_pcallback_echo_text</B>
Summary : Echo callback function for normal TCP text line-based protocol
Category : pcallback
Prototype : ```int vce_protocol_pcallback_echo_text(conn_t ct, char *data, int len )``` 
  - arg 1 : ```conn_t ct```
    Processing conn_t.

  - arg 2 : ```char *data```
    Top address of received data

  - arg 3 : ```int len```
    Length of received data.

  Return value : Returns minus error indicator value.
Returns larger than zero if tramsmit is successful.

  Description : Copies input data into output buffer using text protocol unparser
( vce_protocol_unparser_text function).

  See also : <a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a><a href="#vce_protocol_unparser_text">vce_protocol_unparser_text</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_pcallback_noop"></a>
- <B>vce_protocol_pcallback_noop</B>
Summary : No-Operation callback function for normal TCP connection ( conn_t )
Category : pcallback
Prototype : ```int vce_protocol_pcallback_noop( conn_t ct ,char *data , int len )``` 
  - arg 1 : ```conn_t ct```
    Processing conn_t. 

  - arg 2 : ```char *data```
    Top address of received data.

  - arg 3 : ```int len```
    Length of received data (in bytes).

  Return value : Always returns zero, because this function transmits nothing.

  Description : This function will be specified as an argument to
vce_tcpcontext_set_conn_parser function.
This function just throws away all input data from the conn_t.
In most cases your application don't use this funciton,
but use your original protocol callback function made by yourself.
You may be able to use this function to make your server be quiet
temporarily.

  See also : <a href="#vce_protocol_pcallback_dump">vce_protocol_pcallback_dump</a><a href="#vce_protocol_pcallback_echo_bin16">vce_protocol_pcallback_echo_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_unparser_bin16"></a>
- <B>vce_protocol_unparser_bin16</B>
Summary : Format data into bin16 protocol and write it to a connection.
Category : parser
Prototype : ```int vce_protocol_unparser_bin16( conn_t ct, char *data , int len  )``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  - arg 2 : ```char *data```
    Pointer to input data, which will be transmitted after processing.

  - arg 3 : ```int len```
    Length of input data.

  Return value : Returns number of bytes which is written into the conn_t.
Returns minus error code when any error.
Because this function sends a small data header at the same time,
so number of bytes will be 2 bytes larger than written data itself.
You can consult vce_protocol_parser_bin16 function for detail
content of each records.

  Description : This function is a formatter function for bin16 protocol.
This function sends a data record into a conn_t.
The record is formatted like [header + data].
The header part is always 2 bytes.
<B>Length of sent data</B><BR>
bin16 protocol does not corrupt outgoing data, just it chooses
from two choices send it completely, or do not send.
For example when you want to send 20 bytes of data,
this funciton will return 22 (20 + 2 )  or minus error code.

  Example : <pre>
  // Example of protocol callback function for echoing server
  int callback( conn_t ct, char *data, int len )
  {
      return vce_protocol_unparser_bin16( ct,data,len );
  }
</pre>  

  See also : <a href="#vce_protocol_parser_bin16">vce_protocol_parser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_unparser_bin32"></a>
- <B>vce_protocol_unparser_bin32</B>
Summary : Write a BIN32 record to a conn_t instance
Category : parser
Prototype : ```int vce_protocol_unparser_bin32( conn_t ct, char *data, int len )``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  - arg 2 : ```char *data```
    Pointer to input data which will be transmitted after processing.

  - arg 3 : ```int len```
    Length(byets) of input data.

  Return value : Returns number of bytes which is put out.
Returns minus error code if any errors.
SUccessful return value is always 4 bytes larger than input
data length.

  Description : bin32 protocol is used when you want to send larger packets than
64kb size, which is the maximum size of bin16 protocol.
You can send larger size packets, but at most BIN32DATA_MAX bytes.

  See also : <a href="#vce_protocol_parser_bin32">vce_protocol_parser_bin32</a><a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a>
<a name="vce_protocol_unparser_text"></a>
- <B>vce_protocol_unparser_text</B>
Summary : write a text protocol line into conn_t
Category : parser
Prototype : ```int vce_protocol_unparser_text( conn_t ct, char *data, int len )``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  - arg 2 : ```char *data```
    Pointer to input data which will be transmitted after processing.

  - arg 3 : ```int len```
    Length(bytes) of input data

  Return value : Returns number of bytes which is put out.
Returns minus error code when any errors.
Successful return value is always 1 bytes larger than
original input data.

  Description : This function will write input data without any escaping,
or any processing.
This function will add "\n" at the tail of input data,
so length of outgoing data is always 1 byte larger than original data.

  See also : <a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_protocol_unparser_through"></a>
- <B>vce_protocol_unparser_through</B>
Summary : Write data directly into a TCP connection.
Category : parser
Prototype : ```int vce_protocol_unparser_through( conn_t ct, char *data, int len)``` 
  - arg 1 : ```conn_t ct```
    target conn_t

  - arg 2 : ```char *data```
    Pointer to input data which will be transmitted after processing.

  - arg 3 : ```int len```
    Length(bytes) of input data.

  Return value : Length of transmitted data(in bytes).
Returns minus error indicator value if any error occured.

  Description : This function will write input data into conn_t.

  See also : <a href="#vce_protocol_parser_through">vce_protocol_parser_through</a><a href="#vce_protocol_unparser_bin16">vce_protocol_unparser_bin16</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_read_plain_text_file"></a>
- <B>vce_read_plain_text_file</B>
Summary : Read plain text file by callback function
Category : util
Prototype : ```int vce_read_plain_text_file( const char *filename, int (*callback)(char*,in,char*))``` 
  - arg 1 : ```char *filename```
    Filename of configuration file.

  - arg 2 : ```int (*callback) (char *filename,int lineno,char *line )```
    Callback function for processing content of file.

  Return value : Returns VCE_EACCESSFILE if the file is not readable.
Returns zero if successful.
If callback function returned minus value,
this function quits read-loop and returns the value
which is returned by the callback function.

  Description : 
  See also : <a href="#vce_read_simple_config_file">vce_read_simple_config_file</a>
<a name="vce_read_simple_config_file"></a>
- <B>vce_read_simple_config_file</B>
Summary : Read simple text configuration file by callback function
Category : util
Prototype : ```int vce_read_simple_config_file( const char *filename, int ( *callback ) ( char *,int,char *,char *) )``` 
  - arg 1 : ```char *filename```
    Filename of configuration file being read.

  - arg 2 : ```int (*callback) (char *filename,int lineno,char *param, char *value)```
    Callback function for parsing content of file.

  Return value : Returns VCE_EACCESSFILE if the file is not readable.
Returns zero if successful.
If callback function returned minus value,
this function quits read-loop and returns the value
which is returned by the callback function.

  Description : 
  See also : <a href="#swp">swp</a><a href="#vce_copy_cstring_upto">vce_copy_cstring_upto</a><a href="#vp">vp</a>
<a name="vce_replace_malloc_funcs"></a>
- <B>vce_replace_malloc_funcs</B>
Summary : Replace malloc function used inside VCE.
Category : util
Prototype : ```void vce_replace_malloc_funcs( void*(*a)(size_t), void*(*r)(void*,size_t), void(*f)(void*))``` 
  - arg 1 : ```void * (*a)(size_t)```
    Pointer to memory allocator function.
Ignore if this parameter is set NULL.

  - arg 2 : ```void*(*a)(void*,size_t)```
    Pointer to memory re-allocator function.
Ignore if this parameter is set NULL.

  - arg 3 : ```void (*f)(void*)```
    Pointer to memory free function.
Ignore if this parameter is set NULL.

  Return value : None

  Description : 

<a name="vce_set_heartbeat_wait_flag"></a>
- <B>vce_set_heartbeat_wait_flag</B>
Summary : Control vce_heartbeat's sleep timer adjustment.
Category : core
Prototype : ```void vce_set_heartbeat_wait_flag( int flag )``` 
  - arg 1 : ```int flag```
    wait flag will be off when 0, or on if 1.

  Return value : None

  Description : 
  See also : <a href="#vce_heartbeat">vce_heartbeat</a>
<a name="vce_set_mainloop_callback"></a>
- <B>vce_set_mainloop_callback</B>
Summary : 
Category : core
Prototype : ```void vce_set_mainloop_callback( int (*f)(void) )``` 
  - arg 1 : ```int (*f)(void)```
    Pointer to callback function.

  Return value : None. always success.

  Description : 
  See also : <a href="#vce_heartbeat">vce_heartbeat</a><a href="#vce_mainloop">vce_mainloop</a>
<a name="vce_set_read_write_log_mode"></a>
- <B>vce_set_read_write_log_mode</B>
Summary : Set log mode flag to print VCE's read/write system calls
Category : core
Prototype : ```void vce_set_read_write_log_mode( int mode )``` 
  - arg 1 : ```int mode```
    Output log information if set 1. Nothing will output if zero.

  Return value : None

  Description : 
  See also : <a href="#vce_set_verbose_mode">vce_set_verbose_mode</a>
<a name="vce_set_socket_library_ok"></a>
- <B>vce_set_socket_library_ok</B>
Summary : Notify VCE that underlying socket library is initialized .
Category : core
Prototype : ```void vce_set_socket_library_ok( int flag )``` 
  - arg 1 : ```int flag```
    Initialize flag. Set 1 if socket library is already OK,
otherwise 0.

  Return value : None

  Description : 
  See also : <a href="#vce_initialize">vce_initialize</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_set_verbose_mode"></a>
- <B>vce_set_verbose_mode</B>
Summary : Configure verbose mode for entire VCE library.
Category : core
Prototype : ```void vce_set_verbose_mode( int mode )``` 
  - arg 1 : ```int mode```
    Set verbose mode if larger than zero. Normal mode is set if zero.
"Totaly quiet mode" if -1.

  Return value : None

  Description : 

<a name="vce_show_array_usage"></a>
- <B>vce_show_array_usage</B>
Summary : Print all information about a VCE array.
Category : array
Prototype : ```int vce_show_array_usage( int index , int show_all )``` 
  - arg 1 : ```int index```
    Array descriptor to specify VCE's array.

  - arg 2 : ```int show_all```
    Set 1 if you want description about all elements in VCE array,
otherwise set zero.
You will get huge amount of output string by setting 1.

  Return value : Return number of elements which are currently used.

  Description : This function is created for debugging.
It designates an array, and information about the elements controlled by the
array will be output to a log.
NOTE If the VCE library that is built with the setting
to suppress an error output is linked, this function will output
nothing even when VCE_ESUPPORT is returned.

  Bugs/TODO : Since this function uses the standard error output for outputting,
calling of this function becomes invalid when the
work environment is Win32GUI where the standard error output is not usable.

  See also : <a href="#vce_init_array">vce_init_array</a>
<a name="vce_snprintf"></a>
- <B>vce_snprintf</B>
Summary : wrapper function for libc's snprintf
Category : text
Prototype : ```void vce_snprintf( char *out, int len, const char *format, ... )``` 
  - arg 1 : ```char *out```
    Top address of output string buffer.

  - arg 2 : ```int len```
    Length of output buffer.

  - arg 3 : ```char *format```
    Format string

  Return value : None

  Description : 

<a name="vce_strerror"></a>
- <B>vce_strerror</B>
Summary : Convert VCE error code into string.
Category : err
Prototype : ```char *vce_strerror( int ecode );``` 
  - arg 1 : ```int ecode```
    Error code defined in vce.h.

  Return value : Pointer to returned string.

  Description : 
  See also : <a href="#vce_get_last_error">vce_get_last_error</a>
<a name="vce_strerror_close_reason"></a>
- <B>vce_strerror_close_reason</B>
Summary : Convert VCE CLOSE_REASON code into string.
Category : err
Prototype : ```char *vce_strerror_close_reason( CLOSE_REASON reason );``` 
  - arg 1 : ```CLOSE_REASON reason```
    CLOSE_REASON Error code defined in vce.h.

  Return value : Pointer to returned string.

  Description : 

<a name="vce_tcpcontext_cleanup"></a>
- <B>vce_tcpcontext_cleanup</B>
Summary : Clean up a TCP context.
Category : tcp
Prototype : ```void vce_tcpcontext_cleanup( tcpcontext_t tp )``` 
  - arg 1 : ```tcpcontext_t tp```
    Pointer to tcpcontext_t. This pointer is obtained when calling
vce_tcpcontext_create. This function can used for freeing both server context
and client context .

  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_conn_iterate"></a>
- <B>vce_tcpcontext_conn_iterate</B>
Summary : Call a function against every element of a tcpcontext_t
Category : 
Prototype : ```int vce_tcpcontext_conn_iterate( tcpcontext_t tt, int (*f)(conn_t c))``` 
  - arg 1 : ```tcpcontext_t tt```
    Target TCPcontext.

  - arg 2 : ```int (*f)(conn_t c)```
    Callback function which is called against every elements of
conn.

  Return value : Returns 0 if successful, otherwise minus error indicating code.

  Description : 
  See also : <a href="#vce_tcpcontext_get_all_connection">vce_tcpcontext_get_all_connection</a>
<a name="vce_tcpcontext_connect"></a>
- <B>vce_tcpcontext_connect</B>
Summary : Connect to a remote VCE server and set up a TCP connection.
Category : tcp
Prototype : ```conn_t vce_tcpcontext_connect( tcpcontext_t tp, const char *hostname, unsigned short port );``` 
  - arg 1 : ```tcpcontext_t tp```
    TCPcontext containing configuration information for new
TCP connection.

  - arg 2 : ```char *hname```
    Hostname to connect, or IPaddress string.

  - arg 3 : ```unsigned short port```
    Port number to connect.

  Return value : Returns pointer to newly allocated conn_t struct, which is for
controlling one TCP connection. Returns NULL pointer when any error.
To get detailed error , you'll use vce_get_last_error.

  Description : 
  See also : <a href="#vce_conn_is_valid">vce_conn_is_valid</a><a href="#vce_conn_writable">vce_conn_writable</a><a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_count_connections"></a>
- <B>vce_tcpcontext_count_connections</B>
Summary : Count number of connections maintained by a tcpcontext
Category : tcp
Prototype : ```int vce_tcpcontext_count_connections( tcpcontext_t t, int *conn )``` 
  - arg 1 : ```tcpcontext_t t```
    Target TCPcontext.

  - arg 2 : ```int *conn```
    Top address of return buffer.
It will be ignored if set NULL.

  Return value : Returns 0 if successful, otherwise minus error indicator value.

  Description : 
  See also : <a href="#vce_tcpcontext_get_all_connection">vce_tcpcontext_get_all_connection</a>
<a name="vce_tcpcontext_create"></a>
- <B>vce_tcpcontext_create</B>
Summary : Initialize and allocate a TCP context.
Category : tcp
Prototype : ```tcpcontext_t vce_tcpcontext_create( int flag, const char *bindaddr, unsigned short port, int maxcon, size_t rblen, size_t wblen, int timeout, VCE_BLOCK_CIPHER cipher, int shkeylen , int nonblock_connect, int nodelay, size_t statebuf_size )``` 
  - arg 1 : ```int flag```
    Basic configuration flag for TCPcontext's basic operation.
If 1, it will create IPv4 server tcpcontext.
If 0, it will create IPv4 client tcpcontext.

  - arg 2 : ```char *bindaddr```
    IP address for binding a socket.
For ordinary usage, you use "0.0.0.0" for this.
If you want to bind a socket to a specific address, you can specify it
like "192.168.1.11"

  - arg 3 : ``` unsigned short port```
    Port number to bind a socket.
In UNIX(Linux), you have to be a super user when you want to use
port number less than 1024.
It's completely OK if it's larger than 7000.

  - arg 4 : ```int maxcon```
    Max number of concurrrent TCP sessions.
VCE can support as many TCP sessions as the OS can handle,
but you can restrict number of TCP sessions less than OS limit.
In Linux you can use 1000 or more sessions, in MS-Windows
you can use 64(98/Me) or it depends on memory you have.
We don't recomend you to use too many TCP sessions (>2000)
in one machine for performance and security reasons.
You cannot specify this argument larger than the number that
you previously set by vce_initialize_limited function,
or Linux default value 1000.

  - arg 5 : ```size_t rblen```
    Max length of receiving data from network.
This length is used by each TCP sessions ( conn_t ).

  - arg 6 : ```size_t wblen```
    Max length of outgoing data to network.

  - arg 7 : ```int timeout```
    TCP session timeout in seconds.
If a TCP session doesn't have outgoing data nor incoming data for a
length of time, VCE will close the session according to this configuration.
It rises an error if you try to write any data into closed(timed out)
TCP session.

  - arg 8 : ```VCE_BLOCK_CIPHER cipher```
    
  - arg 9 : ```int shkeylen```
    If you want to use encrypted connection,
you should use one of them VCE_BLOCK_CIPHER_BLOWFISH,
VCE_BLOCK_CIPHER_RIJNDAEL, VCE_BLOCK_CIPHER_TWOFISH.
If you don't want to use encryption, you use VCE_BLOCK_CIPHER_NONE.
Each algorithm has different characteristics each other.
BLOWFISH is the fastest and oldest, but they say it's relatively
weaker. RIJNDAEL is relatively new and strong, but 20% slower.
Yes, let's use RIJNDAEL without thinking about it so long.
In our benchmark, RIJNDAEL at 800MHz PentiumIII can encode 20Mbit/s.
When you use encryption, you may not be able to ignore
server-side CPU high load.

  - arg 10 : ```int nonblock_connect```
    
  - arg 11 : ```nodelay```
    
  - arg 12 : ```size_t statebuf_size```
    
  Return value : Return pointer to a TCPcontext.
Return NULL pointer if any error.

  Description : 
  See also : <a href="#vce_conn_get_state">vce_conn_get_state</a><a href="#vce_initialize">vce_initialize</a><a href="#vce_initialize_limited">vce_initialize_limited</a><a href="#vce_tcpcontext_cleanup">vce_tcpcontext_cleanup</a><a href="#vce_tcpcontext_connect">vce_tcpcontext_connect</a><a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a><a href="#vce_tcpcontext_set_conn_closewatcher">vce_tcpcontext_set_conn_closewatcher</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_tcpcontext_enable_accept"></a>
- <B>vce_tcpcontext_enable_accept</B>
Summary : PENDING
Category : tcp
Prototype : ```void vce_tcpcontext_enable_accept( tcpcontext_t tp, int flag )``` 
  - arg 1 : ```tcpcontext_t tp```
    Target TCPcontext

  - arg 2 : ```int flag```
    Accept next TCPconnection if set 1.
Deny all new TCPconnections if set 0.

  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_close_all_conn">vce_tcpcontext_close_all_conn</a>
<a name="vce_tcpcontext_get_all_connection"></a>
- <B>vce_tcpcontext_get_all_connection</B>
Summary : get all connections included in a tcpcontext
Category : tcp
Prototype : ```int vce_tcpcontext_get_all_connection( tcpcontext_t t , conn_t *a, int max);``` 
  - arg 1 : ```tcpcontext_t t```
    Target TCPcontext.

  - arg 2 : ```conn_t *a```
    Top address of an array of conn_t.

  - arg 3 : ```int max```
    Max number of elements of array parameter "a".

  Return value : Number of elements filled in given array.
This number must be larger than or equal to zero.

  Description : 
  See also : <a href="#vce_tcpcontext_count_connections">vce_tcpcontext_count_connections</a>
<a name="vce_tcpcontext_get_stat"></a>
- <B>vce_tcpcontext_get_stat</B>
Summary : Get tcpcontext's statistics information
Category : tcp
Prototype : ```void vce_tcpcontext_get_stat( tcpcontext_t tp, tcpcontext_stat_t *s )``` 
  - arg 1 : ```tcpcontext_t tp```
    Target TCPcontext.

  - arg 2 : ```tcpcontext_stat_t *s```
    Top address of tcpcontext_stat_t instance. It will save all
status information in this structure.

  Return value : None

  Description : 
  See also : <a href="#vce_conn_get_stat">vce_conn_get_stat</a><a href="#vce_get_stat">vce_get_stat</a>
<a name="vce_tcpcontext_protocol_set_maxlength"></a>
- <B>vce_tcpcontext_protocol_set_maxlength</B>
Summary : pending
Category : tcp
Prototype : ```void vce_tcpcontext_protocol_set_maxlength(tcpcontext_t ct,int maxlength,int(*errcall)(conn_t ct))``` 
  - arg 1 : ```tcpcontext_t t```
    TCPcontext containing configuration information for new
TCP connection.

  - arg 2 : ```int max_length```
    pending

  - arg 3 : ```int(*errcall)(conn_t ct))```
    pending

  Return value : none

  Description : pending

  Bugs/TODO : pending


<a name="vce_tcpcontext_set_accept_max"></a>
- <B>vce_tcpcontext_set_accept_max</B>
Summary : pending
Category : tcp
Prototype : ```void vce_tcpcontext_set_accept_max(tcpcontext_t t,int con_max,int (*accept_warning)(tcpcontext_t t))``` 
  - arg 1 : ```tcpcontext_t t```
    TCPcontext containing configuration information for new
TCP connection.

  - arg 2 : ```int con_max```
    pending

  - arg 3 : ```int (*accept_warning)(tcpcontext_t t)```
    pending

  Return value : none

  Description : pending


<a name="vce_tcpcontext_set_conn_acceptwatcher"></a>
- <B>vce_tcpcontext_set_conn_acceptwatcher</B>
Summary : Make TCPcontext use specified accept watcher function
Category : tcp
Prototype : ```void vce_tcpcontext_set_conn_acceptwatcher( tcpcontext_t tp, int (*aw)(conn_t) )``` 
  - arg 1 : ```tcpcontext_t tp```
    Target TCPcontext

  - arg 2 : ```int (*aw)(conn_t c)```
    Accept watcher function. parameter "c" stands for a newly
accepted connection conn_t.

  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_closewatcher">vce_tcpcontext_set_conn_closewatcher</a>
<a name="vce_tcpcontext_set_conn_call_parser_per_heartbeat"></a>
- <B>vce_tcpcontext_set_conn_call_parser_per_heartbeat</B>
Summary : Adjust number of times of each conn_t parser call within a heartbeat
Category : tcp
Prototype : ```void vce_tcpcontext_set_conn_call_parser_per_heartbeat( tcpcontext_t tt, int v )``` 
  - arg 1 : ```tcpcontext_t tt```
    Target TCpcontext.

  - arg 2 : ```int v```
    Number of repetation. No operation is defined when setting minus
to this parameter.

  Return value : 
  Description : 
  See also : <a href="#vce_heartbeat">vce_heartbeat</a><a href="#vce_tcpcontext_set_conn_parser">vce_tcpcontext_set_conn_parser</a>
<a name="vce_tcpcontext_set_conn_closewatcher"></a>
- <B>vce_tcpcontext_set_conn_closewatcher</B>
Summary : Make TCPcontext use specified close watcher function
Category : tcp
Prototype : ```void vce_tcpcontext_set_conn_closewatcher( tcpcontext_t tp, int (*cw)(conn_t,CLOSE_REASON) )``` 
  - arg 1 : ```tcpcontext_t tp```
    Target TCPcontext.

  - arg 2 : ```int (*cw)(conn_t c, CLOSE_REASON reason)```
    
  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a>
<a name="vce_tcpcontext_set_conn_finalizer"></a>
- <B>vce_tcpcontext_set_conn_finalizer</B>
Summary : Make TCPcontext use specified conn_t finalizer .
Category : tcp
Prototype : ```void vce_tcpcontext_set_conn_finalizer( tcpcontext_t tp , void *finalizer(conn_t) )``` 
  - arg 1 : ```tcpcontext_t tp```
    Pointer to target TCPcontext.

  - arg 2 : ```void *finalizer(conn_t to_be_finalized )```
    Pointer to finalizer function.
"to_be_finalized" parameter stands for a connection which is
being closed.

  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_set_conn_hiwater_acceptwatcher"></a>
- <B>vce_tcpcontext_set_conn_hiwater_acceptwatcher</B>
Summary : Set a special high water accept watcher to a TCPcontext
Category : tcp
Prototype : ```void vce_tcpcontext_set_conn_hiwater_acceptwatcher( tcpcontext_t tp, int water, int (*aw)(conn_t,int))``` 
  - arg 1 : ```tcpcontext_t tp```
    Target TCPcontext

  - arg 2 : ```int water```
    Number to specify high water, that means max number of
concurrent TCP sessions handled by the TCPcontext.
TCPcontext will call specified accept watcher function
when number of concurrent sessions are larger than this,
otherwise call default accept watcher.

  - arg 3 : ```int (*aw)(conn_t c,int num)```
    accept watcher function that will be set to the TCPcontext.
This function is different from normal one because it will get
current number of concurrent sessions by "num" argument.
You can compare it with pre-set max number of sessions.

  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_acceptwatcher">vce_tcpcontext_set_conn_acceptwatcher</a>
<a name="vce_tcpcontext_set_conn_kickip_array"></a>
- <B>vce_tcpcontext_set_conn_kickip_array</B>
Summary : pending
Category : tcp
Prototype : ```void vce_tcpcontext_set_conn_kickip_array(tcpcontext_t tp,unsigned int *null_terminated_ipaddr_array)``` 
  - arg 1 : ```tcpcontext_t t```
    TCPcontext containing configuration information for new
TCP connection.

  - arg 2 : ```unsigned int *null_terminated_ipaddr_array```
    pending

  Return value : none

  Description : pending


<a name="vce_tcpcontext_set_conn_parser"></a>
- <B>vce_tcpcontext_set_conn_parser</B>
Summary : Make TCPcontext use specified parser function
Category : tcp
Prototype : ```void vce_tcpcontext_set_conn_parser( tcpcontext_t tp, int (*parser)(conn_t),int (*pcallback)(conn_t,char*,int))``` 
  - arg 1 : ```tcpcontext_t tp```
    Target TCPcontext

  - arg 2 : ```int (*parser)(conn_t c )```
    Pointer to parser function.

  - arg 3 : ```int (*pcallback)(conn_t c,char *data, int len )```
    Callback function which is called every time when receiving
data record from the connection.

  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a><a href="#vce_tcpcontext_set_conn_call_parser_per_heartbeat">vce_tcpcontext_set_conn_call_parser_per_heartbeat</a>
<a name="vce_tcpcontext_set_equal_io_splitrate"></a>
- <B>vce_tcpcontext_set_equal_io_splitrate</B>
Summary : Configure number of connections to be flushed to network
Category : tcp
Prototype : ```void vce_tcpcontext_set_equal_io_splitrate( tcpcontext_t tt, int v )``` 
  - arg 1 : ```tcpcontext_t tt```
    Target TCPcontext.

  - arg 2 : ```int v```
    Process ( total / v ) connections among all connections in
one vce_heartbeat call.

  Return value : None

  Description : 

<a name="vce_tcpcontext_timeout_control"></a>
- <B>vce_tcpcontext_timeout_control</B>
Summary : Configure timeout operation on a tcpcontext_t.
Category : tcp
Prototype : ```void vce_tcpcontext_timeout_control( tcpcontext_t tp, int recv_reset, int send_reset )``` 
  - arg 1 : ```tcpcontext_t t```
    Target TCPcontext.

  - arg 2 : ```int recv_reset```
    By setting 1, it initializes timeout counter when any data is
received from client. By default, 1 is used.

  - arg 3 : ```int send_reset```
    By setting 1, it initializes timeout counter when any data
is sent to client. Default is zero, but some application
sets this flag 1.

  Return value : None

  Description : 
  See also : <a href="#vce_tcpcontext_create">vce_tcpcontext_create</a>
<a name="vce_tcpcontext_userdata_get_pointer"></a>
- <B>vce_tcpcontext_userdata_get_pointer</B>
Summary : 
Category : tcp
Prototype : ```void *vce_tcpcontext_userdata_set_pointer(tcpcontext_t ct);``` 
  - arg 1 : ```tcpcontext_t ct```
    
  Return value : 
  Description : 

<a name="vce_tcpcontext_userdata_set_pointer"></a>
- <B>vce_tcpcontext_userdata_set_pointer</B>
Summary : 
Category : tcp
Prototype : ```void vce_tcpcontext_userdata_set_pointer(tcpcontext_t ct,void *p);``` 
  - arg 1 : ```tcpcontext_t ct```
    
  - arg 2 : ```void *p```
    
  Return value : 
  Description : 

<a name="vce_utime_diff"></a>
- <B>vce_utime_diff</B>
Summary : get differential time of "struct timeval" in VCEI64 type
Category : util
Prototype : `````` 
  - arg 1 : ```struct timeval *before```
    Previous time

  - arg 2 : ```struct timeval *after```
    Later time

  Return value : 
  Description : 

<!-- make_funcdef end -->
<BR><BR>
Copyright 2000-2005 Community Engine Inc. All rights reserved.
