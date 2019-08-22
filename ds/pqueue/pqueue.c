
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
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

/* add new element to pqueue */
int PQueueEnqueue(pqueue_t *pqueue, const void *data)
{
	assert(NULL != pqueue);
	
	if (SortedListEnd(pqueue->list) == SortedListInsert(pqueue->list,data))
	{
		return PQUEUE_FAILED;
	}
	
	return PQUEUE_SUCCESS;	
}

/* remove top priority element from pqueue */
void PQueueDequeue(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	SortedListPopFront(pqueue->list);
}

/* get pointer to data from top priority element */
void *PQueuePeek(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);	
	return (SortedListGetData(SortedListBegin(pqueue->list)));
}

/* get number of elements in queue */
size_t PQueueSize(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	return (SortedListSize(pqueue->list));
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
void *PQueueErase(pqueue_t *pqueue, is_match func, void *data);

/*
 * Clear all elements from pq
 * Param  pqueue : pointer to pqueue
 * Return: none
 * Errors: none        
 */
void PQueueClear(pqueue_t *pqueue); /*TODO use ForEach with remove to clear?
										*/
