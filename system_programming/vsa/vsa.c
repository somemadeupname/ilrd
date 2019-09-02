
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* abs */
#include <stdint.h> /* uintptr_t */

#include "vsa.h"

#define FALSE 0
#define TRUE 1

#define WORD sizeof(size_t)
#define END_OF_MEMORY 0xDEADBEEFl
#define VSA_MIN_MEMORY_SIZE (4*WORD) /*TODO move this to init? and use sizeof type?*/

#ifndef NDEBUG
#define UNALLOCATED_POINTER 0xDEADBEEFl
#endif

/* Forward declarations */
static int IsAddressWordAligned(void *address);
static void* AlignedEndAddress(void *address, size_t memory_size);

struct vsa
{
	long bytes_of_block;
	#ifndef NDEBUG
    long specific_identifier;
    #endif /* _NDEBUG */
};

/*
 * Initialize variable size allocator
 * @memory : allocated memory to be used as variable sized allocator
 * @memory_size : size of memory in bytes must be at least VSA_MIN_MEMORY_SIZE
 * Return: pointer to variable size allocator
 * Errors: if @memory is not word-aligned, return NULL
 * Note: in DEBUG version, @memory_size must be greater than 4 * WORD
 * 		 in RELEASE version, @memory_size must be greater than 3 * WORD
 */
vsa_t *VSAInit(void *memory, size_t memory_size)
{
	
	vsa_t *vsa = memory;
	vsa_t *end_vsa = NULL;
	
	if (FALSE == IsAddressWordAligned(memory))
	{
		return NULL;
	}
	
	assert(memory_size > VSA_MIN_MEMORY_SIZE);
	
	vsa->bytes_of_block = memory_size;
	
	#ifndef NDEBUG
    vsa->specific_identifier = UNALLOCATED_POINTER;
    #endif /* _NDEBUG */
    
    end_vsa = (vsa_t *)((char *) vsa + memory_size);
    if (FALSE == IsAddressWordAligned(end_vsa))
    {
    	end_vsa = (vsa_t *)AlignedEndAddress(end_vsa, memory_size);
    }
    
    end_vsa->bytes_of_block = END_OF_MEMORY;
    
    return vsa;
}

/* helper for init to check if address is WORD-aligned */
static int IsAddressWordAligned(void *address)
{
	return !((uintptr_t) address % WORD);
}

/* helper which finds the aligned address at the end of the alloced memory */
static void* AlignedEndAddress(void *address, size_t memory_size)
{
	return (char *)address - memory_size % WORD - WORD;
}

/* helper for VSALargestChunk */
/*void UpdateFreeHeader()
{
	TODO
}
*/
/* Find the largest contiguous chunk of free memory */
size_t VSALargestChunk(vsa_t *vsa_pool)
{
	size_t cur_chunk_size = 0;
	size_t largest_chunk_size = 0;
	vsa_t *cur_header = (vsa_t *)vsa_pool;
		
	assert(NULL != vsa_pool);
	
	/* iterate over each chunk */
	while (END_OF_MEMORY != cur_header->bytes_of_block)
	{
		
		for ( ;
		     cur_header = (vsa_t *)((char *)cur_header + abs(cur_header->bytes_of_block)),
		     cur_chunk_size += cur_header->bytes_of_block;
		    )
		{ /* empty body */}
		if (largest_chunk_size < cur_chunk_size)
		{
			largest_chunk_size = cur_chunk_size;
		}
	}
	
	return largest_chunk_size;
}
