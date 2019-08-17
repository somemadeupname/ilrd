/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
 
#include <stdlib.h> /* malloc free */

#include "../slist/slist.c" /* SListCreateNode SListFreeAll
							   SListInsert SListRemove 		*/

#include "queue.h"

struct queue
{
	slist_node_t *start;
	slist_node_t *dummy;
	size_t size;
}

queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue));
	if (NULL == queue)
	{
		return NULL;
	}
	queue->dummy = SListCreateNode(NULL, NULL);
	queue->start = queue->dummy;
	queue->size = 0;
	
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	if (NULL != queue)
	{
		SListFreeAll(queue->start);
	}
	free(queue); queue = NULL;
}

int QueueEnqueue(queue_t *queue, const void *data);
{
	slist_node_t *node_to_enqueue = NULL;	
	if (NULL == queue)
	{
		return FAIL;
	}
	
	node_to_enqueue = SListCreateNode((void*) data, queue->dummy);
	if (NULL == node_to_enqueue)
	{
		return FAIL;
	}	
	
	SListInsert(queue->dummy, node_to_enqueue);
	
	queue->dummy = node_to_enqueue->next_node;
	
	++queue->size;
	
	return SUCCESS;
}

int QueueDequeue(queue_t *queue)
{
	slist_node_t *node_to_remove = NULL;	
	if (NULL == queue)
	{
		return FAIL;
	}

	node_to_remove = SListRemove(queue->start);
	
	free(node_to_remove);
	
	--queue->size;
	
	return SUCCESS;
}

void *QueuePeek(const queue_t *queue)
{
	return queue->start->data;
}

size_t QueueSize(const queue_t *queue)
{
	return queue->size;
}

int QueueIsEmpty(const queue_t *queue)
{
	return (0 == queue->size);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != src);
	assert(NULL != dest);
	
	dest->dummy = src->start;
	
	src->start = dest->dummy;
	
	dest->size += src->size;
	src->size = 0; /* src is now empty */
	
	return dest;
}
