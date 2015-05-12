# Detailed Description of gen.rb 

gen.rb is an automated function generator for protocol processing.

This tool easily implements RPC on VCE.

gen.rb reads a configuration file and then output C source code which can be compiled on Win32/UNIX and Ruby source code which can be used with Ruby.  It supports a network byte order so that it allows the communication between different processors and different languages.

## Index

- gen.rb command usage
  - <a href="#basic">Basic concept</a>
  - <a href="#commandline">Command Line Option </a>
  - <a href="#output">Output File Name</a>
- Protocol definition file
  - <a href="#infile">Input File Format</a>
  - <a href="#comment">Comment</a>
  - <a href="#directives">Directives</a>

- Output code functions
  - <a href="#count">Function Counter </a>
  - <a href="#version">Version Management </a>
  - <a href="#antihack">Handling invalid clients</a>

## gen.rb comand usage


### <a name="basic"></a>Basic Concept


 In VCE, the basis of protocol processing is "remotely handles function calls"; gen.rb generates stub code required for this basis.  In other words, the entity of function is defined by this stub file and a switch function that actually calls a function from remote is also defined.  With TCPcontext, protocol processing is performed in three stages:

1. Data input from TCP connection 
2. Parser splits data into records 
3. Call callback functions for each record 


This switch function corresponds to callback functions called for each record.  Using gen.rb simplifies developing communication application without writing a complicated code such as processing data running in a socket per byte.  It also makes communication programming easy under multi-platform environment so a server by C and a client by Ruby can transparently communicate with each other.  In the future, Java will be supported in addition to C/C++ and Ruby.



### <a name="commandline"></a>Command Line Option

The contents of configuration file can be overwritten by specifying a command line argument.  The name of configuration file is required.

~~~
ruby gen.rb  configuration file name  [option]
~~~

The following options are available.

~~~
--protocolname NAME            
--serverconnection conn|circ
--workbufsize SIZE
~~~

These options are the same with the options used in configuration file and overwrite the contents of configuration file if used as option.

~~~
--noc  Do not output a stub file of C 
--nocpp  Do not output a stub file of C++ 
--noruby  Do not output a stub file of Ruby
--identifier STRING
~~~

These options do not take any arguments, and set the action of gen.rb.
Change the identification used to identify commands in a configuration file from default "=" to a specified string.

~~~
--func_counter_type TYPE
~~~

Change the type of the call counter for callback function.  

~~~
--use_const
~~~
Add "const" to some function prototypes.


### <a name="output"></a>Output File Name

When gen.rb finishes successfully, the following 8 files will be created.

~~~
protocolname_sv.c      C source file for server 
protocolname_cli.c     C source file for client 
protocolname_sv.cpp    C++ source file for server 
protocolname_cli.cpp   C++ source file for client 
protocolname_sv.h      C/C++ header file
protocolname_cli.h     C/C++ header file
protocolname_sv.rb     Ruby source file for server 
protocolname_cli.rb    Ruby source file for client 
~~~



- Files to be used when developing a server with C
Compile/link ```protocolname_sv.c``` and include           ```protocolname_sv.h``` in the source file that defines receive functions and in the all source files that define send functions.

  Also, ```protocolname_sv_sender``` function , ```protocolname_sv_recv_error_callback``` function and ```protocolname_toolong_recv_warning``` function must be defined in addition to receive functions.
At last, specify callback function ```protocolname_sv_pcallback``` for TCPcontext that uses the defined protocol.

  Please see [gen.rb-C output reference](genref_en.md) for detail information.


- Files to be used when developing a client with C
Compile/link ```protocolname_cli.c``` and include ```protocolname_cli.h``` in the source file that defines receive functions and in the all source files that define send functions.
Also, ```protocolname_cli_sender``` function and ```protocolname_cli_recv_error_callback``` function must be defined in addition to receive functions  At last, specify callback function ```protocolname_cli_pcallback``` for TCPcontext that uses the defined protocol.

  Please see [gen-rb-C output reference](genref_en.md) for detail information.

- Files to be used when developing with C++
Same as C, but you can also use files with ".cpp" suffix.

- To develop a server with Ruby
Require ```protocol name_sv.rb``` from application source.
In the source, define the contents of ```protocol name_sv_sender(_co, data )``` , ```protocol name_sv_recv_error_callback(_co, ecode )```, ```protocol name_toolong_recv_warning(_co, protoid, length) method.          Also, specify ```$protocol name_sv_proc``` as the callback Proc of second argument upon calling set_[conn|circ]_parser method for the instance of TCPcontext.
This Proc instance is a Proc object that is called for processing upon receiving a record and it is defined by ```protocol name_sv.rb.```

- To develop a client with Ruby
Require ```protocol name_cli.rb``` from application source.
In the source, define the contents of ```protocol name_cli_sender(_co, data )``` ```protocol name_cli_recv_error_callback(_co, ecode )``` method.
Also, specify ```$protocol name_cli_proc``` as the callback Proc of second argument upon calling set_conn_parser method for the instance of TCPcontext.
This Proc instance is a Proc object that is called for processing upon receiving a record and it is defined by ```protocol name_cli.rb.


