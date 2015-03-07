%option noyywrap
%%
float {printf("double");}

%%

void main() 
{
    //sed "s:float:double:g"
    yylex();
}
