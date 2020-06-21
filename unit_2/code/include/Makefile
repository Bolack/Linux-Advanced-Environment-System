SRCS=$(wildcard ./include/*.cpp)

all:libsockets.so

libsockets.so:$(SRCS)
	gcc -fPIC -shared -o $@ $^ 
	mv libsockets.so ./include/libsockets.so
	rm -rf libsockets.so