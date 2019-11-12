#include <stdio.h>
#include <stdlib.h>

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");


void PrintAddress(void *var, const char *name)
{
	printf("address: %p \tvar: %s\n", var, name);
}

typedef int global_int_t;

global_int_t global_int = 5;
global_int_t global_int_init_to_zero = 0;
static global_int_t static_global_int = 13;

global_int_t global_int_uninit;
static global_int_t static_global_uninit;
static global_int_t static_global_int_init_to_zero = 0;

static int static_func()
{
	int local_int_in_static_func = 12;
	int local_int_uninit_in_static_func;
	
	PrintAddress(&local_int_in_static_func,"local_int_in_static_func");
	PrintAddress(&local_int_uninit_in_static_func, "local_int_uninit_in_static_func");
	
	
	return 0;
}

int non_static_func()
{
	int local_int_in_func = 11;
	int local_int_uninit_in_func;
	
	PrintAddress(&local_int_in_func,"local_int_in_func");
	PrintAddress(&local_int_uninit_in_func, "local_int_uninit_in_func");	

	return 0;
}


int main(int argc, char *argv[], char *envp[])
{
	int *first_heap_int = (int *)malloc(sizeof(int)*2);
	int *second_heap_int = (int *)malloc(sizeof(int)*2);
	
	int stack_var = 16;
	int stack_var2 = 56;
	int stack_var3 = 15;
	
	START_RED
	printf("DATA:\n\n");
	END_RED
	PrintAddress(&global_int,"global_int");
	PrintAddress(&static_global_int,"static_global_int");
	PrintAddress(&global_int_uninit,"global_int_uninit");
	PrintAddress(&static_global_uninit,"static_global_uninit");
	PrintAddress(&static_global_int_init_to_zero,"static_global_int_init_to_zero");
	PrintAddress(&global_int_init_to_zero,"global_int_init_to_zero");		
	
	START_RED
	printf("stack:\n\n");
	END_RED
	PrintAddress(&argc,"argc");	
	PrintAddress(&argv[0],"argv[0]");
	PrintAddress(&envp[0],"envp[0]");
	PrintAddress(&stack_var,"stack_var");
	PrintAddress(&stack_var2,"stack_var2");	
	PrintAddress(&stack_var3,"stack_var3");				
	
	START_RED
	printf("heap:\n\n");
	END_RED
	PrintAddress(&first_heap_int,"first_heap_int");	
	PrintAddress(&second_heap_int,"second_heap_int");	
	
	printf("functions_stack:\n\n");	
	static_func();
	non_static_func();

/*	PrintAddress(&static_func,"static_func");*/
/*	PrintAddress(&non_static_func,"non_static_func");*/

	free(first_heap_int);
	free(second_heap_int);	
	
	return 0;
}
