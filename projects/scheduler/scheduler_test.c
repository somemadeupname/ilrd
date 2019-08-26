#include <stdio.h>
#include <assert.h>

#include "scheduler.h"
#include "task.h"
#include "/home/rd61/test/test_template.c"

#define TRUE 1
#define FALSE 0
#define UNUSED(x) (void)(x)
#define PLUS_X_SECS(x) (x += time)

/* Foward Declarations */

/* Helpers */
void PrintUID(uid_t uid);
task_status PrintSomethingNoRepeat(void *param);

/*Test Functions*/
void SchedulerCreateAndDestroy_test(); /* and size and isempty on empty scheduler */

void SchedulerAddRemoveTask_test();

void SchedulerClear_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	SchedulerCreateAndDestroy_test();
	
	SchedulerAddRemoveTask_test();
	
	SchedulerClear_test();
	
	return 0;
}

void SchedulerClear_test()
{
	scheduler_t *scheduler = SchedulerCreate();
	
	expect_size_t(SchedulerSize(scheduler),0,"SchedulerSize");	
	
	/* add five tasks */
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,2,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,4,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,5,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,6,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,8,0);
	
	expect_size_t(SchedulerSize(scheduler),5,"SchedulerClear_test");	
	
	SchedulerClear(scheduler);

	expect_size_t(SchedulerSize(scheduler),0,"SchedulerClear_test");
	
	expect_int(SchedulerIsEmpty(scheduler),TRUE, "SchedulerClear_test");
	
	/* add five tasks again - confirming that the scheduler is still valid */
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,2,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,4,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,5,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,6,0);
	SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,8,0);
	
	expect_size_t(SchedulerSize(scheduler),5,"SchedulerClear_test");		
	
	SchedulerClear(scheduler);
	
	SchedulerDestroy(scheduler);
}

void SchedulerAddRemoveTask_test()
{
	scheduler_t *scheduler = SchedulerCreate();
	
	uid_t uid_to_remove = SchedulerAddTask(scheduler,NULL,PrintSomethingNoRepeat,2,0);
	
	expect_int(SchedulerIsEmpty(scheduler),FALSE, "SchedulerIsEmpty");
	
	expect_size_t(SchedulerSize(scheduler),1,"SchedulerSize");	
	
	expect_int(SchedulerRemoveTask(scheduler,uid_to_remove), SCHED_SUCCESS, "SchedulerAddRemoveTask_test");
	
	expect_int(SchedulerIsEmpty(scheduler),TRUE, "SchedulerIsEmpty");
	
	expect_size_t(SchedulerSize(scheduler),0,"SchedulerSize");	
	
	SchedulerDestroy(scheduler);
}

void SchedulerCreateAndDestroy_test()
{
	scheduler_t *scheduler = SchedulerCreate();
	
	expect_int(SchedulerIsEmpty(scheduler),TRUE, "SchedulerIsEmpty");
	
	expect_size_t(SchedulerSize(scheduler),0,"SchedulerSize");
	
	SchedulerDestroy(scheduler);
}

/* Task Functions */
/* Print Something */
task_status PrintSomethingNoRepeat(void *param)
{
	printf("Print something\n");
	UNUSED(param);
	
	return SCHED_NO_REPEAT;
}
/* Print UID*/
void PrintUID(uid_t uid)
{
	printf("PrintUID\n");
	printf("%lu%lu\n", uid.uid,uid.counter);
}
