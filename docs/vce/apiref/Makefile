#
# Makefile for VCE document
#

all : docgen0.rb docgen.conf src/*.txt
	rm -rf out
	mkdir out
	ruby docgen0.rb src/*.txt
	rm -r out/ja/man
	rm -r out/en/man

clean:
	rm -rf out




