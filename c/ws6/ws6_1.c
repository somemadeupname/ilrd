#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */



/* for PrintThreeBits */
#define NUM_OF_ON_BITS_TO_PRINT 3
#define TWOS_COMP(x) (~x + 1)

/***************************************
*	Author 	 : 	Shieber
*	Reviewer :  Daya
*	
*			Pow2
****************************************/

unsigned long Pow2(unsigned int x, int y)
{
	unsigned long res = 0;
	
	if ( y < 0 )
	{
		y = TWOS_COMP(y);
		res = (unsigned long)(x>>y);
	}
	else /* y >= 0 */
	{
		res = (unsigned long) (x<<y);
	}
	return res;
}

/***************************************
* 	
* 		returns if n is a power of two
*		in binary this means it only
*		has one on bit.
*	
*			IsPowOf2
****************************************/
int IsPowOf2(unsigned int n)
{
	size_t num_of_on_bits = 0;
	unsigned int mask = 1;
	
	/* makes sure n is greater than 0 and there
	are no more than 1 on bits */
	while ( (n > 0) && (num_of_on_bits < 2) )
	{
		if (n & mask)
		{
			++num_of_on_bits;
		}
		n >>= 1;
	}
	/* if num of bit is 1 return 1:true, otherwise 0:false*/
	return (1 == num_of_on_bits ? 1 : 0);
}

/***************************************
* 	
* 
*	
*			AddOne
****************************************/
unsigned int AddOne(unsigned int num)
{
	unsigned int mask = 1;
	
	while ( 0 != (num & mask) ) /*as long as the last bit is set to 1 */
	{
		num = num&~mask;/* switch the rightmost bit off*/
		mask <<= 1; /* shift mask one bit to the left to check the next bit*/
	}
	return (num | mask); /* switch on the first bit on the right that was off to increase the number by one */
}

/***************************************
* 	
* 
*	
*			PrintThreeBits
****************************************/
void PrintThreeBits(const unsigned int arr[], size_t arr_length)
{
	size_t index = 0;
	unsigned int mask = 1;
	size_t num_of_on_bits = 0;
	unsigned int cur_num = 0;
	
	assert(NULL != arr);
	assert(0 != arr_length);
	/* iterate over each element in the array*/
	for (index = 0; index < arr_length; ++index)
	{
		/* since arr is const, insert current element into cur_num*/
		cur_num = (unsigned int) arr[index];
		/* initialize number of on bits to one each iteration for each element */
		num_of_on_bits = 0;
		while ( (cur_num > 0) && (num_of_on_bits < NUM_OF_ON_BITS_TO_PRINT + 1) )
		{
			if ( cur_num & mask ) /* check if rightmost bit is 1*/
			{
				++num_of_on_bits;
			}
			cur_num >>= 1; /* shift the numbers bits once to the right */
		}
		if (NUM_OF_ON_BITS_TO_PRINT == num_of_on_bits)
		{
			printf("%u\n", arr[index]);
		}
	}
}

/***************************************
* 	
* 
*	
*			ByteMirrorLooped
****************************************/
unsigned char ByteMirrorLooped(unsigned char num)
{
	unsigned char mirrored = 0;
	unsigned char mask = 1;
	size_t bit_index = 0;
	size_t num_bits = 8;

	for (bit_index = 0; bit_index < num_bits; ++bit_index)
	{
		mirrored <<= 1;
		mirrored |= (num & mask);
		num >>= 1;
	}
	return mirrored;
}
