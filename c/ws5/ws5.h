#include <stdio.h>

#define NEW_LINE '\n'
#define USER_INPUT_BUFFER_SIZE 80
#define LINE_BUFFER_SIZE 256
#define NUM_OF_EVENTS 5

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m\n");
#define START_GREEN printf("\033[1;32m");
#define END_GREEN printf("\033[0m\n");
#define REMOVE_COMMAND "-remove"
#define COUNT_COMMAND "-count"
#define EXIT_COMMAND "-exit"
#define PREAPPEND_COMMAND "<"
#define DEFAULT_COMMAND ""

typedef enum
{
	del, count, exit, pre_append, append_default
} command;


/***************** compare functions forward declarations *****************/

int DoStringsMatch(const char *s1, const char *s2);
int DoCharsMatch(const char *s1, const char *s2);
int IsDefaultCompare();


/***************** action functions forwatd declarations *****************/

command RemoveFile(const char *filename);
command CountLines (const char *filename);
command AppendToFile(const char *filename, const char *text_to_append);
command PreAppend (const char *filename, char *text_to_preappend);
command ExitProgram ();

/*********************Other Functions Declarations**************************/
void PrintUserInstructions(const char *filename);

struct Event
{
	const char* command_string;
	int (*compare_function)(/*const char *, const char **/);
	/*TODO should these be * or no *?*/
	command (*action_function)(/*const char *, const char **/);
};
