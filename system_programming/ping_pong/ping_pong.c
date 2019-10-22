
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#define _POSIX_C_SOURCE 200809L /* sigaction */
/*************************************************************************
 *																		 *
 *				      			INCLUDES								 *
 *							 											 *
 ************************************************************************/

#include <signal.h> /* kill pid_t sigaction */
#include <sys/types.h> /* sig_atomic_t */
#include <unistd.h> /* sleep fork getppid */
#include <stdio.h> /* perror printf */

#include "ping_pong.h"

#define UNUSED(x) (void)(x)

const int FAIL = -1;

volatile sig_atomic_t flag = 1;

/*************************************************************************
 *																		 *
 *				      		STATIC FUNCTIONS							 *
 *							 											 *
 ************************************************************************/

static int Action(const char *str, int sig, pid_t pid)
{
	printf("%s\n", str);
	flag = 0;
	if (FAIL == kill(pid, sig))
	{
		perror("kill");
		return (1);
	}
	
	sleep(1);
	
	return 0;
}

static int InitSigaction(int sig, struct sigaction *sa)
{
	if (FAIL == sigaction(sig, sa, NULL))
	{
		perror("sigaction");
		return (1);
	}
	
	return 0;
}

static void SigUsrHandler(int num)
{
	UNUSED(num);
	flag = 1;
}

/*************************************************************************
 *																		 *
 *				      		THE MAIN FUNCTION							 *
 *							 											 *
 ************************************************************************/

int main()
{
	pid_t child_pid = 0;
	struct sigaction sa;
	sa.sa_handler = SigUsrHandler;
	sigemptyset(&sa.sa_mask);
	
	if (FAIL == InitSigaction(SIGUSR1, &sa))
	{
		return (1);
	}
	
	child_pid = fork();
	if (FAIL == child_pid)
	{
		perror("fork");
		return (1);
	}
	else if (0 == child_pid) /* the child process */
	{
		if (FAIL == InitSigaction(SIGUSR2, &sa))
		{
			return (1);
		}
		
		while (1)
		{
			if (flag)
			{
				if (1 == Action("Pong", SIGUSR1, getppid()))
				{
					return (1);
				}
			}
		}
	}
	else /* the parent process */
	{
		while (1)
		{
			if (flag)
			{
				if (1 == Action("Ping", SIGUSR2, child_pid))
				{
					return (1);
				}
			}
		}
	}
	
	return (0);
}

