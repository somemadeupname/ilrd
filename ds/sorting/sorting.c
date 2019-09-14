
/****************************
 *   Author   : Ran Shieber *
 *   Reviewers: 1. Nitzan	*
 *				2. Daya		*
 *	 Status   : Sent	    *
 ****************************/
#include <stdio.h> /* perror */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc calloc free */
#include <string.h> /* memset for Radix */
#include <limits.h> /* INT_MAX */

#include "sorting.h"

enum state {FALSE, TRUE};
enum {SUCCESS, FAIL};

const size_t BYTE_SIZE = 8;

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
static int IsIntBefore(int int1, int int2)
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

static void	FillHistogram(int *arr,
						  size_t arr_size,
						  size_t *hist,
						  int offset_to_first_index)
{		
	size_t arr_index = 0;
	
	assert(NULL != arr);
	assert(NULL != hist);
	
	for (arr_index = 0; arr_index < arr_size; ++arr_index)
	{
		++hist[arr[arr_index] - offset_to_first_index];
	}
}
/* helper for counting - summate histogram */
static void SummateHistogram(size_t *hist, size_t hist_size)
{
	size_t hist_index = 1;
	
	assert(NULL != hist);
	
	for (hist_index = 1; hist_index < hist_size; ++hist_index)
	{
		hist[hist_index] += hist[hist_index - 1];
	}
}

/*helper for counting - fill new arr */
static void FillNewArr(int *new_arr,
					   int *arr,
					   size_t arr_size,
					   size_t *hist,
					   int offset_to_first_index)
{
	size_t arr_index = arr_size;
	
	assert(NULL != arr);
	assert(NULL != hist);
	assert(NULL != new_arr);	
	
	for (arr_index = arr_size; arr_index > 0; --arr_index)
	{
		new_arr[hist[arr[arr_index - 1] - offset_to_first_index ]- 1] =
															 arr[arr_index - 1];
		--hist[arr[arr_index - 1] - offset_to_first_index];
	}
}

/* helper for counting - copy sorted array to original */
static void CopyNewIntArrayToOriginal(int *dest_arr, int *src_arr, size_t size)
{
	size_t arr_index = 0;
	
	assert(NULL != dest_arr);
	assert(NULL != src_arr);	
		
	for (arr_index = 0; arr_index < size; ++arr_index)
	{
		dest_arr[arr_index] = src_arr[arr_index];
	}
}

/* run counting sort */
int Counting(int *arr, size_t size, int min, int max)
{
	size_t arr_size = size;
	size_t hist_size = (size_t)(max - min + 1);
	int *new_array = NULL;
	size_t *hist = NULL;
	
	assert(NULL != arr);
	assert(max >= min);

	hist = (size_t *)calloc(hist_size, sizeof(size_t));
	if (NULL == hist)
	{
		perror("hist calloc failed.\n");
		return FAIL;
	}
	
	new_array = (int *) malloc (arr_size * sizeof(int));
	if (NULL == new_array)
	{
		free(hist);
		hist = NULL;
		perror("malloc new_array failed.\n");
		return FAIL;
	}
	
	FillHistogram(arr, arr_size, hist, min);
	
	SummateHistogram(hist, hist_size);
	
	FillNewArr(new_array, arr, arr_size, hist, min);

	CopyNewIntArrayToOriginal(arr, new_array, arr_size);
	
	free(hist);
	hist = NULL;
	
	free(new_array);
	new_array = NULL;
	
	return SUCCESS;
}

/* helper for new counting - fils histogram */
static void	RadixFillHistogram(int *arr,
						  size_t arr_size,
						  size_t *hist,
						  int mask,
						  size_t shift_by)
{		
	size_t arr_index = 0;
	
	assert(NULL != arr);
	assert(NULL != hist);
	
	for (arr_index = 0; arr_index < arr_size; ++arr_index)
	{
		++hist[(arr[arr_index] & mask) >> shift_by];
	}
}

/*helper for new counting - fill new arr */
static void RadixFillNewArr(int *new_arr,
					   int *arr,
					   size_t arr_size,
					   size_t *hist,
					   int mask,
					   size_t shift_by)
{
	size_t arr_index = arr_size;
	
	assert(NULL != arr);
	assert(NULL != hist);
	assert(NULL != new_arr);	
	
	for (arr_index = arr_size; arr_index > 0; --arr_index)
	{
		new_arr[hist[((arr[arr_index - 1] & mask) >> shift_by)]- 1] =
															 arr[arr_index - 1];
		--hist[((arr[arr_index - 1] & mask) >> shift_by)];
	}
}

/* new counting which takes mask. takes @mask and @shift_by to
													  align to histogram size */
static void NewCounting(int *arr,
						size_t arr_size,
						size_t *hist,
						size_t hist_size,
						int *new_array,
						int mask,
						size_t shift_by)
{
	
	assert(NULL != arr);
	assert(NULL != hist);
	
	RadixFillHistogram(arr, arr_size, hist, mask, shift_by);
	
	SummateHistogram(hist, hist_size);
	
	RadixFillNewArr(new_array, arr, arr_size, hist, mask, shift_by);

}

/* helper for Radix - generates a mask based on num_of_bits */
static int GenerateMask(unsigned int num_of_bits)
{
	int mask = INT_MAX;
	mask <<= num_of_bits;

	return ~mask;
}

/* helper for Radix - clears the histogram */
static void	ClearHistogram(size_t *hist, size_t hist_size)
{
	memset(hist, 0, hist_size * sizeof(size_t));
}

/* helper for Radix */
static void SwapPointers(int **arr1, int **arr2)
{
	int *temp = NULL;

	assert(NULL != *arr1);
	assert(NULL != *arr2);
	
	temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}

static void *FreeObj(void *obj)
{
	free(obj);
	return NULL;
}

/* radix sort an array using mask defined by @num_of_bits */
int Radix(int *arr, size_t size, unsigned int num_of_bits)
{
	size_t *hist = NULL;
	int* new_array = NULL;
	int mask = GenerateMask(num_of_bits);
	size_t iteration = 0;
	size_t hist_size = (1 << num_of_bits);
	
	assert(NULL != arr);
	assert(0 < num_of_bits && 32 > num_of_bits);/* system-dependant */
	assert(0 == 32%num_of_bits);
	
	hist = (size_t *)calloc(hist_size, sizeof(size_t));
	if (NULL == hist)
	{
		perror("Something went wrong.\n");
		return FAIL;
	}
	
	new_array = (int *)malloc(size * sizeof(int));
	if (NULL == new_array)
	{
		perror("Something went wrong.\n");
		hist = FreeObj(hist);
		return FAIL;
	}

	for (iteration = 0;
		 mask != 0;
		 ++iteration, mask <<= num_of_bits
		)
	{
		NewCounting(arr, size, hist, hist_size, new_array, mask,
													   iteration * num_of_bits);
		SwapPointers(&arr, &new_array);
		
		ClearHistogram(hist, hist_size);
	}
	
	new_array = FreeObj(new_array);
	hist = FreeObj(hist);
	
	return SUCCESS;
}
