
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "task.h"
#include "../../ds/uid/uid.c"

#define UNUSED(x) (void)(x)

struct task
{
	void *param;
	task_func func;
	time_t time;
	time_t interval;
	task_uid_t uid;
};

task_t *TaskCreate(void *param, task_func func, time_t time, time_t interval)
{
	task_t *task = NULL;
	assert (NULL != func);
	
	task = (task_t *)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return NULL;
	}
	
	task->param = param;
	task->func = func;
	task->time = time;
	task->interval = interval;
	task->uid = UIDCreate();
	
	assert(!UIDIsSame(task->uid,BAD_UID));
	
	return task;	
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	free(task); task = NULL;
}

task_status TaskExec(task_t *task)
{
	assert (NULL != task);
	
	return task->func(task->param);
}

int TaskIsMatch(void *task, const void *task_uid, void *param)
{
	UNUSED(param);
	assert (NULL != task);
	assert (NULL != task_uid);
	
	return UIDIsSame(((task_t *)task)->uid, *(task_uid_t *)task_uid);
}

task_uid_t TaskGetUID(const task_t *task)
{
	assert (NULL != task);	
	
 	return task->uid;
}

time_t TaskGetTime(const task_t *task)
{
	assert (NULL != task);
	
	return task->time;
}

int TaskIsBefore(const task_t *new_task, const task_t *scheduled_task, 
				 void *param)
{
	UNUSED(param);
	assert(NULL != new_task);
	assert(NULL != scheduled_task);
		
	if (TaskGetTime(new_task) <= TaskGetTime(scheduled_task))
	{
		return 1;
	}
	
	return 0;
}				 

void TaskUpdateTime(task_t *task)
{
	assert (NULL != task);
	task->time += task->interval;
}
