#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*delete the note in the .c file*/
//we are the world
int match(char ch)
{
	char c = getchar();
	if(c != ch)
	{
		ungetc(c, stdin);
		return 0;
	}
	return c;
}

int scan_once()
{
	char ch2, ch_pre = '\0';
	char ch = getchar();

	if(ch == EOF)
		return 0;
	switch(ch)
	{
		case '/':
			if(match('*'))
			{
				while(!match('/') && ch_pre != '*' && (ch2 = getchar()) != EOF)
					ch_pre = ch2;	
			}
			else if(match('/'))
			{
				while(!match('\n') && (ch2 = getchar()) != EOF);
				printf("\n");
			}
			else
			{
				printf("%c", ch);
			}
			break;
		case '\"':
			printf("\"");
			while(!match('\"') && ch_pre != '\\' && (ch2 = getchar()) != EOF)
			{
				printf("%c", ch2);
				ch_pre = ch2;	
			}
			printf("\"");
			break;
		default:
			printf("%c", ch);
	}

	return 1;
}


int main()
{
	while(scan_once());

	printf("/**********************/");
	return 0;
}
