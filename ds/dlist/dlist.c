
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 	*
 *	   Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */
#include "dlist.h"

typedef struct dlist_node dlist_node_t;

struct dlist
{
	dlist_node_t *head;
	dlist_node_t *tail;
	dlist_node_t *dummy_end;
	dlist_node_t *dummy_begin;	
};

struct dlist_node
{
	void *data;
	dlist_iter_t next;
	dlist_iter_t prev;	
};

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

/*
 * Create new doubly linked list
 * Param : none
 * Return : pointer to new dlist
 * Errors : return NULL if allocation fails
 */
dlist_t *DListCreate(void)
{
	dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == dlist)
	{
		return NULL;
	}
	
	dlist->dummy_begin = DListCreateNode(NULL, NULL, NULL);
	dlist->head = dlist->dummy_begin;
	dlist->dummy_end = DListCreateNode(NULL, NULL, NULL);
	dlist->tail = dlist->dummy_end;
	
	return dlist;
}

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);	
	return (list->head == list->dummy_begin);
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
	return dlist->head;
}

dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(NULL != dlist);
	return dlist->dummy_end;
}
