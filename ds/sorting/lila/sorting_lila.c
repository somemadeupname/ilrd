#include <assert.h> /* assert */

#include "sorting.h"

static void SortSwapIntImp(int *int_a, int *int_b)
{
	int temp = 0;

	assert (NULL != int_a);
	assert (NULL != int_b);

	temp = *int_a;
	*int_a = *int_b;
	*int_b = temp;
}

void Insertion(int *arr, size_t arr_len)
{
	size_t i = 0;
	size_t runner = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < arr_len; ++i)
	{
		for (runner = i; 
			 (0 < runner) && (arr[runner] < arr[runner - 1]); 
			 --runner)
		{
			SortSwapIntImp(&arr[runner], &arr[runner - 1]);
		}
	}
}

void Selection(int *arr, size_t arr_len)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < arr_len - 1; ++i)
	{
		size_t runner = 0;
		size_t min_index = i;
		
		for (runner = i; runner < arr_len; ++runner)
		{
			if (arr[runner] < arr[min_index])
			{
				min_index = runner;
			}
		}
		SortSwapIntImp(&arr[min_index], &arr[i]);
	}
}

void Bubble(int *arr, size_t arr_len)
{
	size_t i = 0;
	size_t last_swapped = arr_len;

	assert(NULL != arr);
	
	for (i = 0; i < arr_len - 1; ++i)
	{
		size_t size_of_arr = last_swapped;
		size_t swapping_i = 0;
		
		for (swapping_i = 0; swapping_i < (size_of_arr - 1); ++swapping_i)
		{
			if(arr[swapping_i] > arr[swapping_i + 1])
			{
				SortSwapIntImp(&arr[swapping_i], &arr[swapping_i + 1]);
				last_swapped = swapping_i + 1;
			}
		}
	} 
}

