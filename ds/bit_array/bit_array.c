#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include "bit_array.h"

#define NUM_MAX_BITS 64
#define SIZE_OF_BYTE 8

/* Bits set in byte LUT*/
static unsigned int bit_count_lut[256] = 
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
    
    3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
    
    3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
    
    4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
    
    3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
    
    6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
    
    4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
    
    6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
    
    3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
    
    4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
    
    6, 7, 6, 7, 7, 8
};

/* Bit Mirror LUT*/
static unsigned char bit_mirror_lut[256] = 
{ 
	0x0  , 0x80 , 0x40 , 0xC0 , 0x20 , 0xa0 , 0x60 , 0xe0 , 0x10 , 0x90 ,
	0x50 , 0xD0 , 0x30 , 0xB0 , 0x70 , 0xF0 , 0x8  , 0x88 , 0x48 , 0xC8 ,
	0x28 , 0xA8 , 0x68 , 0xE8 , 0x18 , 0x98 , 0x58 , 0xD8 , 0x38 , 0xB8 ,
	0x78 , 0xF8 , 0x4  , 0x84 , 0x44 , 0xC4 , 0x24 , 0xA4 , 0x64 , 0xE4 ,
	0x14 , 0x94 , 0x54 , 0xD4 , 0x34 , 0xB4 , 0x74 , 0xF4 , 0xC  , 0x8C ,
	0x4C , 0xCC , 0x2C , 0xAC , 0x6C , 0xEC , 0x1C , 0x9C , 0x5C , 0xDC ,
	0x3C , 0xBC , 0x7C , 0xFC , 0x2  , 0x82 , 0x42 , 0xC2 , 0x22 , 0xA2 ,
	0x62 , 0xE2 , 0x12 , 0x92 , 0x52 , 0xD2 , 0x32 , 0xB2 , 0x72 , 0xF2 ,
	0xA  , 0x8A , 0x4A , 0xCA , 0x2A , 0xAA , 0x6A , 0xEA , 0x1A , 0x9A ,
	0x5A , 0xDA , 0x3A , 0xBA , 0x7A , 0xFA , 0x6  , 0x86 , 0x46 , 0xC6 ,
	0x26 , 0xA6 , 0x66 , 0xE6 , 0x16 , 0x96 , 0x56 , 0xD6 , 0x36 , 0xB6 ,
	0x76 , 0xF6 , 0xE  , 0x8E , 0x4E , 0xCE , 0x2E , 0xAE , 0x6E , 0xEE ,
	0x1E , 0x9E , 0x5E , 0xDE , 0x3D , 0xBE , 0x7E , 0xFE , 0x1  , 0x81 ,
	0x41 , 0xC1 , 0x21 , 0xA1 , 0x61 , 0xE1 , 0x11 , 0x91 , 0x51 , 0xD1 ,
	0x31 , 0xB1 , 0x71 , 0xF1 , 0x9  , 0x89 , 0x49 , 0xC9 , 0x29 , 0xA9 ,
	0x69 , 0xE9 , 0x19 , 0x99 , 0x59 , 0xD9 , 0x39 , 0xB9 , 0x79 , 0xF9 ,
	0x5  , 0x85 , 0x45 , 0xC5 , 0x25 , 0xA5 , 0x65 , 0xE5 , 0x15 , 0x95 ,
	0x55 , 0xD5 , 0x35 , 0xB5 , 0x75 , 0xF5 , 0xD  , 0x8D , 0x4D , 0xCD ,
	0x2D , 0xAD , 0x6D , 0xED , 0x1D , 0x9D , 0x5D , 0xDD , 0x3D , 0xBD ,
	0x7D , 0xFD , 0x3  , 0x83 , 0x43 , 0xC3 , 0x23 , 0xA3 , 0x63 , 0xE3 ,
	0x13 , 0x93 , 0x53 , 0xD3 , 0x33 , 0xB3 , 0x73 , 0xF3 , 0xB  , 0x8B ,
	0x4B , 0xCB , 0x2B , 0xAB , 0x6B , 0xEB , 0x1B , 0x9B , 0x5B , 0xDB ,
	0x3B , 0xBB , 0x7B , 0xFB , 0x7  , 0x87 , 0x47 , 0xC7 , 0x27 , 0xA7 ,
	0x67 , 0xE7 , 0x17 , 0x97 , 0x57 , 0xD7 , 0x37 , 0xB7 , 0x77 , 0xF7 ,
	0xF  , 0x8F , 0x4F , 0xCF , 0x2F , 0xAF , 0x6F , 0xEF , 0x1F , 0x9F ,
	0x5F , 0xDF , 0x3F , 0xBF , 0x7F , 0xFF
};


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

/* 
 * Counts on bits in a bit array, must be implemented with a lookup table
 * Param bit_array: the bit array
 * Returns: number of on bits
 * Errors: none
 */
size_t BitArrCountOnBitsLUT(bitarray_t bit_array)
{
	size_t byte_index = 0;
	unsigned long mask = 0x0000000000000FFLU;
	unsigned long on_bits_counter = 0LU;
	
	for (byte_index = 0; byte_index < SIZE_OF_BYTE; ++byte_index)
	{
		on_bits_counter =
		on_bits_counter +
		bit_count_lut[(bit_array & mask) >> (SIZE_OF_BYTE * byte_index)];
		mask = (mask << SIZE_OF_BYTE);
	}
	return on_bits_counter;
}

size_t BitArrCountOffBitsLUT(bitarray_t bit_array)
{
	return (NUM_MAX_BITS - BitArrCountOnBitsLUT(bit_array));
}

bitarray_t BitArrBitMirrorLUT(bitarray_t bit_array)
{
	size_t byte_index = 0;
	unsigned long mask = 0x0000000000000FFLU;
	unsigned long mirrored = 0LU;
	/* mask SIZE_OF_BYTE - 1 of the bytes in each iteration */
	for (byte_index = 0; byte_index < SIZE_OF_BYTE; ++byte_index)
	{
		mirrored =
		bit_mirror_lut[(bit_array & mask) >> (SIZE_OF_BYTE * byte_index)];
		mask <<= SIZE_OF_BYTE;
		mirrored <<= SIZE_OF_BYTE;
	}
	return mirrored;
}

