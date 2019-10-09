
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Hay Hoffman *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* free malloc */

#include "vector.h" /* vector API*/
#include "heap.h" /* heap API */

struct heap
{
	int (*cmp_priority)(const void *data1, const void *data2, void *param);
	void *cmp_param;
	vector_t *vector;
};

typedef enum {UP, DOWN} sift_direction;
typedef enum {LEFT_DOWN, RIGHT_DOWN, SIFT_UP, NONE} sift_status;
typedef enum {LEFT, RIGHT} direction;
/*************************************************************************
*								 										 *
*				      FORWARD DECLARATIONS								 *
*																		 *
*************************************************************************/

static void *FreeAndNullify(void *pointer_to_free);
static void *GetData(vector_t *vector, size_t index);
static void SwapData(vector_t *vector, size_t idx1, size_t idx2);
static int GetIndexToRemove(heap_t *heap,
							int (*is_match)(const void *heap_data,
										    const void *user_data),
							void *data_to_remove);
static void Sift(sift_direction sift_dir, size_t index, heap_t *heap);
static void SiftOnRemove(heap_t *heap, size_t idx_to_remove);
static sift_direction SiftDirection(heap_t *heap, size_t index);
static int IsPriorityGreaterThanParent(const heap_t *heap, size_t index);
static int IsPriorityGreater(const heap_t *heap, size_t index, direction dir);
static int HasChild(const heap_t *heap, size_t index, direction dir);
static direction ChildSiftDirection(heap_t *heap, size_t index);
static int IsLeftChildGreaterPriority(heap_t *heap, size_t parent_idx);
static direction GetDirectionOfChildWithHigherPriority(const heap_t *heap,
													   size_t parent_idx);
static int IsChild(size_t index);
static size_t GetChildIdx(size_t index, direction dir);
static size_t GetParentIdx(size_t idx);

/*************************************************************************
*								 										 *
*				      MAIN HEAP FUNCTIONS								 *
*																		 *
*************************************************************************/
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
	
	#define VECTOR_INIT_CAPACITY 1
	
	heap->vector = VectorCreate(VECTOR_INIT_CAPACITY, sizeof(void *));
	if (NULL == heap->vector)
	{
		heap = FreeAndNullify(heap);
		return NULL;
	}
	
	heap->cmp_priority = cmp_priority;
	heap->cmp_param = param;
	
	return heap;
	
	#undef VECTOR_INIT_CAPACITY
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
	
	return *(void **)VectorGetItemAddress(heap->vector, 0);
}

/* Add new member to heap according to priority */
int HeapPush(heap_t *heap, const void *data)
{
	#define VECTOR_RESERVE_CAPACITY 100
	
	assert(NULL != heap);
	
	if (HeapIsEmpty(heap))
	{
		if (VECTOR_ALLOCATION_FAILED == VectorReserve(heap->vector,
													  VECTOR_RESERVE_CAPACITY))
		{
			return HEAP_ALLOC_FAIL;
		}
	}
	
	if (VECTOR_ALLOCATION_FAILED == VectorPushBack(heap->vector, &data))
	{
		return HEAP_ALLOC_FAIL;
	}
	
	Sift(UP, HeapSize(heap) - 1, heap);
	
	return HEAP_SUCCESS; 
	
	#undef VECTOR_RESERVE_CAPACITY
}

/* Remove member from top priority */
void HeapPop(heap_t *heap)
{
	assert(NULL != heap);
	assert(!HeapIsEmpty(heap));
	
	SwapData(heap->vector, 0, HeapSize(heap) - 1);
	
	VectorPopBack(heap->vector);
	
	if (!HeapIsEmpty(heap))
	{
		Sift(DOWN, 0, heap);
	}
}

/* Remove data from heap */
void *HeapRemove(heap_t *heap, int (*is_match)(const void *heap_data,
			   	 const void *user_data), void *data_to_remove)
{
	int idx_to_remove = 0;
	void *data_to_return = NULL;
	
	assert(NULL != heap);
	
	idx_to_remove = GetIndexToRemove(heap, is_match, data_to_remove);
	
	if (-1 == idx_to_remove)
	{
		return NULL;
	}
	
	data_to_return = GetData(heap->vector, idx_to_remove);
	
	if (HeapSize(heap) - 1 == (size_t) idx_to_remove) /* last index is to be removed */
	{
		if (VECTOR_ALLOCATION_FAILED == VectorPopBack(heap->vector))
		{
			return NULL;
		}
	}
	else
	{
		SwapData(heap->vector, idx_to_remove, HeapSize(heap) - 1);
		
		if (VECTOR_ALLOCATION_FAILED == VectorPopBack(heap->vector))
		{
			return NULL;
		}
		
		SiftOnRemove(heap, idx_to_remove);
	}
	
	return data_to_return;
}

/*************************************************************************
*								 										 *
*				      HELPER FUNCTIONS									 *
*																		 *
*************************************************************************/

/* Get Data using in @index */
static void *GetData(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	
	return *(void **)VectorGetItemAddress(vector, index);
}

static void SwapData(vector_t *vector, size_t idx1, size_t idx2)
{
	void **data1 = NULL;
	void **data2 = NULL;
	void *temp = NULL;
	
	assert(NULL != vector);
	
	data1 = VectorGetItemAddress(vector, idx1);
	data2 = VectorGetItemAddress(vector, idx2);
	
	temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}

static int IsChild(size_t index)
{
	return (0 != index);
}

/* helper for create and destroy */
static void *FreeAndNullify(void *pointer_to_free)
{
	free(pointer_to_free);
	return NULL;
}

