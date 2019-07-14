#include <stdio.h>
#include "ws2_ex.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m\n");
#define START_GREEN printf("\033[1;32m");
#define END_GREEN printf("\033[0m\n");

void TestIsPalindrome(const char *str)
{
	    {
        printf ("string = %s\n", str);
		if ( FALSE == IsPalindrome(str))
        {
			START_RED
            printf ("%s is not a palindrome.\n", str);
			END_RED
        }
        else
        {
			START_GREEN
            printf ("%s is a palindrome.\n", str);
            END_GREEN
        }
    }
}

void TestSwapPtrInt(int left, int right)
{
	int ** left_ptr_ptr = &(&left);
	int ** right_ptr_ptr = &(&right);
	
	int init_value_left = left;
	int init_value_right = right;
	
	SwapPtrInt(left_ptr_ptr, right_ptr_ptr);
	
	If ( ( *(*left_ptr_ptr) == init_value_right ) && ( *(*right_ptr_ptr) == init_value_left )



int main()
{
	/* IsPalindrome test */
    printf("############### IsPalindrome Test ####################\n");	
	TestIsPalindrome("ABBA");
	TestIsPalindrome("ABA");
	TestIsPalindrome("test");
	TestIsPalindrome("");
	
	/* SwapPtrInt test */
    printf("############### SwapPtrInt Test ####################\n");	
    
    	
	return 0;
}
