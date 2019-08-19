#include <stdio.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */
#include "dlist.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");
#define TRUE 1
#define FALSE 0

/* helper functions */
static void expect(void *data, int expected_result, char *func_name);
static void expect_size_t(size_t result, size_t expected_result, char *func_name);
static void expect_int(int result, int expected_result, char *func_name);
static void PrintList(const dlist_t *dlist);

struct dlist_node /* remove when blackboxing */
{
	void *data;
	dlist_iter_t next;
	dlist_iter_t prev;	
};

int CmpFuncInt(void *data, const void *param);
static int IncrementDataByParam(void *data, void *param);
int *GenerateIntLinkedList(dlist_t *list, dlist_iter_t *iter, int size, 
															   int *data_array); 

/* FUNCTIONS */
void TestDListCreate();
void TestDListInsert();
void TestDListInsertBeforeBegin();
void TestDListInsertNormal();
void TestDListRemoveFirst();
void TestDListRemoveSomeNode();
void TestDListSizeEmpty();
void TestDListSizeNotEmpty();

void TestDListPushFront();
void TestDListPopFront();
void TestDListPushBack();
void TestDListPopBack();



int main()
{
	TestDListCreate();
	
	TestDListInsertBeforeBegin();
	
	TestDListInsertNormal();
	
	TestDListRemoveFirst();
	
	TestDListRemoveSomeNode();
	
	TestDListSizeEmpty();
	
	TestDListSizeNotEmpty();
	
	return 0;
}

void TestDListPushFront()
{
	dlist_t *list = DListCreate();
	int *data_array = NULL;
	
	GenerateIntLinkedList()
}
void TestDListPopFront()
{

}
void TestDListPushBack()
{

}
void TestDListPopBack()
{

}

void TestDListSizeEmpty()
{
	dlist_t *list = DListCreate();
	expect_size_t(DListSize(list), 0, "TestDListSizeEmpty");
	DListDestroy(list);	
}
void TestDListSizeNotEmpty()
{
	dlist_t *list = DListCreate();
	dlist_iter_t after_removed_iter = NULL;
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;	
	
	int i1 = 1;
	int *i_ptr = &i1;
	int i2 = 2;
	int *i_ptr2 = &i2;
	
	expect_size_t(DListSize(list), 0, "TestDListSizeNotEmpty");
	
	iter1 = DListInsert(list, DListBegin(list), i_ptr);
	
	expect_size_t(DListSize(list), 1, "TestDListSizeNotEmpty");	
	
	iter2 = DListInsert(list, DListBegin(list), i_ptr2);
	
	expect_size_t(DListSize(list), 2, "TestDListSizeNotEmpty");	
	
	DListDestroy(list);	
}

void TestDListRemoveFirst()
{
	dlist_t *list = DListCreate();
	dlist_iter_t after_removed_iter = NULL;
	dlist_iter_t iter1 = NULL;
	
	int i1 = 1;
	int *i_ptr = &i1;
	
	iter1 = DListInsert(list, DListBegin(list), i_ptr);
	
	expect_int(DListIsEmpty(list),FALSE, "TestDListRemoveFirst");

	DListRemove(list,iter1);
	
	expect_int(DListIsEmpty(list),TRUE, "TestDListRemoveFirst");

	DListDestroy(list);	
}

void TestDListRemoveSomeNode()
{
	dlist_t *list = DListCreate();
	dlist_iter_t after_removed_iter = NULL;
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;	
	
	int i1 = 1;
	int *i_ptr = &i1;
	int i2 = 2;
	int *i_ptr2 = &i2;
	
	iter1 = DListInsert(list, DListBegin(list), i_ptr);
	
	iter2 = DListInsert(list, DListBegin(list), i_ptr2);
	
/*	PrintList(list);*/
	
	after_removed_iter = DListRemove(list,iter2);
	
	expect(after_removed_iter->data,1,"TestDListRemoveSomeNode");
	
/*	PrintList(list);*/
	DListDestroy(list);
}

void TestDListCreate()
{
	dlist_t *dlist = DListCreate();
	DListDestroy(dlist);
}

void TestDListInsertNormal()
{
	dlist_t *dlist = DListCreate();
	
	int i1 = 1;
	int *i_ptr = &i1;
	int i2 = 2;
	int *i_ptr2 = &i2;
	int i3 = 3;
	int *i_ptr3 = &i3;	
	dlist_iter_t iter1 = NULL;
	dlist_iter_t iter2 = NULL;
	dlist_iter_t iter3 = NULL;		

	iter1 = DListInsert(dlist, DListBegin(dlist), i_ptr);

	expect(iter1->data,1,"TestDListInsertNormal");
	
/*	PrintList(dlist);*/
	
	iter2 = DListInsert(dlist, DListBegin(dlist), i_ptr2);

	expect(iter2->data,2,"TestDListInsertNormal");
	
/*	PrintList(dlist);	*/
	
	iter3 = DListInsert(dlist, iter2, i_ptr3);
	
/*	PrintList(dlist);*/
	DListDestroy(dlist);
}

void TestDListInsertBeforeBegin()
{
	dlist_t *dlist = DListCreate();
	
	int i1 = 5;
	int *i_ptr = &i1;
	
	dlist_iter_t iter = DListInsert(dlist, DListBegin(dlist), i_ptr);
	
	expect(iter->data,5,"TestDListInsertBeforeBegin");
	
	DListDestroy(dlist);
}

int CmpFuncInt(void *data, const void *param)
{
	int *d1 = NULL;
	int *d2 = NULL;	
	assert(NULL != data);
	assert(NULL != param);

	d1 = (int *) data;
	d2 = (int *) param;

	return !(*d1 > *d2);/* ! since 0 is success */
}

int IncrementDataByParam(void *data, void *param)
{
	int *int_data = data;
	int *int_param = param;
	if (NULL == data || NULL == param)
	{
		return 1;
	}
	
	*int_data = *int_data + *int_param;
	return 0;
}

static void expect(void *data, int expected_result, char *func_name)
{
	int *int_data = NULL;
	
	assert(NULL != data);
	
	int_data = (int *) data;
	if (*int_data != expected_result)
	{
		START_RED
		printf("ERROR in %s.\n", func_name);
		END_RED
		printf("Expected: \t%d\nActual: \t%d\n", expected_result, *int_data);
	}
}

static void expect_int(int result, int expected_result, char *func_name)
{
	if (result != expected_result)
	{
		START_RED
		printf("ERROR in %s.\n", func_name);
		END_RED
		printf("Expected: \t%d\nActual: \t%d\n", expected_result, result);
	}	
}

static void expect_size_t(size_t result, size_t expected_result, char *func_name)
{
	if (result != expected_result)
	{
		START_RED
		printf("ERROR in %s.\n", func_name);
		END_RED
		printf("Expected: \t%lu\nActual: \t%lu\n", expected_result, result);
	}	
}

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
