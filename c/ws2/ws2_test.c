#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <strings.h> /* strcasecmp */
#include "ws2.h"

void TestStrcpy(char *dest, const char *src)
    {
    	printf ("dest = %s\n", dest);
        printf ("src = %s\n", src);                    
        if ( strcpy(dest,src) != Strcpy(dest,src))
        {
            printf("\033[1;31m");
            printf ("Strcpy Error: pointers don't match");
            printf("\033[0m\n");
    		printf ("dest = %s\n", dest);
       		printf ("src = %s\n",src);                                
        }
        else
        {
            printf("\033[1;32m");
            printf ("Strcpy Success!");
            printf("\033[0m\n");
       		printf ("src = %s\n",src);
	   		printf ("dest = %s\n", dest);       		
        }
    }

void TestStrncpy(char * dest, const char * src, size_t n)
    {
    	printf ("dest = %s\n", dest);
        printf ("src = %s\n",src);                    
    	printf ("n = %d\n", (int) n);
                    
        if (strncpy(dest,src, n) != Strncpy(dest,src,n))
        {
            printf("\033[1;31m");
            printf ("Strncpy Error: pointers don't match");
            printf("\033[0m\n");
        }
        else
        {
            printf("\033[1;32m");
            printf ("Strncpy Success! ");
            printf("\033[0m\n");
            printf ("dest = %s\n", dest);
            printf ("src = %s\n",src);                    
        }
    }
    
int TestStrcasecmp(const char * str1, const char * str2)
    {
        printf ("str1 = %s\n", str1);
        printf ("str2 = %s\n",str2);                    
       
        if (strcasecmp(str1,str2) != Strcasecmp(str1,str2))
        {
            printf("\033[1;31m");
            printf ("Strcasecmp Error: pointers don't match");
            printf("\033[0m\n");
        }
        else
        {
            printf("\033[1;32m");
            printf ("Strcasecmp Success! ");
            printf("\033[0m\n");
        }
        return Strcasecmp(str1,str2);
	}
      
int main()
{
    char str[] = "what is";
    char empty[] = "";
        
    char str1[] = {'a','0','\0'};
    char str2[] = {'A','0','\0'};
    char str3[] = {'\0'};
    char str4[] = {'a','\0'};
    
    char dest[8];
    char* src = "youare";
    
    char str5[] = "cAsE Sendddd";
    char str6[] = "cas esendd";    
    
    
    printf ("############## Strlen ##############\n");
     
    /*empty string*/
    
    printf("%s has %ld chars.\n", empty, Strlen(empty));
    
    /* regular string */

    printf("%s has %ld chars.\n", str, Strlen(str));
       
    printf ("############## Strcmp ##############\n");
      
    printf("str1 is %s\nstr2 is %s\n\
    Diff is %d\n", str1, str2, Strcmp(str1, str2));

    printf("str3 is %s\nstr4 is %s\n\
    Diff is %d\n", str3, str4, Strcmp(str3, str4));
    
    printf ("############## TestStrcpy ##############\n");
    
    
    TestStrcpy(dest,src);
    
    
    printf ("############## TestStrncpy ##############\n");
    
    
    TestStrncpy(dest,"hi",4);
    
    
    printf ("############## TestStrcasecmp ##############\n");
    
    TestStrcasecmp(str5,str6);
            
    printf("Strcasecmp(str5,str6)=%d\n", Strcasecmp(str5,str6));
    printf("strcasecmp(str5,str6)=%d\n", strcasecmp(str5,str6));       
               
    return 0;
}

