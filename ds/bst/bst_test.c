#include <stdio.h>
#include <assert.h>

#include "bst.h"

#define UNUSED(x) (void)(x)
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
int Int_Node_Compare(void *iter_data, void *new_data, void *param);

void BSTCreate_test();

void BSTInsertMiddleSmallerBigger_test();
void BSTInsertSmallSmallSmall_test();
void BSTInsertBigBigBig_test();

void BSTFind_element_is_in_tree_test();
void BSTFind_element_is_NOT_in_tree_test();



int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	BSTCreate_test();
	
	BSTInsertMiddleSmallerBigger_test();		

	BSTInsertSmallSmallSmall_test();	
	
	BSTInsertBigBigBig_test();
	
	BSTFind_element_is_in_tree_test();
	
	BSTFind_element_is_NOT_in_tree_test();
	
	return 0;
}

void BSTFind_element_is_in_tree_test()
{
	bst_t *bst = BSTCreate(Int_Node_Compare, NULL);	
	
	int a = 15;
	int b = 97;
	int c = 301;
	int unadded = 60;
	
	BSTInsert(bst, &a);
	
	BSTInsert(bst, &b);
	
	BSTInsert(bst, &c);

	expect_NULL(BSTFind(bst,&unadded), "BSTFind_element_is_in_tree_test1");
}

void BSTFind_element_is_NOT_in_tree_test()
{
bst_t *bst = BSTCreate(Int_Node_Compare, NULL);
	
	int a = 15;
	int b = 97;
	int c = 301;
	int g = 13;
	
	expect_size_t(BSTSize(bst), 0, "BSTFind_element_is_NOT_in_tree_test");
	
	BSTInsert(bst, &a);
	
	BSTInsert(bst, &b);
	
	BSTInsert(bst, &c);

	expect_Not_NULL(BSTFind(bst,&b), "BSTFind_element_is_NOT_in_tree_test1");

	expect_Not_NULL(BSTFind(bst,&a), "BSTFind_element_is_NOT_in_tree_test2");
	
	expect_Not_NULL(BSTFind(bst,&c), "BSTFind_element_is_NOT_in_tree_test3");
	
	g = *(int *)BSTGetData(BSTFind(bst,&b));
	
	expect_int(g, b, "BSTFind_element_is_NOT_in_tree_test4");
	
	
}

void BSTInsertBigBigBig_test()
{
	bst_t *bst = BSTCreate(Int_Node_Compare, NULL);
	
	int a = 15;
	int b = 97;
	int c = 301;
	
	expect_int(BSTIsEmpty(bst), TRUE, "BSTInsert_test1");
	
	BSTInsert(bst, &a);
	
	expect_int(BSTIsEmpty(bst), FALSE, "BSTInsert_test2");	
	
	BSTInsert(bst, &b);
	
	expect_size_t(BSTSize(bst), 2, "BSTInsert_test3");
	
	BSTInsert(bst, &c);	
	
	expect_size_t(BSTSize(bst), 3, "BSTInsert_test3");
}

void BSTInsertSmallSmallSmall_test()
{
	bst_t *bst = BSTCreate(Int_Node_Compare, NULL);
	
	int a = 3;
	int b = 2;
	int c = 1;
	
	expect_int(BSTIsEmpty(bst), TRUE, "BSTInsert_test1");
	
	BSTInsert(bst, &a);
	
	expect_int(BSTIsEmpty(bst), FALSE, "BSTInsert_test2");	
	
	BSTInsert(bst, &b);
	
	expect_size_t(BSTSize(bst), 2, "BSTInsert_test3");
	
	BSTInsert(bst, &c);	
	
	expect_size_t(BSTSize(bst), 3, "BSTInsert_test3");	
}

void BSTInsertMiddleSmallerBigger_test()
{
	bst_t *bst = BSTCreate(Int_Node_Compare, NULL);
	
	int a = 5;
	int b = 4;
	int c = 7;
	
	expect_int(BSTIsEmpty(bst), TRUE, "BSTInsert_test1");
	
	BSTInsert(bst, &a);
	
	expect_int(BSTIsEmpty(bst), FALSE, "BSTInsert_test2");	
	
	BSTInsert(bst, &b);
	
	expect_size_t(BSTSize(bst), 2, "BSTInsert_test3");
	
	BSTInsert(bst, &c);	
	
	expect_size_t(BSTSize(bst), 3, "BSTInsert_test3");	

}

void BSTCreate_test()
{
	bst_t *new_bst = BSTCreate(Int_Node_Compare, NULL);
}

int Int_Node_Compare(void *iter_data, void *new_data, void *param)
{
	int result = 0;
	int iter_int_data = *(int *)iter_data;
	int new_int_data = *(int *)new_data;	
	UNUSED(param);

	assert(NULL != iter_data);
	assert(NULL != new_data);
	
	if (iter_int_data > new_int_data)
	{
		result = 1;
	}

	else if (iter_int_data < new_int_data)
	{
		result = -1;
	}
	else /* iter_int_data == new_int_data */
	{
		result = 0;
	}
	
	return result;
}
