#ifndef __OL71_PQUEUE_H
#define __OL71_PQUEUE_H

enum { PQUEUE_SUCCESS,
	   PQUEUE_FAIL };

struct pqueue
{
	sorted_list_t *list;
}

/*
 * Create priority queue.
 * Fail: NULL if allocation failed.
 */
pqueue_t *PQueueCreate(cmp_func cmp);

void PQueueDestroy();

int PQueueIsEmpty(const pqueue_t *queue);

size_t PQueueSize(const pqueue_t *queue);

int PQueueEnqueue(pqueue_t *queue);

int PQueueDequeue(pqueue_t *queue);

void *PQueuePeek(const pqueue_t *queue);

int PQueueErase(pqueue_t *queue, const void *priority);

int PQueueClear(pqueue_t *queue);

#endif /* __OL71_PQUEUE_H */
