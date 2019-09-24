#include <stdio.h>
#include <assert.h>
#include <stdlib.h> /* TODO:remove free */

#include "avl.h"

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
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/
static int IntCompare(const void *tree_data, const void *new_data, void *param);

void AVLCreateAndDestroyEmptyAVL_test();
void AVLInsert_test();
void AVLRemoveNaive_test();
void AVLFind_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	AVLCreateAndDestroyEmptyAVL_test();
	
	AVLInsert_test();
	
	AVLRemoveNaive_test();
	
	AVLFind_test();
	
	return 0;
}

/*************************************************************************
								 										 *
				      HELPER FUNCTIONS									 *
																		 *
*************************************************************************/

static int IntCompare(const void *tree_data, const void *new_data, void *param)
{
	assert(NULL != tree_data);
	assert(NULL != new_data);	
	
	UNUSED(param);
	
	return *(int *)tree_data - *(int *)new_data;
}

/*************************************************************************
								 										 *
				      TEST FUNCTIONS									 *
																		 *
*************************************************************************/

void AVLFind_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 10
	int data[DATA_SIZE] = {1,14,32,54,11,12,78,87,90,200};
	int data_not_in_tree = 77;
	size_t i = 0;
	int *found_data = NULL;
	int *data_to_find = &data[8];
	
	found_data = (int *)AVLFind(tree, &data_not_in_tree);	
	
	expect_NULL(found_data, "AVLFind_test_empty_tree");
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
	}
	
	found_data = (int *)AVLFind(tree, data_to_find);
	
	expect_int(*found_data, 90, "AVLFind_test");
	
	found_data = (int *)AVLFind(tree, &data_not_in_tree);	
	
	expect_NULL(found_data, "AVLFind_test2");
	
	AVLDestroy(tree);
	#undef DATA_SIZE
}

void AVLRemoveNaive_test()
{
/*	avl_t *tree = AVLCreate(NULL, IntCompare);*/
/*	*/
/*	int int_data1 = 5, int_data2 = 6;*/
/*	AVLInsert(tree, &int_data1]);*/
/*	AVLInsert(tree, &int_data2]);*/
/*	AVLRemove(tree, &int_data2);*/
}

void AVLInsert_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 10
	int data[DATA_SIZE] = {1,14,32,54,11,12,78,87,90,200};
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
	}
	
	AVLDestroy(tree);
	#undef DATA_SIZE
}

void AVLCreateAndDestroyEmptyAVL_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	AVLDestroy(tree);
}
