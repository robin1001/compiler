#include <stdio.h>
#include <iostream>

#include "global.h"
#include "lexer.h"


extern std::string token_map(TokenType expect_type); 

void test_lexer() {
	TokenType token_type = get_token();
	while (token_type != EOI) {
		printf("%s %s\n", g_token.c_str(), token_map(token_type).c_str());
		//cout << g_token << endl;
		token_type = get_token();
	}
}


int main(int argc, char *argv[]) {
	test_lexer();
}
