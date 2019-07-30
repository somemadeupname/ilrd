#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*int CompareTwoArrays(*/

unsigned long CreateWordFromInt(int c)
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
			printf("i'm here1\n");
			n -= 8;
			s_cur += 8;
		}
		else /* if n < 8 or address is not divisible by 8*/
		{
			/* write byte by byte*/
			printf("i'm here2\n");			
			*(unsigned char *)s_cur = (unsigned char) c;
			--n;
			++s_cur;
		}
	}
	assert (0 == n);
	return s_start;
}

int main()
{
	int c = 5; /* can only contain values represented by char 0-255 since it is later set as char */
	int orig[10] = {0};
	int mine[10] = {0};

	size_t i = 0;
	printf("sizeof(src)=%lu.\n", sizeof(orig));
	
	printf("CreateWordFromInt(%d) = %lu.\n", c, CreateWordFromInt(c));
	
	printf("src address: %ld\n", &orig[i]);
	printf("OffsetFromAddressDivisibleByEight(src) = %d\n", OffsetFromNextAddressDivisibleByEight(orig));
	memset((char *) orig, c + 1, 39);	
	Memset((char *) mine, c + 1, 39);			
	
	for (i = 0; i < 10; ++i)
	{
		printf("orig[%lu] = %10d\n", i, orig[i]);
	}
	printf("\n");

	for (i = 0; i < 10; ++i)
	{
		printf("mine[%lu] = %10d\n", i, mine[i]);
	}	
	
	return 0;
}
