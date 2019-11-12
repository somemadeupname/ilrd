#include "service_func.h"

int main(argc, argv /*FIXME*/)
	
	setenv(WATCHDOG_ENV, "1", OVERWRITE);	
	
	
	struct sigaction alive_signal;
	struct sigaction stop_watching_me;	
	
	if (FAIL ==	InitSigaction(SIGUSR1, &alive_signal, AliveHandler))
	{
		return FAIL;	
	}
	
	if (FAIL ==	InitSigaction(SIGUSR2, &stop_watching_me, StopWatchingHandler))
	{
		return FAIL;	
	}
	
	
	/*
	
	TODO 
	Init Scheduler with two tasks
	sempost : say to user that i'm ready
	
	POST(watchdog)
	*/
