/******************************************************************************/
/* TODO TODO TODO TODO TODO
	MOVE TO H FILE */
	
#include <assert.h> /* assert */
#include <stdlib.h> /* XXX */
#include <signal.h> /* sig_atomic_t, kill, SIGNALS*/

#include "watchdog.h"    /* watchdog_funcs */

#define SAMPLE_FREQ(x) ((x) * 2l) 
const char *WATCHDOG_ENV = "WATCHDOG_ENV";
const char *WATCHDOG_EXEC_PATH = "./watchdog.out";
const int OVERWRITE = 1; /* for setenv arg #3 */

typedef struct sched_args
{
	char **argv;
	pid_t *pid;
} sched_args_t;

enum {ERROR = -1, SUCCESS = 0, FAIL = 1};
enum {FALSE, TRUE};
enum {WD_NOT_EXISTS = '0', WD_EXISTS = '1'};



/* GLOBALS */

sig_atomic_t g_user_alive_flag = 0;
sig_atomic_t g_watchdog_alive_flag = 0;

pid_t g_watchdog_pid = 0; /*update tasks when watchdog process change*/
sem_t *user_semaphore = NULL;

scheduler_t *g_user_scheduler = NULL;
scheduler_t *g_watchdog_scheduler = NULL;

/******************************************************************************/

/* Init signal handling */	
int InitSigaction(int signum, struct sigaction *sa,
						 void(*handler)(int signum))
{
	memset(&sa, 0 sizeof(struct sigaction));
	
	sa.sa_handler = handler;
    sa.sa_flags = 0; 
    sigemptyset(&sa.sa_mask);

	if (ERROR == sigaction(signum, &sa, NULL))
	{
		return FAIL;
	}	
	
	return SUCCESS;
}

scheduler_t *InitScheduler(sched_args_t *sched_args, time_t interval)
{
	scheduler_t *scheduler = SchedulerCreate();
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	alive_task_uid = SchedulerAddTask(scheduler,
									  sched_args->pid,
									  TaskAlive,
  							          time(NULL),
  							          interval);
										   
	if (UIDIsSame(BAD_UID, alive_task_uid))
	{
		SchedulerDestroy(scheduler);
		return NULL;
	}

	revive_task_uid = SchedulerAddTask(scheduler,
									   sched_args,
									   TaskRevive,
    							       time(NULL),
    							       SAMPLE_FREQ(interval));

	if (UIDIsSame(BAD_UID, revive_task_uid))
	{
		SchedulerDestroy(scheduler);
		return NULL;
	}

	return scheduler;	
}


int ShouldCreateWatchdog(void)
{
	char *watchdog_env = getenv(WATCHDOG_ENV);
	
	if ((NULL == watchdog_env) || (WD_NOT_EXISTS == *watchdog_env) /* TODO should return TRUE/FALSE? */
	{
		return FALSE;
	}
	
	return TRUE;
}

/*Task 1*/
task_status TaskAlive(void *pid)
{
	assert(NULL != pid);
	
	kill(*(pid_t *)pid, SIGUSR1);
	
	return SCHED_REPEAT;
}


/*Task 2*/
task_status TaskRevive(void *sched_args)
{ 
	assert(NULL != sched_args);
	
	char *watchdog_env = getenv(WATCHDOG_ENV);
	
	if (WD_EXISTS == *watchdog_env) /* wd proccess */
	{
		if (g_user_alive_flag) /* flag is on */ 
		{
			g_user_alive_flag = 0;
		}
		else /* flag is off */ 
		{
			pid_t watchdog_pid = 0;
			
			kill(*(sched_args_t *)sched_arg->pid, SIGKILL); /*XXX should confirm kill? */
			
			watchdog_pid = fork();
			
			if (0 < watchdog_pid) /* parent exec to user.out */
			{
				g_watchdog_pid = watchdog_pid;
				
				execvp(*(sched_args_t *)sched_arg->argv[0],
					  (sched_args_t *)sched_arg->argv); /*XXX first arg correct? */
			}
			
			user_semaphore = sem_open("check_user_semaphore", O_CREAT);
			sem_wait(user_semaphore);
			sem_close(user_semaphore);
		}
	}
	else /* user proccess */
	{
		if (g_watchdog_alive_flag)
		{
			g_watchdog_alive_flag = 0;
		}
		else
		{
			char *arg_list[] = {WATCHDOG_EXEC_PATH , NULL};
			pid_t watchdog_pid = 0;

			kill(g_watchdog_pid, SIGKILL); /*XXX should confirm kill? */
			setenv(WATCHDOG_ENV, "0", OVERWRITE);
			
			watchdog_pid = fork();
			
			if (0 < watchdog_pid) /* parent proccess */
			{
				watchdog_semaphore = sem_open("check_watchdog_semaphore",
											                        O_CREAT);
				sem_wait(user_semaphore); /* TODO watchdog.out should post 
											 this semaphore before running scheduler */
				sem_close(user_semaphore);
				
			}
			else if (0 == watchdog_pid) /* child process */
			{
				g_watchdog_pid = getpid();
				execvp(arg_list[0], arg_list);
			}
		}
	}
	
	return SCHED_REPEAT;
}
	
