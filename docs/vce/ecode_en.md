# VCE Error Codes and Error Messages

There are two methods to identify an error in VCE; getting an error number by the vce_get_last_error function, and referring to the output strings in the error log (vce_errout).
These codes are explained below.

- <a href="#ecode">VCE error codes</a>
- <a href="#elog">VCE error log messages</a>
  - <a href="#fatalerror">Fatal error messages</a>
  - <a href="#warning">Warning messages</a>
  - <a href="#bug">Bug messages</a>
  - <a href="#note">Note messages</a>

## <a name="ecode"></a>VCE Error Codes

The following list contains all VCE error codes.
The following list refers to the contents of vce.h.



- ```#define VCE_NOERROR (0) ``` No error.
- ```#define VCE_EGENERIC (-1) ```  General error.
- ```#define VCE_EFULL  (-2) ```  Buffer is full.
- ```#define VCE_EBUG   (-3) ```  Error is suspected to be caused an internal VCE bug.
- ```#define VCE_ERANGE (-5) ``` Argument is out of range.
- ```#define VCE_EINVAL (-6) ``` Invalid argument.
- ```#define VCE_EMEM   (-7) ``` Insufficient memory.
- ```#define VCE_ENOENT (-8) ``` No match was found, or file not found.
- ```#define VCE_EIO    (-9) ``` I/O error occurred with either socket or file.
- ```#define VCE_ESOCKET (-10) ``` socket() system call failed.
- ```#define VCE_EBIND (-11) ``` bind() system call failed.
- ```#define VCE_EIPADDR ( -12) ``` Specified IP address is invalid.
- ```#define VCE_ELISTEN (-13) ``` listen() system call failed.
- ```#define VCE_ECONFIG (-14) ``` Configuration problem.
- ```#define VCE_EHOSTNAME (-15) ```Cannot resolve host name.
- ```#define VCE_EFCNTL (-16) ``` fcntl failed.
- ```#define VCE_ECONNECT (-17) ``` connect() system call failed.
- ```#define VCE_EBUFSMALL (-18) ``` Specified buffer is too small.
- ```#define VCE_EPROTO    (-19) ``` Byte string of protocol is invalid.
- ```#define VCE_ENOTREADY (-20) ``` Access was attempted before encryption negotiation was completed.
- ```#define VCE_ENEGO    (-21) ``` Encryption negotiation failed.
- ```#define VCE_EPROTO_INVAL (-22) ``` Argument of protocol is invalid.
- ```#define VCE_EPROTO_ODD (-23) ``` The length of protocol input record is abnormal.
- ```#define VCE_EPROTO_TOOLONG (-24) ``` Input data of protocol is too long.
- ```#define VCE_ENOCALLBACK (-25) ``` Callback function is not defined.
- ```#define VCE_ESUPPORT  (-26) ``` No longer supported.
- ```#define VCE_ECONNSERIAL (-28) ``` Unable to perform I/O because the serial number of conn_t is different.
- ```#define VCE_EVECNOTREADY (-29) ``` Packet vectorizer is not ready.
- ```#define VCE_EALIGNMENT (-32) ``` Alignment of specified object is invalid.
- ```#define VCE_EFORMAT (-33) ``` Format of string is abnormal.
- ```#define VCE_ESEARCH (-34) ``` Search engine internal error.
- ```#define VCE_ECONTENTLEN (-35) ``` Length of record's data part of protocol is invalid.
- ```#define VCE_ECONNINIT (-36) ``` Connection table has not been initialized.
- ```#define VCE_EACCEPT (-38 ) ``` accept() system call failed.
- ```#define VCE_ESETSOCKOPT (-39) ``` setsockopt() system call failed.
- ```#define VCE_EACCESSFILE (-40) ``` Cannot access the file.
- ```#define VCE_EWINSOCKINIT (-41) ``` Failed to initialize Winsock (win32 only)
- ```#define VCE_EWBFULL (-44) ``` Write buffer is full.
- ```#define VCE_ELONGINPUT (-45) ``` Input buffer is too long.
- ```#define VCE_ETOOSHORT (-46) ``` Input buffer is too short.
- ```#define VCE_EPROTO_BADLEN (-47) ``` Length of input record of protocol is abnormal (could be an exploit).
- ```#define VCE_EPROTO_RESULT (-48) ``` Server returned an error at protocol.
- ```#define VCE_EPROTO_SERVERINVAL (-49) ``` Server returned an abnormal value (could be an exploit).
- ```#define VCE_EPROTO_BADCOMMAND (-50) ``` Specified protocol command does not exist.
- ```#define VCE_EFOPEN_W (-51) ``` Cannot open file for writing.
- ```#define VCE_ERENAME (-52) ``` rename(2) system call failed.
- ```#define VCE_ENOTFOUND (-54) ``` Cannot find something
- ```#define VCE_ELENTOOLONG (-55) ``` Specified length is too long.
- ```#define VCE_EDATASHORT (-56) ``` Data part is too short.
- ```#define VCE_EOPENDIR (-57) ``` Cannot open a directory.
- ```#define VCE_EFSEEK (-58) ``` Cannot fseek a file.
- ```#define VCE_EFWRITE (-59) ``` Cannot write data to a file.
- ```#define VCE_EFREAD (-60) ``` Cannot read data from a file.
- ```#define VCE_EMKDIR (-61) ``` Could not create a directory.
- ```#define VCE_EALREADY (-62) ``` Cannot operate the same thing twice; redundant.
- ```#define VCE_EFINALIZE (-63) ``` This is an error caused by releasing VCE. Because VCE was not properly released, memory may have leaked (could be VCE bug or improper usage).
- ```#define VCE_ECLOSED (-64) ``` Access was attempted when connection, etc. had already closed.
- ```#define VCE_EGENCOMMAND (-65) ``` Received a function ID that is not defined in protocol definition.
- ```#define VCE_ENOCRYPTO (-66) ``` Specified block key encryption algorithm does not exist.
- ```#define VCE_ETOOLONGNAME (-67) ``` Specified name is too long.
- ```#define VCE_ESIZE (-68) ``` Specified size is abnormal.
- ```#define VCE_EINIT (-78) ``` This error indicates that VCE is not initialized by vce_initialize(), but the VCE API function is called.
- ```#define VCE_EARRAY (-79) ``` VCE needs more arrays internally. You can avoid this error by setting max_array when vce_initialize_limited.



