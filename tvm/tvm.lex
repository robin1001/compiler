%{
#include <stdio.h>
#include <string.h>

#define MAX_TOKEN 128
typedef enum {
	TOKEN_EOF = 0, //lex return 0 if EOF
	TOKEN_MEM, //LD, ST		
	TOKEN_REG, //LD, ST		
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

char g_token[MAX_TOKEN];

%}

%option noyywrap

digit [0-9]
number {digit}+
letter [a-zA-Z]
label {letter}({digit}|{letter})*

%%

[\t \n]+  /*ignore \t and ' ' */
"ld" 		{/*printf("%s\n", yytext);*/ return TOKEN_MEM;}
"st" 		{/*printf("%s\n", yytext);*/ return TOKEN_MEM;}
"add" 		{/*printf("%s\n", yytext);*/ return TOKEN_CALC;}
"sub" 		{/*printf("%s\n", yytext);*/ return TOKEN_CALC;}
"mul" 		{/*printf("%s\n", yytext);*/ return TOKEN_CALC;}
"dvi" 		{/*printf("%s\n", yytext);*/ return TOKEN_CALC;}
"push"		{/*printf("%s\n", yytext);*/ return TOKEN_STACK;}
"pop" 		{/*printf("%s\n", yytext);*/ return TOKEN_STACK;}
"cmp" 		{/*printf("%s\n", yytext);*/ return TOKEN_CMP;}
"jmp" 		{/*printf("%s\n", yytext);*/ return TOKEN_JMP;}
"je" 		{/*printf("%s\n", yytext);*/ return TOKEN_JMP;}
"jne" 		{/*printf("%s\n", yytext);*/ return TOKEN_JMP;}
"jg" 		{/*printf("%s\n", yytext);*/ return TOKEN_JMP;}
"jl" 		{/*printf("%s\n", yytext);*/ return TOKEN_JMP;}
"jge" 		{/*printf("%s\n", yytext);*/ return TOKEN_JMP;}
"jle" 		{/*printf("%s\n", yytext);*/ return TOKEN_JMP;}
"r0" | 
"r1" |
"r2" |
"r3" |
"r4" |
"r5" | 
"r6" |
"r7" 		{/*printf("%s\n", yytext);*/ return TOKEN_REG;}
{label} 	{/*printf("%s\n", yytext);*/ return TOKEN_LABEL;}
{number} 	{/*printf("%s\n", yytext);*/ return TOKEN_NUMBER;}

"," 		{/*printf("%s\n", yytext);*/ return TOKEN_COMMA;}
":" 		{/*printf("%s\n", yytext);*/ return TOKEN_COLON;}
"[" 		{/*printf("%s\n", yytext);*/ return TOKEN_LEFT_BRACKT;}
"]" 		{/*printf("%s\n", yytext);*/ return TOKEN_RIGHT_BRACKT;}
. {return TOKEN_EOF;}
 
%%

TokenType get_token() {
	TokenType t = (TokenType)yylex();
	strcpy(g_token, yytext);
	return t;
}

int main() 
{
	//while(yylex()) {
	//}
	while(get_token()) {
		printf("%s\n", g_token);	
	}
    return 0;
}
