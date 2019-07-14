#include <stdio.h>
#include <stdlib.h> /* atoi */
#include <assert.h>
#include "ws3_story.h"

#define FIRST_GENERAL (-1)

void Init_Generals (int* generals, const int num_generals)
{
	int gen_index = 0;
	
	for (gen_index = 0; gen_index < num_generals; ++gen_index )
	{
		*(generals + gen_index) = 1;
	}
}

void Print_Generals (int * generals, const int num_generals)
{
	int gen_index = 0;

	for (gen_index = 0; gen_index < num_generals; ++gen_index)
	{
		printf("%d", *(generals + gen_index));
	}
	printf("\n");
}

void Execute_Generals (int *generals, int starting_general, const int num_generals)
{
	int kill = 0;
	int cur = starting_general;
	int killed = 0;
	
	/*TODO*/
	int num_iterations = 0;
	
	for (cur = starting_general; cur < num_generals; ++cur)
	{
		++num_iterations;
		/*Print_Generals (generals, num_generals);*/
		if ( kill && (1 == *(generals + cur) ) )
		{
			*(generals + cur) = 0;
			kill = 0;
			++killed;
		}
		else if ( !kill && 1 == *(generals + cur) )
		{
			kill = 1;
		}
		
		if ( num_generals - 1 == killed)
		{
			printf("num_iterations = %d\n", num_iterations);	
			break; /*once all generals but one were killed */
		}
		else
		{
			if ( num_generals == cur + 1)
			{
				cur = FIRST_GENERAL; /* when reached the end of the array:
							reset cur before it is incremented to 0 
							by the for statement */
			}
		}
	}
}


int Get_Last_General (const int *generals)
{
	int cur = 0;
	while (*(generals + cur) != 1 )
	{
		++cur;
	}
	return (cur + 1); /*+1 for the general, not the index*/
}

/******************************

* 

*

*******************************/



int main(int argc, char *argv[])
{

	/* assert(argc > 1); make sure the correct input was given */
	
	const int num_generals = atoi(argv[1]); /* convert string to int to get the number of generals*/
	const int starting_general = atoi(argv[2]) - 1;
	
	int last_general = -1;
	
	int* generals = (int*) malloc (sizeof(int) * num_generals);
	
	/*printf("starting_general = %d\n", starting_general);*/

	assert (NULL != generals); /* confrim malloc was successfull*/	
	
	Init_Generals(generals, num_generals);
	
	/*Print_Generals(generals, num_generals);*/
	
	Execute_Generals(generals, starting_general, num_generals);
	
	last_general = Get_Last_General (generals);
	
	/*Print_Generals(generals, num_generals);*/

	printf("last_general = %d\n", last_general);
		
	free(generals);
	generals = NULL;


	return 0;
}
