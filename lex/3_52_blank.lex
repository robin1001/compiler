%option noyywrap

%%

[ ]+  { printf(" "); }

%%

void main() 
{
    // sed "s: +: :g"
    yylex();
}
