CXX = g++
CXXFLAGS = -g  -std=c++11 -Wall -Iinclude#-I(include) -L(lib dir) -l(libname)
#SRC_ALL = $(wildcard ./src/*.cc) #./test_src/*.cc)
#OBJ_ALL = $(patsubst %.cc, ./bin/%.o, $(notdir $(SRC_ALL)))
OBJ = $(addprefix bin/, calculator.o parser.o lexer.o)

all: bin/main

bin/main: bin/main.o $(OBJ) 
	$(CXX) -o $@ $< $(OBJ) $(CXXFLAGS)

test: bin/lexer_test bin/parser_test bin/symbol_table_test

bin/%_test: test_src/%_test.cc $(OBJ)
	$(CXX) -o $@ $< $(OBJ) $(CXXFLAGS) 

bin/%.o: src/%.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

echo:
	@echo $(SRC_ALL)
	@echo $(OBJ_ALL)

.PHONY: clean
clean:
	-rm -f bin/*
