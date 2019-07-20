#include <string.h> /* strcmp */
#include <assert.h> /* assert */
#include "ws5.h"

/* Compare functions */

int DoStringsMatch(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
		
	/* return 1 if strings match, otherwise return 0 */
	return !strcmp(s1,s2);
}

int DoCharsMatch(const char *s1, const char *s2)
{
	assert(NULL != c1);
	assert(NULL != c2);
	
	/* if chars are identical return 1. 0 otherwise. */
	return (*s1 == *s2);
}

/* Action functions */

command SomeAction(const char *s1)
{
	/* TODO remove this dummy */
		
