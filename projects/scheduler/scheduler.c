
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
 
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "task.h"
/*#include "../../ds/pqueue/pqueue.c"*/

#define TRUE 1
#define FALSE 0

#define UNUSED(x) (void)(x)

struct scheduler
{
	pqueue_t *queue;
	task_t *is_running;
	int continue_running;
};

/* helper functions */
/* TaskTimeComparator */
static int TaskCompareTime(void *task1, void *task2,
						   const void *param)
{
	UNUSED(param);
	assert(NULL != task1);
	assert(NULL != task2);
	
	if (TaskIsBefore((task_t *)task1,(task_t *)task2,NULL) == TaskIsBefore((task_t *)task2,(task_t *)task1,NULL))
	{
		return 0;
	}
	
	return TaskIsBefore((task_t *)task1,(task_t *)task2,NULL) ? (1) : (-1);
}

/* helpers for run */
static sched_status RescheduleTask(scheduler_t *scheduler, task_t *task);
static void SleepUntilExecution(time_t secs_until_next_execution);

/* create a scheduler */
scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->queue = PQueueCreate(TaskCompareTime, NULL);/* TODO check if this should be NULL*/
	if (NULL == scheduler->queue)
	{
		free(scheduler); scheduler = NULL;
		return NULL;
	}
	
	scheduler->is_running = NULL;
	scheduler->continue_running = 0;
	
	return scheduler;
}
/* destroy a scheduler */
void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	PQueueDestroy(scheduler->queue); scheduler->queue = NULL;
	free(scheduler); scheduler = NULL;	
}

/* Add task to scheduler */
task_uid_t SchedulerAddTask(scheduler_t *scheduler, void *func_param,
                   task_status (*task_func)(void *param), time_t time_in_sec,
                   time_t interval_in_sec)
{
	task_t *task_to_add = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != task_func);
	
	task_to_add = TaskCreate(func_param, task_func,
							 time_in_sec, interval_in_sec);
	if (NULL == task_to_add)
	{
		return BAD_UID;
	}
	
	if (PQUEUE_FAILED == PQueueEnqueue(scheduler->queue, task_to_add))
	{
		return BAD_UID;
	}
	
	return TaskGetUID(task_to_add);
}

/* Remove task from schedule */
sched_status SchedulerRemoveTask(scheduler_t *scheduler, task_uid_t task_uid)
{
	void *task_to_remove = NULL;
	assert(NULL != scheduler);
	
	task_to_remove = PQueueErase(scheduler->queue, TaskIsMatch, &task_uid, NULL);
	
	if (NULL == task_to_remove)
	{
		return SCHED_FAIL;
	}

	TaskDestroy(task_to_remove);

	return SCHED_SUCCESS;
}

/*
 * Stops executing tasks
 * Param scheduler : scheduler
 * Return: none
 * Errors: none
 */
void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->continue_running = FALSE;
}
/* make sure that sleeps works for the entire duration it's set to */
static void SleepUntilExecution(time_t secs_until_next_execution)
{
/*	time_t start_time = time(NULL);*/
	unsigned int seconds_left = (unsigned int) secs_until_next_execution;
	
	while (seconds_left > 0)
	{
		seconds_left = sleep(seconds_left);
	}
}

/*
 * Start executing tasks
 * Param scheduler : scheduler
 * Return: SCHED_SUCCESS for success, SCHED_FAIL otherwise
 * Errors: if rescheduling failed, stops and returns SCHED_FAIL
 */
sched_status SchedulerRun(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	scheduler->continue_running = TRUE;
	
	while((!SchedulerIsEmpty(scheduler) || scheduler->is_running) &&
										    TRUE == scheduler->continue_running)
	{
		scheduler->is_running = PQueuePeek(scheduler->queue);
		SleepUntilExecution(TaskGetTime(scheduler->is_running)-time(NULL));
		PQueueDequeue(scheduler->queue);
		if (SCHED_REPEAT == TaskExec(scheduler->is_running))
		{
			int status = RescheduleTask(scheduler, scheduler->is_running);
			if (SCHED_FAIL == status)
			{
				return SCHED_FAIL;
			}
		}
		else /* TaskExec returns SCHED_NO_REPEAT */
		{
			TaskDestroy(scheduler->is_running); scheduler->is_running = NULL; /* TODO is this where this should be?*/
		}
	}
	return SCHED_SUCCESS;
}

/* helper for run 
 * return SCHED_SUCCESS if rescheduling worked
 * 		  SCHED_FAIL if failed 									
 */
static sched_status RescheduleTask(scheduler_t *scheduler, task_t *task)
{
	assert(NULL != scheduler);
	assert(NULL != task);
	
	TaskUpdateTime(task);
	if (PQUEUE_FAILED == PQueueEnqueue(scheduler->queue,task))
	{
		return SCHED_FAIL;
	}
	return SCHED_SUCCESS;
}

/* return if scheduler is empty */
int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQueueIsEmpty(scheduler->queue) || (scheduler->is_running ? 1 : 0);
}

/* return number of scheduled tasks */
size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return PQueueSize(scheduler->queue) + (scheduler->is_running ? 1 : 0);
}

/* clear scheduler tasks while keeping it valid */
void SchedulerClear(scheduler_t *scheduler)
{
	void *cur_task_to_remove = NULL;
	assert(NULL != scheduler);
	
	while(!SchedulerIsEmpty(scheduler)) /*TODO what about the is_running task? */
	{
		cur_task_to_remove = PQueuePeek(scheduler->queue);
		free(cur_task_to_remove); cur_task_to_remove = NULL;
		PQueueDequeue(scheduler->queue);
	}
	
	PQueueClear(scheduler->queue);
}

