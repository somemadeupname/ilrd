#include <stdio.h>
#include <assert.h>

#include "heap.h"

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
	expect_Not_NULL(&a, "hi");\
}

#define UNUSED(x) (void)(x)

/*************************************************************************
								 										 *
				      GENERAL TEST FUNCTIONS							 *
																		 *
*************************************************************************/
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

/*************************************************************************
								 										 *
				      HELPER FUNCTIONS									 *
																		 *
*************************************************************************/

int IntSizePriority(const void *data1, const void *data2, void *param)
{
	assert(NULL != data1);
	assert(NULL != data2);	
	
	UNUSED(param);
	
	return *(int *)data1 - *(int *)data2;
}

/*************************************************************************
								 										 *
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/

void CreateAndDestroy_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	CreateAndDestroy_test();	
	
	return 0;
}

void CreateAndDestroy_test()
{
	heap_t *heap = HeapCreate(IntSizePriority, NULL);
	
	expect_size_t(HeapSize(heap), 0, "CreateAndDestroy_test1");
	
	expect_int(HeapIsEmpty(heap), 1, "CreateAndDestroy_test2");	
	
	HeapDestroy(heap);
}
