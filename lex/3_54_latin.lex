%option noyywrap

letter [a-zA-Z]
vowel  [aeiou]{letter}*
consonant [bcdfghjklmnpqrstvwxyz]{letter}*

%%
{vowel} {printf("%s_ay", yytext);}
{consonant} {printf("%s_%cay", yytext+1, *yytext); }
%%

void main() 
{
    yylex();
}
