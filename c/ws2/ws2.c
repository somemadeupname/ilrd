#include <stdio.h> 		/* printf */
#include "ws2.h"

/**************** Strlen*****************
*   Author     :      Shieber           *

*   Reviewer   :      Vova              *

*   Version    :      sent              *   

*   Input      :      char*             *

*   Output     :      Length of string  *

*****************************************/


size_t Strlen (const char* str)
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

int Strcmp (const char* str1, const char* str2)
{
    while ( (*str1 != '\0') && (*str2 != '\0'))
    {
    	++str1;
    	++str2;
        if ( *(str1) != *(str2) )
        {
            break;
        }
    }
    return (*str1)-(*str2); /*calculate the diff in ascii */
}
