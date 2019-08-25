#ifndef __OL71_SCHEDULER_H
#define __OL71_SCHEDULER_H

#include "task.h"

scheduler_t *SchedulerCreate(/*TODO*/);

void SchedulerDestroy(scheduler_t *scheduler);

task_uid_t SchedulerAddTask();

task_uid_t SchedulerRemoveTask(scheduler_t *scheduler, task_uid_t *task_to_remove);

void SchedulerStop(scheduler_t *scheduler);

void SchedulerStart(scheduler_t *scheduler);

int SchedulerIsEmpty(const scheduler_t *scheduler);

size_t SchedulerSize(const scheduler_t *scheduler);

void SchedulerClear(scheduler_t *scheduler);

#endif /* __OL71_SCHEDULER_H */
