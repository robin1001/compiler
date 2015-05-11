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

double expr(); 
double term(); 
double factor();

double calc(char op, double x, double y) {
    switch(op) {
        case '+': return x+y;
        case '-': return x-y;
        case '*': return x*y;
        case '/': return x/y;
        default:
            break;
    }
    return 0;
}

double expr() {
    double x = term();
    while('+' == cur_token || '-' == cur_token) {
        char ch = cur_token;
        next_token();
        double y = term();
        x = calc(ch, x, y);
    }
    return x;
}

double term() {
    double x = factor();
    while('*' == cur_token || '/' == cur_token) {
        char ch = cur_token;
        next_token();
        double y = factor();
        x = calc(ch, x, y);
    }
    return x;
}

double factor() {
    double x;
    if(kNumber == cur_token) { //number
        x = number;
        next_token();
    }
    else if('(' == cur_token) {
        next_token(); 
        x = expr();
        if (')' != cur_token)
            error("expected )");
        next_token();
    }
    else 
        error("syntax error, expected number or (");
    return x;
}

int main() {
    next_token();
    printf("calc result:%lf\n", expr());    
	return 0;
}
