#
#
#

EXTERNALS=../externals
MOYAISRCS=$(EXTERNALS)/moyai/common.cpp $(EXTERNALS)/moyai/lodepng.cpp
COMMONSRCS=$(EXTERNALS)/moyai/cumino.cpp $(MOYAISRCS)
SVSRCS=ssproto_sv.cpp main.cpp $(COMMONSRCS)
BENCHSRCS=bench.cpp ssproto_cli.cpp $(COMMONSRCS) 
VCELIB=../vce/libvce.a 
LIBS=-lhiredis $(EXTERNALS)/moyai/libsnappy.a $(VCELIB)
GEN=../vce/gen/gen.rb
CFLAGS= -O3 -g -Wall -I$(EXTERNALS) -I../vce -DGEN_DEBUG_LEN_PRINT

SVOBJS=$(SVSRCS:.cpp=.o)
BENCHOBJS=$(BENCHSRCS:.cpp=.o)

SVOUT=ssv
BENCHOUT=ssbench

all : $(SVOUT) $(BENCHOUT)

$(SVOUT) : $(SVOBJS) $(VCELIB)
	g++ $(CFLAGS) $(SVOBJS) $(LIBS) -o $(SVOUT) 

$(BENCHOUT) : $(BENCHOBJS) $(VCELIB)
	g++ $(CFLAGS) $(BENCHOBJS) $(LIBS) -o $(BENCHOUT)

%.o : %.cpp
	g++ -c $(CFLAGS) $< -o $@

ssproto_sv.cpp ssproto_cli.cpp: ssproto.txt
	ruby -Ku $(GEN) ssproto.txt 


clean:
	rm -f *.o deps.make ssproto_sv.* ssproto_cli.* $(SVOUT) $(BENCHOUT)

depend: ssproto_sv.cpp ssproto_cli.cpp
	$(CC) $(CFLAGS) -MM $(SVSRCS) > deps.make



auto:
	ruby auto.rb

-include deps.make
