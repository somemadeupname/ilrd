#include "circ_buff.h"

typedef struct buffer
{
	size_t capacity;
	void *read;
	void *write;
	char buf[1]; 
};

/*
 * Create circular buffer
 * Params: init_capacity, size_of_element
 * Return: pointer to the created buffer
 * Errors: if buffer creation failed returns NULL 
 */
circ_buff_t *CircBuffCreate(size_t init_capacity)
{
	circ_buff_t * circ_buf = (circ_buff_t *) malloc (sizeof(circ_buff_t));
}

/* 
 * Destroy the buffer
 * Params: pointer to buffer 
 */
void CircBuffDesroy(circ_buff_t *circ_buff);

