#include <stdio.h> /* perror */

/* FORWARD DECLARATIONS */

void TestBitArrCountOnBits()
{
	bitarray_t ba[3] = {1,0,1}; /* 1 + 1 + 2 = 4*/
	if (2 != BitArrCountOnBits(ba))
	{
		perror("BitArrCountOnBits failed.\n");
	}
	
}

void TestBitArrIsBitSet()
{
	bitarray_t ba[3] = {1,0,1}; /* 1 + 1 + 2 = 4*/
	if (2 != BitArrIsBitSet(ba,))
	{
		perror("BitArrCountOnBits failed.\n");
	}
	
}

int main()
{
	
	return 0;
}
