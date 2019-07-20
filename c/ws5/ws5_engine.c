#include <stdio.h>
#include "ws5.h"


int main(int argc, char *argv[])
{
	
	/*nul asserts*/
	
	command action = del;
	/*
	1. check argv to see it's legit
	2. check argc == 2 
	
	*/
	char user_input[USER_INPUT_BUFFER_SIZE];
	size_t event_index = 0;
	char *filename = argv[1]; /* insert filename into argv*/
	struct Event events[NUM_OF_EVENTS]; /* initialize array of Events */
	
	/* initializing the events structs per event */
	events[0].command_string = REMOVE_COMMAND;
	events[0].compare_function = DoStringsMatch;
	events[0].action_function = RemoveFile;
	
	events[1].command_string = COUNT_COMMAND;
	events[1].compare_function = DoStringsMatch;
	events[1].action_function = CountLines;	

	events[2].command_string = EXIT_COMMAND;
	events[2].compare_function = DoStringsMatch;
	events[2].action_function = ExitProgram;	
	
	events[3].command_string = PREAPPEND_COMMAND;
	events[3].compare_function = DoCharsMatch;
	events[3].action_function = CountLines; /* change to relevant function TODO*/
	
	events[4].command_string = DEFAULT_COMMAND;
	events[4].compare_function = IsDefaultCompare;
	events[4].action_function = AppendToFile;	
	
	/* print out usage instructions */
	PrintInstructions(filename);


	
	while (exit != action)
	{
		scanf ("%s", user_input);  /* make sure doesn't fail TODO */
		printf("User_input is %s\n", user_input); /* for testing purpases TODO */	
		for (event_index = 0; event_index < NUM_OF_EVENTS; ++event_index)
		{
			if ( events[event_index].compare_function
			(events[event_index].command_string, user_input) )
				{
					action =
					events[event_index].action_function(filename, user_input);
					break;
				}
		}
	}
	
	return 0;
}
