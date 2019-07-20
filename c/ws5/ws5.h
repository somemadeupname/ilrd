#include <stdio.h>

#define NEW_LINE '\n'
#define USER_INPUT_BUFFER_SIZE 80
#define NUM_OF_EVENTS 5

#define START_GREEN printf("\033[1;32m");
#define END_GREEN printf("\033[0m\n");
#define REMOVE_COMMAND "-remove"
#define COUNT_COMMAND "-count"
#define EXIT_COMMAND "-exit"
#define PREAPPEND_COMMAND "<"
#define DEFAULT_COMMAND ""

typedef enum
{
	del, count, pre_append, exit, append/*default*/
} command;


/***************** compare functions forward declarations *****************/

int DoStringsMatch(const char *s1, const char *s2);
int DoCharsMatch(const char *s1, const char *s2);
int IsDefaultCompare();


/***************** action functions forwatd declarations *****************/

command RemoveFile(const char *filename, const char* user_input);
command CountLines (const char *filename, const char* user_input);
command AppendToFile(const char *filename, const char *text_to_append);
command ExitProgram (const char *filename, const char *text_to_append);

/*********************Other Functions Declarations**************************/
void PrintInstructions(const char *filename);

struct Event
{
	const char* command_string;
	int (*compare_function)(const char *, const char *);
	/*TODO should these be * or no *?*/
	command (*action_function)(const char *, const char *);
};
