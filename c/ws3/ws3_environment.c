#include "ws3_environment.h"

#define NO_WARNINGS	int no = argc; char* warnings = argv[0]; if ((char)no == *warnings){}

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

size_t GetEnvSize(char **env)
{
	int elements_num = 0;
	
	while (NULL != *env)
	{
		++elements_num;
		*(++env);
	}
	return elements_num;
}

char** InitLowerEnv(char **env)
{
	char **lower_env = NULL;
	size_t num_env_vars = 0;

	assert(NULL != env);
	
	num_env_vars = GetEnvSize(env) + 1; /* add one for the null character*/
	lower_env = (char**) malloc (num_env_vars * sizeof(char*));
	
	if (NULL == lower_env) /*if malloc failed*/
	{
		return NULL;
	}
	*(lower_env + num_env_vars - 1) = NULL; /*add NULL to end of array like original env*/
	return lower_env;
}

char** InitEnvVars(char **lower_env, char **env)
{
	/* TODO assert make sure both aren't null*/
	size_t env_var_size = 0;
	
	assert(NULL != env);
	assert(NULL != lower_env);
	
	while (NULL != *env)
	{
		env_var_size = strlen(*env) + 1;/*+ 1 for the '\0' char */
		*lower_env = (char *) malloc ( env_var_size * sizeof(char));
		if (NULL == *lower_env)
		{
			return NULL;
		}
		++env;
		++lower_env;
	}
	return lower_env;
}

void FillLowerEnv (char **lower_env, char **env)
{	
	size_t lower_var_len = 0;
	size_t char_index = 0;
	
	assert(NULL != env);
	assert(NULL != lower_env);
	
	while (NULL != *env)
	{
		*lower_env = StrcpyLower(*lower_env, *env);
		++lower_env;
		++env;
	}
}

void PrintLowerEnv(char **lower_env)
{
	char **cur_lower_env = NULL;
	
	assert(NULL != lower_env);
	
	cur_lower_env = (char**) lower_env;
	
	while (NULL != *cur_lower_env)
	{
		printf("%s\n", *cur_lower_env);
		*(++cur_lower_env);
	}
}
		
void DestroyLowerEnv(char** lower_env)
{
	size_t lower_env_size = 0;
	char* lower_env_cur	= NULL;
	int i = 1;

	assert(NULL != lower_env);
	lower_env_size = GetEnvSize(lower_env);
	for (i = 1; i <= lower_env_size; ++i)
	{
		lower_env_cur = *(lower_env + lower_env_size - i);
		free(lower_env_cur); lower_env_cur = NULL;
	}
	free(lower_env); lower_env = NULL;
}
	
	
	

int main(int argc, char *argv[], char **envp)
{	
	char **lower_env = NULL;
	
	NO_WARNINGS
	
	lower_env = InitLowerEnv(envp);
	
	if ( NULL == InitEnvVars (lower_env, envp) )
	{
		printf("failed allocating memory\n");
		return (-1);
	}
	
	FillLowerEnv(lower_env, envp);
	
	PrintLowerEnv (lower_env);
	
	DestroyLowerEnv(lower_env);
	
	return 0;
}
