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
    double base = 10.0F;
    int index = 0;
    
    if (exp < 0)
    {
    	exp = -exp;
    	/* if exp is negative multiply by 1/base */
    	base = 1.0F/base;
    	printf("----\n");
    	printf("-exp \t= %8d\n",exp);
    }
    
    /* for testing purpuses only */
    else { printf("----\n");printf("exp \t= %8d\n",exp); }
    
    for (index = 0; index < exp; ++index)
    {
        res = res * base;
    }
    
    return res;
}

