//递归实现
#include <stdio.h>
int _match(const char *re, const char *text)
{
    if(*re == '\0')
        return 1;
    if(*(re+1) != '*')
    {
        if((*re == *text || *re == '.') && *text != '\0')
            return _match(re+1, text+1);
        else
            return 0;
    }
    //*re=='*'
    while((*re == *text || *re == '.') && *text !=  '\0')
    {
        if(_match(re+2, text))
            return 1;
        text++;
    }
    return _match(re+2, text);
}

int match(const char *re, const char *text)
{
    while(*text++ != '\0')
        if(_match(re, text))
            return 1;
    return 0;
}

int main()
{
    printf("%d\n", match( ".*b", "aaab" ));
    printf("%d\n", match( ".*b", "aaa" ));
    return 0;
}
  
