#define ON_BITS_REFERENCE 34 /* 100010 for AreBothBitsOn */
#define ON_BITS_REFERENCE_ONE 32 /* 100000 for IsOneBitOn */
#define ON_BITS_REFERENCE_TWO 2 /* 000010 for AreBothBitsOn */

/***************************************
*	Author 	 : 	Shieber
*	Reviewer :  Daya
*	
*			CountSetBitsLoop
****************************************/
unsigned int CountSetBitsLoop(unsigned int num)
{
	unsigned int num_of_on_bits = 0;
	unsigned int mask = 1;
	
	while ( num > 0 )
	{
		if ( num & mask ) /* check if the rightmost bit is on in num */
		{
			++num_of_on_bits;
		}
		num >>= 1; /* decrease num by dividing it by two */
	}
	return num_of_on_bits;
}

/***************************************
*	
*	
*	
*			AreBothBitsOn
****************************************/
int AreBothBitsOn(unsigned char uchar)
{
	/* using the number defined in the macro - see if it matches the set bits */
	return (ON_BITS_REFERENCE == (ON_BITS_REFERENCE & uchar ));
}

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
