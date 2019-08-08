/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Vova	    *
 *	 Status   : Approved    *
 ****************************/
 
#include <stdlib.h> /* malloc free */
#include <string.h> /* memmove */
#include <assert.h> /* assert */
#include "stack.h"

/* stack definition */
struct stack
{
	void *base;
	void *current;
	void *end;
	size_t size_of_element;
};

/****************************
 *	 Status   : Approved        *
 ****************************/
stack_t *StackCreate(size_t max_num_of_elements, size_t size_of_element)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t);
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
	/* since element size is unknown - cast to char * to advance by 1 */
	stack->end = (char *)base + max_num_of_elements*size_of_element;
	stack->size_of_element = size_of_element;
	
	return stack;
}

/****************************
 *	 Status   : Approved    *
 ****************************/
void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	/* free the memory in the reverse order and scope they were allocated */
	free(stack->base); stack->base = NULL;
	free(stack); stack= NULL;
}

/* helper function to see if stack is full */
static int IsStackFull(stack_t *stack)
{
	assert(NULL != stack);
	return (stack->current == stack->end);
}

/****************************
 *	 Status   : Approved        *
 ****************************/
int StackPush(stack_t *stack, const void *element)
{
	assert(NULL != stack);
	assert(NULL != element);
			
	if (IsStackFull(stack))
	{
		return STACK_OVERFLOW_ERROR;
	}
	/* using memmove to copy data from one void pointer to another */
	memmove(stack->current, element, stack->size_of_element);
	/* since element size is unknown - cast to char * to advance by 1 */
	stack->current = (char *) stack->current + stack->size_of_element;
	
	return STACK_SUCCESS;
}

/****************************
 *	 Status   : Approved    *
 ****************************/
int StackPop(stack_t *stack)
{
	assert(NULL != stack);
	if (StackIsEmpty(stack))
	{
		return STACK_UNDERFLOW_ERROR;
	}
	/* since element size is unknown - cast to char * to retreat by 1 */
	stack->current = (char *) stack->current - stack->size_of_element;
		
	return STACK_SUCCESS;	
}

/****************************
 *	 Status   : Approved    *
 ****************************/
void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);	
	/* needs to return the address of the previously added value */
	return (char*) stack->current - stack->size_of_element;
}

/****************************
 *	 Status   : Approved    *
 ****************************/
int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);	
	/* stack is empty if the current pointer points to the base */
	return (stack->current == stack->base);
}

/****************************
 *	 Status   : Approved    *
 ****************************/
size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);	
	/* size of the stack is the difference between the 
	base and current address divided by the size of an element */
	return (((char *)stack->current-(char *)stack->base)/stack->size_of_element);
}
