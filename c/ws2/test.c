#include <stdio.h>

size_t Strlen (const char* str);
int Strcmp (const char* str1, const char* str2);

int main()
{
    /* strlen tests */
    
    /*empty string*/
    
    /*char str[] = {'\0'};*/
    char str[] = "what is";
        
    char str1[] = {'a', 0, '\0'};
    char str2[] = {'a', 2, '\0'};
    
    printf("%s", str2);
    
    /*printf("%s is length %lu.\n", str2, Strlen(str2));*/
    
    /* strcmp tests */
    

    
    printf("Diff is %d.\n", Strcmp(str1, str2));
    
    return 0;
}

