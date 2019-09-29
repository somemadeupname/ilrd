#include <stdio.h>
#include <assert.h>

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
void AVLInsert2_test();
void AVLFind_test();
void AVLForEachSuccess_test();
void AVLForEachFail_test();
void AVLCount_test();
void AVLRemoveRightLeaf_test();
void AVLRemoveLeftLeaf_test();
void AVLRemoveParentOneChild_test();
void AVLRemoveParentTwoChild_test();
void AVLRemoveRootBigTree_test();
void AVLHeightSanity_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	AVLCreateAndDestroyEmptyAVL_test();
	
	AVLInsert_test();	
	
	AVLInsert2_test();
	
	AVLFind_test();
	
	AVLForEachSuccess_test();
	
/*	AVLForEachFail_test();*/
	
	AVLCount_test();	
	
	AVLRemoveRightLeaf_test();
	
	AVLRemoveLeftLeaf_test();
	
	AVLRemoveParentOneChild_test();
	
	AVLRemoveParentTwoChild_test();	
	
	AVLRemoveRootBigTree_test();
	
	AVLHeightSanity_test();

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

static int IncreaseIntDataBy(void *node_data, void *param)
{
	
	assert(NULL != node_data);
	UNUSED(param);	
	
	++*(int*)node_data;

	return 0;
}

static int FailOnEvenData(void *node_data, void *param)
{
	int int_data = 0;
	
	assert(NULL != node_data);
	UNUSED(param);
	
	int_data = *(int *)node_data;
	
	++*(int*)node_data;	
	
	if (int_data % 2 == 0)
	{
		return 1;
	}
	
	return 0;
}

/*************************************************************************
 *								 										 *
 *					      TEST FUNCTIONS								 *
 *																		 *
 *************************************************************************/
void AVLHeightSanity_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	int int_data = 5;
	
	expect_size_t(AVLHeight(tree), 0 ,"AVLHeight_test1");
		
	AVLInsert(tree, &int_data);
	
	expect_size_t(AVLHeight(tree), 1 ,"AVLHeight_test2");
	
	AVLDestroy(tree);
}

void AVLRemoveRootBigTree_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 6
	int data[DATA_SIZE] = {30,50,20,10,25,70};
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
		expect_size_t(AVLCount(tree), (int)(i+1), "AVLRemoveRootBigTree_test1");
	}
	
	expect_size_t(AVLCount(tree), 6, "AVLRemoveRootBigTree_test2");	

	AVLRemove(tree, &data[0]); /*[0] = 30 */
	expect_size_t(AVLCount(tree), 5, "AVLRemoveRootBigTree_test3");	
	
/*	printf("new root data: %d\n", Int(AVLGetRoot(tree)));*/
	
	AVLRemove(tree, &data[1]); 
	expect_size_t(AVLCount(tree), 4, "AVLRemoveRootBigTree_test4");		
	
	AVLRemove(tree, &data[2]); 
	expect_size_t(AVLCount(tree), 3, "AVLRemoveRootBigTree_test");	

	AVLRemove(tree, &data[4]); 
	expect_size_t(AVLCount(tree), 2, "AVLRemoveRootBigTree_test5");		
	
	
	AVLDestroy(tree);

	#undef DATA_SIZE	
}
void AVLRemoveParentTwoChild_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 6
	int data[DATA_SIZE] = {30,50,20,10,25,70};
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
		expect_size_t(AVLCount(tree), (int)(i+1), "AVLCount_test");
	}
	
	expect_size_t(AVLCount(tree), 6, "AVLRemoveParentTwoChild_test1");	
	
	InOrderPrintNodes(AVLGetRoot(tree));
	
	printf("\n");
	
	AVLRemove(tree, &data[2]); /*[2] = 20 */
	
/*	InOrderPrintNodes(AVLGetRoot(tree));		*/

/*	printf("\n");	*/
	
	expect_size_t(AVLCount(tree), 5, "AVLRemoveParentTwoChild_test2");	
	
	AVLDestroy(tree);

	#undef DATA_SIZE
}

