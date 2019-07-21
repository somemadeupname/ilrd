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
<<<<<<< HEAD
#define UNUSED(x) (void)(x)

/*******************func_exit_status enum declaration************************/
typedef enum
{
	exit, success, fail
} func_exit_status;
=======

typedef enum
{
	del, count, exit, pre_append, append_default
} command;
>>>>>>> 0eccd00fe7a4a926265616f16cd60fafc1d5394c


/***************** compare functions forward declarations *****************/

int DoStringsMatch(const char *s1, const char *s2);
int DoCharsMatch(const char *s1, const char *s2);
int IsDefaultCompare();

<<<<<<< HEAD
/***************** action functions forwatd declarations *****************/

func_exit_status RemoveFile(const char *filename, const char *input);
func_exit_status CountLines(const char *filename, const char *input);
func_exit_status AppendToFile(const char *filename, const char *text_to_append);
func_exit_status PreAppend(const char *filename, const char *text_to_preappend);
func_exit_status ExitProgram(const char *filename, const char *input);
=======

/***************** action functions forwatd declarations *****************/

command RemoveFile(const char *filename);
command CountLines (const char *filename);
command AppendToFile(const char *filename, const char *text_to_append);
command PreAppend (const char *filename, char *text_to_preappend);
command ExitProgram ();
>>>>>>> 0eccd00fe7a4a926265616f16cd60fafc1d5394c

/*********************Other Functions Declarations**************************/
void PrintUserInstructions(const char *filename);

<<<<<<< HEAD
/*********************Event struct declarations**************************/
struct Event
{
	const char* command_string;
	int (*compare_function)(const char *, const char *);
	func_exit_status (*action_function)(const char *, const char *);
=======
struct Event
{
	const char* command_string;
	int (*compare_function)(/*const char *, const char **/);
	/*TODO should these be * or no *?*/
	command (*action_function)(/*const char *, const char **/);
>>>>>>> 0eccd00fe7a4a926265616f16cd60fafc1d5394c
};
