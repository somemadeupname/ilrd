/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Hila	    *
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
};

queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	queue->dummy = SListCreateNode(NULL, NULL);
	if  (NULL == queue->dummy)
	{
		free(queue); queue = NULL;
		return NULL;
	}
	
	queue->start = queue->dummy;
	queue->size = 0;
	
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	SListFreeAll(queue->start); queue->start = NULL;
	free(queue); queue = NULL;
}

int QueueEnqueue(queue_t *queue, const void *data)
{
	slist_node_t *node_to_enqueue = NULL;
	
	assert(NULL != queue);
	
	node_to_enqueue = SListCreateNode((void *)data, NULL);	
	
	if (NULL == node_to_enqueue)
	{
		return FAIL;
	}	
	
	node_to_enqueue = SListInsert(queue->dummy, node_to_enqueue);
	
	queue->dummy = node_to_enqueue->next_node;
	
	++queue->size;
	
	return SUCCESS;
}

int QueueDequeue(queue_t *queue)
{
	slist_node_t *node_to_remove = NULL;	
	
	assert(NULL != queue);
	
	if (QueueIsEmpty(queue))
	{
		return FAIL;
	}

	node_to_remove = SListRemove(queue->start);
	
	free(node_to_remove); node_to_remove = NULL;
	
	--queue->size;
	
	return SUCCESS;
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);	
	return queue->start->data;
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);	
	return queue->size;
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);	
	return (0 == queue->size);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	slist_node_t *src_new_dummy = NULL;
	
	assert(NULL != src);
	assert(NULL != dest);
	assert(src != dest);
	
	dest->dummy->next_node = src->start;
	src_new_dummy = SListRemove(dest->dummy);
	
	dest->dummy = src->dummy;
	
	src->start = src_new_dummy;
	
	dest->size += src->size;
	src->size = 0; /* src is now empty */
	
	return dest;
}
