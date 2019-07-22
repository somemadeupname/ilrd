#include <stdio.h>
#include "ws6.h"

void IsPowOf2Test()
{
	printf("########### IsPowOf2 Test ################\n");
	printf("IsPowOf2(%u) = %d.\n", 	2, IsPowOf2(2));
	printf("IsPowOf2(%u) = %d.\n", 	3, IsPowOf2(3));
	printf("IsPowOf2(%u) = %d.\n", 	0, IsPowOf2(0));
	printf("IsPowOf2(%u) = %d.\n", 	1024, IsPowOf2(1024));
	printf("IsPowOf2(%u) = %d.\n", 	33554432, IsPowOf2(33554432));
	printf("IsPowOf2(%u) = %d.\n", 	16777217, IsPowOf2(16777217));
}

void AddOneTest()
{
	printf("########### AddOneTest Test ################\n");
	printf("AddOne(%u) = %u.\n", 	1, AddOne(1));
	printf("AddOne(%u) = %u.\n", 	0, AddOne(0));
	printf("AddOne(%u) = %u.\n", 	13, AddOne(13));
}

void PrintThreeBitsTest()
{
	const unsigned int arr[] = {119,1,29,3,4,7,14,9,16,32,42}; /* 11 elements */
	printf("########### PrintThreeBits Test ################\n");
	PrintThreeBits(arr,11);
}

void CountSetBitsLoopTest()
{
	printf("########### CountSetBitsLoop Test ################\n");
	printf("AddOne(%u) = %u.\n", 	13,CountSetBitsLoop(13));
	printf("AddOne(%u) = %u.\n", 	0, CountSetBitsLoop(0));
	printf("AddOne(%u) = %u.\n", 	1, CountSetBitsLoop(1));
	printf("AddOne(%u) = %u.\n", 	10, CountSetBitsLoop(10));
	printf("AddOne(%u) = %u.\n", 	123123, CountSetBitsLoop(123123));
	printf("AddOne(%u) = %u.\n", 	1048576, CountSetBitsLoop(1048576));
}

int main()
{
	/* IsPowOf2 Test */
	/*IsPowOf2Test();*/
	
	/* AddOne Test*/
	/*AddOneTest();*/
	
	/* PrintThreeBits Test */
	/*PrintThreeBitsTest();*/
	
	/* CountSetBitsLoop Test */
	CountSetBitsLoopTest();
	
	return 0;
}
