CXX = g++
CXXFLAGS = -g #-I(include) -L(lib dir) -l(libname)
OBJ = lexer.o node.o parser.o

expression: $(OBJ) main.o 
	$(CXX) $(CXXFLAGS) $(OBJ) main.o -o expression  
test: $(OBJ) test.o
	$(CXX) $(CXXFLAGS) $(OBJ) test.o -o test
	
lexer.o: global.h
node.o: global.h node.h
parser.o: global.h lexer.h
main.o: global.h lexer.h
test.o: global.h lexer.h

.PHONY: clean
clean:
	-rm expression test
	-rm *.o 
