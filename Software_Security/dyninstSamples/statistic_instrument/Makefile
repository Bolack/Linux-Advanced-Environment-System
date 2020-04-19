SYMTABAPI=/home/wangmin/dyninst-9.3.2/symtabAPI/src
DYNINST_ROOT=/usr/local
DEP_SIMPLE = -libdyninstAPI.so -lboost_system
DYNINSTAPI= /home/wangmin/dyninst-9.3.2/dyninstAPI/src/

all :InterestingProgram Instrumenting_a_function

InterestingProgram:InterestingProgram.c
	gcc -o InterestingProgram InterestingProgram.c

Instrumenting_a_function:Instrumenting_a_function.cpp
	g++ -I$(DYNINST_ROOT)/include -o Instrumenting_a_function Instrumenting_a_function.cpp /usr/local/lib/libdyninstAPI.so  /usr/local/lib/libdyninstAPI_RT.so

clean:
	rm -rf InterestingProgram Instrumenting_a_function