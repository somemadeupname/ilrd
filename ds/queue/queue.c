/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
 
#include <stdlib.h> /* malloc free */

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
		SListFreeAll(queue->base);
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
	
	node_to_enqueue = SListCreateNode((void*) data, queue->start);
	
	SListInsert(queue->dummy, node_to_enqueue);
	
	++queue->size;
	
	return SUCCESS;
}

int QueueDequeue(queue_t *queue)
{
}
