all:
	echo Please type 'make setup'.

setup:
	git submodule update --init --recursive
	cd vce; make
	cd externals/moyai; make server
	cd backend; make
	cd backend/datadir; ruby mkdir.rb
