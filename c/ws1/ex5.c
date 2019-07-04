#include <stdio.h>

#define POSITIVE 1
#define NEGATIVE (-1)
#define BASE 10

long FlipInt (int n)
{
    int sign = POSITIVE;
    
    if (n < 0)
    {
    sign = NEGATIVE;
    //if n<0 make it positive
    n = -n
    }
    
    int res = 0;
    int digit;
    
    for  (n != 0)
    {
    digit = n%BASE;
    n = n/BASE;
    }
