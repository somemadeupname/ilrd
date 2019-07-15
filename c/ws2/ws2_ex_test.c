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
	int *left_ptr_ptr = &left;
	int *right_ptr_ptr = &right;
	
	int init_value_left = left;
	int init_value_right = right;
	
	SwapPtrInt(&left_ptr_ptr, &right_ptr_ptr);
	
	if ( ( *left_ptr_ptr == init_value_right ) && ( *right_ptr_ptr == init_value_left ) )
	{
		START_GREEN
        printf ("init_value_left = %d.\n", init_value_left);
        printf ("init_value_right = %d.\n", init_value_right);        
        printf ("*left_ptr_ptr = %d.\n", *left_ptr_ptr);
        printf ("*right_ptr_ptr = %d.\n", *right_ptr_ptr);        
        END_GREEN
        printf ("Pointers swapped successfully.\n");        
    }
    else
    {
		START_RED
        printf ("Pointers swapping failed.\n");
        END_RED
    }
}

void TestBigNumbers (char * result, const char* num1, const char *num2, const char *expected_result)
{
	BigNumbers(result, num1, num2);
	printf("%s + %s =\n\t%s.", num1, num2, result);
	printf("\t expected: %s\n", expected_result);
}

int main()
{
	char no_save[4] = {'0', '0', '0'};
	char one_save[4] = {'0', '0', '0'};	
	char res_more_digits_than_nums[5] = {'0', '0', '0', '0'};
	/*char big_nums[9] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'};*/
	
	/* IsPalindrome test */
    /*
    printf("#################### IsPalindrome Test ####################\n");	
	TestIsPalindrome("ABBA");
	TestIsPalindrome("ABA");
	TestIsPalindrome("test");
	TestIsPalindrome("");
	*/
	/* SwapPtrInt test */
    /*
    printf("#################### SwapPtrInt Test ####################\n");	

	TestSwapPtrInt(1,2); 
	TestSwapPtrInt(2,2);  
	*/
    printf("#################### BigNumbers Test ####################\n");
    
    
    TestBigNumbers(no_save, "123", "456", "579");
    TestBigNumbers(one_save, "171", "456", "627");   
    TestBigNumbers(res_more_digits_than_nums, "923", "456", "1379");
    /*TestBigNumbers(big_nums, "111111111", "1111111", "112222222");*/
        	
	return 0;
}
