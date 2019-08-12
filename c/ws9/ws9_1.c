#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BYTE_SIZE 8

/***********************
*
*	Author: Shieber
*	Reviewer: Lila
*	Status : Sent Again
***********************/

/************************************************
*
*	Static function used by Memcpy and Memset
*
*	input: int c
*
*	output:
*	word sized representation of c and
*
*************************************************/
static unsigned long CreateWordFromInt(int c)
{
	unsigned long word = 0; 
	unsigned char relevant_byte = (unsigned char) c;
	size_t byte_index = 0;
	
	for (byte_index = 0; byte_index < BYTE_SIZE; ++byte_index)
	{
		word += relevant_byte;
		word <<= BYTE_SIZE;		
	}
	word += relevant_byte;			
	return word;
}
/************************************************
*
*	Static function used by Memcpy and Memset
*
*	input: const void * address
*
*	output:
*	8 if address is divisible by 8
*	Offest from next address divisible by 8
*
*************************************************/

static int OffsetFromNextAddressDivisibleByEight(const void *address)
{
    return ( BYTE_SIZE - ((unsigned long)address % BYTE_SIZE));
}

/* helper function which copies byte by byte from src to dest */
static void CopyByteByByte(char *dest, const char *src, size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);

	while(n > 0)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
}

/************************************************
*
*	Memset
*
*	input: void * s, int c, size_t n
*
*	
*	sets n bytes of c into s
*
*************************************************/

void *Memset(void *s, int c, size_t n)
{
	void *s_start = s;
	unsigned char *s_cur = (unsigned char *) s;
	assert(NULL != s);	
	
	while (n > 0)
	{
		if (( n >= BYTE_SIZE) && ( BYTE_SIZE ==
								  OffsetFromNextAddressDivisibleByEight(s_cur)))
		{
			*(unsigned long *) s_cur = CreateWordFromInt(c);
			n -= BYTE_SIZE;
			s_cur += BYTE_SIZE;
		}
		else /* if n < 8 or address is not divisible by 8*/
		{
			/* write byte by byte*/
			*(unsigned char *)s_cur = (unsigned char) c;
			--n;
			++s_cur;
		}
	}
	assert (0 == n); /* confirm n bytes where written */
	return s_start;
}
/************************************************
*												*
*	Memcpy
*												*
*	input: void* dest, const void* src, size_t n*
*												*
*	
*												*
*	Copies n bytes from src to dest				*
*												*
*************************************************/
void *Memcpy (void *dest, const void *src, size_t n)
{
	char *dest_current = dest;
	const char *src_current = src;
	int c = 0;

	assert(NULL != src);
	assert(NULL != dest);
	
	while (n > 0)
	{
		if ((n >= BYTE_SIZE) && (BYTE_SIZE ==
								   OffsetFromNextAddressDivisibleByEight(dest)))
		{
			c = *(int *) src_current;
			*(unsigned long *) dest_current = CreateWordFromInt(c);
			n -= BYTE_SIZE;
			src_current += BYTE_SIZE;
			dest_current += BYTE_SIZE;
		}
		else /* if address is not aligned or n < 8 */
		{
			c = *(int *) src_current;
			n -= 1;
			++src_current;
			++dest_current;
		}
	}
	assert(0 == n);
	return dest;
}

/************************************************
*
*	Memmove
*
*	input: void* dest, const void* src, size_t n
*
*	Copies n bytes from src to dest even if they
*	overlap.
*
*************************************************/
void *Memmove(void *dest, const void *src, size_t n)
{
	/* Declarations */
	const char *src_current = src;
	char *dest_current = dest;
	
	/* Asserts */		
	assert (NULL != dest);
	assert (NULL != src);
	
	if (src_current > dest_current)
	{
		CopyByteByByte(dest_current, src_current, n);
	}
	else /* src_current < dest_current */
	{
		/* advance pointers to the end and copy backwards */
		src_current += n - 1;
		dest_current += n - 1;
		
		while (n > 0)
		{
			*dest_current = *src_current;
			--dest_current;
			--src_current;
			--n;
		}
	}
	return dest;
}
