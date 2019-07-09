#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <strings.h> /* strcasecmp */
#include "ws2.h"
#include <stdlib.h> /* free */



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

char * TestStrchr(const char *s, int c)
    {
        printf ("s = %s\n", s);
        printf ("c = %c\n",c);                    
       
        
        if (strchr(s,c) != Strchr(s,c))
        {
            printf("\033[1;31m");
            printf ("Strchr Error! ");
            printf("\033[0m\n");
        }
        else
        {
            printf("\033[1;32m");
            printf ("Strcasecmp Success! ");
            printf("\033[0m\n");
        }
        
        return Strchr(s,c);
	}
	
char *TestStrdup(const char *s)
	{
        printf ("s = %s\n", s);
       	/*
        if (! ( strcmp(Strdup(s), strdup(s)) ))
        {
            printf("\033[1;31m");
            printf ("Strdup Error! ");
            printf("\033[0m\n");
        }
        else
        {
            printf("\033[1;32m");
            printf ("Strdup Success! ");
            printf("\033[0m\n");
        }
        */
        return Strdup(s);
	}

char *TestStrcat(char *dest1, const char *src1, char *dest2, const char *src2)
	{
		printf ("dest = %s\n", *dest1);
		printf ("src = %s\n", *src1);		
		if (!strcmp ( Strcat(dest1,src1) , strcat(dest2,src2) ))
			{
            printf("\033[1;31m");
            printf ("Strcat Error! ");
            printf("\033[0m\n");
        	}
        else
        	{
            printf("\033[1;32m");
            printf ("Strcat Success! ");
            printf("\033[0m\n");
        	}
        
    	return dest2;
	}

void TestStrstr(const char *haystack, const char *needle)
	{
		printf ("haystack = %s\n", haystack);
		printf ("needle = %s\n", needle);		
		printf ("Strstr(haystack,needle) = %s\n", Strstr(haystack,needle));
		printf ("strstr(haystack,needle) = %s\n", strstr(haystack,needle));		
		if (!strcmp ( (Strstr(haystack,needle)) , (strstr(haystack,needle)) ))
		{
            printf("\033[1;31m");
            printf ("Strstr Error! ");
            printf("\033[0m\n");
    	}
        else
    	{
            printf("\033[1;32m");
            printf ("Strstr Success! ");
            printf("\033[0m\n");
    	}
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
    
   	char* s1 = "hello";
	int c1 = 'l';
	char* str7 = "yellow";
	char* dest_strdup = Strdup(str7);
	
	char str8[12] = {'a','a','a','a','a',' ','\0','\0','\0','\0','\0','\0'};	
	char str9[12] = {'a','a','a','a','a','a','\0','\0','\0','\0','\0','\0'};	
    
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
    
    /*TestStrcasecmp(str5,str6);*/
            
    printf("Strcasecmp(\"cAsE Sendddd\",\"cas esendd\")=%d\n", Strcasecmp("Ab","Ac"));
    printf("strcasecmp(\"cAsE Sendddd\",\"cas esendd\")=%d\n", strcasecmp("Ab","Ac"));
    
    
    printf ("############## TestStrchr ##############\n");           
	
	

	TestStrchr("hello",'l');
	TestStrchr("",'\0');
	TestStrchr("what's up doc",'u');
	if ( !TestStrchr("what's up doc",'z') )
		{
		printf("null. it's not there!\n");
		}
	
    printf ("############## TestStrdup ##############\n");
    
	
	printf("dest_strdup = %s.\n", dest_strdup);
	free(dest_strdup);
	/*dest_srtdup = NULL;*/
	
	
    printf ("############## TestStrcat ##############\n");	
	
	printf ("%s\n", Strcat(str8, "hello "));
	printf ("str8 = %s\n", str8);		
	printf ("%s\n", Strcat(str8, "there"));	
	printf ("str8 = %s\n", str8);	
	
    printf ("############## TestStrncat ##############\n");	
	
	printf ("%s\n", Strncat(str9, "heallo ", 4));
	printf ("str9 = %s\n", str9);		
	printf ("%s\n", Strncat(str9, "there", 2));	
	printf ("str9 = %s\n", str9);
	
    printf ("############## TestStrstr ##############\n");
	
	TestStrstr("Hello", "lo");
	TestStrstr("Hello", "o");
	TestStrstr("Hello", "");	                
	TestStrstr("Hell o", "Hell");
		
    return 0;
}

