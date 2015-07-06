#ifndef	_LEXER_H_ 
#define	_LEXER_H_ 

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

TokenType get_token();

extern TokenType g_token_type;
extern std::string g_token;

#endif
