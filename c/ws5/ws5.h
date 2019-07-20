#include <stdio.h>


/* compare functions forward declarations */
int DoStringsMatch(const char *s1, const char *s2);
int DoCharsMatch(const char *s1, const char *s2);

typedef enum
{
	del, count, pre_append, exit, append/*default*/
} command;

struct Event
{
	const char* command_string;
	int (*compare_function)(const char *, const char *);
	/*TODO should these be * or no *?*/
	command (*action_function)(const char *);
};
