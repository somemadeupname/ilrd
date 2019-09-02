
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* abs */
#include "vsa.h"

#define WORD sizeof(size_t)
#define END_OF_MEMORY 0xDEADBEEFL

#ifndef NDEBUG
#define UNALLOCATED_POINTER 0xDEADBEEFL
#endif

typedef struct header
{
	long bytes_of_block;
	#ifndef NDEBUG
    long identifier;
    #endif /* _NDEBUG */
} header_t;


/* helper for VSALargestChunk */
void UpdateFreeHeader()
{
	
}

/* Find the largest contiguous chunk of free memory */
size_t VSALargestChunk(vsa_t *vsa_pool)
{
	size_t cur_chunk_size = 0;
	size_t largest_chunk_size = 0;
	header_t *cur_header = (header_t *)vsa_pool;
		
	assert(NULL != vsa_pool);
	
	/* iterate over each chunk */
	while (END_OF_MEMORY != cur_header->bytes_of_block)
	{
		if (FALSE == cur_header->is_free)
		{
			cur_header = (header_t *)((char *)cur_header + abs(cur_header->bytes_of_block));
		}
		for ( ;
			 cur_header->is_free;
		     cur_header = (header_t *)((char *)cur_header + abs(cur_header->bytes_of_block)),
		     cur_chunk_size += cur_header->bytes_of_block
		    )
		{ /* empty body */}
		if (largest_chunk_size < cur_chunk_size)
		{
			largest_chunk_size = cur_chunk_size;
		}
	}
	
	return largest_chunk_size;
}
