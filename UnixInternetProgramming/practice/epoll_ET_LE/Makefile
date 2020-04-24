.PHONY:all
all:local_file_rw main

local_file_rw:local_file_rw.cpp
	g++ -g -o $@ $^

main:main.cpp
	g++ -g $@ $^

.PHONY:clean
	rm -rf main
	rm -rf local_file_rw