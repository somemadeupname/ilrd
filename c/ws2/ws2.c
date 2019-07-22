#include <stdio.h>
#include <string.h> /* strlen */
#include <assert.h>

#define EMPTY_CHAR '\0'
#define TO_CHAR(n) (n + '0')
#define TO_INT(n) (n - '0')

void ReverseString(char *str)
{
	/* TODO assert */
	
	char temp = 0;
	char *str_left = NULL;
	char* str_right = NULL;
	str_right = strlen(str) + str - 1;
	str_left =  str;
	
	while (str_left < str_right)
	{
		temp = *str_left;
		*str_left = *str_right;
		*str_right = temp;
		--str_right;
		++str_left;
	}
}

char *BigNumbers (char *result, char *num1, char *num2)
{
	int save = 0;
	char *temp_result = result;
	char *temp_num1 = (char *) num1;
	char *temp_num2 = (char *) num2;	
	
	/* TODO asserts */
	
	ReverseString(num1);
	ReverseString(num2);
	
	while ( EMPTY_CHAR != *num1 && EMPTY_CHAR != *num2 )
	{
		*result = TO_INT(*num1) + TO_INT(*num2) + save;
		if (*result > '9')
		{
			save = 1;/* add 1 to the next addition*/
			*result -= 10;
		}
		else
		{
			save = 0; /* no need to add 1 to next addition */	
		}
		++num1;
		++num2;
		++result;		
	}
	
	if ( EMPTY_CHAR == *num1 )
	{
		while ( EMPTY_CHAR != *num2 )
		{
			*result = *num2 + save;
			if (*result > '9')
			{
				save = 1;	
				*result -= 10;	
			}
			else
			{
				save = 0;
			}
			++num2;
			++result;
		}
	}
	else
	{
		while ( EMPTY_CHAR != *num1 )
		{
			*result = *num1 + save;
			if (*result > '9')
			{
				save = 1;
				*result -= 10;
			}
			else
			{
				save = 0;
			}
			++num1;
			++result;
		}
	}
	
	if (save != 0)
	{
		*result = TO_CHAR(save); /* if one more digit
									remains from the last addition*/
		++result;
	}
	*result = EMPTY_CHAR; /*appending empty character to the end of the string*/
	ReverseString(temp_result);
	ReverseString(temp_num1);
	ReverseString(temp_num2);		
	
	return result;
}
/*
void TestBigNumbers (char *result ,char* num1, char *num2, const char *expected_result)
{
	BigNumbers(res, num1, num2);
	if (expected_result == res)
	{
        printf ("Success!\n"); 
		printf("\n%s \n+\n%s\n_____\n%s", num1, num2, res);
		printf("\t expected: %s\n", expected_result);              

    }
    else
    {
        printf ("Failed!\n");
		printf("\n%s \n+\n%s\n_____\n%s", num1, num2, res);
		printf("\t expected: %s\n", expected_result); 
	}   
}
*/
/*	
int main()
{
	
	char no_save[4];
	char one_save[4];
	char res_more_digits_than_nums[5];
	char big_nums[10];	
	
	
    char three_digit1[] = "321";
    char three_digit2[] = "213";
    char three_digit_to_four_result[] = "568";
    char three_digit_to_four_result[] = "987";    
    char result[100] = " ";
	
	TestBigNumbers("123", "456", "579");
    TestBigNumbers("171", "456", "627");
    TestBigNumbers("923", "456", "1379");
    TestBigNumbers("1111111", "111111111", "112222222");
    TestBigNumbers("111111111", "111111111", "222222222");
		
	return 0;
}
*/
