#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>

enum Token{
    kEof = -1,
    //commands
    kDef = -2, kExtern = -3,
    //primary
    kIdentifier = -4, kNumber = -5
};


static std::string token;
static double number;

static int get_token() {
    static int last_char = ' ';
		//black tab
    while (' ' == last_char) last_char = getchar();
	//comment
	if ('#' == last_char) {
		do {
			last_char = getchar();
		} while (last_char != '\n' && last_char != EOF);
		if (last_char != EOF) last_char = getchar();
	}
    //eof
	if (last_char == EOF) return kEof;
	//id
    if (isalpha(last_char)) {
        token = last_char;
        while(isalnum(last_char = getchar()))
            token += last_char;
        if ("def" == token) return kDef;
        if ("extern" == token) return kExtern;
        return kIdentifier;
    }
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



int main() {
    int t;
    while ((t = get_token()) != kEof) {
        if (t == kIdentifier) printf("%s\n", token.c_str()); 
        else if (t == kNumber) printf("%lf\n", number); 
        else printf("%c\n", t);
    }
	return 0;
}
