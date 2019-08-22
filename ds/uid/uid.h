#ifndef __OL71_UID_H
#define __OL71_UID_H

#include <time.h>
#include <stddef.h>

typedef struct uid uid_t;

extern const uid_t BAD_UID;

struct uid
{
	time_t uid;
	size_t counter;
};

/*
 * Create new UID
 * Param : none
 * Return : uid
 * Errors : epoch overflow at 2038 
 */
uid_t UIDCreate(void);

/*
 * Compares two UIDs' 
 * Param uid1 : UID
 * param uid2 : UID
 * Return : 1 if same, 0 otherwise
 * Errors : none
 */
int UIDIsSame(uid_t uid1, uid_t uid2);

#endif /*__OL71_UID_H*/

