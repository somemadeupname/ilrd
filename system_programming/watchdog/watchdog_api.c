#include "service_func.h"


int WDMakeMeImmortal(char *argv[], time_t interval)
{
	struct sigaction alive_signal;
	sched_args_t user_sched_args = {NULL};
	
	if (FAIL ==	InitSigaction(SIGUSR1, &alive_signal, AliveHandler))
	{
		return FAIL;	
	}
	
	if (ShouldCreateWatchdog())
	{
		pid_t watchdog_pid = fork();
		
		if (ERROR == watchdog_pid)
		{
			return FAIL;
		}
		else if (0 == watchdog_pid)
		{
			char *arg_list[] = {"./watchdog.out", NULL};
			execvp(arg_list[0], arg_list);
			
			return FAIL;
		}
		else
		{
			g_watchdog_pid = watchdog_pid; /*XXX is it true ?*/
		}
	}
	
	user_sched_args->pid = g_watchdog_pid;
	user_sched_args->argv = argv;
	
	g_user_scheduler = InitScheduler(&user_sched_args, interval);
	if (NULL == g_user_scheduler)
	{
		return FAIL;
	}
	
	OPEN_SEM
	
	pthread Create ---> Wrapper (semwait(watchdog) + Run Scheduler)
	
}


void WDDoNotResuscitate(void);
