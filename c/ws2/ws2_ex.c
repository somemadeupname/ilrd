#include <stdio.h>
#include <stdlib.h> /* abs */
#include <string.h> /* strlen */
#include <assert.h>
#include <stdlib.h> /* atoi */
#include "ws2_ex.h"

#define WANTED_DIGIT 7
#define BASE 10
#define DIVIDES_WITH_NO_REMAINDER(n) ( (n % WANTED_DIGIT) ? 0 : 1 )
#define TO_CHAR(n) (n + '0')
#define TO_INT(n) (n - '0')

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
		/*abs for it to work with negative numbers. modulu is undefined for negatives. */
		if ( HasDigit(abs(cur_num)) || DIVIDES_WITH_NO_REMAINDER(abs(cur_num)) )
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
	assert (left != right); /*no need to do anything if left and right point to the same address*/
	assert (NULL == left);
	assert (NULL == right);
	
	temp = *right;
	*right = *left;
	*left = temp;
}

void AddOneToNextDigitPlace (char *res)
{
	*res = '1';
}

void AddTwoDigits (const char *num1, const char *num2, char *res, int *save)
{
	int temp = 0;
	temp = TO_INT(*num1) + TO_INT(*num2) + *save;
	if ( temp > 10)
	{
		*res = TO_CHAR(temp%10);
		*save = 1;
	}
	else
	{
		*res = TO_CHAR(temp);
		*save = 0;
	}
}
			

/**********************
* 
*
***********************/
char *BigNumbers (char * result, const char* num1, const char *num2)
{
	char *num1_cur = NULL;
	char *num2_cur = NULL;
	char *result_cur = NULL;
	
	size_t digit_place = 0;
	int save = 0;
	size_t result_len = 0;

	assert(NULL != result);
	assert(NULL != num1);
	assert(NULL != num2);
	
	num1_cur = (char *) (num1 + strlen(num1) - 1);
	num2_cur = (char *) (num2 + strlen(num2) - 1);
	result_cur = (char *) (result + strlen(result) - 1);
	result_len = strlen(result);
	
	while ( digit_place < result_len/* && (result != result_cur && 0 == save) */)
	{		
		AddTwoDigits (num1_cur, num2_cur, result_cur, &save);

		if  (1 == save)
		{	
			AddOneToNextDigitPlace ((result_cur-1));
		}
		--num1_cur;
		--num2_cur;
		--result_cur;
		++digit_place;		
	}
	return result;
}
	
			
	
