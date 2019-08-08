#ifndef __OL71_CIRCULAR_BUFFER_H
#define __OL71_CIRCULAR_BUFFER_H

typedef struct circular_buffer circular_buffer_t;

enum 
{
	CIRC_BUFF_SUCCESS,
	CIRC_BUFF_FAILED
};

/* 
 * Create a circular buffer
 * Param 
 * Param  
 * Return : A pointer to the created vector 
 * Errors: Returns NULL if vector creation failed
 */
circular_buffer_t *CircBuffCreate(size_t num_of_elements, size_t size_of_element);

/* 
 * Destroy the circular buffer
 * Param vector: circular buffer 
 * Return: None
 * Errors: None
 */
void CircBuffDestroy(circular_buffer_t *circular_buffer);

/* 
 * Write n bytes  into buffer
 * Param 
 * Param 
 * Return: 
 * Errors: 
 */
int CircBuffWrite(circular_buffer_t *circular_buffer, void *src, size_t n);

/* 
 * 
 * 
 * Param vector: pointer to vector 
 * Return : VECTOR_SUCCESS, non-zero otherwise
 * Errors : If vector points to unreadable address or if vector is empty,
 * 			
 */
int CircBuffRead(circular_buffer_t *circular_buffer);

/* 
 * 
 * Param
 * Return
 * Errors: 
 */
int CircBuffIsEmpty(const circular_buffer_t *circular_buffer);

/* 
 * Check if vector is empty
 * Param vector: pointer to vector 
 * Return : 1 if vector is empty. 0 otherwise
 * Errors: If vector points to unreadable address, behavior is undefined
 */
int VectorIsEmpty(const vector_t *vector);

/* 
 * Get the vector capacity
 * Param vector: pointer to vector 
 * Return : current capacity of vector 
 * Errors: none
 */
size_t VectorCapacity(const vector_t *vector);

/* 
 * Request additional memory for vector
 * Param vector: pointer to vector
 * Param size: number of elements to increase capacity by
 * Return : VECTOR_SUCCESS, non-zero otherwise
 * Errors: if memory allocation failed - return VECTOR_ALLOCATION_FAILED
 */
int VectorReserve(vector_t *vector, size_t size);


#endif /* __OL71_CIRCULAR_BUFFER_H */
