%{
int num_lines = 0, num_chars = 0;
%}

%option noyywrap
%%
\n {num_lines++; num_chars++;}
.  {num_chars++;}
%%

void main()
{
    yylex();
    printf("line:%d\tchar:%d\n",num_lines, num_chars);
}
