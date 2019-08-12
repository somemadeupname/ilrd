/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Dandan	    *
 *	 Status   : Sent	    *
 ****************************/
 
#include <stdlib.h> /* malloc realloc free */
#include <assert.h> /* assert */
#include <string.h> /* memmove */

#include "vector.h"

#define CAPACITY_TO_SIZE_RATIO_PUSH 2
#define CAPACITY_TO_SIZE_RATIO_POP 4

/* vector definition */
struct vector
{
	void *base;
	void *current;
	void *end;
	size_t size_of_element;
	size_t capacity;
	size_t init_capacity;
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
	vector->init_capacity = init_capacity;
	
	return vector;
}

void VectorDestroy(vector_t *vector)
{	
	assert(NULL != vector);
	/* free the memory in the reverse order and scope they were allocated */
	free(vector->base); vector->base = NULL;
	free(vector); vector = NULL;
}
/*  static function which is used by popback when the vector's capacity
	needs to be decreased												 */
static int UnReserve(vector_t *vector, size_t size)
{
	assert(NULL != vector);
	assert(NULL != vector->base);
	assert(0 != size);
	
	/* if user asked for a certain capacity when creating the vector - 
	the user init value will take precedence						 */
	if (size > vector->init_capacity) 
	{
		vector->base = (void *)
						realloc (vector->base, size * vector->size_of_element);
		vector->capacity = size;
	}
	
	if (NULL == vector->base)
	{
		return VECTOR_ALLOCATION_FAILED;
	}
	
	return VECTOR_SUCCESS;
}

void *VectorGetItemAddress(const vector_t *vector, size_t element_index)
{
	assert(NULL != vector);	
	return (char *) vector->base + (element_index * vector->size_of_element);
}

int VectorPushBack(vector_t *vector, const void *element_value)
{	
	size_t size = 0;
	assert(NULL != vector);
	assert(NULL != element_value);
	
	/* check if capacity needs to be increased */
	if ((VectorSize(vector)) >
							 VectorCapacity(vector)/CAPACITY_TO_SIZE_RATIO_PUSH) 
	{
		size = VectorSize(vector) * vector->size_of_element;
		if (VECTOR_ALLOCATION_FAILED ==
								  VectorReserve(vector, VectorCapacity(vector)))
		{
			return VECTOR_ALLOCATION_FAILED;
		}
		vector->current = (char *) vector->base + size;
	}
	
	memmove(vector->current, element_value, vector->size_of_element);
	
	vector->current = (char *) vector->current + vector->size_of_element;
		
	return VECTOR_SUCCESS;
}

int VectorPopBack(vector_t *vector)
{
	size_t size = 0;
	assert(NULL != vector);
	assert(1 != VectorIsEmpty(vector));
	
	/* decrease the vector's capacity when size is 1/4 of the capacity  */
	if ((VectorSize(vector)) ==
							VectorCapacity(vector) / CAPACITY_TO_SIZE_RATIO_POP) 
	{
		/* save the number of elements to
		   update current once base it realloced */
		size = VectorSize(vector) * vector->size_of_element;
		if (VECTOR_ALLOCATION_FAILED ==
								  UnReserve(vector, (VectorCapacity(vector)/2)))
		{
			return VECTOR_ALLOCATION_FAILED;
		}
		/* updating current to base's new address */
		vector->current = (char *) vector->base + size;
	}
	
	/* pop the element */
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
	assert(NULL != vector);
	assert(NULL != vector->base);
	assert(0 != size);
	
	/* allocate additonal space for vector->base */
	vector->base = (void *) realloc
			(vector->base, (vector->capacity + size) * vector->size_of_element);
	
	if (NULL == vector->base)
	{
		return VECTOR_ALLOCATION_FAILED;
	}
	
	/* update capacity */
	vector->capacity += size;
	
	return VECTOR_SUCCESS;
}
