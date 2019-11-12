#include <assert.h> /*assert*/
#include <stdio.h>  /*printf*/

#include "heap.h"

#define UNUSED(x) ((void)x)

/******************************************************************************/
/**************************** forward declaration *****************************/
/******************************************************************************/
static void CreateDestroy_test();
static void PushPop_test();
static void Remove_test();
static heap_t *CreateFullHeap();

static int CmpPriority(const void *data1, const void *data2, void *param);
int IsMatch(const void *heap_data, const void *user_data);

/******************************************************************************/
/*********************************** main *************************************/
/******************************************************************************/
int main()
{	
	CreateDestroy_test();
	PushPop_test();
	Remove_test();
	
	return 0;
}

/******************************************************************************/
/**************************** test functions **********************************/
/******************************************************************************/
static void Remove_test()
{
	heap_t *heap = CreateFullHeap();
	int arr[14] = {20, 80, 90, 70, 75, 60, 50, 10, 5, 72, 74, 40, 30, 100};
	size_t i = 0;
	int data_not_found = -1;

	assert(0 == HeapIsEmpty(heap));
	assert(14 == HeapSize(heap));
	
	assert(NULL == HeapRemove(heap, IsMatch, &data_not_found));
	
	while (i < 14)
	{
		assert(arr[i] == *(int *)HeapRemove(heap, IsMatch, &arr[i]));
		++i;
	}
	
	assert(1 == HeapIsEmpty(heap));
	assert(0 == HeapSize(heap));

	HeapDestroy(heap);
}

static void PushPop_test()
{
	int data1 = 5, data2 = 10, data3 = 3;
	
	heap_t *heap = HeapCreate(CmpPriority, NULL);
	assert(NULL != heap);
	
	assert(1 == HeapIsEmpty(heap));
	assert(0 == HeapSize(heap));
	
	assert(0 == HeapPush(heap, &data1));
	assert(data1 ==  *(int *)HeapPeek(heap));
	assert(0 == HeapPush(heap, &data2));
	assert(data2 ==  *(int *)HeapPeek(heap));
	assert(0 == HeapPush(heap, &data3));
	assert(data2 ==  *(int *)HeapPeek(heap));

	assert(0 == HeapIsEmpty(heap));
	assert(3 == HeapSize(heap));

	HeapPop(heap);
	assert(data1 == *(int *)HeapPeek(heap));
	assert(2 == HeapSize(heap));

	HeapPop(heap);
	assert(data3 == *(int *)HeapPeek(heap));
	assert(1 == HeapSize(heap));

	HeapPop(heap);

	assert(1 == HeapIsEmpty(heap));
	assert(0 == HeapSize(heap));

	HeapDestroy(heap);
}

static void CreateDestroy_test()
{
	heap_t *heap = HeapCreate(CmpPriority, NULL);
	assert(NULL != heap);
	
	assert(1 == HeapIsEmpty(heap));
	assert(0 == HeapSize(heap));
	
	HeapDestroy(heap);
}

static heap_t *CreateFullHeap()
{
	static int arr[14] = {100, 80, 90, 70, 75, 60, 50, 10, 5, 72, 74, 40, 30, 20};
	size_t i = 0;
	heap_t *heap = HeapCreate(CmpPriority, NULL);
	assert(NULL != heap);
	
	assert(1 == HeapIsEmpty(heap));
	assert(0 == HeapSize(heap));
	
	while (i < 14)
	{
		assert(0 == HeapPush(heap, &arr[i]));		
		++i;
		assert(0 == HeapIsEmpty(heap));
		assert(i == HeapSize(heap));
	}
	
	assert(i == HeapSize(heap));
	
	return heap;
}

/******************************************************************************/
/**************************** service functions *******************************/
/******************************************************************************/
static int CmpPriority(const void *data1, const void *data2, void *param)
{
	UNUSED(param);
	
	return (*( int*)data2 - *(int *)data1);	
}

int IsMatch(const void *heap_data, const void *user_data)
{
	return (*(int *)heap_data == *(int *)user_data);
}
