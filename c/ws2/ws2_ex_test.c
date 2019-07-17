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

void TestBigNumbers (char * result, char* num1, char *num2, const char *expected_result)
{
	BigNumbers(result, num1, num2);
	if (expected_result == result)
	{
		START_GREEN
        printf ("Sucess!\n"); 
        END_GREEN         
		printf("\n%s \n+\n%s\n_____\n%s", num1, num2, result);
		printf("\t expected: %s\n", expected_result);              

    }
    else
    {
		START_RED
        printf ("Failed\n");
        END_RED        
		printf("\n%s \n+\n%s\n_____\n%s", num1, num2, result);
		printf("\t expected: %s\n", expected_result);        

    }
}

int main()
{
	char result[100] = " ";
			    /* no_save */
    char num1[] = "123";
    char num2[] = "456";
    			/* one save */
    char num3[] = "171";
    char num4[] = "456";    			
				/* more digits than numbers */
    char num5[] = "923";
    char num6[] = "456";    			
    			/* big numbers */
    char num7[] = "1111111";
    char num8[] = "111111111";    
    			/* big numbers 2 */		
    char num9[] = "111111111";
    char num10[] = "111111111";        				 
	
	/* IsPalindrome test */
    
    printf("#################### IsPalindrome Test ####################\n");	
	TestIsPalindrome("ABBA");
	TestIsPalindrome("ABA");
	TestIsPalindrome("test");
	TestIsPalindrome("");
	
	/* SwapPtrInt test */
    /*
    printf("#################### SwapPtrInt Test ####################\n");	
	
	TestSwapPtrInt(1,2); 
	TestSwapPtrInt(2,2);  
	*/
    printf("#################### BigNumbers Test ####################\n");
    
			    /* no_save */
    BigNumbers(result, num1, num2); /* 579 */
    printf("%s <-> 579\n", result);
    			/* one save */
    BigNumbers(result, num3, num4); /* 627 */
    printf("%s <-> 627\n", result);    
				/* more digits than numbers */
    BigNumbers(result, num5, num6); /* 1379 */
    printf("%s <-> 1379\n", result);    
    			/* big numbers */
    BigNumbers(result, num7, num8); /* 112222222  */
    printf("%s <-> 112222222\n", result);    
    BigNumbers(result, num9, num10); /* 222222222 */
    printf("%s <-> 222222222\n", result);    
            	
	return 0;
}
