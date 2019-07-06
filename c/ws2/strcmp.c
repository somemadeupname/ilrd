#include <stdio.h>

#define TRUE 0

/********************* WS2 *******************************

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
    while ( (*(str1++) != '\0') || (*(str2++) != '\0'))
    {
        if ( *(str1) != *(str2) )
        {
            return (*str2)-(*str1); /*calculate the diff in ascii */
        }
    }
    return TRUE;
}
