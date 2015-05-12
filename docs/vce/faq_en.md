# VCE FAQ

- <B>Cannot establish more than a thousand of TCP connection.</B>
If you initialize VCE with a vce_initialize function, the maximum number of connection is set to 1000.
Initialize by using the vce_initialize_limited function and specify a large number for max_conn member of vce_limit_t.

- <B>Calling vce_initialize reserves memory for a few MB.</B>
You can decrease the amount of memory usage as much as possible with the vce_initialize_limited function instead of the vce_initialize function.
See vce_initialize_limited function reference for an instruction.

- <B>parser function is never called</B>

  If you find nothing wrong with your source code, but a parser is not called, several causes are considered to be causing the problem.

  - The order of calling tcpcontext_connect function and configuring parser.
    Usually this problem happens when you call a function (ex. vce_tcpcontext_set_conn_parser ) that configures tcpcontext_t after vce_tcpcontext_connect. A process such as vce_tcpcontext_connect that assigns a new connection copies the configuration of tcpcontext_t upon assignment. For a detailed information, see vce_tcpcontext_connect and vce_tcpcontext_create manual.
  - Using gen.rb with p2p application.
    With p2p application, the same program can be a client and a server, and sometimes it shares a protocol with a single protocol configuration file. In this case, if you write "=c2s" and "=s2c" the other way around, calling a protocol function does not reach the destination party.

    You should have written
    ~~~
    =c2s hello ( char name[100] )
    =s2c hello_reply ( char answer[100] )
    ~~~
    but you made a mistake and wrote
    ~~~
    =s2c hello ( char name[100] )
    =c2s hello_reply ( char answer[100] )
    ~~~
    Please check the protocol file again.

- <B>vce_heartbeat causes an infinite recursion </B>
  You have called vce_heartbeat in a callback function (parser, acceptwatcher, closewatcher, etc.) that is called from vce_heartbeat. To fix the problem, modify the code.

- <B>Memory leak was found with the memory leak check program.</B>
  You probably forgot the vce_tcpcontext_cleanup and vce_finalize. These functions free the memory used by tcpcontext_t and VCE itself.            Take care that the vce_finalize function does not free memory used by tcpcontext_t (both functions must be called properly).
Also, some requires calling the cleanup function.

- <B>Is VCE thread safe?</B>
No.

- <B>Is it possible not to use VCE on either the client or the server? </B>
  Yes, you can use VCE only in client side, or, only in server side.

- <B>vce_tcpcontext_create function returns EINVAL.</B>
  If vce_tcpcontext_create returns EINVAL and is unable to initialize tcpcontext with various arguments settings, this is mostly because of a missing vce_initialize() function call.

- <B>Although a connection has been closed, it is not released right away. </B>
When you close a connection with a vce_conn_close function, if data remain in the send buffer of the closed connection, VCE will attempt sending the remaining data until the default timeout (an argument of vce_tcpcontext_create function) expires.
If you do not need to take care of this problem,      for instance a client side program, use vce_conn_set_timeout and specify the timeout value to zero or closet to zero for applicable           connections so that a connection is released right away.
For detailed information, see vce_conn_close function reference. The timeout for a connection established again by connect/accept is set back to the default value.

- <B>A callback function is called only once in a single heartbeat.</B>
  It's a default setting of VCE. You can change it by vce_tcpcontext_set_conn_call_parser_per_heartbeat function.

- <B>Performance is improved by calling vce_heartbeat several times. </B>
  Even if you set vce_tcpcontext_set_conn_call_parser_per_heartbeat to the maximum value (ex 10000), calling vce_heratbeat several times rather than once may improve the performance of a callback.
This is because VCE acquires only 32KB per single connection for a single vce_heartbeat.
This is in consideration that the load for each connection should be uniform for a server program.
However, this may deteriorate performance when there are too many small queries or performing a bulk transmission.
In this case, call vce_heartbeat successively for several times.

- <B>What is a "bind error" (VCE_EBIND)?</B>
  Under UNIX (Linux), to keep up a server using TCP/IP, server processes must occupy 65536 "TCP ports" from #0 to #65535.
  Use a system called "bind" to occupy those ports (with VCE's C API, "bind" is executed when the vce_tcpcontext_create function is called).           Therefore, when a server process that uses a #2000 port is working already, if another process that uses a #2000 port tries to start, the vce_tcpcontext_create function returns a VCE_EBIND error, which means a process was unable to start since the port is already  bound.

- <B>How to judge success or failure when connecting from client?</B>
  Please refer to [Connecting from client](connect_en.md).

- <B>How to make file transfer programs and streaming applications using VCE?</B>
  Not only the VCE, it is desirable to carry out the data demand of client initiative, but not one-way data transmission by server like HTTP.
  The client initiative means implementing the server in order to carry out the request message from a client faithfully; for example, if the client request "data of 1KB", the server returns "data of 1KB".
  Each time the client transmits this request, a counter increases only one, and whenever data returns, it decreases one.
  And if the frequency of the transmission demand is adjusted to keep the value of this counter 4 or less, only 4KB will not save on a network at the maximum.
  By carrying out like this, the server load of the application which tends to require load for a server memory like a file transfer is reduced sharply, and also the zone of the server side can be used evenly.

- <B>What is VCEI64 data type?</B>
VCEI64 is typedef'ed as "long long" in Linux and MacOS X, typedef'ed as "__int64" in win32.

This data type is defined by VCE to use 64bit longer integer when calling VCE functions.

- <B>What external libraries VCE depends on?</B>
  - Windows: WSOCK2_32.DLL
  - Linux, MacOS X: Nothing special

- <B>Memory shortage error when VCE initialization</B>
Did you use vce_init_limit_t function to initialize vce_limit_t?

