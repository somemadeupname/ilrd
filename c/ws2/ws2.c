#include <stdio.h> 		/* printf */
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* abs*/
#include <string.h>	
#include <ctype.h> 		/* isalpha */
#include "ws2.h"

#define CASE_DIFFERENCE 32 /* should be in header */
#define EMPTY_CHAR '\0'


/**************** Strlen*****************
*   Author     :      Shieber           *

*   Reviewer   :      Vova              *

*   Version    :      sent              *   

*   Input      :      char*             *

*   Output     :      Length of string  *

*****************************************/


size_t Strlen(const char* str)
{
    size_t length = 0; /*default length for empty string*/
    
    while ( *(str++) != '\0') /*   used str++ instead of ++str to make sure  */
        {                     /*   the first character isn't NULL            */
        ++length;
        }    
    return length;
}

/********************* Strcmp ****************************

*   Author     :      Shieber                            *

*   Reviewer   :      Vova                               *

*   Version    :      sent                               *   

*   Input      :      char* str1, char* str2             *

*   Output     :      if the strings match - 0. 
                      else the ascii difference of
                      the first unmatching characters    *

*********************************************************/

int Strcmp(const char* str1, const char* str2)
{
    while ( (*str1 != '\0') && (*str2 != '\0'))
    {
        if ( *(str1) != *(str2) )
        {
            break;
        }
        ++str1;
    	++str2;
    }
    return (*str1)-(*str2); /*calculate the diff in ascii */
}

char* Strcpy(char *dest, const char *src)
{
	char* dest_start = dest;
	/*NULL checks*/
	assert (dest != NULL);
	assert (src != NULL);

	while (*src != '\0')
		{
		*dest = *src;
		++src;
		++dest;
		}
	/*append empty char to dest */
	*dest = '\0';
	
	return dest_start;
}

char* Strncpy(char *dest, const char *src, size_t n)
{
	int index = 0;
	char* dest_start = dest;
	
	/*NULL checks*/
	assert (dest != NULL);
	assert (src != NULL);

	while (*src != '\0' && index < (int) n)
		{
		*dest = *src;
		++src;
		++dest;
		++index;
		}
	
	/*append empty chars to dest */
	for (; index < (int) n; ++index)
		{
		*dest = '\0';
		++dest;
		}
	
	return dest_start;
}

int Strcasecmp(const char *s1, const char *s2)
	{
	
	int compare_char = *s1 - *s2;

	/*NULL checks*/
	assert (dest != NULL);
    assert (src != NULL);
    	
	
	while ( *s1 != EMPTY_CHAR || *s2 != EMPTY_CHAR )
		{
/*
		printf("index=%d\n", (index++));
		printf("(*s1)=%d\n", (*s1));
		printf("(*s2)=%d\n", (*s2));
		printf("(s1)=%s\n", (s1));
		printf("(s2)=%s\n", (s2));		
		printf("isalpha(*s1)=%d\n", isalpha(*s1));
		printf("isalpha(*s2)=%d\n", isalpha(*s2));	
*/
														
			
		if ( isalpha(*s1) && isalpha(*s2) )
			{
				compare_char = *s1 - *s2;

				printf("compare_char=%d\n", compare_char);			
				
				
					
				if ( 0 == compare_char || CASE_DIFFERENCE == abs(compare_char) )
					{
						++s1;
						++s2;
					}
			}
		else if ( !isalpha(*s1) && !isalpha(*s2) )
			{
				++s1;
				++s2;
			}
		else /* one alphabet one isn't */
			{
			break;
			}
		}
	return *s1 - *s2;
	}

