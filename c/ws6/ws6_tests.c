#include <stdio.h>
#include "ws6.h"

void Pow2Test()
{
	/*
	printf("########### Pow2 Test ################\n");
	printf("IsPowOf2(%u,%u) = %d.\n", 0, 0 , Pow2(0,0));
	printf("IsPowOf2(%u,%u) = %d.\n", 1, 1 , Pow2(1,1));
	printf("IsPowOf2(%u,%u) = %d.\n", 1, 1 , Pow2(1,1));
	printf("IsPowOf2(%u,%u) = %d.\n", 1, 1 , Pow2(1,1));
	printf("IsPowOf2(%u,%u) = %d.\n", 1, 1 , Pow2(1,1));
	*/
}

void IsPowOf2Test()
{
	/*
	printf("########### IsPowOf2 Test ################\n");
	printf("IsPowOf2(%u) = %d.\n", 	2, IsPowOf2(2));
	printf("IsPowOf2(%u) = %d.\n", 	3, IsPowOf2(3));
	printf("IsPowOf2(%u) = %d.\n", 	0, IsPowOf2(0));
	printf("IsPowOf2(%u) = %d.\n", 	1024, IsPowOf2(1024)); 2**10 
	printf("IsPowOf2(%u) = %d.\n", 	2147483648, IsPowOf2(2147483648)); 2**35 
	printf("IsPowOf2(%u) = %d.\n", 	16777217, IsPowOf2(16777217));  not pow of 2
	*/
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
	/* 01110111, 1 , 00011101, 00000011, 100, 111,  */
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

void AreBothBitsOnTest()
{
	/*
111111 63 y
111110 62 y
111100 60 n
1111100 124 n
1100110 102 y
0000010 2 n
*/
	printf("########### AreBothBitsOn Test ################\n");
	printf("AreBothBitsOn(%u) = %d.\n", 63 ,AreBothBitsOn(63));
	printf("AreBothBitsOn(%u) = %d.\n", 62 ,AreBothBitsOn(62));
	printf("AreBothBitsOn(%u) = %d.\n", 60 ,AreBothBitsOn(60));
	printf("AreBothBitsOn(%u) = %d.\n", 124 ,AreBothBitsOn(124));	
	printf("AreBothBitsOn(%u) = %d.\n", 102 ,AreBothBitsOn(102));			
	printf("AreBothBitsOn(%u) = %d.\n", 2 ,AreBothBitsOn(2));				
}

void IsOneBitOnTest()
{
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
	printf("########### IsOneBitOn Test ################\n");
	printf("IsOneBitOn(%u) = %d.\n", 63 ,IsOneBitOn(63));
	printf("IsOneBitOn(%u) = %d.\n", 62 ,IsOneBitOn(62));
	printf("IsOneBitOn(%u) = %d.\n", 60 ,IsOneBitOn(60));
	printf("IsOneBitOn(%u) = %d.\n", 124 ,IsOneBitOn(124));	
	printf("IsOneBitOn(%u) = %d.\n", 102 ,IsOneBitOn(102));			
	printf("IsOneBitOn(%u) = %d.\n", 2 ,IsOneBitOn(2));					
	printf("IsOneBitOn(%u) = %d.\n", 64 ,IsOneBitOn(64));					
	printf("IsOneBitOn(%u) = %d.\n", 65 ,IsOneBitOn(65));					
	printf("IsOneBitOn(%u) = %d.\n", 0 ,IsOneBitOn(0));								
}

void ByteMirrorLoopedTest()
{
	printf("########### ByteMirrorLooped Test ################\n");
	printf("ByteMirrorLooped(%u) = %u.\n", 6 ,ByteMirrorLooped(6)); /* 3 */
	printf("ByteMirrorLooped(%u) = %u.\n", 5 ,ByteMirrorLooped(5)); /* 5 */
	printf("ByteMirrorLooped(%u) = %u.\n", 42 ,ByteMirrorLooped(42)); /*21*/
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
	/*CountSetBitsLoopTest();*/
	
	/* AreBothBitsOn Test */
	/* AreBothBitsOnTest(); */
	
	/*IsOneBitOn Test*/
	/*sOneBitOnTest();*/
	
	/* ByteMirrorLooped Test */
	ByteMirrorLoopedTest();
	
	return 0;
}
