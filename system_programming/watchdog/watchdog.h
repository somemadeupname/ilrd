/****************************************
 * Title  : Watchdog				    *
 * Author : Dandan Ogni                 *
 * Group  : OL712                       *
 * Date   : 28/10/2019               	*
 ****************************************/

#ifndef __OL712_WATCHDOG_H
#define __OL712_WATCHDOG_H

#include <time.h> /* time_t */

/*
 * Set watchdog to resuscitate the calling process if needed
 * @argv: main's argv
 * @interval: interval in secs for sending signals between user process and
 *			  watchdog. must be at least 1.
 * Return: 0 if success, non-zero if failed
 * Errors: if argv[0] is not the process's executable, behaviour is undefined.
 *         if you call WDMakeMeImmortal twice without WDDoNotResuscitate,
 *		   behaviour is undefined.
 * Note: while watchdog is active, the singals SIGUSR1 and SIGUSR2 are used
 *		 by the watchdog. Using these signals in the user's program could
 *       cause unexpected behaviour.
 */
int WDMakeMeImmortal(char *argv[], time_t interval);

/*
 * Unset watchdog
 * Return: none
 * Errors: if you call WDDoNotResuscitate without calling WDMakeMeImmortal,
 *		   behaviour is undefined.
 * Note: you must call WDDoNotResuscitate after a call to WDMakeMeImmortal,
 *		 even if the process was resuscitated.
 */
void WDDoNotResuscitate(void);

#endif /* __OL712_WATCHDOG_H */

