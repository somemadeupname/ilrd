
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Nitzan	    *
 *	 Status   : Sent	    *
 ****************************/
#include <stdio.h> /* perror */
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc free */

#include "sorting.h"

enum state {FALSE, TRUE};
enum return_status {SUCCESS, FAIL};

/* int * swap function */
static void IntSwap(int *element1, int *element2)
{
	int num_copy = 0;
	
	assert(NULL != element1);
	assert(NULL != element2);
	
	num_copy = *element1;
	*element1 = *element2;
	*element2 = num_copy;
}

/* isbefore function */
int IsIntBefore(int int1, int int2)
{
	return int2 < int1;
}

/* Sorts @arr using insertion sort  */
void Insertion(int *arr, size_t size)
{
	size_t sorted_runner = 1;

	assert(NULL != arr);
	
	for (sorted_runner = 1; sorted_runner < size; ++sorted_runner)
	{
		size_t swap_index = sorted_runner - 1;
		int cur_value = arr[sorted_runner];
		
		for (swap_index = sorted_runner - 1;
			((int)swap_index >= 0) && (arr[swap_index] > cur_value);
			--swap_index)
		{
			arr[swap_index + 1] = arr[swap_index];
		}
		
		arr[swap_index + 1] = cur_value;
	}	
}

/* Sorts @arr using selection sort */
void Selection(int *arr, size_t size)
{
	size_t swap_index = 0;
	size_t unsorted_runner = 0;
	
	assert(NULL != arr);
	
	for (swap_index = 0; swap_index < size - 1; ++swap_index)
	{
		size_t min_index = swap_index;
		
		for (unsorted_runner = swap_index + 1;
	    	 unsorted_runner < size;	
		 	 ++unsorted_runner
		 	)
		{
			if (IsIntBefore(arr[min_index], arr[unsorted_runner]))
			{
				/* new minimum is found */
				min_index = unsorted_runner;
			}
		}
		/* swap minimum value to first sorted */
		IntSwap(&arr[swap_index],&arr[min_index]);		
	}
}

/* Sorts @arr using bubble sort */
void Bubble(int *arr, size_t size)
{
	int swapped = TRUE; /* optimization: if swapped
						   isn't performed array is sorted */
	
	size_t index = 1;	
	size_t cur_size = size;

	assert(NULL != arr);
	
	while (swapped)
	{
		swapped = FALSE;
		
		for (index = 1; index < cur_size; ++index)
		{
			if (IsIntBefore(arr[index-1], arr[index]))
			{
				IntSwap(&arr[index], &arr[index - 1]);
				swapped = TRUE;
			}
		}
		
		--cur_size; /* since last element is always the greatest in
					   each iteration  */
	}
}
/* helper for counting */
static void PrintArray(int* arr, size_t size, const char* arr_name)
{
	size_t index = 0;
	printf("%s = {", arr_name);
	for (index = 0; index < size; ++index)
	{
		printf("%d ", arr[index]);
	}
	printf("}\n");	
}

/* run counting sort */
int Counting(int *arr, size_t size, int min, int max)
{
	size_t arr_index = 0;
	size_t arr_size = size;
	size_t hist_index = 0;
	size_t hist_size = (size_t)(max - min + 1); /*TODO check +1 */
	int *new_array = NULL;
	
	int *hist = (int *)calloc(hist_size, sizeof(int));
	if (NULL == hist)
	{
		perror("hist calloc failed.\n");
		return FAIL;
	}
	
	new_array = (int *) malloc (arr_size * sizeof(int));
	if (NULL == new_array)
	{
		free(hist); hist = NULL;
		perror("malloc new_array failed.\n");
		return FAIL;
	}
	
	/*TODO function fill hist*/
	PrintArray(arr, arr_size, "original array");	
	PrintArray(hist, hist_size, "unfilled hist");
	for (arr_index = 0; arr_index < arr_size; ++arr_index)
	{
		++hist[arr[arr_index] - min]; /* shift/align/adjust to 0 index using min */
	}
	PrintArray(hist, hist_size, "filled hist");
	/* summate */
	for (hist_index = 1; hist_index < hist_size; ++hist_index)
	{
		hist[hist_index] += hist[hist_index - 1];
	}
	PrintArray(hist, hist_size, "summated hist");	
	
	/* fill new arr */
	for (arr_index = arr_size; arr_index > 0; --arr_index)
	{
		new_array[hist[arr[arr_index - 1] - min ]- 1] = arr[arr_index - 1];
		--hist[arr[arr_index - 1] - min];
	}
	PrintArray(new_array, arr_size, "new_array");
	/* copy new array to given array */
	for (arr_index = 0; arr_index < arr_size; ++arr_index)
	{
		arr[arr_index] = new_array[arr_index];
	}
	
	free(hist);
	hist = NULL;
	
	free(new_array);
	new_array = NULL;
	
	return SUCCESS;
}
