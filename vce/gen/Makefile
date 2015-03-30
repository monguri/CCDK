#
# Makefile for gen.rb
#
#
# Copyright (C) 2000-2005 Community Engine Inc. All rights reserved.
# For more information, please visit our website at www.ce-lab.net.
#


SHELL=/bin/sh
RM=rm -f
RUBY=/usr/bin/ruby
RACC=racc
TARGET=gen.rb
SRC=gen.y
SUBSRC=gen_footer.rb gen_inner.rb gen_maker.rb gen_maker_c.rb gen_maker_rb.rb


all: $(TARGET) 

$(TARGET):  $(SRC) $(SUBSRC)
		$(RACC) -E -l $(SRC) -o $(TARGET)

clean:
		$(RM) $(TARGET)

