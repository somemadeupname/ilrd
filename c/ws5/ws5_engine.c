#include <stdio.h>
#include "ws5.h"


int main(int argc, char *argv[])
{
	command input = 0;
	/*
	1. check argv to see it's legit filename 
	
	*/
	
	struct Event events[5];
	
	events[0].command_string = "-remove";
	events[0].CmpFunc = DoStringsMatch;
	events[0].ActionFunc = ;
	
	return 0;
}
