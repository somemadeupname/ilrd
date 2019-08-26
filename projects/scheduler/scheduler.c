
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

#include "scheduler.h"
#include "task.h"

struct scheduler
{
	pqueue_t *queue;
	/*compare?*/
};

/* return if scheduler is empty */ /* TODO test */
int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQueueIsEmpty(scheduler->queue);
}

/* return number of scheduled tasks */ /* TODO test */
size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQueueSize(scheduler->queue);
}

/* clear scheduler tassk while keeping it valid */
void SchedulerClear(scheduler_t *scheduler) /* TODO test */
{
	assert(NULL != scheduler);
	
	PQueueErase(scheduler->queue);
}

