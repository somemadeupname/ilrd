#include <stdio.h>
#include <assert.h> /* assert */

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
	expect(&a,1,"hi");\
}
static void expect(void *data, int expected_result, char *func_name)
{	
	
	int *int_data = NULL;
	assert(NULL != data);
	
	int_data = (int *) data;
	if (*int_data != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%d\nActual: \t%d\n", expected_result, *int_data);
	}
}

static void expect_int(int result, int expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%d\nActual: \t%d\n", expected_result, result);
	}	
}

static void expect_size_t(size_t result, size_t expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%lu\nActual: \t%lu\n", expected_result, result);
	}	
}
/*
static void PrintList(const dlist_t *dlist)
{
	size_t iter_index = 0;
	dlist_iter_t cur_iter = DListBegin(dlist);
	while (DListEnd(dlist) != cur_iter)
	{
		printf("[n%lu. data: %d]--", iter_index, *(int *)cur_iter->data);
		cur_iter = cur_iter->next;
		++iter_index;
	}
	printf("\n");
}

int *GenerateIntLinkedList(dlist_t *list, dlist_iter_t *iter, int size,
																int *data_array)
{
	int index = size - 1;
	data_array = (int *)malloc(sizeof(int)*size);
	while (index >= 0)
	{
		data_array[index] = index;
		DListInsert(list, DListBegin(list),&data_array[index]);
		--index;
	}
	return data_array;
}
*/
