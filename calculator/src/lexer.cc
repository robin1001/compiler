#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>

#include "lexer.h"

std::string g_token;
TokenType g_token_type;

std::string token_map(TokenType expect_type) {
	switch (expect_type) {
		case TOKEN_ID: return "ID";
		case TOKEN_NUMBER: return "NUMBER";
		case TOKEN_ASSIGN: return "=";
		case TOKEN_ADD: return "+";
		case TOKEN_MINUS: return "-";
		case TOKEN_MULTI: return "*";
		case TOKEN_DEVI: return "/";
		case TOKEN_LEFT_PAREN: return "(";
		case TOKEN_RIGHT_PAREN: return ")";
		case TOKEN_SEMICOLON: return ";";
		default: return "unexpected";
	}
}

TokenType get_token() {
	using namespace std;
    char last_char = getchar();
    //black tab
    while (' ' == last_char || '\t' == last_char || '\n' == last_char) last_char = getchar();
    //eof
	if (last_char == EOF) return TOKEN_EOI;
    //id
    if (isalpha(last_char)) {
        stringstream ss;
        do {
            ss << last_char;
            last_char =  getchar();
        }while (isalpha(last_char));
        g_token = ss.str();
		ungetc(last_char, stdin);
        return TOKEN_ID;
    }
	//number
	if (isdigit(last_char)) {
        string num_str;
		do{
			num_str += last_char;
			last_char = getchar();
		}while (isdigit(last_char));//bug 
		g_token = num_str;
		ungetc(last_char, stdin);
		//g_number = strtod(num_str.c_str(), 0);
		return TOKEN_NUMBER;
	}
	g_token = last_char;
	//other
	switch(last_char) {
		case '=':	return TOKEN_ASSIGN;
		case '+':	return TOKEN_ADD;
		case '-':	return TOKEN_MINUS;
		case '*':	return TOKEN_MULTI;
		case '/':	return TOKEN_DEVI;
		case '(':	return TOKEN_LEFT_PAREN;
		case ')':	return TOKEN_RIGHT_PAREN;
		case ';':	return TOKEN_SEMICOLON;
	}
	printf("unknown char %c\n", last_char);
	exit(-1);
	return TOKEN_UNKNOWN;
}


