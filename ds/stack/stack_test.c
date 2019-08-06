#include <stdio.h>
#include "stack.h"

#define CHECK(X) (printf("%d\n", X))

void TestCreateAndDestroy();
void TestStackPush();
void TestStackPop();
void TestStackPeek();

int main()
{
	/*TestCreateAndDestroy();*/
	/*TestStackPush();*/
	/*TestStackPop();*/
	TestStackPeek();	
	return 0;
}

void TestCreateAndDestroy()
{
	stack_t *stack = StackCreate(4,4);
	StackDestroy(stack);
}

void TestStackPush()
{
	stack_t *stack = StackCreate(4,4);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;			
	CHECK(StackPush(stack, &a));
	CHECK(StackPush(stack, &b));
	CHECK(StackPush(stack, &c));
	CHECK(StackPush(stack, &d));
	CHECK(StackPush(stack, &e));		
	
	StackDestroy(stack);	
}

void TestStackPop()
{
	stack_t *stack = StackCreate(2,4);
	
	int a = 1;
	int b = 2;
	
	CHECK(StackPop(stack));
		
	StackPush(stack, &a);
	StackPush(stack, &b);
	
	CHECK(StackPop(stack));
	CHECK(StackPop(stack));
	CHECK(StackPop(stack));	
	
	StackDestroy(stack);
}

void TestStackPeek()
{	
	stack_t *stack = StackCreate(2,4);
	
	int a = 6;
	int b = 5;
	int * i_ptr = NULL;
	
	StackPush(stack, &a);
	StackPush(stack, &b);
	
	i_ptr = (int *) StackPeek(stack);
	
	CHECK(*i_ptr);
	
	
	StackDestroy(stack);
}
