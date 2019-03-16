CC=/soft/gcc/7.1.0/Linux_x86_64/bin/gcc
CXX=/soft/gcc/7.1.0/Linux_x86_64/bin/g++

-include ../../../Makefile.local

all: googletest

googletest: build
	cd build; cmake --build . --target install

build:
	mkdir -p build
	cd build; CC=$(CC) CXX=$(CXX) cmake ../../../../../googletest -DCMAKE_INSTALL_PREFIX=../../../../build

clean:
	rm -rf build

