#ifndef __OL71_BUFFER_H
#define __OL71_BUFFER_H

#include <stddef.h> /* size_t */

typedef struct buffer circ_buff_t;

enum
{
    BUFFER_SUCCESS,
    BUFFER_WRITE_FAILED,
	BUFFER_READ_FAILED
}

/*
 * Create circular buffer
 * Params: init_capacity, size_of_element
 * Return: pointer to the created buffer
 * Errors: if buffer creation failed returns NULL 
 */
circ_buff_t *CircBuffCreate(size_t init_capacity);

/* 
 * Destroy the buffer
 * Params: pointer to buffer 
 */
void CircBuffDesroy(circ_buff_t *circ_buff);

/* 
 * Write count bytes to the circ_buff to buf
 * Params: circ_buff, buf, count
 * Return: BUFFER_SUCCESS, BUFFER_WRITE_FAILED
 * Errors: if writing is failed returns BUFFER_WRITE_FAILED
 */
int CircBuffWrite(circ_buff_t *circ_buff, const void *src, size_t count);

/* 
 * Read count bytes from the buf to circ_buff
 * Params: circ_buff, buf, count
 * Return: BUFFER_SUCCESS, BUFFER_READ_FAILED
 * Errors: if reading is failed returns BUFFER_READ_FAILED
 */
int CircBuffRead(circ_buff_t *circ_buff, void *dest, size_t count);

/*
 * Check if buffer is empty
 * Params: pointer to buffer
 * Return: if buffer is empty 1, else 0
 * Errors: if buffer points to unreadable address, behavior is undefined
 */
int CircBuffIsEmpty(const circ_buff_t *circ_buff);

/* 
 * Get the buffer capacity
 * Params: pointer to buffer 
 * Return: current capacity of buffer 
 */
size_t CircBuffCapacity(const circ_buff_t *circ_buff);

/*
 * Get size of free space of buffer
 * Params: pointer to buffer 
 * Return: current free space of buffer 
 */
size_t CircBuffFreeSpace(const circ_buff_t *circ_buff);

#endif /* __OL71_BUFFER_H */

