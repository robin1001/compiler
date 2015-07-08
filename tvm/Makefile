CXX = g++
CXXFLAGS = -g -Wall
LEX_FILE = tvm.lex

all:
	
lex: 
	#flex $(LEX_FILE) -o lex.cc
	flex $(LEX_FILE) 

test: lex.test parse.test

lex.test: lex.yy.o 
	$(CXX) -o $@ lex.test.cc lex.yy.o $(CXXFLAGS)
parse.test: parse.o lex.yy.o
	$(CXX) -o $@ parse.test.cc parse.o lex.yy.o $(CXXFLAGS)

lex.yy.o: lex.h
parse.o: parse.h lex.h

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.exe