## Protocol definition file

### <a name="infile"></a>Input File Format

The format of input file can be anything like HTML, ASCII, or TEXT.
A line that begins with '=' is interpreted as a command line.  Using this functionality, you can write description about protocol in HTML, and the same file can be used as a configuration file for gen.rb by adding command lines as necessary.

gen.rb parses an input file line by line; if it finds '=' at the beginning of line, then retrieves a command and arguments the following '=' and performs the operation of the command.
Any number of spaces after '=' are perceived as a single space.  Also, a command line can be spread into lines by adding back slash at the end of the line.
'=' line must be written with a single command line, but it can be written with multiple lines as follows: 

~~~
=s2c 100 login ( int id, \
                   	  char password[100] )
~~~


### <a name="comment"></a>Comments

With the input file of gen.rb, all the text after '#' character will be ignored.


### <a name="directives"></a>Directives

A line begins with '=' is called a directive line.
A directive line begins with '=' followed by directive strings.  The following is a list of available directives.

- ```protocolname NAME```
  This specifies a protocol name.
Because a protocol name is used in various places such as function name or file name, use strings that are clearly recognized as C  language's identifier.
It is a good practice to add suffix "proto" so that it is easily identified as a protocol function.
See the following example:
~~~
=protocolname toyproto
=protocolname gameproto
~~~

- ```serverconnection CONNECTION_TYPE```
  This command specifies the type of connection used by a server.
Always set "conn" in CCDK app development. ```=serverconnection conn```

- ```version NUMBER```
  This command specifies the version of protocol.
An integer number can be specified in NUMBER.
The specified version number can be retrieved as a return value of 
```int someproto_get_version( int *subv)``` function. 
See <a href="#version">version management</a>.

- ```idmax NUMBER```
  Specify max ID number of protocol functions.
Internal ID size will be 1 if this number is equal to or less than  255, 2 bytes if equals to or less than 65535, otherwise 4 bytes.
It's recommended to keep this number small, to reduce traffic.
Default is 255. if you specify function ID larger than this number in <B>s2c</B> or <B>c2s</B> directives, it gets error.

- ```define IDENTIFIER EXPRESSION```
  This command defines a macro.  At present, it supports C only.
~~~
=define TEST 1
~~~
Use as in the above shown example.
This is an argument of function and mainly used to define a subscript of array. 
~~~
=define TEST_A(x) (x+1)
~~~
Therefore, it cannot define a complex macro such as a macro with an argument like the following example.
If you define this,
~~~
#define ??_IDENTIFIER EXPRESSION
~~~
similar to the above will be defined in XXproto_sv.h and XXproto_cli.h.
By defining error codes and size constants that are frequently used in protocol, clients and servers can share a constant definition file and the development efficiency will be increased.

- ```enum ENUMTYPE IDENTIFIER [EXPRESSION]```
  Like define command, this defines enum of C.
~~~
=enum HOGE INVALID_ARGUMENT -999
=enum HOGE NOT_SUPPORTED
~~~
If you define as shown above, and the protocol name is GAMEPROTO,
~~~
typedef enum {
  GAMEPROTO_INVALID_ARGUMENT=-999,
  GAMEPROTO_NOT_SUPPORTED,
} GAMEPROTO_HOGE;
~~~
an enum with a type of GAMEPROTO_HOGE is defined.  More than one ENUMTYPE can be specified and in that case multiple definitions of enum are created.
If a number (-?[0-9]+) is specified in EXPRESSION, then it is taken as a defined value.  If no value is specified, an enum with a default value is created.

