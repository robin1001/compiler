#ifndef	_LEXER_H_ 
#define	_LEXER_H_ 

#include <stdio.h>
#include <string>

typedef enum {
    TOKEN_EOI, //end of input, EOF
    TOKEN_NUMBER, TOKEN_ID,
	TOKEN_ASSIGN, TOKEN_ADD, TOKEN_MINUS, TOKEN_MULTI, TOKEN_DEVI,// = + - * /
	TOKEN_SEMICOLON, //;
	TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_UNKNOWN
}TokenType;

TokenType get_token();
std::string token_map(TokenType expect_type); 

extern TokenType g_token_type;
extern std::string g_token;

#endif
