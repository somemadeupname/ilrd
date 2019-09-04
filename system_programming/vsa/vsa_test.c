#include <stdio.h>
#include <assert.h>
#include <stdlib.h> /* malloc free */

#include "vsa.h"
#include "test_template.h"

#define UNUSED(x) (void)(x)

/* Forward Declarations */

void VSAInit_AlignedMemory_test();
void VSAInit_NotAlignedMemory_test();
void VSAInit_EndIsAligned_test();
void VSAInit_EndIsNotAligned_test();

void VSAAlloc_Sanity_test();
void VSAAlloc_AllocExactCapacity_test();
void VSAAlloc_AllocWhenFull_test();

void VSAFree_Naive_test();

void VSALargestChunk_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	VSAInit_AlignedMemory_test();
	
	VSAInit_NotAlignedMemory_test();
	
	VSAInit_EndIsAligned_test();
	
	VSAInit_EndIsNotAligned_test();
	
	VSAAlloc_Sanity_test();
	
	VSAAlloc_AllocExactCapacity_test();
	
	VSAFree_Naive_test();
	
	VSALargestChunk_test();
	
	return 0;
}
void VSALargestChunk_test()
{
	size_t memory_size = 264;
	int *i = (int *)malloc(memory_size);
	void *alloced_address = NULL;
	
	vsa_t *new_vsa = VSAInit(i, memory_size);
	
	#ifndef NDEBUG
	memory_size = 280;
    #endif /* _NDEBUG */
	
	alloced_address = VSAAlloc(new_vsa, 248);

	VSAFree(alloced_address);
	
	VSAFree(alloced_address);	
	
	alloced_address = VSAAlloc(new_vsa, 248);

	free(i);	
}

void VSAFree_Naive_test()
{
	size_t memory_size = 264;
	int *i = (int *)malloc(memory_size);
	void *alloced_address = NULL;
	
	vsa_t *new_vsa = VSAInit(i, memory_size);
	
	#ifndef NDEBUG
	memory_size = 280;
    #endif /* _NDEBUG */
	
	alloced_address = VSAAlloc(new_vsa, 248);

	expect_size_t(VSALargestChunk(new_vsa),0,"VSAFree_Naive_test1");
	
	VSAFree(alloced_address);
	
	expect_size_t(VSALargestChunk(new_vsa),248,"VSAFree_Naive_test2");
	
	VSAFree(alloced_address);	
	
	alloced_address = VSAAlloc(new_vsa, 248);

	free(i);	
	
}

void VSAAlloc_AllocExactCapacity_test()
{
	size_t memory_size = 280;
	int *i = (int *)malloc(memory_size);
	
	vsa_t *new_vsa = VSAInit(i,memory_size);
	
	void *alloced_address = VSAAlloc(new_vsa,248);
	
	expect_Not_NULL(alloced_address, "VSAAlloc_AllocExactCapacity_test1" );
	
	alloced_address = VSAAlloc(new_vsa,16);
	
	expect_NULL(alloced_address, "VSAAlloc_AllocExactCapacity_test2" );
	
	UNUSED(new_vsa);
	
	free(i);
}

void VSAAlloc_Sanity_test()
{
	size_t memory_size = 170;
	int *i = (int *) malloc (memory_size);
	void *alloced_address = NULL;
	
	vsa_t *new_vsa = VSAInit(i, memory_size);
	
	alloced_address = VSAAlloc(new_vsa, 70);
	
	expect_Not_NULL(alloced_address, "VSAAlloc_Sanity_test1");
	
	alloced_address = VSAAlloc(new_vsa, 200);
	
	expect_NULL(alloced_address, "VSAAlloc_Sanity_test2");
	
	alloced_address = VSAAlloc(new_vsa, 30);
	
	expect_Not_NULL(alloced_address, "VSAAlloc_Sanity_test3");	
	
	UNUSED(new_vsa);
	
	free(i);
}

void VSAInit_EndIsNotAligned_test()
{
	size_t memory_size = 35;
	int *i = (int *) malloc (memory_size);
	vsa_t *new_vsa = VSAInit(i,memory_size);
	
	UNUSED(new_vsa);
	
	free(i);
}

void VSAInit_EndIsAligned_test()
{
	size_t memory_size = 64;
	int *i = (int *) malloc (memory_size);
	vsa_t *new_vsa = VSAInit(i,memory_size);
	
	UNUSED(new_vsa);	
	
	free(i);
}

void VSAInit_AlignedMemory_test()
{
	size_t memory_size = 65;
	int *i = (int *) malloc (memory_size);
	vsa_t *new_vsa = VSAInit(i, memory_size);
	
	UNUSED(new_vsa);	
	
	free(i);
}

void VSAInit_NotAlignedMemory_test()
{
	size_t memory_size = 65;
	int *i = (int *) malloc (memory_size);
	vsa_t *new_vsa = VSAInit((char *)i + 1,memory_size);
	
	UNUSED(new_vsa);	
	
	expect_NULL(new_vsa, "VSAInit_NotAlignedMemory_test" );
	
	free(i);
}
