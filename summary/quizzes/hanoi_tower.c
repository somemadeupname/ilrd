#include <stdio.h>

#include "stack.h"

void MoveDisc(stack_t *src, stack_t *dest);
void HanoiTower(stack_t *src, stack_t *dest, stack_t *aux, size_t size);
void HanoiTowerTestEven();
void HanoiTowerTestOdd();

int main()
{
	HanoiTowerTestEven();
	
	HanoiTowerTestOdd();

	return 0;
}

void HanoiTowerTestOdd()
{
	stack_t *src = StackCreate(5, sizeof(int));
	stack_t *dest = StackCreate(5, sizeof(int));
	stack_t *aux = StackCreate(5, sizeof(int));
	
	int ar[] = {5,4,3,2,1};
	size_t i = 0;
	for (i = 0; i < sizeof(ar)/sizeof(ar[0]); ++i)
	{
		StackPush(src, &ar[i]);
	}	
	
	HanoiTower(src, dest, aux, sizeof(ar)/sizeof(ar[0]));
	
	for (i = 0; i < sizeof(ar)/sizeof(ar[0]); ++i)
	{
		printf("disc %d\n", *(int *)StackPeek(dest));
		StackPop(dest);
	}
	
	StackDestroy(src);
	StackDestroy(dest);
	StackDestroy(aux);
}

void HanoiTowerTestEven()
{
	stack_t *src = StackCreate(4, sizeof(int));
	stack_t *dest = StackCreate(4, sizeof(int));
	stack_t *aux = StackCreate(4, sizeof(int));
	
	int ar[] = {4,3,2,1};
	size_t i = 0;
	for (i = 0; i < sizeof(ar)/sizeof(ar[0]); ++i)
	{
		StackPush(src, &ar[i]);
	}	
	
	HanoiTower(src, dest, aux, sizeof(ar)/sizeof(ar[0]));
	
	for (i = 0; i < sizeof(ar)/sizeof(ar[0]); ++i)
	{
		printf("disc %d\n", *(int *)StackPeek(dest));
		StackPop(dest);
	}
	
	StackDestroy(src);
	StackDestroy(dest);
	StackDestroy(aux);	
	
}

void HanoiTower(stack_t *src, stack_t *dest, stack_t *aux, size_t size)
{
	if (1 == size)
	{
		MoveDisc(src, dest);
		return;
	}
	
	HanoiTower(src, aux, dest, size - 1);
	
	MoveDisc(src, dest);
	
	HanoiTower(aux, dest, src, size - 1);
}

void MoveDisc(stack_t *src, stack_t *dest)
{
	StackPush(dest, StackPeek(src));
	StackPop(src);
}
