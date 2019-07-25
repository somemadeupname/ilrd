#ifndef WS5_H
#define WS5_H

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
#define UNUSED(x) (void)(x)

/*******************func_exit_status enum declaration************************/
typedef enum
{
	exit, success, fail
} func_exit_status;


/***************** compare functions forward declarations *****************/

int DoStringsMatch(const char *s1, const char *s2);
int DoCharsMatch(const char *s1, const char *s2);
int IsDefaultCompare();

/***************** action functions forwatd declarations *****************/

func_exit_status RemoveFile(const char *filename, const char *input);
func_exit_status CountLines(const char *filename, const char *input);
func_exit_status AppendToFile(const char *filename, const char *text_to_append);
func_exit_status PreAppend(const char *filename, const char *text_to_preappend);
func_exit_status ExitProgram(const char *filename, const char *input);

/*********************Other Functions Declarations**************************/
void PrintUserInstructions(const char *filename);

#endif
