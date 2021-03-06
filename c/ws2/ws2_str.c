#include <stdio.h> 		/* printf */
#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* abs malloc */
#include <string.h>	
#include <ctype.h> 		/* to lower */
#include "ws2_str.h"


#define EMPTY_CHAR '\0'
#define FALSE 0
#define TRUE 1


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

int Strncmp(const char *s1, const char *s2, size_t n)
{
    size_t num = 0;
    
    while ( (*s1 != '\0') && (*s2 != '\0') && num < n - 1)
    {
        if ( *s1 != *s2 )
        {
            break;
        }
        ++s1;
    	++s2;
    	++num;
    }
    return (*s1 - *s2); /*calculate the diff in ascii */
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
	/*append empty char to end of dest */
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
	
	/*NULL checks*/
	assert (s1 != NULL);
    assert (s2 != NULL);
    	
	
	while ( *s1 != EMPTY_CHAR && ( tolower(*s1) == tolower(*s2) ) )
	{
		++s1;
		++s2;
	}
	return *s1 - *s2;
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
		
		assert(s != NULL); /*TODO change to if. should also work in release version*/
		
		return Strcpy (dest, s);
	}

char *Strcat(char *dest, const char *src)
	{
		char * dest_start = dest;
		
		Strcpy ( (dest + (int) Strlen(dest)), src);
		
		return dest_start;
	}

char *Strncat(char *dest, const char *src, size_t n)
	{
		char * dest_start = dest;
		Strncpy ( (dest + (int) Strlen(dest)), src, n);
		/* TODO add null char in the end strlen(n) */		
		return dest_start;
	}

char *Strstr(const char *haystack, const char *needle)
{
	char* cur_hay = (char*) haystack;
	int ne_size = (int) Strlen(needle);
	char* cur_nee = (char*) needle;
	int hay_index = 0;
	
	/* edge case when needle == NULL */
	if ( *needle == EMPTY_CHAR )
	{
		return cur_hay;
	}
	
	for (hay_index = 0; *(cur_hay + hay_index) != EMPTY_CHAR; ++hay_index)
	{	
		if ( !Strncmp(cur_nee, cur_hay, ne_size) )
		{
			return cur_hay;
		}
		++cur_hay;
	}
	
	return NULL;
}
