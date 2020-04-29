all:clean test test.s test2 \
install

test:test.c
	gcc -g -o $@ $^ -fno-stack-protector

test.s:test.c
	gcc -S -o $@ $^ -fno-stack-protector

test2:test2.c
	gcc -g -o $@ $^ -fno-stack-protector

install:test
	cp test ../test
	cp file.txt ../file.txt
	cp test.s ../test.s
	cp test2 ../test2

clean:
	rm -rf test
	rm -rf test.s
	rm -rf test2
