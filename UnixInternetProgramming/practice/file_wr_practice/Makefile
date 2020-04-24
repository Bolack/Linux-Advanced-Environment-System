.PHONY:all

all:hello filecpy ls

hello:hello.c
	gcc -g -o $@ $^

filecpy:filecpy.c
	gcc -g -o $@ $^

ls:ls.c
	gcc -g -o $@ $^
.PHONY:clean

clean:
	rm -rf hello
	rm -rf filecpy
	rm -rf hellorewrite