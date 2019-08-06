#include <stdio.h>
#include "stack.h"

#define CHECK(X) (printf("%d\n", X))

void TestCreateAndDestroy();
void TestStackPush();

int main()
{
	TestCreateAndDestroy();
	TestStackPush();	
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

