#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include "bit_array.h"

#define NUM_MAX_BITS 64


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
		/* check if the rightmost bit is on in bit_array */
		if (bit_array & mask) 
		{
			++num_of_on_bits;
		}
		/* decrease bit_array by dividing it by two */		
		bit_array >>= 1;
	}
	return num_of_on_bits;
}

size_t BitArrCountOffBits(bitarray_t bit_array)
{
	return (NUM_MAX_BITS - BitArrCountOnBits(bit_array));
}
/* helper function for BitArrBitToStr which reverses
   the string bit representation 					 */
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
	
	for (index = 0; index < NUM_MAX_BITS; ++index)
	{
		if (bit_array & mask)/* check if the rightmost bit is on in bit_array */
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
	/* bring the set bit to the bit_index
	location and switch it on in bit_array */
	unsigned long mask = 1LU;	
	return (bit_array | (mask << bit_index));
}

bitarray_t BitArrSetBitOff(bitarray_t bit_array, size_t bit_index)
{
	unsigned long full_mask = 0xFFFFFFFFFFFFFFFFLU;
	unsigned long mask = 1LU;	
	full_mask = full_mask & ~(mask << bit_index);
	return (bit_array & full_mask);
}

bitarray_t BitArrSetBit(bitarray_t bit_array, size_t bit_index, int value)
{
	unsigned long mask = 1LU;		
	if (1 == value)
	{
		bit_array = (bit_array | (mask << bit_index));
	}
	else /* if (0 == value) */
	{
		bit_array = (bit_array & ~(mask << bit_index));	
	}		
	return bit_array;
}

bitarray_t BitArrFlipBit(bitarray_t bit_array, size_t bit_index)
{
	unsigned long mask = 1LU;
	unsigned long bit_value = bit_array & (mask << bit_index);
	unsigned long full_mask = 0xFFFFFFFFFFFFFFFFLU;
	full_mask = full_mask & ~(mask << bit_index);	
	
	if (0 != bit_value) /* if it's on - switch it off */
	{
		bit_array = bit_array & full_mask;
	}
	else /* 0 == bit_value */
	{
		bit_array = bit_array | (mask << bit_index);
	}

	return bit_array;
}

bitarray_t BitArrFlipAllBits(bitarray_t bit_array)
{
	return ~bit_array;
}

bitarray_t BitArrSetAllBitsOn(bitarray_t bit_array)
{
	return bit_array = (bitarray_t) 0xFFFFFFFFFFFFFFFFLU;
}

bitarray_t BitArrSetAllBitsOff(bitarray_t bit_array)
{
	return bit_array = (bitarray_t) 0LU;
}

bitarray_t BitArrSwapBits(bitarray_t bit_array,
						  size_t bit_index1,
						  size_t bit_index2)
{
	unsigned long mask = 1LU;
	unsigned long mask2 = 0xFFFFFFFFFFFFFFFFLU;
	
	/* get the bits' values */
	unsigned long bit1 = ((bit_array>>bit_index1) & mask);
	unsigned long bit2 = ((bit_array>>bit_index2) & mask);
	
	/* switch off bit indices in bit_array */
	mask2 = (mask2 &~(mask << bit_index1));
	mask2 = (mask2 &~(mask << bit_index2));	
	
	bit_array = bit_array & mask2;
	
	/* move the bits to the relevant index and set their values to bit_array */
	bit_array = (bit_array | bit1 << bit_index2);
	bit_array = (bit_array | bit2 << bit_index1);
	
	return bit_array;
}
/*
 * Function rotates the bit_array one step to the right.
 * Param bit_array
 * Returns: The rotated bit array
 */
static bitarray_t BitArrRotateOneBitsRight(bitarray_t bit_array)
{
	#define RIGHTMOST_BIT_INDEX 0
	unsigned long rightmost_bit = BitArrIsBitSet(bit_array, RIGHTMOST_BIT_INDEX);
	unsigned long mask = 0x8000000000000000LU;/* only the rightmost bit is on */
	bit_array >>= 1LU;
	if (0 != rightmost_bit)
	{
		bit_array = (bit_array | mask);
	}
	return bit_array;	
}

bitarray_t BitArrRotateBitsRight(bitarray_t bit_array, size_t rotate_by)
{
	size_t index = 0;
	
	/* no need to rotate more than the bit_array's size */
	if (NUM_MAX_BITS < rotate_by)
	{
		rotate_by %= NUM_MAX_BITS;
	}
	
	for (index = 0; index < rotate_by; ++index)
	{
		bit_array = BitArrRotateOneBitsRight(bit_array);
	}
	
	return bit_array;
}

/*
 * Function rotates the bit_array one step to the left.
 * Param bit_array
 * Returns: The rotated bit array
 */
static bitarray_t BitArrRotateOneBitsLeft(bitarray_t bit_array)
{
	#define LEFTMOST_BIT_INDEX (NUM_MAX_BITS - 1)
	unsigned long leftmost_bit = BitArrIsBitSet(bit_array, LEFTMOST_BIT_INDEX);
	unsigned long mask = 1LU;
	bit_array <<= 1;
	if (0 != leftmost_bit)
	{
		bit_array = bit_array | mask;
	}
	return bit_array;
}

bitarray_t BitArrRotateBitsLeft(bitarray_t bit_array, size_t rotate_by)
{
	size_t index = 0;
	
	/* no need to rotate more than the bit_array's size */
	if (NUM_MAX_BITS < rotate_by)
	{
		rotate_by %= NUM_MAX_BITS;
	}
	
	for (index = 0; index < rotate_by; ++index)
	{
		bit_array = BitArrRotateOneBitsLeft(bit_array);
	}
	
	return bit_array;
}

bitarray_t BitArrBitMirror(bitarray_t bit_array)
{
	/* initializations  */
	bitarray_t mirrored = 0LU;
	unsigned long mask = 1LU;
	size_t bit_index = 0;
	
	/* iterate over bit_array bit-by-bit and switch on
	   		the opposite bit index in mirrored 		   */
	for (bit_index = 0; bit_index < NUM_MAX_BITS; ++bit_index)
	{
		mirrored <<= 1;
		mirrored |= (bit_array & mask);
		bit_array >>= 1;
	}
	return mirrored;
}
