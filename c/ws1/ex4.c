#include <stdio.h>
/********************************
*   Author     :      Shieber   *

*   Reviewer   :      Yuval     *

*   Version    :      Sent      *   

*   Input      :      exp       *

*   Output     :      10^exp    *

********************************/

double PowTen(int exp)
{
    /* initializing base, result and index */
    double res = 1.0;
    float base = 10.0F;
    int index = 0;
    
    if (exp < 0)
    {
    exp = -exp;
    /* if exp is negative multiply by 1/base */
    base = 1.0F/base;
    }
    
    for (index = 0; index < exp; ++index)
    {
        res = res * base;
    }
    
    return res;
}

/*

int main ()
{
    int exp = 10;
    printf ("10^%d = %f.\n", exp, PowTen(exp));
    return 0;
}
*/

