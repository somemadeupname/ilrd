#include <stdio.h>

size_t Strlen (const char* str)
int Strcmp (const char* str1, const char* str2);

int main()
{
    /* strlen tests */
    
    /*empty string*/
    
    char str[] = {'\0'};
    printf("%s is length %lu.\n", str, Strlen(str));
    
    return 0;
}

