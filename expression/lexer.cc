#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>

#include "global.h"

std::string g_token;
double g_number;
int g_token_type;



int get_token() {
	using namespace std;
    static int last_char = ' ';
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
        return ID;
    }
	//number
	if (isdigit(last_char)) {
        string num_str;
		do{
			num_str += last_char;
			last_char = getchar();
		}while (isdigit(last_char) || last_char == '.');//bug 
		g_number = strtod(num_str.c_str(), 0);
		return NUMBER;
	}
	
	int cur_char = last_char;
	last_char = getchar();
	return cur_char;
}


