%{
#include <stdio.h>
%}

%option noyywrap

%%
[0-9]+ {printf("number:%s\n", yytext);}
.|\n   {}

%%

int main() 
{
    yylex();
    return 0;
}
