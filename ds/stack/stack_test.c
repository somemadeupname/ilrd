#include <stdio.h>
#include "stack.h"

#define CHECK(X) (printf("%d\n", X))
#define CHECK_LD(X) (printf("%lu\n", X))

void TestCreateAndDestroy();
void TestStackPush();
void TestStackPop();
void TestStackPeek();
void TestStackIsEmpty();
void TestStackSize();

int main()
{
	/*TestCreateAndDestroy();*/
	/*TestStackPush();*/
	/*TestStackPop();*/
	/*TestStackPeek();*/
	/*TestStackIsEmpty();*/
	TestStackSize();
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
	int *i_ptr = NULL;
	int *i_ptr2 = NULL;	
	int *i_ptr3 = NULL;		
	
	StackPush(stack, &a);
	StackPush(stack, &b);
	
	i_ptr = (int *) StackPeek(stack);
	
	StackPop(stack);
	
	i_ptr2 = (int *) StackPeek(stack);
	
	StackPop(stack);
	
	i_ptr3 = (int *) StackPeek(stack);	
	
	CHECK(*i_ptr);
	CHECK(*i_ptr2);	
	/*CHECK(*i_ptr3);		*/
	
	StackDestroy(stack);
}

void TestStackIsEmpty()
{
	stack_t *stack = StackCreate(400,1);
	char a = 'a';
	CHECK(StackIsEmpty(stack));
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);
	StackPush(stack, &a);		
	CHECK(StackIsEmpty(stack));
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	CHECK(StackIsEmpty(stack));	
	StackDestroy(stack);	
}

void TestStackSize()
{
	stack_t *stack = StackCreate(400,4);
	
	int a = 6;
	int b = 5;
	int *i_ptr = NULL;
	int *i_ptr2 = NULL;	
	
	CHECK_LD(StackSize(stack));
	
	StackPush(stack, &a);
	
	CHECK_LD(StackSize(stack));
	
	StackPush(stack, &b);

	CHECK_LD(StackSize(stack));	
	
	i_ptr = (int *) StackPeek(stack);
	StackPop(stack);

	CHECK_LD(StackSize(stack));	
	
	i_ptr2 = (int *) StackPeek(stack);
	StackPop(stack);
	
	CHECK_LD(StackSize(stack));
	
	StackDestroy(stack);	
}
