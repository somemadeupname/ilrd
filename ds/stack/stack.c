#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc free */
#include "stack.h"

#define SIZE_OF_POINTER 8
#define NUM_OF_ELEMENTS_IN_STRUCT 4

typedef struct stack
{
	void *base;
	void *current;
	void *end;
	size_t size_of_element;
} stack_t;

stack_t *StackCreate(size_t max_num_of_elements, size_t size_of_element)
{
	stack_t *stack = (stack *)malloc(NUM_OF_ELEMENTS_IN_STRUCT*SIZE_OF_POINTER);
	
	if (NULL == stack) /* if malloc failed */
	{
		return NULL;
	}
	
	void *base = (void *) malloc (size_of_element * max_num_of_elements);
	
	if (NULL == base) /* if malloc failed */
	{
		free(stack); stack = NULL; /* free previously allocated memory */
		return NULL;
	}
	
	/* stack initialization */
	stack->base = base;
	stack->current = base;
	stack->end = base + max_num_of_elements;
	stack->size_of_element = size_of_element;
	
	return stack;
}

