#include <stdio.h> 		/* printf */
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* abs malloc */
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
	assert (s1 != NULL);
    assert (s2 != NULL);
    	
	
	while ( *s1 != EMPTY_CHAR || *s2 != EMPTY_CHAR )
		{
		/*break*/						
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
		else if ( !isalpha(*s1)	)
			/* one alphabet one isn't */
			{
			break;
			}
		}
	return *s2 - *s1;
	}

char *Strchr(const char *s, int c)
{	
	char* c_position = NULL;
	assert(s != NULL);
	
	/* if c and s start with empty char */
	if (EMPTY_CHAR == *s && EMPTY_CHAR == c)
		{
			c_position = (char*) s;
		}
	
	while (*s != c && *s != EMPTY_CHAR)
		{
			s++;
		}
	
	if ( c == *s )
		{
			c_position = (char*) s;
		}
	return c_position;
}

char *Strdup(const char *s)
	{

		int string_size = (int) (Strlen(s) + 1); /*adding 1 for the empty char */

		char* dest = (char*) malloc (string_size * sizeof(char));
		
		assert(s != NULL);
		
		return Strcpy (dest, s);
	}

char *Strcat(char *dest, const char *src)
	{
		return Strcpy ( (dest + (int) Strlen(dest)), src);
	}

char *Strncat(char *dest, const char *src, size_t n)

	{
		return Strncpy ( (dest + (int) Strlen(dest)), src, n);
	}

char *Strstr(const char *haystack, const char *needle)
	{
		/*getting the substring size*/
		int sub_str_size = (int) Strlen(needle);
		int position = 0;
		char* needle_pos = (char*) needle;
		char* haystack_pos = (char*) haystack;
		char* result = NULL;
		
		assert(haystack != NULL);
		assert(needle != NULL);
				
		while ( *haystack != EMPTY_CHAR )
			{
				while ( position < sub_str_size && *haystack_pos != EMPTY_CHAR )
					{
						if (*needle_pos != *haystack_pos)
							{
								/* return needle pointer to the
								start for the next compare iteration*/	
								char* needle_pos = (char*) needle;
								break;
							}
						else
							{
								++needle_pos;
								++haystack_pos;
							}
					}
					
					if ( position == sub_str_size )
						{
							result = haystack_pos;
						}
				}
			return result;
		}
						