- ```c2s ID FUNCNAME ( ARGDECL )``` or ```s2c ID FUNCNAME ( ARGDECL )```
<B>c2s</B> and <B>s2c</B> define functions generated by gen.rb.
c2s and s2c can be added up to idmax pieces in a single file.
c2s is an abbreviation of "client to server" and it defines a send function on the client side and a receive function on the server side.
In other words, if you write a c2s directive, then a send function is added to ```protocol name_cli.c``` and a receive function call (not a definition) is added to ```protocol name_sv.c```.          The process upon receiving is defined by application so only a receive function call is performed.
Specify a message ID in <B>ID</B> with a number under idmax.
A message ID is used by client and server to identify a function, and it is possible to handle up to idmax type of functions in total for s2c and c2c.
This ID can be added manually to keep compatibility with the past protocol when a new function is added later.
Therefore, if you plan to add new functions in the future, making an ID a jump number would be useful.
Specify a function name in <B>FUNCNAME</B>.
As an identification of C, proper strings must be used for a function name.
Specify arguments for each function in <B>ARGDECL</B>.
Following types are available.
~~~
int i       : int type integer
short i     : short type integer
char i      : char type integer
int a[100]  : int type array
short a[100] : short type array
char a[100]  : char type array
stringarray a[100][100] : array of string [maximum number of string][maximum number of characters for each string]
~~~
A size must be specified when you specify an array.
It is required to avoid overflowing the work area that is reserved in output code of gen.rb.
Be careful that the work area is created on a stack so setting a large value may result in insufficient stack.
An order of a few thousands is no problem.
  The size of array is a "maximum size" so a full amount of data would not actually be transmitted. For instance, if the first 10 byte of char a[100] is used, only 10 byte is transmitted.  Also, if an array is specified as an argument, an argument of int type that indicates the number of elements in the array is added.  Its name is set to variable name_len.

  The following is an example of configuration and functions to be generated.  someproto is a protocol name.
~~~
=s2c 100 login( int id, char passwd[20] )
~~~
Above defines C prototype below:
~~~
int someproto_login_send( conn_t _c, int id, char *passwd, int passwd_len )
~~~
And Ruby method below:
~~~
someproto_login_send( Conn c, Fixnum id, String passwd )
~~~
And next example:
~~~
=c2s 101 sendbig( int bigdata[1000] )
~~~
defines C prototype below:
~~~
int someproto_sendbig_send( conn_t _c, int *bigdata, int bigdata_len )
~~~
And Ruby method below:
~~~
someproto_sendbig_send( Conn c, Array ia )
~~~
The maximum size of array is not a byte count but a number of elements.

- ```=sh Code```  or ```=ch Code```

  Add any code in generated header file.
<B>sh</B> Adds code to server header, and <B>ch</B> adds code to client header.
For example, adding this:
~~~
=sh #include "server.h"
=sh extern Server * sv;
=sh extern Server2 sv2;
=ch #include "client.h"
=ch extern Client * cli;
=ch extern Client2 cli2;
~~~
in a definition file named "testproto.txt",
Following code snippet will be generated in testproto_sv.h.
~~~
#ifndef _TESTPROTO_SV_H_
#define _TESTPROTO_SV_H_
#include "vce.h"
#include "server.h"
extern Server * sv;
extern Server2 sv2;
#undef TESTPROTO_MAX_CONNECTION
#define TESTPROTO_MAX_CONNECTION 1024
....
~~~
And in testproto_cli.h,
~~~
#ifndef _TESTPROTO_CLI_H_
#define _TESTPROTO_CLI_H_
#include "vce.h"
#include "client.h"
extern Client * cli;
extern Client2 cli2;
#ifdef __cplusplus
extern "C" {
....
~~~

## Output code functions

### <a name="count"></a>Function Counter

gen.rb defines a function that counts how many times each command written in a protocol configuration is sent/received.
When defining "login" function is sent from a client to server, the following function is defined on the client side in C:
~~~
VCEI64 someproto_get_login_send_count(void)
~~~
And then in Ruby:
~~~
someproto_get_login_send_count()
~~~
Server side, in C:
~~~
VCEI64 someproto_get_login_recv_count(void)
~~~
And in Ruby:
~~~
someproto_get_login_recv_count()
~~~

By default, the type of return value is VCEI64, but it can be changed by ```--func_counter_type``` command line argument or ```=func_counter_type``` directive.


### <a name="version"></a> Version Management

Protocol is continuously changing in development so the version management is indispensable.
With gen.rb, we propose managing the version numbers of protocol with two values.  One is a version number that is specified by a programmer, and the other is a sub version number that is retrieved by hashing the contents of the configuration file and it can be used as a strict "finger print of contents".
The version number specified by ```=version``` directive.

This is called as a major-version.
Both sub version and major version can be retrieved by the following function.

In C server, you can use:
~~~
int someproto_sv_get_version(int *subv )
~~~
In C client:
~~~
int someproto_cli_get_version(int *subv )
~~~
In Ruby server:
~~~
someproto_sv_get_version()
~~~
In Ruby client:
someproto_cli_get_version()
~~~


These function returns the major version that is specified in a definition file and returns the sub version for the int value directed by subv pointer.
A sub version is used only when a strict match of protocol is required.
Usually it can be ignored by specifying NULL for subv.
If ```=version``` is not included in a configuration file, this function always returns -1 as a major version number.
With Ruby version method, it always returns an array with two elements; 0th element indicates a major version and 1st element indicates a sub version.