static size_t GetChildIdx(size_t index, direction dir)
{
	return ((2 * index) + (dir + 1));
}

static size_t GetParentIdx(size_t idx)
{
	return ((idx - 1) / 2);
}

/*************************************************************************
*								 										 *
*				      SIFT AND REMOVE HELPERS							 *
*																		 *
*************************************************************************/

/* returns positive number if index exists. -1 otherwise. */
static int GetIndexToRemove(heap_t *heap,
							int (*is_match)(const void *heap_data,	
							const void *user_data),
							void *data_to_remove)
{
	int i = 0;
	
	assert(NULL != heap);
	
	for (i = 0; (size_t) i < HeapSize(heap); ++i)
	{
		void *heap_data = GetData(heap->vector, (size_t) i);
		
		if (1 == is_match(heap_data, data_to_remove))
		{
			return i;
		}
	}
	
	return -1;
}

/* swaps data up or down the heap per priority */
static void Sift(sift_direction sift_dir, size_t index, heap_t *heap)
{
	sift_status status = NONE;
	
	assert(NULL != heap);
	
	for (status = SiftDirection(heap, index);
		 NONE != status;
		 status = SiftDirection(heap, index)
		)
	{
		int dir = status;
		
		if (UP == sift_dir)
		{
			size_t parent_idx = GetParentIdx(index);
			SwapData(heap->vector, index, parent_idx);
			index = parent_idx;
		}
		else /* DOWN == sift_dir */
		{
			size_t child_idx = GetChildIdx(index, dir);
			SwapData(heap->vector, index, child_idx);
			index = child_idx;	
		}
	}
}

/* sift when removing node from heap */
static void SiftOnRemove(heap_t *heap, size_t idx_to_remove)
{
	sift_status sift_stat = SiftDirection(heap, idx_to_remove);
	
	assert(NULL != heap);
	
	if ((LEFT_DOWN == sift_stat) || (RIGHT_DOWN == sift_stat))
	{
		Sift(DOWN, idx_to_remove, heap);
	}
	else if (SIFT_UP == sift_stat)
	{
		Sift(UP, idx_to_remove, heap);
	}
}

/* gets direction to sift based on index */
static sift_direction SiftDirection(heap_t *heap, size_t index)
{
	assert(NULL != heap);
	
	if (IsChild(index) && IsPriorityGreaterThanParent(heap, index))
	{
		return SIFT_UP;
	}
	
	else if (HasChild(heap, index, LEFT))
	{
		return ChildSiftDirection(heap, index);
	}
	
	return NONE;
}

/* check if child's priority is greater than its parent */
static int IsPriorityGreaterThanParent(const heap_t *heap, size_t index)
{
	size_t parent_idx = GetParentIdx(index);
	void *child_data = NULL;
	void *parent_data = NULL;
	
	assert(NULL != heap);
	
	child_data = GetData(heap->vector, index);
	parent_data = GetData(heap->vector, parent_idx);
	
	return (heap->cmp_priority(parent_data, child_data, heap->cmp_param) > 0);
}

/* check if child with given direction's priority is greater than its parent */
static int IsPriorityGreater(const heap_t *heap, size_t index, direction dir)
{
	void *child_data = NULL;
	void *parent_data = NULL;
	
	assert(NULL != heap);
	
	child_data = GetData(heap->vector, GetChildIdx(index, dir));
	parent_data = GetData(heap->vector, index);
	
	return (heap->cmp_priority(parent_data, child_data, heap->cmp_param) > 0);
}

/* checks if node has children based on its index */
static int HasChild(const heap_t *heap, size_t index, direction dir)
{
	size_t child_idx = 0;
	
	assert(NULL != heap);
	
	child_idx = GetChildIdx(index, dir);
	
	return (HeapSize(heap) > child_idx);
}

/* returns of the direction to sift */
static direction ChildSiftDirection(heap_t *heap, size_t index)
{
	assert(NULL != heap);
	
	if (HasChild(heap, index, RIGHT))
	{
		direction dir = GetDirectionOfChildWithHigherPriority(heap, index);
		
		if (IsPriorityGreater(heap, index, dir))
		{
			return dir;
		}
		
		return NONE;
	}
	
	if (IsLeftChildGreaterPriority(heap, index))
	{
		return LEFT_DOWN;
	}
	
	return NONE;
}

/* checks if left child has a greater priority */
static int IsLeftChildGreaterPriority(heap_t *heap, size_t parent_idx)
{
	void *parent_data = NULL;
	void *left_data = NULL;
	size_t left_idx = GetChildIdx(parent_idx, LEFT);
	
	assert(NULL != heap);
	
	parent_data = GetData(heap->vector, parent_idx);
	left_data = GetData(heap->vector, left_idx);
	
	return (heap->cmp_priority(parent_data, left_data, heap->cmp_param) > 0);
}

/* gets the direction of the higher priority child */
static direction GetDirectionOfChildWithHigherPriority(const heap_t *heap, size_t parent_idx)
{
	size_t left_idx = GetChildIdx(parent_idx, LEFT);
	size_t right_idx = GetChildIdx(parent_idx, RIGHT);
	
	void *left_data = NULL;
	void *right_data = NULL;
	
	assert(NULL != heap);
	
	left_data = GetData(heap->vector, left_idx);
	right_data = GetData(heap->vector, right_idx);
	
	if (heap->cmp_priority(left_data, right_data, heap->cmp_param) > 0)
	{
		return RIGHT;
	}
	
	return LEFT;
}
