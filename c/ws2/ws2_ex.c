#include <stdio.h>
#include <stdlib.h> /* abs */
#include <string.h> /* strlen */
#include <assert.h>
#include <stdlib.h> /* atoi */
#include "ws2_ex.h"

#define EMPTY_CHAR '\0'
#define WANTED_DIGIT 7
#define BASE 10
#define DIVIDES_WITH_NO_REMAINDER(n) ( (n % WANTED_DIGIT) ? 0 : 1 )
#define TO_CHAR(n) (n + '0')

/**********************
* 
*
***********************/
int HasDigit (int num)
{
	int digit = 0;
	
	if (0 == num)
	{
		return FALSE;
	}

	while ( 0 != num )
	{
		digit = num % BASE;
		if ( WANTED_DIGIT == digit )
		{
			return TRUE;
		}
		num /= BASE;
	}
	return FALSE;
}

/**********************
* 
*
***********************/
void SevenBoom(int from, int to)
{	
	int cur_num = from;
	assert(from < to);
	
	for (cur_num = from; cur_num < to; ++cur_num)
	{
		/*abs for it to work with negative numbers.\
		modulu is undefined for negatives. */
		if ( HasDigit(abs(cur_num)) ||
			 DIVIDES_WITH_NO_REMAINDER(abs(cur_num)) )
		{
			printf("BOOM\n");
		}
		else
		{
			printf("%d\n", cur_num);
		}
	}
}

/**********************
* 
*
***********************/
int IsPalindrome(const char *str)
{

	int left = 0;
	int right = 0;
	int length = 0;
	
	assert (str != NULL);

	length = (int) strlen(str) - 1;	
	
	for (left = 0, right = length; left <= right; ++left, --right)
	{
		if ( *(str + left) != *(str + right) )
		{
			return FALSE;
		}
	}
	return TRUE;
}

/**********************
* 
*
***********************/
void SwapPtrInt(int **left, int **right)
{
	int* temp = NULL;
	assert (left != right); /*no need to do anything if left
							and right point to the same address*/
	assert (NULL == left);
	assert (NULL == right);
	
	temp = *right;
	*right = *left;
	*left = temp;
}

void ReverseString(char *str)
{
	char temp = 0;
	char *str_left = NULL;
	char *str_right = NULL;
	str_right = strlen(str) + str - 1;
	str_left =  str;
	
	while (str_left < str_right) /* as long as the left
								pointer doesn't meet the right */
	{
		temp = *str_right;
		*str_right = *str_left;
		*str_left = temp;		
		++str_left;
		--str_right;		
	}
}

void BigNumbers (char *result, char *num1, char *num2)
{
	int save = 0;
	char *temp_result = result;
	char *temp_num1 = num1;
	char *temp_num2 = num2;	
	
	assert( NULL != result);
	assert( NULL != num1);
	assert( NULL != num2);		
	
	ReverseString(num1);
	ReverseString(num2);
	
	/* when both numbers still have characters */
	while ( EMPTY_CHAR != *num1 && EMPTY_CHAR != *num2 )
	{
		/* convert result to char by using -'0' */
		*result = (*num1) + (*num2) + save - '0';
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
			if (*result > '9') /*if it's greater than 9*/
			{
				save = 1;	
				*result -= 10; /* getting the rightmost digit */
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
			if (*result > '9') /*if it's greater than 9*/
			{
				save = 1;
				*result -= 10; /* getting the rightmost digit */
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
	
	/* reversing the strings back to the correct order*/
	ReverseString(temp_result);
	ReverseString(temp_num1);
	ReverseString(temp_num2);		
}
