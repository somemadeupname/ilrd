
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Lila 		 *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h>
#include "fsa.h"

#define WORD_SIZE sizeof(size_t)
#define FSA_START_OFFSET sizeof(fsa_t)
#define BLOCK_START_OFFSET sizeof(meta_t)

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

/* initialize a fixed sized allocator */
fsa_t *FSAInit(void *memory, size_t memory_size, size_t block_size)
{
	fsa_t *fsa_pool = NULL;
	meta_t *cur_metadata = NULL;
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

	cur_metadata = (meta_t *)((char *)fsa_pool + FSA_START_OFFSET);
	
	for ( block_offset = block_size
		; block_offset < memory_size - block_size /* check extreme values for all alignments TODO */
		; block_offset += block_size, cur_metadata = (meta_t *)((char *) cur_metadata + block_size)
		)
	{
		cur_metadata->block = (block_offset * block_size + BLOCK_START_OFFSET);
	}
	cur_metadata->block = 0; /* when all blocks are filled pool reaches 0 blocks */
	
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
	
	fsa_pool->free_block_offset = ((meta_t *)allocated_return_address)->block;

	((meta_t *)allocated_return_address)->block = temp;
}

/* Allocate memory block in fixed size allocator */
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
	
	return (char *)allocated_return_address + BLOCK_START_OFFSET;
}

/* Free memory block in fixed size allocator */
void FSAFree(void *block_to_free)
{
	char *cur_block = (char *)block_to_free;
	void *temp_block = NULL;
	
	if (NULL == block_to_free)
	{
		return;
	}
	
	cur_block -= BLOCK_START_OFFSET; /* get it to the start of the metadata */
	temp_block = (char *)cur_block - ((meta_t *)cur_block)->block;
	
	SwapBlockInfo((fsa_t *)temp_block, &((meta_t *)cur_block)->block);	
}

/* Count number of free blocks in fixed size allocator */
size_t FSACountFree(const fsa_t *fsa_pool)
{
	size_t num_free_blocks = 0;
	meta_t *cur_block = NULL;
	
	assert(NULL != fsa_pool);
	
	for (num_free_blocks = 0,
	     cur_block = (meta_t *)((char *)fsa_pool + fsa_pool->free_block_offset);
	     0 != cur_block->block;
	     ++num_free_blocks,
	     cur_block = (meta_t *)((char *)fsa_pool + cur_block->block)
	     )
	     {/* empty body */}	
	
	return num_free_blocks;
}

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	size_t total_block_size = sizeof(meta_t) + AlignBlockSize(block_size);
	return (sizeof(fsa_t) + num_of_blocks * total_block_size);
}
