# # DYNINST_ROOT=/home/xm13/dyninstapi/install
# # DEP_SIMPLE = -ldyninstAPI -lboost_system
# # DEP_MEMORY = -ldyninstAPI -lparseAPI -linstructionAPI -lcommon -lboost_system


# all:SimpleShadowStack libshadowstack.so test

# SimpleShadowStack: SimpleShadowStack.cpp
# 	g++ -O2 -g -o SimpleShadowStack SimpleShadowStack.cpp  /usr/local/lib/libdyninstAPI.so \
# 	-Wl,-rpath=./
		

# libshadowstack.so: shadowstack.c
# 	gcc -fPIC -shared -o libshadowstack.so shadowstack.c

# test: test.c
# 	gcc -o test test.c

# clean:
# 	rm -f SimpleShadowStack test test.inst libshadowstack.so
SYMTABAPI=/home/wangmin/dyninst-9.3.2/symtabAPI/src
DYNINST_ROOT=/usr/local
DEP_SIMPLE = -libdyninstAPI.so -lboost_system
DYNINSTAPI= /home/wangmin/dyninst-9.3.2/dyninstAPI/src/

all: SimpleShadowStack libshadowstack.so test
# -I 链接文件时目录
# 
SimpleShadowStack: SimpleShadowStack.cpp
	g++ -O2 -g -I$(DYNINST_ROOT)/include  -I$(SYMTABAPI) -I$(DYNINSTAPI)\
		-Wl,-rpath=./ \
		-o SimpleShadowStack SimpleShadowStack.cpp /usr/local/lib/libdyninstAPI.so  /usr/local/lib/libdyninstAPI_RT.so

libshadowstack.so: shadowstack.c
	gcc -fPIC -shared -o libshadowstack.so shadowstack.c

test: test.c
	gcc -o test test.c

clean:
	rm -f SimpleShadowStack test test.inst libshadowstack.so
