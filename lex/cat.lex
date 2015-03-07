
%option noyywrap 
%%

.|\n {ECHO;/*default action*/}

%%

void main() {
    yylex();
}
