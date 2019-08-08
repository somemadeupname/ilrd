#include <stdlib.h> /* malloc realloc free */
#include <assert.h> /* assert */
#include <string.h> /* memmove */

#include "vector.h"

/* vector definition */
struct vector
{
	void *base;
	void *current;
	void *end;
	size_t size_of_element;
	size_t capacity;
};

vector_t *VectorCreate(size_t init_capacity, size_t size_of_element)
{
	vector_t * vector = (vector_t *) malloc (sizeof(vector_t));
	void* base = NULL;
	
		if (NULL == vector)
	{
		return NULL;
	}
	base = (void *) malloc (size_of_element * init_capacity);
	
	if (NULL == base)
	{
		free(vector); vector = NULL; /* free previously allocated memory */
		return NULL;
	}
	
	/* vector members initialization */
	vector->base = base;
	vector->current = base;
	vector->end = (char *)base + init_capacity * size_of_element;
	vector->size_of_element = size_of_element;
	vector->capacity = init_capacity;
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{	
	assert(NULL != vector);
	/* free the memory in the reverse order and scope they were allocated */
	free(vector->base); vector->base = NULL;
	free(vector); vector = NULL;
}

static int UnReserve(vector_t *vector, size_t size)
{
	return VECTOR_SUCCESS;
}

void *VectorGetItemAddress(const vector_t *vector, size_t element_index)
{
	assert(NULL != vector);	
	return (char*) vector->base + (element_index * vector->size_of_element);
}

int VectorPushBack(vector_t *vector, const void *element_value)
{	
	assert(NULL != vector);
	assert(NULL != element_value);
	
	if ((VectorSize(vector) + 1) == VectorCapacity(vector) / 2) /*TODO macro/const*/
	{
		if (VECTOR_ALLOCATION_FAILED ==
								   VectorReserve(vector, (VectorSize(vector))))
		{
			return VECTOR_ALLOCATION_FAILED;
		}
	}
	
	memmove(vector->current, element_value, vector->size_of_element);
	
	vector->current = (char *) vector->current + vector->size_of_element;
		
	return VECTOR_SUCCESS;
}

/* 
 * Remove last element
 * if new size is quarter of capacity decrease capacity by half
 * Param vector: pointer to vector 
 * Return : VECTOR_SUCCESS, non-zero otherwise
 * Errors : If vector points to unreadable address or if vector is empty,
 *			behavior is undefined.
 *			If allocation failed - return VECTOR_ALLOCATION_FAILED
 * 			
 */
int VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);	

	if ((VectorSize(vector) - 1) == VectorCapacity(vector) / 4) /*TODO macro/const*/
	{
		if (VECTOR_ALLOCATION_FAILED ==
								   UnReserve(vector, (VectorSize(vector)/2)))
		{
			return VECTOR_ALLOCATION_FAILED;
		}
	}
	vector->current = (char *) vector->current - vector->size_of_element;
	
	return VECTOR_SUCCESS;
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	return
	 (((char *)vector->current - (char *)vector->base)/vector->size_of_element);	
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);	
	/* vector is empty if the current pointer points to the base */
	return (vector->current == vector->base);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);	
	return vector->capacity;
}

int VectorReserve(vector_t *vector, size_t size)
{
	return VECTOR_SUCCESS;
}
