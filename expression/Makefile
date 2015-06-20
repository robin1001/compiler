CXX = g++
CXXFLAGS = -g #-I(include) -L(lib dir) -l(libname)
OBJ = lexer.o parser.o

expression: $(OBJ) main.o 
	$(CXX) $(CXXFLAGS) $(OBJ) main.o -o expression  
test: $(OBJ) lexer_test.o parser_test.o
	$(CXX) $(CXXFLAGS) $(OBJ) lexer_test.o -o lexer_test
	$(CXX) $(CXXFLAGS) $(OBJ) parser_test.o -o parser_test
	
lexer.o: global.h
node.o: global.h node.h
parser.o: global.h lexer.h
main.o: global.h lexer.h
lexer_test.o: global.h lexer.h
parser_test.o: global.h lexer.h parser.h node.h

.PHONY: clean
clean:
	-rm expression test
	-rm *.o 
