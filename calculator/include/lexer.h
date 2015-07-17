#ifndef	_LEXER_H_ 
#define	_LEXER_H_ 

#include <stdio.h>
#include <string>

typedef enum {
    TOKEN_EOI, //end of input, EOF
    TOKEN_NUMBER, TOKEN_ID,
	TOKEN_ASSIGN, TOKEN_ADD, TOKEN_MINUS, TOKEN_MULTI, TOKEN_DEVI,// = + - * /
	TOKEN_SEMICOLON, //;
	TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_UNKNOWN
}TokenType;

class Lexer {
public:
    Lexer(char *input, is_file = true): is_file_(is_file), input_cur_(0), is_read_(false) {
        if (is_file_) {
            fp_ = fopen(input, "r");
        } else {
            input_ = input;
        }
    }
    ~Lexer() {
        if (is_file_) fclose(fp_);
    }
    TokenType get_token() { return token_type_; }
    static std::string token_map(TokenType expect_type); 
protected:
    char read_char(); 
protected:
    bool is_file_;
    bool is_read_; //if already read next char
    FILE *fp_;
    std::string input_; 
    int input_cur_;
    TokenType token_type_;
    std::string token_;
};

#endif
