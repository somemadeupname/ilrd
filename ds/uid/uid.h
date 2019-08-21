#include <time.h>
#include <stddef.h>

extern const uid_t BAD_UID;

typedef struct uid uid_t;

struct uid
{
	time_t uid;
	size_t counter;
};

/*
 * Create new UID
 * Param : none
 * Return : uid
 * Errors : apoch overflow at 2038 
 */
uid_t UIDCreate(void)

/*
 * Compares two UIDs' 
 * Param uid1 : UID
 * param uid2 : UID
 * Return : 1 if same, 0 otherwise
 * Errors : none
 */
int UIDIsSame(uid_t uid1, uid_t uid2);


