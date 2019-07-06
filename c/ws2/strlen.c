#include <stdio.h>

/**************** WS2 *******************
*   Author     :      Shieber           *

*   Reviewer   :      Vova              *

*   Version    :      sent              *   

*   Input      :      char*             *

*   Output     :      Length of string  *

*****************************************/


size_t Strlen (const char* str)
{
    int length = 0; /*default length for empty string*/
    
    while ( *(str++) != '\0') /*   used str++ instead of ++str to make sure  */
        {                     /*   the first character isn't NULL            */
        ++length;
        }    
    return length;
}