## <a name="elog"></a>VCE Error Log messages

There are four kinds of messages stored in a log by VCE: Fatal, Warning, Bug, and Note.
All messages are numbered; Fatal error messages start from 1000, Warning messages start from 4000, Bug messages start from 7000, and Note messages start from 10000.
These nmbers will increase in future versions of VCE, but existing messages will not be deleted nor modified (their detailed descriptions may be changed).  The following messages are for VCEgg 0.2.  These are defined as macros by vce.h.

Because descriptions of these messages may be changed in the future, always use the error number such as "Fatal: 1101" rather than the English description as a clue to analyze a log with backup and administration tools.


### <a name="#fatalerror"></a>Fatal Error Messages

Fatal error messages are generally caused by the incorrect usage of VCE by an application, or are due to the insufficient configuration of the operating system (problem with ports, free memory, permissions issues, etc.)  Errors can be resolved by carefully tracking down the cause through the below messages.



- ```Fatal:1000 cannot initialize winsock``` Cannot initialize Winsock.
- ```Fatal:1003 array table scarcity (init_array)```　The number of remaining array tables is insufficient. Too many vce_init_array. Check if array leak has occurred.
- ```Fatal:1010 MALLOC fail (index=%d)``` MALLOC (wrapper of malloc) failed, can't allocate master buffer.
- ```Fatal:1011 MALLOC fail (index=%d)``` MALLOC (wrapper of malloc) failed, can't allocate entry list.
- ```Fatal:1012 MALLOC fail (index=%d)``` MALLOC (wrapper of malloc) failed, can't allocate used list.
- ```Fatal:1020 array full in %s``` Free element of array does not exist. When you receive this error unexpectedly, check if vce_free_array_object was called.
- ```Fatal:1050 odd buffer size: %d``` Buffer size is not divisible.
- ```Fatal:1080 please set buffer with length of n*256 bytes.```  Buffer length is not a multiple of 256.
- ```Fatal:1200 tcp: no more connections are available``` TCP connection exceeds the maximum number of connection restricted by  VCE, so it cannot be increased.
- ```Fatal:1201 tcp: bad secret key length: %d``` Length of shared secret key is abnormal.  With Blowfish, it must be either 4 or 56.
- ```Fatal:1202 tcp: bad encryption type specified:%d``` Value of encrypt argument of vce_tcpcontext_create must be either 0 or 1.
- ```Fatal:1203 need a parser when creating tcpcontext``` To use vce_tcpcontext_create, a parser function must be specified.  Otherwise it is left out without defining how to process the input from the socket.
- ```Fatal:1204 socket() fail addr:%s port:%d os_errno:%s``` socket() system call failed and its status is returned as an error number of C library.
- ```Fatal:1205 gethostbyname() error: %s``` gethostbyname function failed.  Also displays error output of C library.
- ```Fatal:1206 gethostbyname() error: %s``` gethostbyname function failed.  Also displays error output of C library.
- ```Fatal:1207 bind() error. os_errno:%s addr:%s port:%d``` bind function failed.
- ```Fatal:1208 listen() error. os_errno:%s addr:%s port:%d``` listen function failed.
- ```Fatal:1209 setsockopt() fail. os_errno:%s``` setsockopt function failed.
- ```Fatal:1210 gethostbyname() error: %s``` gethostbyname function failed.  Also displays error output of C library.
- ```Fatal:1212 fcntl fail: %s``` fcntl function failed.
- ```Fatal:1213 setsockopt() fail: %s``` setsockopt function failed.
- ```Fatal:1256 pointer to tcpcontext is null``` A pointer that redirects tcpcontext is NULL.  It has not passed the sanity check.
- ```Fatal:1260 win32 fatal: gethostbyname() error:%s``` At Winsock, gethostbyname failed.
- ```Fatal:1265 Memory shortage when creating tcpcontext state buffer``` Could not save status management memory for status attached to protocol due to insufficient memory in vce_tcpcontext_create.
- ```Fatal:1277 setsockopt(SO_REUSEADDR) fail:%s``` Failed to configure SO_REUSEADDR.

