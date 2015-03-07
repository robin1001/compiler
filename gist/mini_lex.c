/*
keyword: if end while for and or
note: '#'
operator: ":" "==" "!=" "<" ">" "<=" ">=" "+" "-" "*" "/" "\t" 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_LEN  128

int lineno = 1;
char token[MAX_LEN];

int match_ch(char ch)
{
	char c = getchar();
	if(c != ch)
	{
		ungetc(c, stdin);
		return 0;
	}
	return 1;
}

void copy(char *s)
{
	strcpy(token, s);
}

int scan()
{
	char ch;
	int i=0;
	//note
	while((ch = getchar()) && ch == '#')
	{
		while((ch = getchar()) && ch != '\n');
		lineno++;
	}
	ungetc(ch, stdin);

	//enter
	while((ch = getchar()) && ch == '\n') lineno++;
	ungetc(ch, stdin);

	//space
	while((ch = getchar()) && ch == ' ');
	ungetc(ch, stdin);

	ch = getchar();

	if(ch == EOF)	return 0; //filter EOF;
	//operator
	switch(ch)
	{
		case ':':	copy(":");	return 1;
		case '+':	copy("+"); 	return 1;
		case '-':	copy("-"); 	return 1;
		case '*':	copy("*"); 	return 1;
		case '/':	copy("/");	return 1;
		case '(':	copy("("); 	return 1;
		case ')':	copy(")");	return 1;
		case '<':	
			if(match_ch('=')){	copy("<=");	return 1;}
			else {copy("<");	return 1;}
		case '>':
			if(match_ch('=')){	copy(">=");	return 1;}
			else {copy(">");	return 1;}
		case '=':	
			if(match_ch('=')){	copy("==");	return 1;}
			else {copy("=");	return 1;}
		case '!':
			if(match_ch('=')){	copy("!=");	return 1;}
		case ';':	copy(";");	return 1;
		case '\t':	return 1;
	}

	//number
	if(isdigit(ch))
	{	
		token[i++] = ch;
		while((ch = getchar()) && isdigit(ch)) token[i++] = ch;
		ungetc(ch, stdin);
		if(!match_ch('.'))//int
		{
			token[i] = '\0';
			return 1;			
		}	
		else{//float
			while((ch = getchar()) && isdigit(ch)) token[i++] = ch;
			ungetc(ch, stdin);
			token[i] = '\0';
			return 1;
		}
	}

	//word
	if(ch == '_' || isalpha(ch))
	{
		token[i++] = ch;
		while((ch = getchar()) && (ch == '_' || isalpha(ch) || isdigit(ch) ) ) token[i++] = ch;
		ungetc(ch, stdin);
		token[i] = '\0';
		return 1;
	}

	//syntax error
	return 0;
}


int main(int argc, char **argv)
{
	while(!feof(stdin))
	{
		if(scan())
			printf("%04d:	%s\n", lineno, token);	
		else
			printf("%04d:	lex syntax error, letter\n", lineno);
	}
	return 0;
}
