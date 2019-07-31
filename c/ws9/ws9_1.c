#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/***********************
*
*	Author: Shieber
*	Reviewer: Lila
*
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
	unsigned long word = 0; /*change this*/
	unsigned char relevant_byte = (unsigned char) c;
	size_t byte_index = 0;
	
	for (byte_index = 0; byte_index < 8; ++byte_index)
	{
		word += relevant_byte;
		word <<= 8;/* size of byte */		
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
    return ( 8 - ((unsigned long)address % 8));
}

void *Memset(void *s, int c, size_t n)
{
	void *s_start = s;
	unsigned char *s_cur = (unsigned char *) s;
	assert(NULL != s);	
	
	while (n > 0)
	{
		printf("OffsetFromNextAddressDivisibleByEight(s_cur) = %d\n", OffsetFromNextAddressDivisibleByEight(s_cur));		
		if (( n >= 8) && ( 8 == OffsetFromNextAddressDivisibleByEight(s_cur)))
		{
			*(unsigned long *) s_cur = CreateWordFromInt(c);
			n -= 8;
			s_cur += 8;
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
*	Static function used by Memcpy and Memset	*
*												*
*	input: const void * address					*
*												*
*	output:										*
*	8 if address is divisible by 8				*
*	Offest from next address divisible by 8		*
*												*
*************************************************/
void *Memcpy (void *dest, const void *src, size_t n)
{
	void *dest_start = dest;
	int c = 0;
	assert(src != dest);
	assert(NULL != src);
	assert(NULL != dest);
	
	/*
	TODO test:
	a. misaligned address
	b. =8
	c. <8
	d. >8
	e. >>8
	*/
	
	while (n > 0)
	{
		if ((n >= 8) && (8 == OffsetFromNextAddressDivisibleByEight(dest)))
		{
			c = *(int *) src;
			*(unsigned long *) dest = CreateWordFromInt(c);
			n -= 8;
			src = ((unsigned long *) src + 1);
			dest = ((unsigned long *) dest + 1);
		}
		else /* if address is not aligned or n < 8 */
		{
			c = *(int *) src;
			n -= 1;
			src =((char *) src + 1);
			dest =((char *) dest + 1);
		}
	}
	assert(0 == n);
	
	return dest_start;
}

static int DoAddressesOverlap (	const void *dest,
								const void *src,
								size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);
	return ((char *)src <= (char *) dest && ((char *)src + n) > (char *) dest);	
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
void *Memmove(void *dest, const void *src, size_t n)
{
		
		/* Declarations */
		void *src_cur = (void *) src; /* to allow dereferencing */
		
		/* Asserts */		
		assert (NULL != dest);
		assert (NULL != src);
		
		while (n > 0)
		{ /* assuming addresses are aligned */
			
			if (DoAddressesOverlap(dest, src, n))
			{
				/* copy byte-by-byte from end to start to prevent overriding */
				*((char *) dest + n - 1) = *((char *) src_cur + n - 1);
				--n;				
			}
			else /* if addresses don't overlap */
			{
				Memcpy(dest, src_cur, n);
				n = 0;
			}
		}
		/* assert that all bytes were written */
		assert(0 == n);
		
		return dest;
}

int main()
{
	int c = 5; /* can only contain values represented
				  by char 0-255 since its value is later cast as char */
	int orig[10] = {0};
	int mine[10] = {0};
	int cop[10] = {0};	

	size_t i = 0;
	printf("sizeof(src)=%lu.\n", sizeof(orig));
	
	printf("CreateWordFromInt(%d) = %lu.\n", c, CreateWordFromInt(c));
	
	printf("src address: %ld\n", &orig[i]);
	/*printf("OffsetFromAddressDivisibleByEight(src) = %d\n", OffsetFromNextAddressDivisibleByEight(orig));*/
	/*memset((char *) orig, c + 1, 39);	*/
	Memset(mine, c, 40);	
	Memcpy(cop, mine, 40);
	printf("OffsetFromAddressDivisibleByEight(cop) = %d\n", OffsetFromNextAddressDivisibleByEight(cop));
	for (i = 0; i < 10; ++i)
	{
		printf("cop[%lu] = %10d\n", i, cop[i]);
	}
	printf("\n");

	for (i = 0; i < 10; ++i)
	{
		printf("mine[%lu] = %10d\n", i, mine[i]);
	}
	
	Memmove(cop, mine, 39); 
	
	return 0;
}
