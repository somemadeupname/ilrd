#include <stdio.h> /* printf */
#include <assert.h>

#include "slist_ops.h"
#include "slist.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");

enum {LOOP, NO_LOOP};


/* FORWARD DECLARATIONS */
void BreakLoopTest();
void FlipListRecursiveTest();
void FlipListIterativeTest();

void PrintList(slist_node_t *node, const char *list_name)
{
	size_t i = 0;
	slist_node_t *cur = node;
	assert(NULL != node);
	
	printf("%s:", list_name);
	
	while (NULL != cur) /* works for lists longer than 1 nodes */
	{
		START_RED
		printf("| ");
		END_RED
		printf("[%lu], %d", i, *(int *)cur->data);
		START_RED
		printf(" |->");		
		END_RED
		++i;
		cur = cur->next_node;
	}
	printf(" NULL\n");
}


slist_node_t *InitSList(int flag)
{
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8;
	slist_node_t *node_a = NULL; 
	slist_node_t *node_b = NULL;
	slist_node_t *node_c = NULL;
	slist_node_t *node_d = NULL;
	slist_node_t *node_e = NULL; 
	slist_node_t *node_f = NULL;
	slist_node_t *node_g = NULL;
	slist_node_t *node_h = NULL;
	
	node_h = SListCreateNode(&h, NULL);
	node_g = SListCreateNode(&g, NULL);
	node_f = SListCreateNode(&f, NULL);
	node_e = SListCreateNode(&e, NULL);
	node_d = SListCreateNode(&d, NULL);
	node_c = SListCreateNode(&c, NULL);
	node_b = SListCreateNode(&b, NULL);
	node_a = SListCreateNode(&a, NULL);
	
	SListInsertAfter(node_a, node_h);
	SListInsertAfter(node_a, node_g);
	SListInsertAfter(node_a, node_f);
	SListInsertAfter(node_a, node_e);
	SListInsertAfter(node_a, node_d);
	SListInsertAfter(node_a, node_c);
	SListInsertAfter(node_a, node_b);
	
	/* create the loop */
	if (LOOP == flag)
	{
		node_h->next_node = node_d;
	}
	
	return node_a;
}

int main()
{
/*	BreakLoopTest();*/
	
	FlipListRecursiveTest();
	
	return 0;
}

void BreakLoopTest()
{
	slist_node_t *head = InitSList(LOOP);
	
	FindAndBreakLoop(head);
	
	PrintList(head, "after loop removal");
	
	SListFreeAll(head);
}

void FlipListRecursiveTest()
{
	slist_node_t *head = InitSList(NO_LOOP);

	PrintList(head, "before flip");
	
	FlipListRecursive(head);
	
	PrintList(head, "after flip");
	
	SListFreeAll(head);
}
