
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Dandan	    *
 *	 Status   : Sent	    *
 ****************************/

#include <stdlib.h> /*malloc free*/
#include <assert.h> /* assert */

#include "pqueue.h"
/*#include "../sorted_list/sorted_list.h"*/

#define UNUSED(x) (void)(x)

typedef struct params
{
	cmp_priority cmp;
	void *param;
} params_t;

struct pqueue
{
	sorted_list_t *list;
	params_t *params;
};

/* HELPER FUNCTIONS */
/* comparator for the sorted list */
static int IsBefore(void *d1, void *d2, const void *pqueue)
{
	pqueue_t *non_const_pq = (pqueue_t *)pqueue;
	
	assert (NULL != pqueue);
	
	return (0 < non_const_pq->params->cmp(d1, d2, non_const_pq->params->param));
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
	
	pqueue->params = (params_t *)malloc(sizeof(params_t));
	if (NULL == pqueue->params)
	{
		free(pqueue->list); pqueue->list = NULL;
		free(pqueue); pqueue = NULL;
		return NULL;
	}
	
	pqueue->params->cmp = is_lower_priority;
	pqueue->params->param = (void *)param;
	
	return pqueue;	
}

void PQueueDestroy(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	SortedListDestroy(pqueue->list); pqueue->list = NULL;
	free(pqueue->params); pqueue->params = NULL;
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
/* erase data if found in pqueue */
void *PQueueErase(pqueue_t *pqueue, is_match func, void *data, void *param)
{
	sorted_list_iter_t from = {NULL};
	sorted_list_iter_t to = {NULL};
	sorted_list_iter_t data_iter = {NULL};
	void *data_to_remove = NULL;
	UNUSED(param);
	
	assert(NULL != pqueue);
	
	from = SortedListBegin(pqueue->list);
	to = SortedListEnd(pqueue->list);
	
	data_iter = SortedListFindIf(from,to,func,data,NULL);
	
	if (SortedListIsSameIter(data_iter, to))
	{
		return NULL;
	}
	data_to_remove = SortedListGetData(data_iter);
	
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
	{ /* Empty Body */ }	
}
