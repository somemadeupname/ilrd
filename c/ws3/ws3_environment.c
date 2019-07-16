#include "ws3_environment.h"

/*****************************************
* input: 1. dest: char* to copy lower
			case chars from the src string
*		 2. src: char* to copy the 
*		 	chars from
* output: 	dest which contains a lower
		  	case copy of src char*
*
*****************************************/
char* StrcpyLower(char *dest, char *src)
{
	char* dest_start = NULL;

	assert (NULL != dest);
	assert (NULL != src);
	
	dest_start = dest;

	while (*src != '\0')
	{
		*dest = tolower(*src);
		++src;
		++dest;
	}
	/*append empty char to end of dest */
	*dest = '\0';
	
	return dest_start;
}
/*********************************
* input: char** env
*
* output: number of env variables
**********************************/
size_t GetEnvSize(char **env)
{
	int elements_num = 0;
	
	while (NULL != *env)
	{
		++elements_num;
		++env;
	}
	return elements_num;
}

/************************************************
* input: char** env
*
* output: malloc'ed char **. NULL if malloc fails
*************************************************/
char** InitLowerEnv(char **env)
{
	char **lower_env = NULL;
	size_t num_env_vars = 0;

	assert(NULL != env);
	
	num_env_vars = /*5;*/ GetEnvSize(env) + 1; /* add one for the null character*/
	lower_env = (char**) malloc (num_env_vars * sizeof(char*));
	
	if (NULL == lower_env) /*if malloc failed*/
	{
		return NULL;
	}
	/*add NULL to end of array like original env*/
	*(lower_env + num_env_vars - 1) = NULL; 
	return lower_env;
}

/***************************************************************************
* input: char** env
*
* output: number of env variables * malloc'ed (char *) within lower_env.
			NULL if any of the mallocs fail
****************************************************************************/
char** InitEnvVars(char **lower_env, char **env, size_t *num_successful_allocs)
{
	size_t env_var_size = 0;
	size_t num_alloced = 0;
	
	assert(NULL != env);
	assert(NULL != lower_env);
	assert(NULL != num_successful_allocs);	
	
	
	while (NULL != *env)
	{
		env_var_size = strlen(*env) + 1;/*+ 1 for the '\0' char */
		*lower_env = (char *) malloc ( env_var_size * sizeof(char));
		++num_alloced;
		*num_successful_allocs = num_alloced;		
		
		if (NULL == lower_env) 
		{
			--num_successful_allocs;
			return NULL;
		}
		++env;
		++lower_env;
	}
	return lower_env;
}

/************************************************
* input: char** lower_env, char** env
*
* copies env string by string into lower_env
  and converts to lower case
*  
*************************************************/
void FillLowerEnv(char **lower_env, char **env)
{	
	assert(NULL != env);
	assert(NULL != lower_env);
	
	while (NULL != *env)
	{
		*lower_env = StrcpyLower(*lower_env, *env);
		++lower_env;
		++env;
	}
}

/************************************************
* input: char** lower_env
*
* prints lower_env string by string, separated
  by newlines
*  
*************************************************/
void PrintLowerEnv(char **lower_env)
{
	char **cur_lower_env = NULL;
	
	assert(NULL != lower_env);
	
	cur_lower_env = (char**) lower_env;
	
	while (NULL != *cur_lower_env)
	{
		printf("%s\n", *cur_lower_env);
		++cur_lower_env;
	}
}

/************************************************
* input: char** lower_env
*
* frees memory allocated to lower_env
*  
*************************************************/		
void DestroyLowerEnv(char **lower_env, size_t *num_alloced_strings)
{
	size_t lower_env_size = 0;
	char* lower_env_cur	= NULL;
	size_t ptr_advance = 1;

	assert(NULL != lower_env);
	assert(NULL != num_alloced_strings);		
	
	lower_env_size = *num_alloced_strings;
	for (; ptr_advance <= lower_env_size; ++ptr_advance)
	{
		lower_env_cur = *(lower_env + lower_env_size - ptr_advance);
		free(lower_env_cur); lower_env_cur = NULL;
	}
	free(lower_env); lower_env = NULL;
}

/************************************
*
* The main function of the program
*
*
 *************************************/

int main(int argc, char *argv[], char **envp)
{	
	char **lower_env = NULL;
	size_t num = 0;
	size_t *num_alloced_strings = &num; /* pointer to number of successfull
										alloc'ed env variable. if a malloc
										fails - this counter will be sent to
										the destructor*/
	
	NO_WARNINGS /*remove warnings regarding unused argc argv */
	
	/* first malloc of the char** */
	lower_env = InitLowerEnv(envp);
	
	/*if either memory allocation fails*/
	if ( NULL == lower_env ||
		 NULL == InitEnvVars (lower_env, envp, num_alloced_strings) )
	{
		DestroyLowerEnv(lower_env, num_alloced_strings);
		printf("Failed allocating memory.\n");
		return (-1);
	}
	
	FillLowerEnv(lower_env, envp);
	
	PrintLowerEnv (lower_env);
	
	DestroyLowerEnv(lower_env, num_alloced_strings);
	
	return 0;
}
