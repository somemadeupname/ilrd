
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h>
#include <stdlib.h> /* free malloc */

#include "vector.h"
#include "heap.h"

#define VECTOR_INIT_CAPACITY 1

struct heap
{
	int (*cmp_priority)(const void *data1, const void *data2, void *param);
	vector_t *vector;
	void *cmp_param;
};

/*************************************************************************
*								 										 *
*				      FORWARD DECLARATIONS								 *
*																		 *
*************************************************************************/

static void *FreeAndNullify(void *pointer_to_free);


/* Create new heap */
heap_t *HeapCreate(int (*cmp_priority)(const void *data1,
				   		const void *data2, void *param), void *param)
{
	heap_t *heap = NULL;
	
	assert(NULL != cmp_priority);
	
	heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		return NULL;
	}
	
	heap->vector = VectorCreate(VECTOR_INIT_CAPACITY, sizeof(void *));
	if (NULL == heap->vector)
	{
		heap = FreeAndNullify(heap);
		return NULL;
	}
	
	heap->cmp_priority = cmp_priority;
	heap->cmp_param = param;
	
	return heap;
}

/* Destroy heap */
void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);
	
	VectorDestroy(heap->vector);
	heap->vector = NULL;
	
	heap = FreeAndNullify(heap);
}

/* Return amount of elements in heap */
size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	
	return VectorSize(heap->vector);
}

/* Check if heap is empty */
int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	
	return VectorIsEmpty(heap->vector);
}

/* Return pointer to data from top priority */
void *HeapPeek(const heap_t *heap)
{
	assert(NULL != heap);
	assert(!HeapIsEmpty(heap));
	
	return VectorGetItemAddress(heap->vector, 0);
}

/* helper for create and destroy */
static void *FreeAndNullify(void *pointer_to_free)
{
	free(pointer_to_free);
	return NULL;
}

static size_t GetParentIdx(size_t idx)
{
	return ((idx - 1)/2);
}

static size_t GetLeft(size_t idx)
{
	return 2*idx + 1;
}

static size_t GetRight(size_t idx)
{
	return 2*idx + 2;
}
