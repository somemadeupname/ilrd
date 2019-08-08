#include <stdlib.h> /* malloc realloc free */
#include <assert.h> /* assert */

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

int VectorPushBack(vector_t *vector, const void *element_value)
{
		
}
