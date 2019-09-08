#include <stdio.h>
#include <assert.h> /* assert */

#include "test_template.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");
#define TRUE 1
#define FALSE 0

#define PRINT_ERROR START_RED printf("ERROR in %s.\n", func_name); END_RED

#define PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE \
{\
	int a = 1;\
	expect_int(1,1,"hi");\
	expect_size_t(1lu,1lu,"hi");\
	expect(&a,1,"hi");\
}

#define PRINT_ERROR START_RED printf("ERROR in %s.\n", func_name); END_RED

void expect_int(int result, int expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%d\nActual: \t%d\n", expected_result, result);
	}	
}

void expect_size_t(size_t result, size_t expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%lu\nActual: \t%lu\n", expected_result, result);
	}	
}

void expect_NULL(void *pointer, char *func_name)
{
	if (pointer != NULL)
	{
		PRINT_ERROR
		printf("pointer isn't NULL.\n");
	}	
}

void expect_Not_NULL(void *pointer, char *func_name)
{
	if (pointer == NULL)
	{
		PRINT_ERROR
		printf("pointer isn't NULL.\n");
	}	
}
