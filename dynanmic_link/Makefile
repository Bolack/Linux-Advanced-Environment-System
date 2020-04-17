all: libhello.so test

libhello.so:hello.c
	gcc -fPIC -shared -o libhello.so hello.c

test:test.c
	gcc -o test test.c -L. libhello.so \
	-Wl,-rpath=./ 

# test.s:test.c
# 	gcc -S test.s test.c -L. libhello.so