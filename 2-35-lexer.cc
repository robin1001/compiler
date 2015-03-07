#include <stdio.h>
#include <ctype.h>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

class Token {
public:
	Token(int t): tag_(t) {}
	const int tag_;
};

class Tag {
public:
	enum {kNum=256, kId, kTrue, kFalse};
};

class Num: public Token {
public:
	Num(int v): Token(Tag::kNum), value_(v) {}
	const int value_;
};

class Word: public Token {
public:
	Word(int t, string s): Token(t), lexeme_(s) {}
	const string lexeme_;
};

class Lexer {
public:
	Lexer() {
		line_ = 1;
	}
	int line_;
	Token Scan();
    void Lex() {
        while(!feof(stdin)) {
            Scan();
        }
    }
private:
	unordered_map <string, Token> words_;
};

Token Lexer::Scan() {
	char ch;
	while (ch = getchar()) {
		if (' ' == ch || '\t' == ch) continue;
		else if ('\n' == ch) line_++;
		else break;
	}

	if (isdigit(ch)) {
		int v = 0;
		do {
			v = v * 10 + (ch - '0');
			ch = getchar();
		}while(isdigit(ch)); 
        printf("%d ", v);
		ungetc(ch, stdin);
		return Num(v);
	}
	else if (isalpha(ch)) {
		stringstream ss;
		do {
			ss<<ch;
			ch = getchar();
		} while(isalnum(ch));
		ungetc(ch, stdin);
	    string s = ss.str();
		//Word w;
		////add in words_
		//if (words_.find(s) != words_.end()) w = words_[s];
		//else {
		//	Word w = Word(Tag::kId, s); 
		//	words_[s] = w;
		//}
        printf("%s ", s.c_str());
		//return w;
        return Word(Tag::kId, s);
	} 
    else {
        printf("%c ", ch);
        return Token(ch);
    }
}

int main() {
    Lexer lexer;
    lexer.Lex();
    return 0;
}


