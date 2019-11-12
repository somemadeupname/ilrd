#include <stdio.h> /* fprintf */
#include <assert.h> /* assert */
#include <stdlib.h>
#include <string.h> /* strcmp */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork execvp */
#include <sys/wait.h> /* wait */

#define INPUT_BUFFER_SIZE 100
#define ARG_BUFFER_SIZE 40

const char *EXIT_COMMAND = "exit\n";
const char INVALID_INPUT_ERROR[] = "Invalid input.\n";
const char FGETS_ERROR[] = "fgets failed.\n";
const char FORK_ERROR[] = "fork failed.\n";

enum {SUCCESS, ERROR};

static void ParseArgs(char *input, char *my_argv[]);
static int ShouldRun(const char *input);

/* Spawn a child process running @program */
static int Spawn(char *program, char** arg_list)
{
	pid_t child_pid = 1;
	int *status = 0;
	
	child_pid = fork(); /* Duplicate this process. */
	
	if (-1 == child_pid)
	{
		fprintf(stderr, FORK_ERROR);
		return ERROR;	
	}
	
	else if (0 != child_pid) /* This is the parent process. */
	{
		wait(status);
	}
	else /* this is the child process */
	{
		execvp(program, arg_list);
		
		fprintf(stderr, INVALID_INPUT_ERROR);
		return ERROR;
	}
	
	return SUCCESS;
}
int main()
{	
	static char input[INPUT_BUFFER_SIZE] = {'\0'};
	static char *my_argv[ARG_BUFFER_SIZE] = {'\0'};
	
	if (NULL == fgets(input, INPUT_BUFFER_SIZE, stdin))
	{
		fprintf(stderr, FGETS_ERROR);
		return ERROR;
	}
	
	while (ShouldRun(input))
	{
		ParseArgs(input, my_argv);
		/* Spawn a child process */
		Spawn(my_argv[0], my_argv);
		
		if (NULL == fgets(input, INPUT_BUFFER_SIZE, stdin))
		{
			fprintf(stderr, FGETS_ERROR);
			return ERROR;
		}
	}
	
	return 0;
}

static int ShouldRun(const char *input)
{
	assert(NULL != input);
	
	return (0 != strcmp(EXIT_COMMAND, input));
}

static void ParseArgs(char *input, char *my_argv[])
{
	size_t i = 0;
	
	assert(NULL != input);
	assert(NULL != my_argv);
	
	my_argv[i] = strtok(input, " \n");
    while (NULL != my_argv[i])
    {
        ++i;
        my_argv[i] = strtok(NULL, " \n");
    }
}	
