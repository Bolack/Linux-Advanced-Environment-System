# buffer.exe : buffer.c
# 	gcc -o buffer buffer.c -g

all: test_dyninst instrument

test_dyninst.exe:test_dyninst.c
	gcc -o test_dyninst test_dyninst.c -g

instrument:instrument.cpp
	g++ -std=c++11 -o instrument instrument.cpp /usr/local/lib/libdyninstAPI.so