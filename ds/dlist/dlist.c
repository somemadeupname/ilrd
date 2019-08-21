
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Adi Peretz	*
 *   Status   : 	Fixing  *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free sizeof */
#include "dlist.h"

#define TRUE 1
#define FALSE 0

typedef struct dlist_node dlist_node_t;

struct dlist
{
	dlist_node_t *dummy_begin;
	dlist_node_t *dummy_end;	
};

struct dlist_node
{
	void *data;
	dlist_node_t *next;
	dlist_node_t *prev;	
};

/* Forward Declaration */
static void *DListPopIter(dlist_iter_t iter_to_pop);

/* create double nodes */
static dlist_node_t *DListCreateNode(void *data, dlist_node_t *prev,
															 dlist_node_t *next)
{
	dlist_node_t *node = (dlist_node_t *)malloc(sizeof(dlist_node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->next = next;
	node->prev = prev;
	node->data = data;
	
	return node;
}

dlist_t *DListCreate(void)
{
	dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == dlist)
	{
		return NULL;
	}
	
	dlist->dummy_begin = DListCreateNode(NULL, NULL, NULL);
	if (NULL == dlist->dummy_begin)
	{
		free(dlist->dummy_begin); dlist->dummy_begin = NULL;
		
	}
	
	dlist->dummy_end = DListCreateNode(NULL, dlist->dummy_begin, NULL);
	if (NULL == dlist->dummy_end)
	{
		free(dlist->dummy_begin); dlist->dummy_begin = NULL;
		
		
	}
	dlist->dummy_begin->next = dlist->dummy_end;
	
	return dlist;
}

void DListDestroy(dlist_t *list)
{
	dlist_iter_t runner = list->dummy_begin;
	dlist_iter_t temp_iter_to_free = NULL;
	
	assert(NULL != list);
	
	while (!DListIsSameIter(runner,DListEnd(list)))
	{
		temp_iter_to_free = runner;
		runner = DListNext(runner);
		free (temp_iter_to_free); temp_iter_to_free = NULL;
	}
	free(list->dummy_end); list->dummy_end = NULL;
	free(list); list = NULL;
}

dlist_iter_t DListInsert(dlist_t *list, dlist_iter_t iter, void *data)
{
	dlist_iter_t iter_to_insert = NULL;
	
	assert(NULL != list);
	assert(NULL != iter);
	
	iter_to_insert = DListCreateNode(data, iter->prev, iter);	
	
	if (NULL == iter_to_insert)
	{
		return DListEnd(list);
	}
	
	iter->prev->next = iter_to_insert;
	iter->prev = iter_to_insert;
	
	return iter_to_insert;
}

dlist_iter_t DListRemove(dlist_iter_t iter_to_remove)
{
	dlist_iter_t following_iter = NULL;	
	
	assert(NULL != iter_to_remove);
	
	following_iter = iter_to_remove->next;	
	
	iter_to_remove->prev->next = following_iter;
	following_iter->prev = iter_to_remove->prev;
			
	free(iter_to_remove); iter_to_remove = NULL;
	
	return following_iter;
}

size_t DListSize(const dlist_t *list)
{
	size_t elements_counter = 0;
	dlist_iter_t runner = NULL;
	
	assert(NULL != list);
	
	for (runner = DListBegin(list);
		 !DListIsSameIter(runner,DListEnd(list));
		 runner = DListNext(runner), ++elements_counter
		)
		{/* empty body */}
	
	return elements_counter;
}

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);	
	return DListIsSameIter(DListBegin(list),DListEnd(list));
}

int DListForEach(dlist_iter_t from,
				 dlist_iter_t to,
				 action_func func, 
				 void *param	)
{
	dlist_iter_t runner = from;
	int exit_status = 0;
	
	assert(NULL != from);
	assert(NULL != to);	
	
	while (!DListIsSameIter(runner,to) && 0 == exit_status)
	{
		exit_status = func(runner->data, param);	
		runner = DListNext(runner);
	}
	
	return exit_status;
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, cmp_func cmp,
					   const void *data)
{
	dlist_iter_t runner = from;
	
	while (!DListIsSameIter(runner,to) && 0 != cmp(runner->data, data))
	{
		runner = DListNext(runner);
	}
	
	return runner;
}				

dlist_iter_t DListPushFront(dlist_t *list, const void *data)
{
	return DListInsert(list, DListBegin(list), (void *)data);
}

/* wrapper for the pop functions: pops iter and returns its data */
static void *DListPopIter(dlist_iter_t iter_to_pop)
{
	void *data = DListIterGetData(iter_to_pop);
	
	DListRemove(iter_to_pop);
		
	return data;
}

void *DListPopFront(dlist_t *list)
{		
	assert(NULL != list);	
	return DListPopIter(DListBegin(list));
}

dlist_iter_t DListPushBack(dlist_t *list, const void *data)
{
	assert(NULL != list);	
	return DListInsert(list, DListEnd(list), (void *)data);
}

void *DListPopBack(dlist_t *list)
{
	assert(NULL != list);
	return DListPopIter(DListBack(DListEnd(list)));
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->next;
}

dlist_iter_t DListBack(dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->prev;
}

void *DListIterGetData(dlist_iter_t iter)
{
	assert(NULL != iter);
	return iter->data;
}

dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert(NULL != dlist);
	return dlist->dummy_begin->next;
}

dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(NULL != dlist);
	return dlist->dummy_end;
}

int DListIsSameIter(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	return (iter1 == iter2);
}

dlist_iter_t DListSplice(dlist_iter_t iter_dest, dlist_iter_t iter_src_start, 
						 dlist_iter_t iter_src_end)
{
	dlist_iter_t src_last_inclusive_node = DListBack(iter_src_end);
	
	/* mend the pointers in src before removing its nodes */
	iter_src_start->prev->next = iter_src_end;
	iter_src_end->prev = iter_src_start->prev;
	
	/* connect dest to first src iter */
	iter_dest->prev->next = iter_src_start;
	iter_src_start->prev = iter_dest->prev;
	
	/* connect dest to last src iter */
	iter_dest->prev = src_last_inclusive_node;
	src_last_inclusive_node->next = iter_dest;
	
	return iter_dest;	
}
