#include <stdio.h>
#include "ws6.h"

void Pow2Test()
{
	
	printf("########### Pow2 Test ################\n");
	printf("Pow2(%u,%d) = %ld.\n", 0, 0 , Pow2(0,0));
	printf("Pow2(%u,%d) = %ld.\n", 1, 2 , Pow2(1,2));
	printf("Pow2(%u,%d) = %ld.\n", 1, 5 , Pow2(1,5));
	printf("Pow2(%u,%d) = %ld.\n", 6, -3 , Pow2(6,-3));
	printf("Pow2(%u,%d) = %ld.\n", 5, -2 , Pow2(5,-2));
	printf("Pow2(%u,%d) = %ld.\n", 2147483647, 2 , Pow2(2147483647,2));	
	
}

void IsPowOfTwoLoopTest()
{
	
	printf("########### IsPowOfTwoLoop Test ################\n");
	printf("IsPowOf2(%u) = %d.\n", 	2, IsPowOfTwoLoop(2));
	printf("IsPowOf2(%u) = %d.\n", 	3, IsPowOfTwoLoop(3));
	printf("IsPowOf2(%u) = %d.\n", 	0, IsPowOfTwoLoop(0));
	printf("IsPowOf2(%u) = %d.\n", 	1024, IsPowOfTwoLoop(1024)); /* 2**10 */
	printf("IsPowOf2(%lu) = %d.\n", 	2147483648, IsPowOfTwoLoop(2147483648)); /* 2**35 */
	printf("IsPowOf2(%u) = %d.\n", 	16777217, IsPowOfTwoLoop(16777217)); /* not pow of 2 */
	
}

void IsPowOfTwoTest()
{
	printf("########### IsPowOfTwo Test ################\n");
	printf("IsPowOfTwo(%u) = %d.\n", 	2, IsPowOfTwo(2));
	printf("IsPowOfTwo(%u) = %d.\n", 	3, IsPowOfTwo(3));
	printf("IsPowOfTwo(%u) = %d.\n", 	0, IsPowOfTwo(0));
	printf("IsPowOfTwo(%u) = %d.\n", 	1024, IsPowOfTwo(1024)); /* 2**10 */
	printf("IsPowOfTwo(%lu) = %d.\n", 	2147483648, IsPowOfTwo(2147483648)); /* 2**35 */
	printf("IsPowOfTwo(%u) = %d.\n", 	16777217, IsPowOfTwo(16777217)); /* not pow of 2 */
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
	printf("CountSetBitsLoop(%u) = %u.\n", 	13,CountSetBitsLoop(13));
	printf("CountSetBitsLoop(%u) = %u.\n", 	0, CountSetBitsLoop(0));
	printf("CountSetBitsLoop(%u) = %u.\n", 	1, CountSetBitsLoop(1));
	printf("CountSetBitsLoop(%u) = %u.\n", 	10, CountSetBitsLoop(10));
	printf("CountSetBitsLoop(%u) = %u.\n", 	123123, CountSetBitsLoop(123123));
	printf("v(%u) = %u.\n", 	1048576, CountSetBitsLoop(1048576));
}

void AreBothBitsOnTest()

	/*
111111 63 y
111110 62 y
111100 60 n
1111100 124 n
1100110 102 y
0000010 2 n
*/

{
	printf("########### AreBothBitsOn Test ################\n");
	printf("AreBothBitsOn(%u) = %d.\n", 63 ,AreBothBitsOn(63));
	printf("AreBothBitsOn(%u) = %d.\n", 62 ,AreBothBitsOn(62));
	printf("AreBothBitsOn(%u) = %d.\n", 60 ,AreBothBitsOn(60));
	printf("AreBothBitsOn(%u) = %d.\n", 124 ,AreBothBitsOn(124));	
	printf("AreBothBitsOn(%u) = %d.\n", 102 ,AreBothBitsOn(102));			
	printf("AreBothBitsOn(%u) = %d.\n", 2 ,AreBothBitsOn(2));				
}


void IsOneBitOnTest()
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
	
{
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

void ByteMirrorLoopTest()
{
	printf("########### ByteMirrorLooped Test ################\n");
	printf("ByteMirrorLooped(%u) = %u.\n", 6 ,ByteMirrorLoop(6)); /* 3 */
	printf("ByteMirrorLooped(%u) = %u.\n", 5 ,ByteMirrorLoop(5)); /* 5 */
	printf("ByteMirrorLooped(%u) = %u.\n", 42 ,ByteMirrorLoop(42)); /*21*/
}

void SwapBitsTest()
{
	printf("########### SwapBits Test ################\n");
	printf("SwapBits(%u) = %u.", 251 ,SwapBits(251)); /* 251 <-> 239 */	
	printf(" expected: 239\n");
	printf("SwapBits(%u) = %u.", 200 ,SwapBits(200)); /* should stay 200*/
	printf(" expected: 200\n");	
	printf("SwapBits(%u) = %u.", 174 ,SwapBits(174)); /* 174 <-> 186 */
	printf(" expected: 186\n");		
}

void ClosestMultiplyOf16Test()
{
	printf("########### ClosestMultiplyOf16 Test ################\n");
	printf("ClosestMultiplyOf16(%u) = %u.", 34 ,ClosestMultiplyOf16(34));
	printf(" expected: 32\n");		
	printf("ClosestMultiplyOf16(%u) = %u.", 66 ,ClosestMultiplyOf16(66));
	printf(" expected: 64\n");		
	printf("ClosestMultiplyOf16(%u) = %u.", 60 ,ClosestMultiplyOf16(60));
	printf(" expected: 48\n");		
	printf("ClosestMultiplyOf16(%u) = %u.", 16 ,ClosestMultiplyOf16(16));
	printf(" expected: 16\n");		
	printf("ClosestMultiplyOf16(%u) = %u.", 129 ,ClosestMultiplyOf16(129));
	printf(" expected: 128\n");		
}

void SwapVarsTest()
{
	unsigned int a = 1;
	unsigned int b = 2;
	SwapVars(&a,&b);
	printf("a=%d, b=%d.\n", a,b);
}

void PrintFloatTest()
{
	printf("########### PrintFloat Test ################\n");
	PrintFloat(13.44f);
	PrintFloat(-13.44f);
}

int main()
{
	/* Pow2Test Test */	
	/*Pow2Test();*/
	
	/* IsPowOfTwoLoop Test */
	/*IsPowOfTwoLoopTest();*/
	
	/* IsPowOfTwo Test */
	IsPowOfTwoTest();
	
	/* AddOne Test*/
	/*AddOneTest();*/
	
	/* PrintThreeBits Test */
	/*PrintThreeBitsTest();*/
	
	/* CountSetBitsLoop Test */
	/*CountSetBitsLoopTest();*/
	
	/* AreBothBitsOn Test */
	/*AreBothBitsOnTest();*/
	
	/*IsOneBitOn Test*/
	/*IsOneBitOnTest();*/
	
	/* ByteMirrorLooped Test */
	/*ByteMirrorLoopTest();*/
	
	/* SwapBits Test */
	/*SwapBitsTest();*/
	
	/* ClosestMultiplyOf16 Test*/
	/*ClosestMultiplyOf16Test();*/
	
	/* SwapVars Test */
	/*SwapVarsTest();*/
	
	/* PrintFloat Test */
	PrintFloatTest();
	
	return 0;
}
