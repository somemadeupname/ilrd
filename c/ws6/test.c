#include <stdio.h>

#define ON_BITS_REFERENCE_ONE 32 /* 100000 for IsOneBitOn */
#define ON_BITS_REFERENCE_TWO 2 /* 000010 for AreBothBitsOn */

/*
one bit:

111111 63 y
111110 62 y
111100 60 y
1111100 124 y
1100110 102 y
0000010 2 y
1000000 64 n
1000001 65 n
0		0  n
*/

int main()
{
	unsigned char c = 0;
	
	unsigned char mask1 = 32;
	unsigned char mask2 = 2;
	/*int is_either = 0;
	
	is_either = ;*/
	
	printf("%d\n", !!( (mask1 & c) | (mask2 & c) ) );	
	return 0;
}
