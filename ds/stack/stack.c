#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memmove */
#include <assert.h> /* assert */
#include "stack.h"

#define SIZE_OF_POINTER 8
#define NUM_OF_ELEMENTS_IN_STRUCT 4

struct stack
{
	void *base;
	void *current;
	void *end;
	size_t size_of_element;
};

stack_t *StackCreate(size_t max_num_of_elements, size_t size_of_element)
{
	stack_t *stack = (stack_t *)malloc(NUM_OF_ELEMENTS_IN_STRUCT*SIZE_OF_POINTER);
	void* base = NULL;
	
	if (NULL == stack) /* if malloc failed */
	{
		return NULL;
	}
	
	base = (void *) malloc (size_of_element * max_num_of_elements);
	
	if (NULL == base) /* if malloc failed */
	{
		free(stack); stack = NULL; /* free previously allocated memory */
		return NULL;
	}
	
	/* stack members initialization */
	stack->base = base;
	stack->current = base;
	stack->end = (char *)base + max_num_of_elements*size_of_element;
	stack->size_of_element = size_of_element;
	
	return stack;
}

void StackDestroy(stack_t *stack)
{
	free(stack->base); stack->base = NULL;
	free(stack); stack= NULL;
}

/* helper function to see if stack is full */
static int IsStackFull(stack_t *stack)
{
	assert(NULL != stack);
	return (stack->current == stack->end);
}

int StackPush(stack_t *stack, const void *element)
{
	if (IsStackFull(stack))
	{
		return STACK_OVERFLOW_ERROR;
	}
	
	memmove(stack->current, element, stack->size_of_element);
	stack->current = (char *) stack->current + stack->size_of_element;
	
	return STACK_SUCCESS;
}

int StackPop(stack_t *stack)
{
	if (StackIsEmpty(stack))
	{
		return STACK_UNDERFLOW_ERROR;
	}

	stack->current = (char *) stack->current - stack->size_of_element;
		
	return STACK_SUCCESS;	
}

/*
 * Get the address of the value in the top element of the stack.
 * Param stack: pointer to a stack
 * Returns: A pointer to the value of the top element.
 * Errors: If stack points to unreadable address, behavior is undefined.
 */
void *StackPeek(const stack_t *stack)
{
	return (char*) stack->current - stack->size_of_element;
}

int StackIsEmpty(const stack_t *stack)
{
	return (stack->current == stack->base);
}

size_t StackSize(const stack_t *stack)
{
	return (((char*)stack->current-(char*)stack->base)/stack->size_of_element);
}
