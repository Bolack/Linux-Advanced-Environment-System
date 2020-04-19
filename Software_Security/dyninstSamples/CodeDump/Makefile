#DYNINST_ROOT = /home/xm13/projects/liteCFI/thirdparty/dyninst-10.1.0/install
DYNINST_ROOT = /usr/local
CFLAGS = -g -O0 -std=c++11
INC = -I$(DYNINST_ROOT)/include
LIB = -L$(DYNINST_ROOT)/lib 
DEP = -lparseAPI -linstructionAPI -lsymtabAPI -lelf -ldynDwarf -lelf -ldynElf -lcommon -lboost_system


CodeDump: CodeDump.cpp
	g++ $(CFLAGS) $(INC) $(LIB) CodeDump.cpp -o CodeDump $(DEP)

clean:
	rm -f CodeDump
