#include <stdio.h>

#define TRUE 1
#define FALSE 0

int IsSystemLittleEndian()
{
	int var = 1;
	int *var_p = &var;
	/* 		assign value which can be represented by
	   		8 least sig bits in int (-256-255) 			*/
	int big_value = 5;

	 /* assign int 4 into 4th byte on the right of var */
	*((char*)(var_p) + 3) = big_value;
	
	return (big_value == *var_p ? FALSE : TRUE);
}

int main()
{
	printf ("IsSystemLittleEndian() = %d\n", IsSystemLittleEndian());
	return 0;
}
