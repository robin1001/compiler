#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>

#include <string>

typedef enum {
    EOI, //end of input, EOF
    NUMBER, ID,
	ASSIGN, ADD, MINUS, MULTI, DEVI,
	SEMICOLON, //;
	LEFT_PAREN, RIGHT_PAREN,
    UNKNOWN
}TokenType;


#endif
