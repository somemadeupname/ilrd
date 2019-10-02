#include <stdio.h> /* prtinf */
#include <assert.h> /* assert */
#include <stdlib.h> /* qsort */

#include "sorting.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");
#define TRUE 1
#define FALSE 0

#define PRINT_ERROR START_RED printf("ERROR in %s.\n", func_name); END_RED

#define PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE \
{\
	int a = 1;\
	expect_int(1,1,"hi");\
	expect_size_t(1lu,1lu,"hi");\
	expect_NULL(NULL,"hi");\
	expect_Not_NULL(&a,"hi");\
}

#define PRINT_ERROR START_RED printf("ERROR in %s.\n", func_name); END_RED


void expect_int(int result, int expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%d\nActual: \t%d\n", expected_result, result);
	}	
}

void expect_size_t(size_t result, size_t expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%lu\nActual: \t%lu\n", expected_result, result);
	}	
}

void expect_NULL(void *pointer, char *func_name)
{
	if (pointer != NULL)
	{
		PRINT_ERROR
		printf("pointer isn't NULL.\n");
	}	
}

void expect_Not_NULL(void *pointer, char *func_name)
{
	if (pointer == NULL)
	{
		PRINT_ERROR
		printf("pointer isn't NULL.\n");
	}	
}

/* print array testing purposes TODO remove */
void PrintArr(int arr[], size_t arr_size)
{
	size_t index = 0;
	printf("arr = {");
	for (index = 0; index < arr_size; ++index)
	{
		printf("%d ", arr[index]);
	}
	printf("}\n");	
}

/* TODO remove */
/*static void PrintHist(size_t *hist, size_t size, char *hist_name)-
{
	size_t index = 0;
	printf("%s = {", hist_name);
	for (index = 0; index < size; ++index)
	{
		printf("%d ", hist[index]);
	}
	printf("}\n");	
}*/

/* helper for counting */
/*static void PrintArray(int* arr, size_t size, const char* arr_name)
{
	size_t index = 0;
	printf("%s = {", arr_name);
	for (index = 0; index < size; ++index)
	{
		printf("%d ", arr[index]);
	}
	printf("}\n");	
}*/

static int MergeIsBefore(int a, int b)
{
	return a - b;
}

/* Forward Declarations */
static int AreArraysEqual(const int arr1[], const int arr2[], size_t size);
void CompareTwoArrays(const int arr1[], const int arr2[], size_t size, const char *func_name);
static int Qsort_Cmp_Wrapper(const void *i1,const void *i2);


void Insertion_test();
void Selection_test();
void Bubble_test();
void Counting_test();
void Radix_test();
void Merge_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
/*	Insertion_test();*/

/*	Selection_test();*/
/*	*/
/*	Bubble_test();*/
/*	*/
/*	Counting_test();*/
	
	Radix_test();
	
	Merge_test();
	
	return 0;
}

