#include <stdio.h>
#include <stdlib.h> /* abs */
#include <string.h>
#include <assert.h>
#include "ws2_ex.h"

#define WANTED_DIGIT 7
#define BASE 10
#define DIVIDES_WITH_NO_REMAINDER(n) ( (n % WANTED_DIGIT) ? 0 : 1 )
#define FALSE 0
#define TRUE 1

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
	int length = (int) strlen(str) - 1;
	
	assert (str != NULL);
	
	for (left = 0, right = length; left <= right; ++left, --right)
	{
		if ( *(str + left) != *(str + right) )
		{
			return 0;
		}
	}
	return 1;
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
			
			
			
			
			
			
			
	
