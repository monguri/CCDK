# Maximum number of concurrent connections on VCE server


The following describes success/failure conditions for VCE clients connecting to a VCE server, especially when it have near maximum number of concurrent connections.


## Recommended Connection Methods

It is recommended that connection tests are performed using only the vce_conn_writable function, and connection of non-blocking encryption in VCE applications.


~~~
tcpcontext_t t = vce_tcpontext_create( 0, ... );
conn_t new_con = vce_tcpcontext_connect( t, "localhost" , 80 ); 
while (1 ){
  vce_heartbeat();
  if( vce_conn_writable( new_con ) >= 4 ){
    vce_conn_write( new_con, "test" , 4 );
  } else {
    //  Error will occur if fixed time passes 
  }
}      
~~~

In this case, when vce_conn_writable does not return a positive value within a fixed time using a timer, add the process to display an error on the client terminal to notify the user. 

When using VCE's "blocking connection," some pesky procedures such as test programs and server-monitoring programs can be omitted. 

However, omitting procedures such as test programs and server-monitoring programs is often a requirement  to make it easily.

"Blocking connection" of VCE can be used for such a purpose.

Especially making N:N games in Shinra System, VCE is only used inside data center, so TCP initiation is very quick and almost no error occurs.

When you use the "blocking connection," you can check the connection success without looping, as below.


~~~
tcpcontext_t t = vce_tcpontext_create( 0, ... );
conn_t new_con = vce_tcpcontext_connect( t, "localhost" , 80 );
if( vce_conn_is_valid( new_con ) == 0 ){
  // Error! Handy for determining problem. 
}
while (1 ){
  vce_heartbeat();
  if( vce_conn_writable(new_con)&gt;0 ){
    // write process 
  }
}
~~~


However, when used in this fashion, it does not work as expected, and only when the server has reached the number of the absolute maximum number of connections.

Once it starts looping, vce_conn_writable returns an error, even when vce_conn_is_valid function return true (success).

It's expected for vce_conn_writable to finally return an error, since the server reached the maximum number of connections. But here issue is that the first vce_conn_is_valid returns success.

This reason for this is the internal operation when reaching the maximum number of connections on the VCE server, since the connection is accepted once and then closed when the number of client connections reaches the preset maximum number.

VCE and other UNIX tools (Apache, etc.) behave in this fashion because of the following limitations on socket library functions.

The socket libraries of UNIX do not have any function to limit maximum concurrent connections. When an TCP server is reaching maximum number, it can't return "connection refused", since the TCP/IP function does not have the concept of "maximum 
  connections" when some servers reach the maximum number of connections.
  
You can make TCP servers to destroy listening socket when getting maximum connection, but it is not recommended to repeat binding/listening or releasing the same port near the maximum number of the connections. 
This is not recommended because it will cause performance issues and other security issues like DoS.

Therefore, for server applications which currently run on UNIX, the operations will be accepted and then close the connection by default. 


## How to handle the maximum number of connections


The operation explained above is the default for connecting above the maximum number of VCE connections. 

However, users who access a full server will not know whether the server is full or is down. 


So, VCE sets up a "temporary" number of maximum connections besides the absolute number of maximum connections, and it has the function to call other connection-monitoring functions when connections beyond the temporary number of maximum connections are accepted.

vce_tcpcontext_set_circ_hiwater_acceptwatcher and vce_tcpcontext_set_conn_hiwater_acceptwatcher functions can be used to implement this.
For details, refer to the vce_tcpcontext_set_conn_hiwater_acceptwatcher function. 

