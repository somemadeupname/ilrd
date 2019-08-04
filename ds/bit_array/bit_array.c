#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include "bit_array.h"

int BitArrIsBitSet(bitarray_t bit_array, size_t bit_index)
{
	return ((bit_array & ( 1LU << bit_index)) > 0);
}

size_t BitArrCountOnBits(bitarray_t bit_array)
{
	size_t num_of_on_bits = 0;
	unsigned long mask = 1LU;
	
	while (bit_array > 0)
	{
		if (bit_array & mask) /* check if the rightmost bit is on in bit_array */
		{
			++num_of_on_bits;
		}
		bit_array >>= 1; /* decrease bit_array by dividing it by two */
	}
	return num_of_on_bits;
}

size_t BitArrCountOffBits(bitarray_t bit_array)
{
	return (64LU - BitArrCountOnBits(bit_array));
}

static void ReverseString(char *str)
{
	char *reverse = str;
	int temp = 0;
	
	assert (NULL != str);
	str += (strlen(str) - 1);

	while (reverse < str)
	{
		temp = *str;
		*str = *reverse;
		*reverse = temp;
		--str;
		++reverse;
	}
}

char *BitArrBitToStr(bitarray_t bit_array, char *str)
{
	/* init values */
	unsigned long mask = 1LU;	
	char * str_start = str;
	size_t index = 0;
	assert(NULL != str);
	
	for (index = 0; index < 64; ++index)
	{
		if (bit_array & mask) /* check if the rightmost bit is on in bit_array */
		{
			*str = (char)(1 + '0');
		}
		else /*  */
		{
			*str = (char)(0 + '0');			
		}
		++str;		
		bit_array >>= 1;
	}
	*str = '\0'; /* append terminating null char */
	
	ReverseString(str_start);
	
	return str_start;
}

bitarray_t BitArrSetBitOn(bitarray_t bit_array, size_t bit_index)
{
	unsigned long mask = 1LU;	
	return (bit_array | (mask << bit_index));
}

bitarray_t BitArrSetBitOff(bitarray_t bit_array, size_t bit_index);
{
	unsigned long mask = 1LU;	
	return (bit_array & (mask << bit_index));
}

bitarray_t BitArrSetBit(bitarray_t bit_array, size_t bit_index, int value);
