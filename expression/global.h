#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>

#include <string>
#include <sstream>

typedef enum {
    EOI, //end of input, EOF
    NUMBER, ID,
	ASSIGN, ADD, MINUS, MULTI, DEVI,
	SEMI, //;
    UNKONWN
}TokenType;




#endif
