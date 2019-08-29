
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

typedef struct meta
{
	size_t next_node;
} meta_t;

struct fsa
{
	size_t free_block_index;
}

/* 
 * helper for init
 * calculate and return aligned block size 
 */
static size_t AlignBlockSize(size_t block_size)
{
	size_t remainder = block_size % WORD_SIZE;
	size_t = 0;
	
	if (block_size < WORD_SIZE)
	{
		aligned_block_size = WORD_SIZE;
	}
	else if (0 == remainder) /* block_size is already aligned */
	{
		aligned_block_size = block_size;
	}
	else 					/* block_size isn't aligned */
	{
		aligned_block_size = block_size + WORD_SIZE - remainder;
	}
	return aligned_block_size;
}

/*
 * Initialize new fixed size allocator
 * @memory : allocated memory to be used as fixed sized allocator
 * @memory_size : size of mem in bytes
 * @block_size  : size of fixed block in bytes
 * Return: pointer to fixed sized allocator
 * Errors: if @memory_size is too small for 1 block of size @block_size, 
 *         return NULL
 *   	   if @block_size is 0, behavior is undefined
 *		   if @memory is not aligned, behavior is undefined
 */
fsa_t *FSAInit(void *memory, size_t memory_size, size_t block_size)
{
	(fsa_t *) fsa = NULL;
	size_t block_offset = 1;
	
	assert(NULL != memory);
	assert(0 != block_size);
	
	if (memory_size < block_size)
	{
		return NULL;
	}
	
	block_size = AlignBlockSize(block_size);
	
	fsa = (fsa_t *) memory;
	
	fsa->free_block_index = 1;

	meta_t *metadata = (meta_t *)(fsa + (char *)(sizeof(fsa_t)));
	
	for ( block_offset = 0
		; block_offset < block_size * memory_size
		; ++block_offset
		)
	{
		*metadata = (block_offset * block_size);
	}
	*metadata = 0; /* when all blocks are filled */
	
	return fsa;
}

/*
 * Allocate memory block in fixed size allocator
 * @fsa_pool : fixed sized allocator
 * Return: pointer to allocated memory
 * Errors: if fsa is full, return NULL
 */
void *FSAAlloc(fsa_t *fsa_pool);
