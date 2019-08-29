
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h>
#include "fsa.h"

#define WORD_SIZE sizeof(size_t)
#define FSA_START_OFFSET sizeof(fsa_t)

/* Forward Declarations */
static size_t AlignBlockSize(size_t block_size);

typedef struct meta
{
	size_t block;
} meta_t;

struct fsa
{
	size_t free_block_offset;
};

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
	fsa_t *fsa_pool = NULL;
	meta_t *metadata = NULL;
	size_t block_offset = block_size;
	
	assert(NULL != memory);
	assert(0 != block_size);
	
	if (memory_size < block_size)
	{
		return NULL;
	}
	
	block_size = AlignBlockSize(block_size);
	
	fsa_pool = (fsa_t *) memory;
	
	fsa_pool->free_block_offset = FSA_START_OFFSET;

	metadata = (meta_t *)((char *)fsa_pool + FSA_START_OFFSET);
	
	for ( block_offset = block_size
		; block_offset < memory_size - block_size /* check extreme values for all alignments TODO */
		; block_offset += block_size, metadata = (meta_t *)((char *) metadata + block_size)
		)
	{
		metadata->block = (block_offset * block_size);
	}
	metadata->block = 0; /* when all blocks are filled pool reaches 0 blocks */
	
	return fsa_pool;
}

/* 
 * helper for init
 * calculate and return aligned block size 
 */
static size_t AlignBlockSize(size_t block_size)
{
	size_t remainder = block_size % WORD_SIZE;
	size_t aligned_block_size = 0;
	
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
 * helper for free and alloc 
 * swaps the info for where the next free block is
 */
static void SwapBlockInfo(fsa_t *fsa_pool, void *allocated_return_address)
{
	size_t temp = 0;

	assert(NULL != fsa_pool);
	
	temp = fsa_pool->free_block_offset;
	
	fsa_pool->free_block_offset = *(size_t *) allocated_return_address;

	allocated_return_address = &temp;
}

/*
 * Allocate memory block in fixed size allocator
 * @fsa_pool : fixed sized allocator
 * Return: pointer to allocated memory
 * Errors: if fsa is full, return NULL
 */
void *FSAAlloc(fsa_t *fsa_pool)
{
	void *allocated_return_address = NULL;

	assert(NULL != fsa_pool);
	
	allocated_return_address = (char *)(fsa_pool) + FSA_START_OFFSET + fsa_pool->free_block_offset;
	
	if (0 == *(size_t *)allocated_return_address) /* fsa is full */
	{
		return NULL; 
	}
	
	SwapBlockInfo(fsa_pool, allocated_return_address);
	
	return allocated_return_address;
}

/*
 * Count number of free blocks in fixed size allocator
 * @fsa_pool  : fixed sized allocator
 * Return: number of free blocks in fsa_pool
 * Errors: none
 */
size_t FSACountFree(const fsa_t *fsa_pool)
{
	size_t num_free_blocks = 0;
	assert(NULL != fsa_pool);
	
	
	
	return num_free_blocks;
}

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	size_t total_block_size = sizeof(meta_t) + AlignBlockSize(block_size);
	return (sizeof(fsa_t) + num_of_blocks * total_block_size);
}
