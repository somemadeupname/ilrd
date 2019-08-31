#include <stdio.h>
#include <assert.h>
#include <stdlib.h> /* malloc free */

#include "fsa.h"
#include "/home/shieber/git/ran-shieber/scripts/test_template.c"

/* Forward Declarations */
void FSAInit_LessThanWord_test();
void FSAInit_WordAligned_test();
void FSAInit_MoreThanWord_test();
void FSAAlloc_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	FSAInit_LessThanWord_test();
	
	FSAInit_WordAligned_test();
	
	FSAInit_MoreThanWord_test();
	
	FSAAlloc_test();
	
	return 0;
}

void FSAInit_LessThanWord_test()
{
	fsa_t *fsa_pool = NULL;
	size_t memory_size = 40;
	size_t block_size = 4;
	int *memory = (int *)malloc(memory_size);
	
	fsa_pool = FSAInit(memory, memory_size,block_size);
	
	free(memory);
}

void FSAInit_WordAligned_test()
{
	fsa_t *fsa_pool = NULL;
	size_t memory_size = 40;
	size_t block_size = 8;
	int *memory = (int *)malloc(memory_size);
	
	fsa_pool = FSAInit(memory, memory_size,block_size);
	
	free(memory);
}

void FSAInit_MoreThanWord_test()
{
	fsa_t *fsa_pool = NULL;
	size_t memory_size = 40;
	size_t block_size = 10;
	int *memory = (int *)malloc(memory_size);
	
	fsa_pool = FSAInit(memory, memory_size,block_size);
	
	free(memory);
}

void FSAAlloc_test()
{
	fsa_t *fsa_pool = NULL;
	void *alloc_result = NULL;
	size_t memory_size = 40;
	size_t block_size = 4;
	int *memory = (int *)malloc(memory_size);
	
	fsa_pool = FSAInit(memory, memory_size,block_size);
	
	alloc_result = FSAAlloc(fsa_pool);
	
	free(memory);
}
