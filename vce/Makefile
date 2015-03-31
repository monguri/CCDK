CFLAGS=-Wall -I. -g -O2 #-DGEN_DEBUG_PRINT
CC=gcc

GEN=gen/gen.rb
OUTLIB=libvce.a

SRCS=core.c mem.c util.c uselog.c tcp.c protocol.c conn.c sbuf.c ecode.c text.c bin.c osdep.c



OBJS=$(SRCS:.c=.o) 


all : $(OUTLIB) testsv testcl 

$(OUTLIB) : $(OBJS)
	ar cr $(OUTLIB) $(OBJS) 
	ranlib $(OUTLIB)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

testsv: test_sv.c $(OUTLIB) testproto_sv.o
	$(CC) test_sv.c -o testsv testproto_sv.o libvce.a 

testcl: test_cl.c $(OUTLIB) testproto_cli.o
	$(CC) test_cl.c -o testcl testproto_cli.o libvce.a 

testproto_cli.c testproto_sv.c : $(GEN) testproto.txt
	ruby $(GEN) testproto.txt


depend:
	$(CC) -I. -MM $(SRCS) > deps.make

clean:
	rm -f testproto_*.c testproto_*.cpp testproto_*.h testproto_*.rb testcl testsv
	rm -f $(OUTLIB) *.a
	rm -f $(OBJS) *.o


-include deps.make