### <a name="warning"></a>Warning Messages

Warning messages indicate that the exhaustion of resource or the deterioration of performance may be experienced in the future even though VCE continues working.  It is recommended to avoid warning messages as much as possible by tuning VCE's configuration.


- ```Warning:4000 freeing null pointer in %s``` Attempted to free a null pointer.
- ```Warning:4001 freeing an out-of-bound element in %s address:%p master-address:%p```  An element that is attempting to be released is placed outside of an array's memory area.
- ```Warning:4002 freeing an oddly-aligned element in %s address:%p master-address:%p sizeof:%u``` An element that is attempting to be released is a pointer to a buffer which is not an  array element.
- ```Warning:4003 freeing an out-of-bound element in %s address:%p master-address:%p sizeof:%u``` An element trying to release is placed outside of array memory.
- ```Warning:4100 tcp: only %d connections are usable``` Because it exceeds the maximum number of connection in VCE, only the number of connections displayed can be used.
- ```Warning:4101 tcp: accept() error. os_errno:%s port:%d```  accept() error
- ```Warning:4102 tcp: conn_alloc fail no more accept. max:%d port:%d``` Because it reached the maximum number of connections that VCE can manage, no more TCP connections can be added (or accepted).
- ```Warning:4103 tcp: acceptwatcher fail fd:%d``` Function specified as acceptwatcher returned an error.
- ```Warning:4104 select() returns %d: %s``` select() returned an invalid value.
- ```Warning:4105 connection timeout. fd:%d sec:%d``` Connection timed out because a client is not working well. The value of time out is specified when vce_tcpcontext_create function is called.
- ```Warning:4215 winsock select() returns SOCKET_ERROR, and WSAGetLastError:%d``` With Winsock, select returned an error.
- ```Warning:4214 re-freeing an element in %s address:%p``` Trying to release the same element twice. Possibly the application called free_array_object twice.
- ```Warning:4225 vce_tcpcontext_create: reached max connection num %d``` Reached the maximum number of connections specified with tcp context.
- ```Warning:4300 vce_conn_io: conn does not have parser function. use vce_tcpcontext_set_conn_parser``` TCP connection "conn" does not have a parser. Configure a parser by using vce_tcpcontext_set_conn_parser to process data input.

