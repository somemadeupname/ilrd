#include <stdio.h>
#include <assert.h>

#include "pow.h"

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
	expect_NULL(NULL,"hi");\
	expect_Not_NULL(&a, "hi");\
}

/*************************************************************************
								 										 *
				      GENERAL TEST FUNCTIONS							 *
																		 *
*************************************************************************/
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

void expect_double(long double result, long double expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%Lf\nActual: \t%Lf\n", expected_result, result);
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

/*************************************************************************
								 										 *
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/

void AddOneBitwise_test()
{
	unsigned long a = 5ul;
	a = AddOneBitwise(a);
	
	expect_size_t(a, 6ul, "AddOneBitwise_test");
}

void SubtractOneBitwise_test()
{
	unsigned long a = 5ul;
	a = SubtractOneBitwise(a);
	
	expect_size_t(a, 4ul, "SubtractOneBitwise_test");
}

void Addition_test()
{
	unsigned long a = 5ul;
	a = Addition(a, 7ul);
	
	expect_size_t(a, 12ul, "Addition_test");
}

void Subtraction_test()
{
	unsigned long a = 5ul;
	a = Subtraction(a, 3ul);
	
	expect_size_t(a, 2ul, "Subtraction_test");
}

void Multiply_test()
{
	unsigned long a = 5ul;
	a = Multiply(a, 7ul);
	
	expect_size_t(a, 35ul, "Multiply_test");	
}

/*void Divide_test()*/
/*{*/
/*	unsigned long a = 40ul;*/
/*	a = Divide(a, 10ul);*/
/*	*/
/*	expect_size_t(a, 4ul, "Divide_test");		*/
/*}*/

void Pow_test()
{
	unsigned long a = 5ul;
	long double result = 0;
	
	result = Pow(a, 2ul);
	
	expect_size_t(result, 25, "Pow_test1");
	
	a = 3;
	
	result = Pow(a, 2l);
	
	expect_size_t(result, 9, "Pow_test2");
	
	a = 2ul;
}

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	AddOneBitwise_test();
	
	SubtractOneBitwise_test();
	
	Addition_test();
	
	Subtraction_test();
	
	Multiply_test();

	Pow_test();
	
	return 0;
}
