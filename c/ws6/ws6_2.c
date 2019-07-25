#define ON_BITS_REFERENCE 34 /* 100010 for AreBothBitsOn */
#define ON_BITS_REFERENCE_ONE 32 /* 100000 for IsOneBitOn */
#define ON_BITS_REFERENCE_TWO 2 /* 000010 for AreBothBitsOn */

/****************** Q9 ******************
*	Author 	 : 	Shieber
*	Reviewer :  Daya
*	
*			CountSetBitsLoop
****************************************/
unsigned int CountSetBitsLoop(unsigned int num)
{
	unsigned int num_of_on_bits = 0;
	unsigned int mask = 1;
	
	while (num > 0)
	{
		if (num & mask) /* check if the rightmost bit is on in num */
		{
			++num_of_on_bits;
		}
		num >>= 1; /* decrease num by dividing it by two */
	}
	return num_of_on_bits;
}

/*************** 6a *********************
*	
*			Approved
*	
*			AreBothBitsOn
****************************************/
int AreBothBitsOn(unsigned char uchar)
{
	/* using the number defined in the macro - see if it matches the set bits */
	return (ON_BITS_REFERENCE == (ON_BITS_REFERENCE & uchar));
}

/*************** 6b *********************
*	
*	
*	
*			AreBothBitsOn
****************************************/
int IsOneBitOn(unsigned char uchar)
{
	/* masks get the value where the relevant single bit are on */
	unsigned char mask1 = ON_BITS_REFERENCE_ONE;
	unsigned char mask2 = ON_BITS_REFERENCE_TWO;
	
	/* mask# & uchar returns 0 if the on bit in the mask doesn't match its
	equivalent in uchar. returns uchar if it's on
	!! returns 1 if the receives result is not zero, zero otherwise  */	
	return ( !!( (mask1 & uchar) | (mask2 & uchar) ) );
}

/*************** Q 6c *******************
*	
*	
*	
*			SwapBits
****************************************/

unsigned char SwapBits(unsigned char uchar)
{
	unsigned char mask = 1;
	unsigned char bit_3 = ((uchar>>2) & mask);
	unsigned char bit_5 = ((uchar>>4) & mask);
	uchar = (uchar & 235); /* 11101011 switch off bits 3 and 5 */
	uchar = (uchar | (bit_3 << 4)); /* shift the bit to location 5 */
	uchar = (uchar | (bit_5 << 2)); /* shift bit to location 3 */
	
	return uchar;
}

/*************** Q 7 ********************
*	
*	
*	
*			ClosestMultiplyOf16
****************************************/
unsigned int ClosestMultiplyOf16(unsigned int num)
{
	return num & 0xFFFFFFF0;
}

/*************** Q 8 ********************
*	
*	
*	
*			SwapVars
****************************************/
void SwapVars(unsigned int *a, unsigned int *b)
{	
	if (a != b)
	{
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;	
	}
}
