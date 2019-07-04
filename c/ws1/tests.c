#include <stdio.h>                  /* printf */

void PrintHelloFromHex();
double PowTen(int exp);
long FlipInt (int n);

void TestPowTen(double expected_result, int exp)
    {
        if (expected_result != PowTen(exp))
        {
            printf("\033[1;31m");
            printf ("ex4 Error: ");
            printf("\033[0m");
            printf ("%f != %f\n", expected_result, PowTen(exp));        
        }
        
        else
        {
            printf("\033[1;32m");
            printf ("ex4 Success! ");
            printf("\033[0m");
            printf("PowTen(%d) = %f\n", exp, PowTen(exp));
        }
    }
    
void TestFlipInt(long expected_result, int n)
    {
        if (expected_result != FlipInt(n))
        {
            printf("\033[1;31m");
            printf ("ex5 Error: ");
            printf("\033[0m\n");
            printf("input = %d\n", n);
            printf ("%ld != %ld\n", expected_result , FlipInt(n));        
        }
        else
        {
            printf("\033[1;32m");
            printf ("ex5 Success! ");
            printf("\033[0m");
            printf ("%ld <-> %ld\n", expected_result , FlipInt(n));
        }
    }

int main ()
{
    /*           ex 3 test      */
    
    PrintHelloFromHex();
    
    /*           ex 4 tests      */
    
    
    TestPowTen(100, 2);
    
    
    /*           ex 5 tests      */
    
    TestFlipInt(23, 32);
    TestFlipInt(-2301, -1032);
    
    
    return 0;
}


