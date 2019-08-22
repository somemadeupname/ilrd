
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

#include "uid.h"

const uid_t BAD_UID = {-1,0};

/*
 * Create new UID
 * Param : none
 * Return : uid
 * Errors : epoch overflow after the year 2038.
 */
uid_t UIDCreate(void)
{
	uid_t uid;
	static time_t seconds_before;
	time_t seconds = time(NULL);
	static size_t counter = 0;
	
	if (seconds_before == seconds)
	{
		++counter;
	}
	else
	{
		counter = 0;
	}
	seconds_before = seconds;
	uid.uid = seconds;
	uid.counter = counter;
	
	return uid;
}

/*
 * Compares two UIDs' 
 * Param uid1 : UID
 * param uid2 : UID
 * Return : 1 if same, 0 otherwise
 * Errors : none
 */
int UIDIsSame(uid_t uid1, uid_t uid2)
{
	return (uid1.uid == uid2.uid) && (uid1.counter == uid2.counter);
}

