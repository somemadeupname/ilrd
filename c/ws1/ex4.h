#include <stdio.h>

long double PowTen(int exp)
{
    //initializing base and result
    long double res = 1;
    int base = 10;
    
    if (exp < 0)
    {
    exp = -exp;
    //if exp is negative use root instead of power
    base = 1/base;
    }
    
    int index = 0;
    
    for (index; index < exp; index++)
    {
        res = res * base;
    }
    
    return res;
}
