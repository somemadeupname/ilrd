#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "ws5.h"


int main(int argc, char *argv[])
{
	command action = del;
	char user_input[USER_INPUT_BUFFER_SIZE];
	size_t event_index = 0;
	char *filename = NULL;
	int result = 0;
	struct Event events[NUM_OF_EVENTS]; /* initialize array of Events */	
	
	if (2 != argc) /* print error if incorrect number of arguments*/
	{
		fprintf(stderr, "Please insert a filename when running the program.\n");
		return(1);
	}
	
	assert (NULL != argv[1]);

	filename = argv[1]; /* insert filename into argv*/
	
	/* initializing the events structs per event */
	events[del].command_string = REMOVE_COMMAND;
	events[del].compare_function = DoStringsMatch;
	events[del].action_function = RemoveFile;
	
	events[count].command_string = COUNT_COMMAND;
	events[count].compare_function = DoStringsMatch;
	events[count].action_function = CountLines;	

	events[exit].command_string = EXIT_COMMAND;
	events[exit].compare_function = DoStringsMatch;
	events[exit].action_function = ExitProgram;	
	
	events[pre_append].command_string = PREAPPEND_COMMAND;
	events[pre_append].compare_function = DoCharsMatch;
	events[pre_append].action_function = PreAppend;
	
	/* THIS PROGRAM ONLY WORKS IF THIS ACTION
	IS ALWAYS THE LAST ONE IN THE EVENTS ARRAY. 
	To add additional events add them BEFORE this action */
	events[append_default].command_string = DEFAULT_COMMAND;
	events[append_default].compare_function = IsDefaultCompare;
	events[append_default].action_function = AppendToFile;	
	
	/* print out usage instructions */
	PrintUserInstructions(filename);


	/* as long as the user doesn't type in the exit command continue 
	iterating over the event loop */	
	while (exit != action)
	{
		result = scanf ("%s", user_input);  /* make sure doesn't fail TODO */
		if (EOF == result)
		{
			perror("scanf failed.\n");
			return (-1);
		}
		
		printf("User_input is %s\n", user_input); /* for testing purpases TODO */	
		
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
