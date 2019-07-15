#include "ws3_environment.h"

char* StrcpyLower(char *dest, char *src)
{
	char* dest_start = dest;
	/*NULL checks*/
	assert (dest != NULL);
	assert (src != NULL);

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
	/*printf ("elements_num = %d\n", elements_num);*/
	return elements_num;
}

char** InitLowerEnv(char **env)
{
	char **lower_env = NULL;
	size_t num_env_vars = 0;
	/*TODO assert null on both pointers*/
	
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
	char** start = lower_env;
	
	size_t lower_var_len = 0;
	size_t char_index = 0;
	/* TODO assert make sure both aren't null*/
	while (NULL != *env)
	{
		*lower_env = StrcpyLower(*lower_env, *env);
		++lower_env;
		++env;
	}
	
}

void PrintLowerEnv(char **lower_env)
{
	/* TODO assert make sure aren't null*/
	
	char ** cur_lower_env = (char**) lower_env;
	
	while (NULL != *cur_lower_env)
	{
		printf("%s\n", *cur_lower_env);
		*(++cur_lower_env);
	}
}
		
void DestroyLowerEnv(char** lower_env)
{
	/*TODO assert NULL*/
	
	size_t lower_env_size = GetEnvSize (lower_env) + 1;
	char* lower_env_cur = *(lower_env + lower_env_size);
	
	while ( lower_env_cur != *lower_env )
	{
		free(lower_env_cur); lower_env_cur = NULL;
		--lower_env_cur;
	}	
	free(lower_env); lower_env = NULL;
}
	
	
	

int main(int argc, char *argv[], char **envp)
{
	char **lower_env = NULL;
	char s[] = "test";	
	
	/*TODO isn't NULL and malloc succeded*/
	
	lower_env = InitLowerEnv(envp);
	
	if ( NULL == InitEnvVars (lower_env, envp) )
	{
		printf("failed allocating memory\n");
	}
	
	FillLowerEnv(lower_env, envp);
	
	PrintLowerEnv (lower_env);
	
	DestroyLowerEnv(lower_env);
	
	return 0;
}
