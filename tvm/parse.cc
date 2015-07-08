#include <stdio.h>
#include <stdlib.h>

#include "lex.h"
#include "parse.h"


void syntax_unexpected(char *s) {
	printf("unexpted token %s\n", s);
	exit(-1);
}


void match(TokenType expected) {
	if (g_token_type == expected) g_token_type = get_token();
	else {
		printf("syntax error, expected %d but get %d %s\n", expected, g_token_type, g_token);
		exit(-1);
	}
}

void expr() {
	if (TOKEN_LABEL == g_token_type) {
		//TODO add label in symbol table	
		match(TOKEN_LABEL);
		match(TOKEN_COLON);
	}
	switch(g_token_type) {
		case TOKEN_LDST: //ld st
			match(TOKEN_LDST);
			match(TOKEN_REG);
			match(TOKEN_COMMA);
			//TODO mem
			match(TOKEN_LEFT_BRACKT);
			match(TOKEN_REG);
			if (TOKEN_COMMA == g_token_type) {
				match(TOKEN_COMMA);
				match(TOKEN_REG);
			}
			match(TOKEN_RIGHT_BRACKT);
			break;
		case TOKEN_MOV:
			match(TOKEN_MOV);
			match(TOKEN_REG);
			match(TOKEN_COMMA);
			if (TOKEN_NUMBER == g_token_type)
				match(TOKEN_NUMBER);
			else 
				match(TOKEN_REG);
			break;
		case TOKEN_STACK:
			match(TOKEN_STACK);
			match(TOKEN_REG);
			break;
		case TOKEN_CMP:
			match(TOKEN_CMP);
			match(TOKEN_REG);
			match(TOKEN_COMMA);
			match(TOKEN_REG);
			break;
		case TOKEN_CALC:
			match(TOKEN_CALC);
			match(TOKEN_REG);
			match(TOKEN_COMMA);
			match(TOKEN_REG);
			match(TOKEN_COMMA);
			match(TOKEN_REG);
			break;
		case TOKEN_JMP:
			match(TOKEN_JMP);
			match(TOKEN_LABEL);
			break;
		default:
			syntax_unexpected(g_token);	
	}
}

void parse() {
	g_token_type = get_token();
	while (g_token_type) {
		expr();
	}
}
