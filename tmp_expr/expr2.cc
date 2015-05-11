#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>

enum Token{
    kEof = -1,
    kNumber = -2
};


static std::string token;
static double number;

static int get_token() {
    static int last_char = ' ';
    //black tab
    while (' ' == last_char) last_char = getchar();
    //eof
	if (last_char == EOF) return kEof;
	//number
	if (isdigit(last_char)) {
        std::string num_str;
		do {
			num_str += last_char;
			last_char = getchar();
		} while(isdigit(last_char) || last_char == '.');//bug 
		number = strtod(num_str.c_str(), 0);
		return kNumber;
	}
	
	int cur_char = last_char;
	last_char = getchar();
	return cur_char;
}

static int cur_token;
void error(char* msg) {
    printf("%s\n", msg);
    exit(-1);
}
int next_token() {
    cur_token = get_token();
    if (kNumber == cur_token) 
        printf("%lf\n", number);
    else
        printf("%c\n", cur_token);
}

void expr(); 
void term(); 
void factor();

void expr() {
    term();
    while('+' == cur_token || '-' == cur_token) {
        next_token();
        term();
    }
}

void term() {
    factor();
    while('*' == cur_token || '/' == cur_token) {
        next_token();
        factor();
    }
}

void factor() {
    if(kNumber == cur_token) { //number
        next_token();
    }
    else if('(' == cur_token) {
        next_token(); 
        expr();
        if (')' != cur_token)
            error("expected )");
        next_token();
    }
    else 
        error("syntax error, expected number or (");
}

int main() {
    next_token();
    expr();    
	return 0;
}
