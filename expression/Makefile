CXX = g++
CFLAGS = -g -o2#-I(include) -L(lib dir) -l(libname)
OBJ = lexer.o main.o

expression: $(OBJ)
	$(CXX) -o expression $(OBJ) 

lexer.o: global.h
main.o: global.h

.PHONY: clean
clean:
	-rm *.o 