void Merge_test()
{
	int my_array_big_unsorted[] = {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};
	int qsort_big_unsorted[] =	  {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};	
	size_t my_array_big_unsorted_size = 19;
	
	int my_array_small_unsorted[] = {5,4,7,1};
	int qsort_small_unsorted[] = 	{5,4,7,1};
	size_t my_array_small_unsorted_size = 4;
	
	
	int my_array_sorted[] =    {1,5,8,10,13,98,1001,202020202};
	int qsort_array_sorted[] = {1,5,8,10,13,98,1001,202020202};	
	size_t my_array_sorted_size = 8;
	
	int my_array_with_negatives[] = {3,1,7,9,3,2,0};
	int qsort_array_with_negatives[] = {3,1,7,9,3,2,0};	
	size_t my_array_with_negatives_size = 7;
	
	/*TODO Remove*/
/*	PrintArr(my_array_big_unsorted, my_array_big_unsorted_size);*/
	/*TODO Remove*/	

	Merge(my_array_big_unsorted, my_array_big_unsorted_size, MergeIsBefore);
	qsort(qsort_big_unsorted, my_array_big_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	/*TODO Remove*/
/*	PrintArr(my_array_big_unsorted, my_array_big_unsorted_size);*/
	/*TODO Remove*/	
	
	Merge(my_array_with_negatives,my_array_with_negatives_size,MergeIsBefore);
	qsort(qsort_array_with_negatives, my_array_with_negatives_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Merge(my_array_small_unsorted,my_array_small_unsorted_size,MergeIsBefore);
	qsort(qsort_small_unsorted, my_array_small_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Merge(my_array_sorted,my_array_sorted_size,MergeIsBefore);
	qsort(qsort_array_sorted, my_array_sorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	CompareTwoArrays(my_array_with_negatives, qsort_array_with_negatives, my_array_with_negatives_size, "Merge with negatives");
	CompareTwoArrays(my_array_small_unsorted, qsort_small_unsorted, my_array_small_unsorted_size, "Merge small unsorted");
		
	CompareTwoArrays(my_array_sorted, qsort_array_sorted, my_array_sorted_size, "Merge sorted");
	
	CompareTwoArrays(my_array_big_unsorted, qsort_big_unsorted, my_array_big_unsorted_size, "Merge big unsorted");	
}

void Radix_test()
{	
	int my_array_big_unsorted[] = {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};
	int qsort_big_unsorted[] =	  {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};	
	size_t my_array_big_unsorted_size = 19;
	
	int my_array_small_unsorted[] = {5,4,7,1};
	int qsort_small_unsorted[] = 	{5,4,7,1};
	size_t my_array_small_unsorted_size = 4;
	
	
	int my_array_sorted[] =    {1,5,8,10,13,98,1001,202020202};
	int qsort_array_sorted[] = {1,5,8,10,13,98,1001,202020202};	
	size_t my_array_sorted_size = 8;
	
	int my_array_with_negatives[] = {3,1,7,9,3,2,0};
	int qsort_array_with_negatives[] = {3,1,7,9,3,2,0};	
	size_t my_array_with_negatives_size = 7;
	
	Radix(my_array_big_unsorted, my_array_big_unsorted_size, 16);
	qsort(qsort_big_unsorted, my_array_big_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Radix(my_array_with_negatives,my_array_with_negatives_size,16);
	qsort(qsort_array_with_negatives, my_array_with_negatives_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Radix(my_array_small_unsorted,my_array_small_unsorted_size,16);
	qsort(qsort_small_unsorted, my_array_small_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Radix(my_array_sorted,my_array_sorted_size,16);
	qsort(qsort_array_sorted, my_array_sorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	CompareTwoArrays(my_array_with_negatives, qsort_array_with_negatives, my_array_with_negatives_size, "Radix with negatives");
	CompareTwoArrays(my_array_small_unsorted, qsort_small_unsorted, my_array_small_unsorted_size, "Radix small unsorted");
		
	CompareTwoArrays(my_array_sorted, qsort_array_sorted, my_array_sorted_size, "Radix sorted");
	
	CompareTwoArrays(my_array_big_unsorted, qsort_big_unsorted, my_array_big_unsorted_size, "Radix big unsorted");		
	
}

void Counting_test()
{
	
	int my_array_big_unsorted[] = {1,4,3,4,5,6,7,867,567,456,345,245,35,-400,-5,-19,65,67,5678,56789,456,7345};
	int qsort_big_unsorted[] =	  {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345, -400,-5,-19};	
	size_t my_array_big_unsorted_size = 22;
	
	int my_array_small_unsorted[] = {5,4,7,1};
	int qsort_small_unsorted[] = 	{5,4,7,1};
	size_t my_array_small_unsorted_size = 4;
	
	
	int my_array_sorted[] =    {1,5,8,10,13,98,1001,202020202};
	int qsort_array_sorted[] = {1,5,8,10,13,98,1001,202020202};	
	size_t my_array_sorted_size = 8;
	
	int my_array_with_negatives[] = {3,1,7,9,3,-2,0};
	int qsort_array_with_negatives[] = {3,1,7,9,3,-2,0};	
	size_t my_array_with_negatives_size = 7;
	
	Counting(my_array_with_negatives,my_array_with_negatives_size,-2,9);
	qsort(qsort_array_with_negatives, my_array_with_negatives_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Counting(my_array_small_unsorted,my_array_small_unsorted_size,1,7);
	qsort(qsort_small_unsorted, my_array_small_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Counting(my_array_big_unsorted,my_array_big_unsorted_size,-400,56789);
	qsort(qsort_big_unsorted, my_array_big_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	Counting(my_array_sorted,my_array_sorted_size,1,202020202);
	qsort(qsort_array_sorted, my_array_sorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	
	CompareTwoArrays(my_array_with_negatives, qsort_array_with_negatives, my_array_with_negatives_size, "Counting sort 1");
	CompareTwoArrays(my_array_small_unsorted, qsort_small_unsorted, my_array_small_unsorted_size, "Counting sort 2");
	CompareTwoArrays(my_array_big_unsorted, qsort_big_unsorted, my_array_big_unsorted_size, "Counting sort 3");		
	CompareTwoArrays(my_array_sorted, qsort_array_sorted, my_array_sorted_size, "Counting sort 4");
	
}

/* IsBefore wrapper to be compatible with qsort() for tests */
static int Qsort_Cmp_Wrapper(const void *i1,const void *i2)
{
	return (*(int *)i2 < *(int *)i1);
}

static int AreArraysEqual(const int arr1[], const int arr2[], size_t size)
{
	size_t index = 0;
	
	assert(NULL != arr1);
	assert(NULL != arr2);	
	
	for (index = 0; index < size; ++index)
	{
		if (arr1[index] != arr2[index])
		{
			return FALSE;
		}
	}
	return TRUE;
}

void Insertion_test()
{
	int my_array_big_unsorted[] = {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};
	int qsort_big_unsorted[] =	  {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};	
	size_t my_array_big_unsorted_size = 19;
	
	int my_array_small_unsorted[] = {5,4,7,1};
	int qsort_small_unsorted[] = 	{5,4,7,1};
	size_t my_array_small_unsorted_size = 4;
	
	
	int my_array_sorted[] =    {1,5,8,10,13,98,1001,202020202};
	int qsort_array_sorted[] = {1,5,8,10,13,98,1001,202020202};	
	size_t my_array_sorted_size = 8;
	
	Insertion(my_array_big_unsorted, my_array_big_unsorted_size);
	Insertion(my_array_small_unsorted, my_array_small_unsorted_size);
	Insertion(my_array_sorted, my_array_sorted_size);
	
	qsort(qsort_big_unsorted, my_array_big_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	qsort(qsort_small_unsorted, my_array_small_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);	
	qsort(qsort_array_sorted, my_array_sorted_size, sizeof(int), Qsort_Cmp_Wrapper);	
	
	CompareTwoArrays(my_array_big_unsorted, qsort_big_unsorted, my_array_big_unsorted_size, "Insertion_big");
	CompareTwoArrays(my_array_small_unsorted, qsort_small_unsorted, my_array_small_unsorted_size, "Insertion_small");
	CompareTwoArrays(my_array_sorted, qsort_array_sorted, my_array_sorted_size, "Insertion_sorted");
}

void Selection_test()
{
	int my_array_big_unsorted[] = {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};
	int qsort_big_unsorted[] =	  {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};	
	size_t my_array_big_unsorted_size = 19;
	
	int my_array_small_unsorted[] = {5,4,7,1};
	int qsort_small_unsorted[] = 	{5,4,7,1};
	size_t my_array_small_unsorted_size = 4;
	
	
	int my_array_sorted[] =    {1,5,8,10,13,98,1001,202020202};
	int qsort_array_sorted[] = {1,5,8,10,13,98,1001,202020202};	
	size_t my_array_sorted_size = 8;
	
	Selection(my_array_big_unsorted, my_array_big_unsorted_size);
	Selection(my_array_small_unsorted, my_array_small_unsorted_size);
	Selection(my_array_sorted, my_array_sorted_size);
	
	qsort(qsort_big_unsorted, my_array_big_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	qsort(qsort_small_unsorted, my_array_small_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);	
	qsort(qsort_array_sorted, my_array_sorted_size, sizeof(int), Qsort_Cmp_Wrapper);	
	
	CompareTwoArrays(my_array_big_unsorted, qsort_big_unsorted, my_array_big_unsorted_size, "Selection_big");
	CompareTwoArrays(my_array_small_unsorted, qsort_small_unsorted, my_array_small_unsorted_size, "Selection_small");
	CompareTwoArrays(my_array_sorted, qsort_array_sorted, my_array_sorted_size, "Selection_sorted");
}

void Bubble_test()
{
	int my_array_big_unsorted[] = {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};
	int qsort_big_unsorted[] =	  {1,4,3,4,5,6,7,867,567,456,345,245,35,65,67,5678,56789,456,7345};	
	size_t my_array_big_unsorted_size = 19;
	
	int my_array_small_unsorted[] = {5,4,7,1};
	int qsort_small_unsorted[] = 	{5,4,7,1};
	size_t my_array_small_unsorted_size = 4;
	
	
	int my_array_sorted[] =    {1,5,8,10,13,98,1001,202020202};
	int qsort_array_sorted[] = {1,5,8,10,13,98,1001,202020202};	
	size_t my_array_sorted_size = 8;
	
	Bubble(my_array_big_unsorted, my_array_big_unsorted_size);
	Bubble(my_array_small_unsorted, my_array_small_unsorted_size);
	Bubble(my_array_sorted, my_array_sorted_size);
	
	qsort(qsort_big_unsorted, my_array_big_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);
	qsort(qsort_small_unsorted, my_array_small_unsorted_size, sizeof(int), Qsort_Cmp_Wrapper);	
	qsort(qsort_array_sorted, my_array_sorted_size, sizeof(int), Qsort_Cmp_Wrapper);	
	
	CompareTwoArrays(my_array_big_unsorted, qsort_big_unsorted, my_array_big_unsorted_size, "Bubble_big");
	CompareTwoArrays(my_array_small_unsorted, qsort_small_unsorted, my_array_small_unsorted_size, "Bubble_small");
	CompareTwoArrays(my_array_sorted, qsort_array_sorted, my_array_sorted_size, "Bubble_sorted");
	
}

void CompareTwoArrays(const int arr1[], const int arr2[], size_t size, const char *func_name)
{
	if (!AreArraysEqual(arr1, arr2, size))
	{
		START_RED
		printf("%s:\n", func_name);
		END_RED
		printf("Arrays aren't identical.\n");
	}
}
