
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 	*
 *	   Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */
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
	dlist_iter_t next;
	dlist_iter_t prev;	
};

/* Forward Declaration */
static void *DListPopIter(dlist_t *list, dlist_iter_t iter_to_pop);

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
	dlist->dummy_end = DListCreateNode(NULL, dlist->dummy_begin, NULL);
	dlist->dummy_begin->next = dlist->dummy_end;

	return dlist;
}

void DListDestroy(dlist_t *list)
{
	dlist_iter_t runner = list->dummy_begin;
	dlist_iter_t temp_iter_to_free = NULL;
	
	assert(NULL != list);
	
	while (runner != list->dummy_end)
	{
		temp_iter_to_free = runner;
		runner = runner->next;
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

dlist_iter_t DListRemove(dlist_t *list, dlist_iter_t iter_to_remove)
{
	dlist_iter_t following_iter = NULL;	
	
	/*assert(DListEnd(list) != iter_to_remove);*/
	assert(NULL != iter_to_remove);
	assert(NULL != list);
	
	if (DListEnd(list) == iter_to_remove)
	{
		return DListEnd(list);
	}
	
	iter_to_remove->prev->next = iter_to_remove->next;
	iter_to_remove->next->prev = iter_to_remove->prev;
		
	following_iter = iter_to_remove->next;
	
	free(iter_to_remove);
	
	return following_iter;
}

size_t DListSize(const dlist_t *list)
{
	size_t elements_counter = 0;
	dlist_iter_t runner = NULL;
	
	assert(NULL != list);
	
	for (runner = DListBegin(list);
		 runner != DListEnd(list);
		 runner = DListNext(runner), ++elements_counter
		)
		{/* empty body */}
	
	return elements_counter;
}

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);	
	return (list->dummy_begin->next == list->dummy_end);
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func func, 
				 void *param)
{
	dlist_iter_t runner = from;
	int exit_status = 0;
	
	while (runner != to)
	{
		exit_status = func(runner->data, param);
		if (0 != exit_status)
		{
			return exit_status;
		}
		
		runner = DListNext(runner);
	}
	return exit_status;
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, cmp_func cmp,
					   const void *data)
{
	dlist_iter_t runner = from;
	int exit_status = 0;
	
	while (runner != to)
	{
		exit_status = cmp(runner->data, data);
		if (0 == exit_status)
		{
			return runner;
		}
		runner = DListNext(runner);
	}
	return to;
}				

dlist_iter_t DListPushFront(dlist_t *list, const void *data)
{
	void *temp_data = (void *) data;
	return DListInsert(list, DListBegin(list), temp_data);
}

/* wrapper for the pop functions */
static void *DListPopIter(dlist_t *list, dlist_iter_t iter_to_pop)
{
	dlist_iter_t iter = iter_to_pop;
	void *data = iter->data;
	
	assert(NULL != list);
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
		
	return data;
}

void *DListPopFront(dlist_t *list)
{		
	return DListPopIter(list, DListBegin(list));
}

dlist_iter_t DListPushBack(dlist_t *list, const void *data)
{
	void *temp_data = (void *) data;
	return DListInsert(list, DListEnd(list), temp_data);
}

void *DListPopBack(dlist_t *list)
{
	return DListPopIter(list, DListEnd(list)->prev);
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
	return (iter1 == iter2); /* comparison of pointers */
}

/*
 * Insert part of list before iter_dest 
 * Param iter_dest: pointer to the list for adding.
 * Param iter_src_start: pointer to beginning of source
 * Param iter_src_end: pointer to end of source (not included) - must be after
					   iter_src_start.
 * Return: pointer to iter_dest
 * Errors: if iter_src_end is before iter_src_start, behaviour is undefined
 */
dlist_iter_t DListSplice(dlist_iter_t iter_dest, dlist_iter_t iter_src_start, 
						 dlist_iter_t iter_src_end)
{
	dlist_iter_t src_last_inclusive_node = DListBack(iter_src_end);
	
	iter_src_start->prev->next = iter_src_end;
	iter_src_end->prev = iter_src_start->prev;
	
	iter_dest->prev->next = iter_src_start;
	iter_src_start->prev = iter_dest->prev;
	
	iter_dest->prev = src_last_inclusive_node;
	src_last_inclusive_node->next = iter_dest;
	
	return iter_dest;	
	
}
