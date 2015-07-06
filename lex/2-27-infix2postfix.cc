#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

class Parser {
public:
    Parser() {
        lookhead_ = getchar();
    }

    void Expr() {
        Term();
        Rest();
    }

private:
    int lookhead_;
    void Rest() {
        if (lookhead_ == '+') {
            Match('+'); Term(); putchar('+'); Rest();
        }
        else if (lookhead_ == '-') {
            Match('-'); Term(); putchar('-'); Rest();
        }
        else {}
    }

    void Term() {
        if (isdigit(lookhead_)) {
            putchar(lookhead_);
            Match(lookhead_);
        }
        else Error("Syntax error");
    }

    void Match(int t) {
        if (lookhead_ == t) lookhead_ = getchar();
        else Error("Syntax error");
    }

    void Error(const char *msg) {
        printf("%s\n", msg);
        exit(-1);
    }
};

int main()
{
    printf("Simple translator that translate infix expression to postfix expression in recursive descent method\n");
    Parser parser; 
    parser.Expr();
    printf("\n");
    return 0;
}
