#include <stdio.h>                  /* printf */

void PrintHelloFromHex();
double PowTen(int exp);
long FlipInt (int n);
void SwapInt (int *a, int *b);

/***************************************

*       Tests Functions                *

****************************************/

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

void TestSwapInt(int a, int b)
    {
        int old_a = a;
        int old_b = b;
        SwapInt(&a,&b);
        if (old_a != b || old_b != a)
        {
            printf("\033[1;31m");
            printf ("ex6 Error: ");
            printf("\033[0m\n");
        }
        else
        {
            printf("\033[1;32m");
            printf ("ex6 Success! ");
            printf("\033[0m");
            printf("Values successfully swapped!\n");
        }
    }
    

int main ()
{
    /*           ex 3 test      */
    
    /*
    PrintHelloFromHex();
    */
    
    /*           ex 4 tests      */
    double d = 0.010000;
    printf("################### ex4 tests ###############\n");
    
    

    TestPowTen(100.000000, 2);
    TestPowTen(d, -2);
    TestPowTen(100000.000000, 5);
    TestPowTen(1, 0);
    
    
    printf("PowTen(2) = %f\n",  PowTen(2));
    printf("PowTen(0) = %f\n",  PowTen(0));
    printf("PowTen(5) = %f\n",  PowTen(5));
    printf("PowTen(-5) = %f\n",  PowTen(-5));
    
    /*           ex 5 tests      */
    
    /*
    TestFlipInt(23, 32);
    TestFlipInt(-2301, -1032);
    */
    
    /*           ex 6 tests      */
    
    /*
    TestSwapInt(3,5);
    */
    
    
    return 0;
}


