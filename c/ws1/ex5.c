#include <stdio.h>

#define POSITIVE 1
#define NEGATIVE (-1)
#define BASE 10

/********************************
*   Author     :      Shieber   *

*   Reviewer   :      Yuval     *

*   Version    :      Sent      *   

*   Input      :      n         *

*   Output     :      n reversed*

********************************/

long FlipInt (int n)
{
    int sign = POSITIVE;
    int res = 0;
    int digit = 1;
    
    if (n < 0)
    {
    sign = NEGATIVE;
    /* if n<0 make n positive */
    n = -n;
    }
    
    
    while (n != 0)
    {
        res *= BASE;
        digit = n%BASE;
        n = n/BASE;
        res += digit;
    }
    
    return res * sign;
}