### <a name="bug"></a>Bug Messages

Most Bug Messages indicate errors that can not be solved with the application.

- ```Bug:7000 blank-list stack overflow: %s``` Management of a free list of arrays is abnormal.
- ```Bug:7002 use flag is 0! in %s address:%p``` Sanity check error for the array of vce_show_array_usage function.
- ```Bug:7003 usenum doesn't match in %s stack:%d link_inuse:%d```  The number of count in use is different from the length of stacks actually increased.
- ```Bug:7010 tcp: nobuf?``` The free buffer for TCP that should have been free is insufficient.
- ```Bug:7011 tcp: nomem?``` The free memory for TCP that should have been reserved is insufficient.
- ```Bug:7109 state buffer is full.(accept)``` Status management buffer is full even though connection is not full. Obviously it is VCE's bug.
- ```Bug:7112 connect: statebuf shortage``` Only status management buffer is full when vce_tcpcontext_connect was called.  It is VCE's bug.


### <a name="note"></a>Note Messages

Note Messages are displayed only when VCE is set to verbose mode.  If you want to debug or record detailed actions of VCE into a log, while fatal messages or warning messages are displayed by VCE, set to verbose mode and output Note Messages.


- ```Note:10001 NOOP PROTOCOL: %d bytes from conn_t. serial:%d```  Received data with NOOP protocol.
- ```Note:10002 DUMP PROTOCOL: %d bytes from conn_t. serial:%d``` Received data with DUMP protocol.
- ```Note:10200 new connection fd:%d I:%d sbuflen:%d``` Accepted a new connection.
- ```Note:10201 non blocking connect().``` Connection has been set as non-blocking.
- ```Note:10202 connect ok on %d``` connect() was successful.
- ```Note:10220 malloc(%u) returns %p``` malloc returned value.
- ```Note:10221 free(%p)``` Freed.
- ```Note:10320 conn_t detected EOF on fd %d``` read returned 0 on TCP.
- ```Note:10321 conn_t detected read error on fd %d``` read returned -1 on TCP.
- ```Note:10322 conn_t detected write error on fd %d (%s)``` write returned -1 on TCP.  Display the value of errno.
- ```Note:10323 conn_t detected encryption negotiation error on fd %d error code:%d``` Initialization negotiation of encryption session failed. The session was not established.
- ```Note:10326 conn_t detected protocol error on fd %d error code: %d``` Protocol function (such as vce_protocol_parser_bin16) returned an error code (negative).
- ```Note:10342 allocated state buffer for conn.``` Status buffer was assigned to connection.
- ```Note:10345 vce_tcpcontext_create could allocate state buffer.``` vce_tcpcontext_create function successfully assigned status buffer.
- ```Note:10347 freed state buffer for conn``` Successfully released the status buffer.
- ```  "Note:10400: vce: finalized``` VCE was successfully ended.  This is displayed if vce_finalize function has succeeded.

