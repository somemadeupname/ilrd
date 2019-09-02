
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

#ifndef NDEBUG
#define VSA_MIN_MEMORY_SIZE (4*WORD)
#else
#define VSA_MIN_MEMORY_SIZE (3*WORD)
#endif

#ifndef NDEBUG
#define POINTER_TO_LEGIT_ADDRESS 0xDEADBEEFl
#endif

/* Forward declarations */
static int IsAddressWordAligned(const void *address);
static void* AlignedEndAddress(void *address, size_t memory_size);
static vsa_t *NextChunk(const vsa_t* vsa_pool);
static int IsChunkFree(const vsa_t *vsa_pool);
static long ChunkSize(const vsa_t *vsa_pool);
static long AlignedBytes(long bytes_to_alloc);

struct vsa
{
	#ifndef NDEBUG
    long specific_identifier;
    #endif /* _NDEBUG */
	long bytes_of_block;
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
	
	/* decrease by sizes of metadata and END_OF_MEMORY */
	vsa->bytes_of_block = memory_size - sizeof(vsa_t) - sizeof(vsa_t);
	
	#ifndef NDEBUG
    vsa->specific_identifier = POINTER_TO_LEGIT_ADDRESS;
    #endif /* _NDEBUG */
    
    end_vsa = (vsa_t *)((char *)vsa + memory_size - sizeof(vsa_t));

   	end_vsa = (vsa_t *)AlignedEndAddress(end_vsa, memory_size);
    
    end_vsa->bytes_of_block = END_OF_MEMORY;
    
    return vsa;
}

/************************
*						*
*	  HELPER FUNCS		*
*						*
************************/

/* helper for init to check if address is WORD-aligned */
static int IsAddressWordAligned(const void *address)
{
	return !((uintptr_t) address % WORD);
}

/* helper which finds the aligned address at the end of the alloced memory */
static void* AlignedEndAddress(void *address, size_t memory_size)
{
	return (char *)address - memory_size % WORD - WORD;
}

/*
 * Allocate memory block in variable size allocator
 * @ vsa_pool : variable sized allocator
 * @ bytes_to_alloc : num of bytes to allocate
 * Return: pointer to allocated memory
 * Errors: if bytes_to_alloc is larger than largest free chunk in vsa, 
 *		   returns NULL
 */
void *VSAAlloc(vsa_t *vsa_pool, size_t bytes_to_alloc)
{
	void *allocated_address = NULL;
	vsa_t *cur_chunk = vsa_pool;
			
	assert(NULL != vsa_pool);
	assert(POINTER_TO_LEGIT_ADDRESS == vsa_pool->specific_identifier);
	assert(0 != bytes_to_alloc);
	
	bytes_to_alloc = AlignedBytes(bytes_to_alloc);
	
	if (bytes_to_alloc > VSALargestChunk(vsa_pool) )
	/* TODO should this be in general flow? optimization */
	{
		return NULL;
	}
	
	for (
		 cur_chunk = vsa_pool;
		 cur_chunk->bytes_of_block != END_OF_MEMORY;
		 cur_chunk = NextChunk(cur_chunk)
		)
	{
		if (IsChunkFree(cur_chunk) && (ChunkSize(cur_chunk) >= (long) bytes_to_alloc))
		{
			vsa_t *next_chunk = NULL;
			
			long excess_size = cur_chunk->bytes_of_block - bytes_to_alloc;
			
			cur_chunk->bytes_of_block = -bytes_to_alloc;
			
			/* set next free chunk */
			next_chunk = NextChunk(cur_chunk);
			
			next_chunk->bytes_of_block = excess_size - sizeof(vsa_t);
			
			#ifndef NDEBUG
		    cur_chunk->specific_identifier = POINTER_TO_LEGIT_ADDRESS;
		    #endif /* _NDEBUG */
		    
		    allocated_address = cur_chunk + sizeof(vsa_t);
		    break;
		}
	}
	
	return allocated_address;
}

/* helper for alloc
 *
 *
 */
static vsa_t *NextChunk(const vsa_t* vsa_pool)
{
	return (vsa_t *)((char *)vsa_pool + abs(vsa_pool->bytes_of_block));
}

/* helper for alloc
 *
 *
 */
static int IsChunkFree(const vsa_t *vsa_pool)
{
	return vsa_pool->bytes_of_block > 0;
}

/* helper for alloc
 *
 *
 */
static long ChunkSize(const vsa_t *vsa_pool)
{
	return vsa_pool->bytes_of_block;
}

/* helper for alloc */
static long AlignedBytes(long bytes_to_alloc)
{
	long aligned_bytes = bytes_to_alloc;
	int remainder = (bytes_to_alloc % WORD);
	if (0 != remainder)
	{
		aligned_bytes += WORD - remainder;
	}
	return aligned_bytes;
}


/* helper for VSALargestChunk */
size_t GetSizeOfCurrentChunk(vsa_t *vsa_pool)
{
	size_t size_of_current_chunk = 0;
	vsa_t *first_chunk = vsa_pool;
	vsa_t *cur_chunk = first_chunk;
	
	assert(NULL != vsa_pool);
	
	for (cur_chunk = vsa_pool;
		 cur_chunk->bytes_of_block != END_OF_MEMORY && IsChunkFree(cur_chunk);
		 cur_chunk = NextChunk(cur_chunk)
		)
	{
		size_of_current_chunk += cur_chunk->bytes_of_block + sizeof(vsa_t);
	}
	
	first_chunk->bytes_of_block = size_of_current_chunk - sizeof(vsa_t);

	return size_of_current_chunk - sizeof(vsa_t);
}


/* Find the largest contiguous chunk of free memory */

/*
 * Find the largest continuous chunk of free memory
 * @vas_pool : vsa to count
 * Return: Size in bytes of the largest continuous chunk of free memory
 * Errors: none
 */
size_t VSALargestChunk(vsa_t *vsa_pool)
{
	size_t size_of_largest_chunk = 0;
	size_t size_of_current_chunk = 0;
	vsa_t *cur_chunk = NULL;

	assert(NULL != vsa_pool);
	
	for (cur_chunk = vsa_pool;
		 cur_chunk->bytes_of_block != END_OF_MEMORY;
		 cur_chunk = NextChunk(cur_chunk)
		)
	{
		if (ChunkSize(cur_chunk) > 0)
		{
			size_of_current_chunk = GetSizeOfCurrentChunk(vsa_pool);
		}
		
		if (size_of_current_chunk > size_of_largest_chunk)
		{
			size_of_largest_chunk = size_of_current_chunk;
		}
	}
	
	return size_of_largest_chunk;
}



















