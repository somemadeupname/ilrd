#include <stdio.h>
#include <stdlib.h> /* atoi */
#include <assert.h> /* assert */

#define FIRST_GENERAL (-1)

/* Forward Declarations of functions */

void InitGenerals(int* generals, const size_t num_generals);
void ExecuteGenerals(int *generals,
					 const size_t starting_general,
	   				 const size_t num_generals);
int GetLastGeneral(const int *generals);
													
												
/**************************************

		coder: Shieber

		reviewer: Lila

**************************************/


/**************************************

* input: 1. pointer to array of int
		 2. const int number of generals

* initializes array to 1's 

****************************************/
void InitGenerals(int* generals, const size_t num_generals)
{
	size_t gen_index = 0;
	
	for (gen_index = 0; gen_index < num_generals; ++gen_index )
	{
		generals[gen_index] = 1;
	}
}
#ifndef NDEBUG
/******************************

* input: pointer to array of int, const int number of generals

* prints current status of which general's alive and which isn't

FOR TESTING PURPOSES ONLY

*******************************/

void PrintGenerals(int *generals, const size_t num_generals)
{
	size_t gen_index = 0;

	for (gen_index = 0; gen_index < num_generals; ++gen_index)
	{
		printf("%d", generals[gen_index]);
	}
	printf("\n");
}

#endif
/*******************************************************************

* input: 
		1. pointer to array of int
		2. const int number of generals
		3. const int of the starting general

* the main algorithm. loops over the generals array, executing per
* the algorithm until there is only one general left

********************************************************************/

void ExecuteGenerals(int *generals,const size_t starting_general,
					 const size_t num_generals)
{
	int is_kill = 0; /*boolean to determine if the next action should be kill*/
	int current = starting_general;
	size_t killed_counter = 0; /*counter for how many generals were killed so far*/
		
	/*for (cur = starting_general; cur < num_generals; ++cur)*/
	while (killed_counter < num_generals - 1)
	{
		/*if the current action is to kill and the next general is alive*/
		if ( is_kill && (1 == generals[current] ) )
		{
			generals[current] = 0;
			is_kill = 0;
			++killed_counter;
		}
		/*if current action is not to kill and current general is alive*/
		else if ( !is_kill && 1 == generals[current] )
		{
			is_kill = 1;
		}
		
		if ( num_generals == (size_t) (current + 1) )
		{
			/* when the end of the array is reached: set cur to the start
			of the cirlce. Because it's incremended before the beginning of
			the next iteration - set it to -1  */							
			current = FIRST_GENERAL; 
		}
		++current;
	}
}
/******************************

* input: pointer to array of int generals

* returns index+1 of the one remaining general

*******************************/
int GetLastGeneral(const int *generals)
{
	size_t cur = 0;
	while (1 != generals[current] )
	{
		++current;
	}
	return (current + 1); /*+1 for the general, not the index*/
}

/********************************
* The main function of the program.
* Recevies arguments:
* 1. program name
* 2. int num of generals
* 3. int starting generals
*********************************/

int main(int argc, char *argv[])
{

	int num_generals = 0;
	int starting_general = 0;
	
	int last_general = FIRST_GENERAL; /*init before setting last general*/
	int *generals = NULL;
	
	/*make sure you got valid number of inputs  */
	if (argc != 3) 	
	{						
		fprintf(stderr ,"Incorrect input. insert\
						./prog num_generals starting gen.\n");
		return (1);
	}
	
	/* convert string to int to get the number of generals*/
	num_generals = atoi(argv[1]); 
	/* insert starting general into int */
	starting_general = atoi(argv[2]) - 1;
	
	/* make sure that starting general is within correct range */
	if (num_generals < starting_general + 1 || starting_general < 0 )
	{
		printf("Starting general must be between 1 and %d.\n", num_generals);
		return (1);
	}
	
	generals = (int*) malloc (sizeof(int) * num_generals);				

	if (NULL == generals)
	{
		printf("Malloc failed.\n");
		return (1);
	}		
	
	InitGenerals(generals, num_generals);
	
	ExecuteGenerals(generals, starting_general, num_generals);
	
	last_general = GetLastGeneral(generals);
	
	printf("Number of generals is %d\a.\n", num_generals);
	printf("Starting general is %d\a.\n", starting_general + 1);
		/*+ 1 for general number and not index number in array ^ */	
	printf("Last living general is %d.\a\n", last_general);
	
	/*freeing previously malloc'ed memory*/
	free(generals); generals = NULL;

	return 0;
}
