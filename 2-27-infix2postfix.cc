#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

class Parser {
public:
    Parser() {
        lookhead_ = getchar();
    }

    void expr() {
        term();
        rest();
    }

private:
    int lookhead_;
    void rest() {
        if (lookhead_ == '+') {
            match('+'); term(); putchar('+'); rest();
        }
        else if (lookhead_ == '-') {
            match('-'); term(); putchar('-'); rest();
        }
        else {}
    }

    void term() {
        if (isdigit(lookhead_)) {
            putchar(lookhead_);
            match(lookhead_);
        }
        else error("Syntax error");
    }

    void match(int t) {
        if (lookhead_ == t) lookhead_ = getchar();
        else error("Syntax error");
    }

    void error(const char *msg) {
        printf("%s\n", msg);
        exit(-1);
    }
};

int main()
{
    printf("Simple translator that translate infix expression to postfix expression in recursive descent method\n");
    Parser parser; 
    parser.expr();
    printf("\n");
    return 0;
}
