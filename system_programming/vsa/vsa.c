
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Hila 	    *
 *	 Status   : Sent	    *
 ****************************/
 
#include <assert.h> /* assert */
#include <stdlib.h> /* labs */
#include <stdint.h> /* uintptr_t */

#include "vsa.h"

#define FALSE 0
#define TRUE 1

#define WORD sizeof(size_t)
#define END_OF_MEMORY 0xDEADBEEFl

#ifndef NDEBUG
#define VSA_MIN_MEMORY_SIZE (4*WORD)
#else
/* for potential future use. not relevant for now */
#define VSA_MIN_MEMORY_SIZE (3*WORD)
#endif

#ifndef NDEBUG
#define POINTER_TO_LEGIT_ADDRESS 0xDEADBEEFl
#endif

/* Forward declarations */
static int IsAddressWordAligned(const void *address);
static vsa_t *NextChunk(const vsa_t* vsa_pool);
static int IsChunkFree(const vsa_t *vsa_pool);
static long ChunkSize(const vsa_t *vsa_pool);
static long AlignedBytes(long bytes_to_alloc);
static size_t GetSizeOfCurrentChunk(vsa_t *vsa_pool);

struct vsa
{
	#ifndef NDEBUG
    long specific_identifier;
    #endif /* _NDEBUG */
	long bytes_of_block;
};

/* Initialize variable size allocator */
vsa_t *VSAInit(void *memory, size_t memory_size)
{
	
	vsa_t *vsa = memory;
	vsa_t *end_vsa = NULL;
	
	if (FALSE == IsAddressWordAligned(memory))
	{
		return NULL;
	}
	
	assert(memory_size > VSA_MIN_MEMORY_SIZE);
	
	/* align memory_size and decrease by sizes of metadata and END_OF_MEMORY */
	if (memory_size != (size_t) AlignedBytes(memory_size))
	{
		memory_size = AlignedBytes(memory_size) - WORD;
	}
	
	/* set number of free bytes and subtract sizes of END and START chunks */
	vsa->bytes_of_block = memory_size - sizeof(vsa_t) - sizeof(vsa_t);
	
	#ifndef NDEBUG
    vsa->specific_identifier = POINTER_TO_LEGIT_ADDRESS;
    #endif /* _NDEBUG */
    
    end_vsa = (vsa_t *)((char *)vsa + memory_size - sizeof(vsa_t));
    
    end_vsa->bytes_of_block = END_OF_MEMORY;
    
    return vsa;
}

/*Allocate memory block in variable size allocator */
void *VSAAlloc(vsa_t *vsa_pool, size_t bytes_to_alloc)
{
	void *allocated_address = NULL;
	vsa_t *cur_chunk = vsa_pool;
			
	assert(NULL != vsa_pool);
	assert(POINTER_TO_LEGIT_ADDRESS == vsa_pool->specific_identifier);
	assert(0 != bytes_to_alloc);
	
	bytes_to_alloc = AlignedBytes(bytes_to_alloc);
	
	for (
		 cur_chunk = vsa_pool;
		 cur_chunk->bytes_of_block != END_OF_MEMORY;
		 cur_chunk = NextChunk(cur_chunk)
		)
	{
		if (IsChunkFree(cur_chunk) &&
								(ChunkSize(cur_chunk) >= (long) bytes_to_alloc))
		{
			vsa_t *next_chunk = NULL;
			
			/* set aside size which is left after allocation */
			long excess_size = cur_chunk->bytes_of_block - bytes_to_alloc;
			
			cur_chunk->bytes_of_block = -bytes_to_alloc;
			
			/* set next free chunk */
			next_chunk = NextChunk(cur_chunk);
			
			if (0 < excess_size - (long) sizeof(vsa_t))
			{
				next_chunk->bytes_of_block = excess_size - sizeof(vsa_t);
			}
			
			#ifndef NDEBUG
		    cur_chunk->specific_identifier = POINTER_TO_LEGIT_ADDRESS;
		    #endif /* _NDEBUG */
		    
		    allocated_address = (char *)cur_chunk + sizeof(vsa_t);
		    break;
		}
	}
	
	return allocated_address;
}

/* Free block starting in @address_to_free from variable size allocator */
void VSAFree(void *address_to_free)
{
	vsa_t *chunk_meta = NULL;
	
	if (NULL == address_to_free)
	{
		return;
	}
	
    /* get to the meta data for the given chunk */
    chunk_meta = (vsa_t *)((char *)address_to_free - sizeof(vsa_t));
    
	#ifndef NDEBUG
    if (POINTER_TO_LEGIT_ADDRESS != *(long *)chunk_meta)
    {
    	return;
    }
    #endif /* _NDEBUG */
    
    chunk_meta->bytes_of_block = labs(ChunkSize(chunk_meta));
}


/* Find the largest contiguous chunk of free memory */
size_t VSALargestChunk(vsa_t *vsa_pool)
{
	size_t size_of_largest_chunk = 0;
	size_t size_of_current_chunk = 0;
	vsa_t *cur_chunk = NULL;

	assert(NULL != vsa_pool);
	
	for (
		 cur_chunk = vsa_pool;
		 cur_chunk->bytes_of_block != END_OF_MEMORY;
		 cur_chunk = NextChunk(cur_chunk)
		)
	{
		if (ChunkSize(cur_chunk) > 0)
		{
			size_of_current_chunk = GetSizeOfCurrentChunk(cur_chunk);
		}
		
		if (size_of_current_chunk > size_of_largest_chunk)
		{
			size_of_largest_chunk = size_of_current_chunk;
		}
	}
	
	return size_of_largest_chunk;
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

/* helper for alloc - returns next chunk */
static vsa_t *NextChunk(const vsa_t* vsa_pool)
{
	return (vsa_t *)((char *)vsa_pool + labs(vsa_pool->bytes_of_block)
															   + sizeof(vsa_t));
}

/* helper for alloc - checks if chunk is free */
static int IsChunkFree(const vsa_t *vsa_pool)
{
	return (vsa_pool->bytes_of_block > 0);
}

/* helper for alloc - gets chunk size */
static long ChunkSize(const vsa_t *vsa_pool)
{
	return vsa_pool->bytes_of_block;
}

/* helper for alloc - returns number of WORD-aligned bytes */
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

/* helper for VSALargestChunk - returns the size of the current chunk */
static size_t GetSizeOfCurrentChunk(vsa_t *vsa_pool)
{
	size_t size_of_current_chunk = 0;
	vsa_t *first_chunk = vsa_pool;
	vsa_t *cur_chunk = first_chunk;
	
	assert(NULL != vsa_pool);
	
	for (
		 cur_chunk = NextChunk(vsa_pool);
		 cur_chunk->bytes_of_block != END_OF_MEMORY && IsChunkFree(cur_chunk);
		 cur_chunk = NextChunk(cur_chunk)
		)
	{
		size_of_current_chunk += cur_chunk->bytes_of_block + sizeof(vsa_t);
	}
	
	/* updates the size of the chunk to include size of the next free blocks */
	first_chunk->bytes_of_block += size_of_current_chunk;

	return first_chunk->bytes_of_block;
}
