#include <stdio.h> /* printf, fprintf, EOF,  */
#include <assert.h> /* assert */
#include "ws5.h"

/*********************Event struct declarations**************************/
struct Event
{
	const char* command_string;
	int (*compare_function)(const char *, const char *);
	func_exit_status (*action_function)(const char *, const char *);
};


static 	struct Event events[NUM_OF_EVENTS] =  /* initialize array of Events */	

{	/* initializing the events structs per event */
{ REMOVE_COMMAND, DoStringsMatch, RemoveFile },
{ COUNT_COMMAND, DoStringsMatch, CountLines },
{ EXIT_COMMAND, DoStringsMatch, ExitProgram },
{ PREAPPEND_COMMAND, DoCharsMatch, PreAppend },

/* THIS SHOULD ALWAYS BE THE LAST ELEMENT OF THE EVENTS ARRAY */
{ DEFAULT_COMMAND, IsDefaultCompare, AppendToFile }
};
									


int main(int argc, char *argv[])
{
	func_exit_status action = success;
	char user_input[USER_INPUT_BUFFER_SIZE];
	size_t event_index = 0;
	char *filename = NULL;
	int result = 0;

	
	if (2 != argc) /* print error if incorrect number of arguments*/
	{
		fprintf(stderr, "Please insert a filename when running the program.\n");
		return(1);
	}
	
	assert (NULL != argv[1]);

	filename = argv[1]; /* insert filename into argv*/
	
	/* print out usage instructions */
	PrintUserInstructions(filename);


	/* as long as the user doesn't type in the exit command continue 
	iterating over the event loop */	
	while (exit != action)
	{
		result = scanf ("%s", user_input); 
		if (EOF == result)
		{
			perror("scanf failed in main.\n");
			return (-1);
		}
		
		/* The event loop */
		for (event_index = 0; event_index < NUM_OF_EVENTS; ++event_index)
		{
			/* comparing the user input with the known commands user the 
			events' invidividual comparison functions  */
			if ( events[event_index].compare_function
			(events[event_index].command_string, user_input) )
				{
					/* once a compare function of an event returns true - 
					execute the relevant action user the event's action
					function */
					action =
					events[event_index].action_function(filename, user_input);
					break;
				}
		}
	}
	return 0;
}
