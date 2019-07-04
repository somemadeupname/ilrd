#include <stdio.h>                  /* printf */

void PrintHelloFromHex();
double PowTen(int exp);
long FlipInt (int n);


int main ()
{
    /*           ex 3 test      */
    
    /* PrintHelloFromHex(); */
    
    /*           ex 4 tests      */
    
    int exp = -2;
    if (0.010000 != PowTen(exp))
        {
        printf ("PowTen(%d) = %f\n", exp, PowTen(exp));
        }
    
    
    /*           ex 5 tests      */
    
    
    /*
    int num = 23;
    if (FlipInt(num) != 32)
    {
        printf("\033[0;31m");
        printf ("Error: ");
        printf("\033[0m");
        printf("Mismatch when n = %d.\n",num);
    }
    else
    {
        ("Success when n = %d.\n", n);
    } 
    */ 
    
    
    return 0;
}


