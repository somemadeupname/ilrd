#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "slist.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");

/* Forward Declarations */

/* Test Functions */
void TestSListCreateNode();
void TestSListInsert();
void TestSListInsertAfter();
void TestSListFind();
void TestSListCount();
void TestSListForEach();
void TestSListRemove();

/* helper functions */
static void expect(void *data, int expected_result, char *func_name);
static void expect_size_t(size_t result, size_t expected_result, char *func_name);
int* GenerateIntLinkedList(slist_node_t *head, int size, int * data_array);
static int IncrementDataByParam(void *data, void *param);

int main()
{
	TestSListCreateNode();

	TestSListInsert();
	
	TestSListInsertAfter();
	
	TestSListFind();
	
	TestSListCount();
	
	TestSListForEach();
	
	TestSListRemove();
	
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

static void PrintList(const slist_node_t *head)
{
	size_t node_index = 0;
	slist_node_t *cur_node = (slist_node_t *) head;
	while (NULL != cur_node)
	{
		printf("[n%lu. data: %d]--", node_index, *(int *)cur_node->data);
		cur_node = cur_node->next_node;
		++node_index;
	}
	printf("\n");
}

void TestSListCreateNode()
{
	int a = 3;
	slist_node_t *head = SListCreateNode(&a, NULL); 
	
	expect(head->data, 3, "TestSListCreateNode");
	
	SListFreeAll(head);
	
	head = SListCreateNode(NULL, NULL);
	
	SListFreeAll(head);
}

void TestSListInsert()
{
	int a = 3;
	int b = 5;
	slist_node_t *returned_head = NULL;

	slist_node_t *head = SListCreateNode(&a, NULL);
	slist_node_t *new_head = SListCreateNode(&b, NULL);
	
	returned_head = SListInsert(head, new_head);
	
	expect(returned_head->data, 5, "TestSListInsert");
	expect(returned_head->next_node->data, 3, "TestSListInsert");	
	
	SListFreeAll(returned_head);
}

void TestSListInsertAfter()
{
	int a = 3;
	int b = 5;
	slist_node_t *returned_head = NULL;

	slist_node_t *head = SListCreateNode(&a, NULL);
	slist_node_t *next = SListCreateNode(&b, NULL);
	
	returned_head = SListInsertAfter(head, next);
	
	expect(returned_head->data, 3, "TestSListInsertAfter");
	expect(returned_head->next_node->data, 5, "TestSListInsertAfter");	
	
	SListFreeAll(returned_head);
}

/* comparator function for Find */
int CmpFunc(void *node_data, const void *param_data)
{
	int *d1 = NULL;
	int *d2 = NULL;	
	assert(NULL != node_data);
	assert(NULL != param_data);

	d1 = (int *) node_data;
	d2 = (int *) param_data;

	return !(*d1 > *d2);/* ! since 0 is success */
}

void TestSListFind()
{
	int a = 1;
	int b = 2;
	int c = 3;	
	int d = 4;
	int cmp_data = 2;
	slist_node_t *found_node = NULL;

	slist_node_t *head = SListCreateNode(&a, NULL);
	slist_node_t *node_b = SListCreateNode(&b, NULL);
	slist_node_t *node_c = SListCreateNode(&c, NULL);
	slist_node_t *node_d = SListCreateNode(&d, NULL);		
	
	SListInsertAfter(head, node_d);
	SListInsertAfter(head, node_c);
	SListInsertAfter(head, node_b);
	
	found_node = SListFind(head, CmpFunc, &cmp_data);
	
	expect(found_node->data, 3, "TestSListFind");
	
	SListFreeAll(head);
}

int *GenerateIntLinkedList(slist_node_t *head, int size, int * data_array)
{
	int index = size - 1;
	data_array = (int *)malloc(sizeof(int)*size);
	while (index >= 0)
	{
		data_array[index] = index;
		SListInsertAfter(head,SListCreateNode(&data_array[index], NULL));
		--index;
	}
	return data_array;
}

void TestSListCount()
{
	int *data_array = NULL;
	int a = 1;
	slist_node_t *head = SListCreateNode(&a, NULL);
	data_array = GenerateIntLinkedList(head, 9, data_array);
	
	expect_size_t(SListCount(head),10,"TestSListCount");
	
	SListFreeAll(head);
	free(data_array);
}

static int IncrementDataByParam(void *data, void *param)
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

void TestSListForEach()
{
	int *data_array = NULL;
	int a = 1;
	int param = 2;
	slist_node_t *head = SListCreateNode(&a, NULL);
	data_array = GenerateIntLinkedList(head, 3, data_array);

	expect(head->data, 1, "TestSListForEach");
	expect(head->next_node->data, 0, "TestSListForEach");
	expect(head->next_node->next_node->data, 1, "TestSListForEach");			
	
	SListForEach(head,IncrementDataByParam,&param);
	
	expect(head->data, 3, "TestSListForEach");
	expect(head->next_node->data, 2, "TestSListForEach");
	expect(head->next_node->next_node->data, 3, "TestSListForEach");
	
	SListFreeAll(head);
	free(data_array);
}

void TestSListRemove()
{
	int *data_array = NULL;
	int a = -1;
	slist_node_t *head = SListCreateNode(&a, NULL);
	slist_node_t *node_to_remove = NULL;
	
	data_array = GenerateIntLinkedList(head, 3, data_array);
	
	PrintList(head);

	node_to_remove = head->next_node;
	
	expect(node_to_remove->data, 0, "TestSListRemove");

	expect_size_t(SListCount(head),4,"TestSListRemove");
	
	node_to_remove = SListRemove(node_to_remove);
	
	expect_size_t(SListCount(head),3,"TestSListRemove");
	
	expect(node_to_remove->data, 0, "TestSListRemove");
	
	SListFreeAll(head);
	free(data_array);
	SListFreeAll(node_to_remove);
}
