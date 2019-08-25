
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Dandan	    *
 *	 Status   : Sent	    *
 ****************************/

#include "pqueue.h"
#include "../sorted_list/sorted_list.c"
#include "../sorted_list/sorted_list.h"

struct pqueue
{
	sorted_list_t *list;
	cmp_priority cmp;
	void *param;
};

/* HELPER FUNCTIONS */
/* comparator for the sorted list */
static int IsBefore(void *d1, void *d2, const void *pqueue)
{
	pqueue_t *non_const_pq = (pqueue_t *)pqueue;
	assert(NULL != pqueue);
	return (0 < non_const_pq->cmp(d1, d2, non_const_pq->param));
}

/* PQUEUE FUNCTIONS */

pqueue_t *PQueueCreate(cmp_priority is_lower_priority, const void *param)
{
	pqueue_t *pqueue = (pqueue_t *)malloc(sizeof(pqueue_t));
	if (NULL == pqueue)
	{
		return NULL;
	}
	
	pqueue->list = SortedListCreate(IsBefore, pqueue);
	if (NULL == pqueue->list)
	{
		free(pqueue); pqueue = NULL;
		return NULL;
	}
	
	pqueue->cmp = is_lower_priority;
	pqueue->param = (void *)param;
	
	return pqueue;	
}

void PQueueDestroy(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	SortedListDestroy(pqueue->list); pqueue->list = NULL;
	free(pqueue); pqueue = NULL;
}

/* add new element to pqueue */
int PQueueEnqueue(pqueue_t *pqueue, const void *data)
{
	assert(NULL != pqueue);
	
	if (SortedListIsSameIter(SortedListEnd(pqueue->list),
	    SortedListInsert(pqueue->list,data)))
	{
		return PQUEUE_FAILED;
	}
	
	return PQUEUE_SUCCESS;	
}

/* remove top priority element from pqueue */
void PQueueDequeue(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	assert(!PQueueIsEmpty(pqueue));
	
	SortedListPopFront(pqueue->list);
}

/* get pointer to data from top priority element */
void *PQueuePeek(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);	
	assert(!PQueueIsEmpty(pqueue));
	return SortedListGetData(SortedListBegin(pqueue->list));
}

/* get number of elements in queue */
size_t PQueueSize(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedListSize(pqueue->list);
}

/* return 1 if queue is empty, 0 otherwise */
int PQueueIsEmpty(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	return SortedListIsEmpty(pqueue->list);
}

/*
 * Erase iter from pqueue
 * Param pqueue : pointer to pqueue
 * Param func : is_match function to compare <data>
 * Param data : data to compare
 * Return: void pointer to data of erased iter
 * Errors: none    
 */
void *PQueueErase(pqueue_t *pqueue, is_not_match func, void *data)
{
	sorted_list_iter_t from = {NULL};
	sorted_list_iter_t to = {NULL};
	sorted_list_iter_t data_iter = {NULL};
	void *data_to_remove = NULL;
	
	assert(NULL != pqueue);
	
	from = SortedListBegin(pqueue->list);
	to = SortedListEnd(pqueue->list);
	
	data_iter = SortedListFindIf(from,to,func,data);
	
	data_to_remove = SortedListGetData(data_iter);
	if (NULL == data_to_remove)
	{
		return NULL;
	}
	
	SortedListRemove(data_iter);
	
	return data_to_remove;
}

void PQueueClear(pqueue_t *pqueue)
{
	sorted_list_iter_t cur = {NULL};
	sorted_list_iter_t end = {NULL};
	
	assert(NULL != pqueue);
	
	end = SortedListEnd(pqueue->list);
	
	for (cur = SortedListBegin(pqueue->list);
		!SortedListIsSameIter(cur,end);
		cur = SortedListRemove(cur))
		{ /* Empty Body */}	
}
