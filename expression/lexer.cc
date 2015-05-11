#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>

#include "global.h"

std::string g_token;
int g_token_type;


TokenType get_token() {
	using namespace std;
    char last_char = getchar();
    //black tab
    while (' ' == last_char) last_char = getchar();
    //eof
	if (last_char == EOF) return EOI;
    //id
    if (isalpha(last_char)) {
        stringstream ss;
        do {
            ss << last_char;
            last_char =  getchar();
        }while (isalpha(last_char));
        g_token = ss.str();
		ungetc(last_char, stdin);
        return ID;
    }
	//number
	if (isdigit(last_char)) {
        string num_str;
		do{
			num_str += last_char;
			last_char = getchar();
		}while (isdigit(last_char) || last_char == '.');//bug 
		g_token = num_str;
		ungetc(last_char, stdin);
		//g_number = strtod(num_str.c_str(), 0);
		return NUMBER;
	}
	g_token = last_char;
	//other
	switch(last_char) {
		case '=':	return ASSIGN;
		case '+':	return ADD;
		case '-':	return MINUS;
		case '*':	return MULTI;
		case '/':	return DEVI;
		case ';':	return SEMI;
	}
	return UNKONWN;
}


