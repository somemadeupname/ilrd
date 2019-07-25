#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */


/* for PrintThreeBits */
#define NUM_ON_BITS_TO_PRINT 3
#define NUM_OF_BINARY_DIGITS 32

/***************** Q1 **********************
*	Author 	 : 	Shieber
*	Reviewer :  Daya
		
			Approved
*	
*			Pow2
****************************************/

unsigned long Pow2(unsigned int x, int y)
{
	unsigned long res = 0;
	
	if (y < 0)
	{
		y = -y;
		res = (unsigned long)(x>>y);
	}
	else /* y >= 0 */
	{
		/* only casting x to unsigned long to prevent overflow */
		res = ((unsigned long)x)<<y;
	}
	return res;
}

/***************** Q2a ********************
* 	
* 		returns if n is a power of two
*		in binary this means it only
*		has one on bit.
*
			Approved
*	
*			IsPowOfTwoLoop
****************************************/
int IsPowOfTwoLoop(unsigned int n)
{
	size_t num_on_bits = 0;
	unsigned int mask = 1;
	
	/* makes sure n is greater than 0 and there
	are no more than 1 on bits */
	while ((n > 0) && (num_on_bits < 2))
	{
		if (n & mask)
		{
			++num_on_bits;
		}
		n >>= 1;
	}
	return (1 == num_on_bits ? 1 : 0);
}

/***************** Q2a ********************
* 	
* 		returns if n is a power of two
*		
*
*	
*			IsPowOfTwo No loop
****************************************/
int IsPowOfTwo(unsigned int n)
{
	return (0 == (n & n-1));  
}

/***************** Q3 *******************
* 	
*			Approved
*	
*			AddOne
****************************************/
unsigned int AddOne(unsigned int num)
{
	unsigned int mask = 1;
	
	while (0 != (num & mask)) /* as long as the current bit is set to 1 */
	{
		num = num&~mask;/* switch the rightmost bit off*/
		mask <<= 1;
	}
	return (num | mask);
}

/****************** Q4 ******************
* 	
* 
*			
*			PrintThreeBits
****************************************/
void PrintThreeBits(const unsigned int arr[], size_t arr_length)
{
	size_t arr_index = 0;
	unsigned int mask = 1;
	size_t num_on_bits = 0;
	size_t binary_digit_index = 0;
	
	assert(NULL != arr);
	assert(0 != arr_length);

	for (arr_index = 0; arr_index < arr_length; ++arr_index)
	{
		/* initialize number of on bits to one each iteration for each element */	
		num_on_bits = 0;
		while ((binary_digit_index < NUM_OF_BINARY_DIGITS)
			&& (num_on_bits <= NUM_ON_BITS_TO_PRINT))
		{
			if ( arr[arr_index] & mask ) /* check if current bit is 1*/
			{
				++num_on_bits;
			}
			mask <<= 1;
			++binary_digit_index;
		}
		if (NUM_ON_BITS_TO_PRINT == num_on_bits)
		{
			printf("%u\n", arr[arr_index]);
		}
	}
}

/****************** Q5a ****************
* 	
*				
*	
*			ByteMirrorLooped
****************************************/
unsigned char ByteMirrorLoop(unsigned char uchar)
{
	unsigned char mirrored = 0;
	unsigned char mask = 1;
	size_t bit_index = 0;
	size_t num_bits = 8;

	for (bit_index = 0; bit_index < num_bits; ++bit_index)
	{
		mirrored <<= 1;
		mirrored |= (uchar & mask);
		uchar >>= 1;
	}
	return mirrored;
}
