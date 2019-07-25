#include <stdio.h>
#include <stddef.h>

#define NUM_BITS_REPRESENTING_FLOAT 32

/****************** Q11 ****************
* 	
*				
*	
*			PrintFloat
****************************************/
void PrintFloat(float fnum)
{
	unsigned int mask = 0x80000000;	/*1 and 31 zeros*/
	/* to be able to print a floating point's bits, 
	it is first required to cast it to an integer */
	unsigned int *float_p = (unsigned int *) &fnum;
	
	size_t cur_bit = 0;
	
	for (cur_bit = 0; cur_bit < NUM_BITS_REPRESENTING_FLOAT; ++cur_bit)
	{
		printf("%u", (*float_p & mask)>>31);
		*float_p <<=1; /* shift the value pointed
						  by float_p to the left
						  in each iteration */
	}
	printf("\n");
}
