#include <stdio.h>
#include <stdlib.h> /* malloc free*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/
#include <ctype.h> /* tolower*/

#define NO_WARNINGS	int no = argc; char* warnings = argv[0]; if ((char)no == *warnings){}

char* StrcpyLower(char *dest, char *src);
size_t GetEnvSize(char **env);
char** InitLowerEnv(char **env);
char** InitEnvVars(char **lower_env, char **env, size_t *num_successful_allocs);
void FillLowerEnv(char **lower_env, char **env);
void DestroyLowerEnv(char** lower_env, size_t *num_successful_allocs);