void AVLRemoveParentOneChild_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 6
	int data[DATA_SIZE] = {30,50,20,10,25,70};
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
		expect_size_t(AVLCount(tree), (int)(i+1), "AVLCount_test");
	}
	
	expect_size_t(AVLCount(tree), 6, "AVLRemoveParentOneChild_test1");		
	
	AVLRemove(tree, &data[1]); /*[1] = 50 */
	
	expect_size_t(AVLCount(tree), 5, "AVLRemoveParentOneChild_test2");		
	
	AVLDestroy(tree);

	#undef DATA_SIZE
}

void AVLRemoveLeftLeaf_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	
	int int_data1 = 6, int_data2 = 5;
	
	expect_size_t(AVLCount(tree), 0, "AVLRemoveRightLeaf_test1");	
	
	AVLInsert(tree, &int_data1);
	
	expect_size_t(AVLCount(tree), 1, "AVLRemoveRightLeaf_test2");		
	AVLInsert(tree, &int_data2);
	
	expect_size_t(AVLCount(tree), 2, "AVLRemoveRightLeaf_test3");			

	AVLRemove(tree, &int_data2);
	
	expect_size_t(AVLCount(tree), 1, "AVLRemoveRightLeaf_test4");	
	
	AVLDestroy(tree);	

}

void AVLRemoveRightLeaf_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	
	int int_data1 = 5, int_data2 = 6;
	
	expect_size_t(AVLCount(tree), 0, "AVLRemoveRightLeaf_test1");	
	
	AVLInsert(tree, &int_data1);
	
	expect_size_t(AVLCount(tree), 1, "AVLRemoveRightLeaf_test2");		
	AVLInsert(tree, &int_data2);
	
	expect_size_t(AVLCount(tree), 2, "AVLRemoveRightLeaf_test3");			

	AVLRemove(tree, &int_data2);
	
	expect_size_t(AVLCount(tree), 1, "AVLRemoveRightLeaf_test4");	
	
	AVLDestroy(tree);	
}

void AVLCount_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 6
	int data[DATA_SIZE] = {30,50,20,10,25,70};
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
		expect_size_t(AVLCount(tree), (int)(i+1), "AVLCount_test");
	}
	
	AVLDestroy(tree);

	#undef DATA_SIZE
}

void AVLForEachFail_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 6
	int data[DATA_SIZE] = {30,50,20,10,25,70};
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
		InOrderPrintNodes(AVLGetRoot(tree));			
		printf("\n");
	}
	
/*	InOrderPrintNodes(AVLGetRoot(tree));	*/
	
		
	expect_int(AVLForEach(NULL, tree, FailOnEvenData), 1, "AVLForEachFail_test");
	
/*	InOrderPrintNodes(AVLGetRoot(tree));		*/
	
	AVLDestroy(tree);
	#undef DATA_SIZE
}
void AVLForEachSuccess_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 6
	int data[DATA_SIZE] = {30,50,20,10,25,70};
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
	}
	
/*	InOrderPrintNodes(AVLGetRoot(tree));	*/
/*	*/
/*	printf("\n");*/
	
	expect_int(AVLForEach(NULL, tree, IncreaseIntDataBy), 0, "AVLForEachSuccess_test");
	
/*	InOrderPrintNodes(AVLGetRoot(tree));*/
	
	AVLDestroy(tree);
	#undef DATA_SIZE
}

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

void AVLInsert2_test()
{
	avl_t *tree = AVLCreate(NULL, IntCompare);
	#define DATA_SIZE 15
	int data[DATA_SIZE] = {38,68,29,88,60,35,15,77,66,45,36,33,24,2,34};
	
	size_t i = 0;
	
	for (i = 0; i < DATA_SIZE; ++i)
	{
		AVLInsert(tree, &data[i]);
	}
	
	AVLRemove(tree, &data[0]);
	
	printf("new root data: %d\n", Int(AVLGetRoot(tree)));
	
	AVLDestroy(tree);
	#undef DATA_SIZE
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
