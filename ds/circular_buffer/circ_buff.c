#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */

#include "circ_buff.h"

#define TRUE 1
#define FALSE 0
#define OFFSET 8

struct buffer
{
	size_t capacity;
	size_t read_index;
	size_t write_index;
	int is_buffer_full;
	char buf[1];	
};

circ_buff_t *CircBuffCreate(size_t init_capacity)
{
	circ_buff_t *circ_buf = NULL;
	/*
	if (init_capacity < OFFSET)
	{
		init_capacity = 0;
	}
	*/
	
	circ_buf = (circ_buff_t *) malloc (sizeof(circ_buff_t) + init_capacity);
	
	if (NULL == circ_buf)
	{
		return NULL;
	}

	/* initialization of circ_buf */
	circ_buf->capacity = init_capacity;
	circ_buf->read_index = 0;
	circ_buf->write_index = 0;
	circ_buf->is_buffer_full = FALSE;
	
	return circ_buf;
}

void CircBuffDestroy(circ_buff_t *circ_buff)
{
	free(circ_buff); circ_buff = NULL;
}

size_t CircBuffWrite(circ_buff_t *circ_buff, const void *src, size_t count)
{
	size_t bytes_written = 0;
	size_t free_bytes_to_write = CircBuffFreeSpace(circ_buff);
	
	assert(NULL != src);
	assert(NULL != circ_buff);
	assert(0 != count);	
	
	if (count > free_bytes_to_write)
	{
		count = free_bytes_to_write;
	}
	
	while (bytes_written < count)
	{
		if (circ_buff->write_index == circ_buff->read_index && !CircBuffIsEmpty(circ_buff))
		{
			circ_buff->is_buffer_full = TRUE;
			break;
		}
		circ_buff->buf[circ_buff->write_index] = *((char *) src + bytes_written);
		++bytes_written;
		++circ_buff->write_index;	
	}
	return bytes_written;
}

size_t CircBuffRead(circ_buff_t *circ_buff, void *dest, size_t count)
{
	
	size_t bytes_read = 0;
	size_t fixed_bytes_read = 0;
	assert(NULL != dest);
	assert(NULL != circ_buff);
	assert(0 != count);	
	
	for (bytes_read = 0; bytes_read < count && CircBuffIsEmpty(circ_buff) == FALSE; ++bytes_read)
	{
		fixed_bytes_read = circ_buff->read_index % circ_buff->capacity;
		
		*((char *) dest + bytes_read) = circ_buff->buf[fixed_bytes_read];
		
		++circ_buff->read_index;
	}
	
	if (0 < bytes_read)
	{
		circ_buff->is_buffer_full = FALSE; /* when done writing, buffer isn't
											  full if read more than 0 bytes */
	}
	
	return bytes_read; 
}


int CircBuffIsEmpty(const circ_buff_t *circ_buff)
{
	assert(NULL != circ_buff);

	if ((circ_buff->read_index == circ_buff->write_index)
										&& (FALSE == circ_buff->is_buffer_full))
	{
		return TRUE;
	}
	return FALSE;
}

size_t CircBuffCapacity(const circ_buff_t *circ_buff)
{
	assert(NULL != circ_buff);
	return circ_buff->capacity;
}

size_t CircBuffFreeSpace(const circ_buff_t *circ_buff)
{
	int taken = 0;
	assert(NULL != circ_buff);
	
	taken = circ_buff->write_index - circ_buff->read_index;
	
	if (taken < 0)
	{
		taken *= (-1); /* flip sign */
	}
	
	return circ_buff->capacity - (size_t) taken;
}
