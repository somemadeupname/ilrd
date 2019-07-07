#include <stdio.h>
#include <stddef.h>

size_t Strlen (const char* str);
int Strcmp (const char* str1, const char* str2);

int main()
{
    char str[] = "what is";
    char empty[] = "";
        
    char str1[] = {'a','0','\0'};
    char str2[] = {'A','0','\0'};
    char str3[] = {'\0'};
    char str4[] = {'a','\0'};
    
    
    /* strlen tests */
     
    /*empty string*/
    
    printf("%s has %ld chars.\n", empty, Strlen(empty));
    
    /* regular string */

    printf("%s has %ld chars.\n", str, Strlen(str));
       
    /* strcmp tests */
      
    printf("str1 is %s\nstr2 is %s\n\
    Diff is %d\n", str1, str2, Strcmp(str1, str2));

    printf("str3 is %s\nstr4 is %s\n\
    Diff is %d\n", str3, str4, Strcmp(str3, str4));
    
    return 0;
}

