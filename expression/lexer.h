#ifndef	LEXER_H_ 
#define	LEXER_H_ 

#include <string>

#include "global.h"

extern std::string g_token;
extern TokenType g_token_type;
extern TokenType get_token();

#endif
