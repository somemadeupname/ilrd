#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define CCHAR '123'
#define CINT 0x313233
#define IS_LITTLE_ENDIAN (CCHAR == CINT)

int IsSystemLittleEndian()
{
	int var = 1;
	int *var_p = &var;
	/* 		assign value which can be represented by
	   		8 least sig bits in int (-256-255) 			*/
	int big_value = 5;

	 /* assign int 5 into 4th byte on the right of var */
	*((char*)(var_p) + 3) = big_value;
	
	return (big_value == *var_p ? FALSE : TRUE);
}
