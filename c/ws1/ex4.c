#include <stdio.h>
#include <stdlib.h>

long double PowTen(int exp)
{
    //initializing base and result
    long double res = 1;
    float base = 10;
    
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
    
int main (int argc, char *argv[])
{
    int exp = atoi(argv[1]);
    //printf ("%d", atoi(argv[1]));
    printf ("10^%d = %Le.\n", exp, PowTen(exp));
    return 0;
}
