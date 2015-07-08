#ifndef _LEX_H_
#define _LEX_H_

#define MAX_TOKEN 128

typedef enum {
	TOKEN_EOF = 0, //lex return 0 if EOF
	TOKEN_LDST, //LD, ST		
	TOKEN_MOV, //mov 
	TOKEN_REG, //reg 		
	TOKEN_STACK, //POP PUSH
	TOKEN_CALC, //ADD SUB DVI MUL
	TOKEN_CMP, //CMP
	TOKEN_JMP, //JMP, JE,	JNE ...
	TOKEN_NUMBER, //123
	TOKEN_LABEL, //l1
	TOKEN_COMMA, //,
	TOKEN_COLON, //:
	TOKEN_LEFT_BRACKT,
	TOKEN_RIGHT_BRACKT,
}TokenType;


#ifdef __cplusplus
extern "C" {
#endif

TokenType get_token(); 
extern char g_token[MAX_TOKEN];
extern TokenType g_token_type;

#ifdef __cplusplus
}
#endif

#endif
