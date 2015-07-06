CXX = g++
CXXFLAGS = -g  -std=c++11 -Wall#-I(include) -L(lib dir) -l(libname)
OBJ = parser.o lexer.o 

main: $(OBJ) main.o 
	$(CXX) $(CXXFLAGS) $(OBJ) main.cc -o $@ 

#TODO type check
test: $(OBJ) 
	$(CXX) $(CXXFLAGS) $(OBJ) lexer_test.cc -o lexer_test 
	$(CXX) $(CXXFLAGS) $(OBJ) parser_test.cc -o parser_test
	$(CXX) $(CXXFLAGS) $(OBJ) symbol_table_test.cc -o symbol_table_test

lexer.o: lexer.h
parser.o: lexer.h node.h symbol_table.h


.PHONY: clean
clean:
	-rm -f main test
	-rm -f *.o 
