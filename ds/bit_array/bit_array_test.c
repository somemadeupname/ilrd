#include <stdio.h> /* printf */
#include "bit_array.h"

/* FORWARD DECLARATIONS */
/* 1-3 */
void TestBitArrIsBitSet();
void TestBitArrCountOnBits();
void TestBitArrCountOffBits();

/* 4-9 */
void TestBitArrBitToStr();
void TestBitArrSetBitOn();
void TestBitArrSetBitOff();
void TestBitArrSetBit();
void TestBitArrFlipBit();
void TestBitArrFlipAllBits();
/* 10-11 */
void TestBitArrSetAllBitsOn();
void TestBitArrSetAllBitsOff();

/* 12-15 */
void TestBitArrSwapBits();
void TestBitArrRotateBitsRight();
void TestBitArrRotateBitsLeft();

/* main */

int main()
{
	/* 1-3 */
	TestBitArrIsBitSet();

	TestBitArrCountOnBits();
	
	TestBitArrCountOffBits();

	/* 4-9 */
	
	TestBitArrBitToStr();
	
	TestBitArrSetBitOn();
	
	TestBitArrSetBitOff();
	
	TestBitArrSetBit();
	
	TestBitArrFlipBit();
	
	TestBitArrFlipAllBits();

	/* 10-11 */	
	TestBitArrSetAllBitsOn();

	TestBitArrSetAllBitsOff();

	/* 12-15 */
	TestBitArrSwapBits();
	
	TestBitArrRotateBitsRight();
	
	TestBitArrRotateBitsLeft();
	
	return 0;
}

/* test function implementations */

void TestBitArrIsBitSet()
{
	bitarray_t ba = 3;
	if (1 != BitArrIsBitSet(ba,1))
	{
		printf("BitArrIsBitSet failed 1.\n");
	}
	ba = 4;
	if (0 != BitArrIsBitSet(ba,1))
	{
		printf("BitArrIsBitSet failed 2.\n");
	}	
	ba = 4294967296; /* 2^32 */
	
	if (1 != BitArrIsBitSet(ba,32))
	{
		printf("BitArrIsBitSet failed 3.\n");
	}
	
	ba = 0x8000000000000000LU; 
	if (1 != BitArrIsBitSet(ba,63))
	{
		printf("BitArrIsBitSet failed 4.\n");
	}			
}

void TestBitArrCountOnBits()
{
	bitarray_t ba = 5;
	if (2 != BitArrCountOnBits(ba))
	{
		printf("BitArrCountOnBits failed 1.\n");
	}
	
	ba = 4;
	if (1 != BitArrCountOnBits(ba))
	{
		printf("BitArrCountOnBits failed 2.\n");
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (1 != BitArrCountOnBits(ba))
	{
		printf("BitArrCountOnBits failed 3.\n");
	}
	
	ba = 0xFFFFFFFFFFFFFFFFLU; 
	if (64 != BitArrCountOnBits(ba))
	{
		printf("BitArrCountOnBits failed 4.\n");
		printf("BitArrCountOnBits(0xFFFFFFFFFFFFFFFLU) = %lu.\n", BitArrCountOnBits(ba));		
	}					
}

void TestBitArrCountOffBits()
{
	bitarray_t ba = 5;
	if (62 != BitArrCountOffBits(ba))
	{
		printf("BitArrCountOffBits failed 1.\n");
		printf("BitArrCountOffBits(5) = %lu.\n", BitArrCountOffBits(ba));								
	}
	
	ba = 4;
	if (63 != BitArrCountOffBits(ba))
	{
		printf("BitArrCountOffBits failed 2.\n");
		printf("BitArrCountOffBits(4) = %lu.\n", BitArrCountOffBits(ba));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (63 != BitArrCountOffBits(ba))
	{
		printf("BitArrCountOffBits failed 3.\n");
		printf("BitArrCountOffBits(2^32) = %lu.\n", BitArrCountOffBits(ba));				
	}
	
	ba = 0xFFFFFFFFFFFFFFFFLU; 
	if (0 != BitArrCountOffBits(ba))
	{
		printf("BitArrCountOffBits failed 4.\n");
		printf("BitArrCountOffBits(0xFFFFFFFFFFFFFFFLU) = %lu.\n", BitArrCountOffBits(ba));		
	}
}

void TestBitArrBitToStr()
{
	char str1[65];
	char str2[65];
	char str3[65];
	char str4[65];
					
	bitarray_t ba = 5;
		
	printf("BitArrBitToStr(5) = %s.\n", BitArrBitToStr(ba,str1));								
	
	ba = 4;
	printf("BitArrBitToStr(4) = %s.\n", BitArrBitToStr(ba,str2));								
	
	ba = 4294967296; /* 2^32 */
	
	printf("BitArrBitToStr(2^32) = %s.\n", BitArrBitToStr(ba,str3));								
	
	ba = 0xFFFFFFFFFFFFFFFFLU; 
	printf("BitArrBitToStr(0xFFFFFFFFFFFFFFFFLU) = %s.\n", BitArrBitToStr(ba,str4));
}

void TestBitArrSetBitOn()
{	
	bitarray_t ba = 5;
	if (13 != BitArrSetBitOn(ba,3))
	{
		printf("BitArrSetBitOn failed 1.\n");
		printf("BitArrSetBitOn(5,3) = %lu.\n", BitArrSetBitOn(ba,2));								
	}
	
	ba = 10;
	if (14 != BitArrSetBitOn(ba,2))
	{
		printf("BitArrSetBitOn failed 2.\n");
		printf("BitArrSetBitOn(10,2) = %lu.\n", BitArrSetBitOn(ba,1));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (4294967297 != BitArrSetBitOn(ba,0))
	{
		printf("BitArrSetBitOn failed 3.\n");
		printf("BitArrSetBitOn(2^32) = %lu.\n", BitArrSetBitOn(ba,1));				
	}
	
	ba = 0xFFFFFFFFFFFFFFFFLU; 
	if (0xFFFFFFFFFFFFFFFFLU != BitArrSetBitOn(ba,56))
	{
		printf("BitArrSetBitOn failed 4.\n");
		printf("BitArrSetBitOn(0xFFFFFFFFFFFFFFFLU) = %lu.\n", BitArrSetBitOn(ba,56));		
	}
}

void TestBitArrSetBitOff()
{	
	bitarray_t ba = 5;
	if (1 != BitArrSetBitOff(ba,2))
	{
		printf("BitArrSetBitOff failed 1.\n");
		printf("BitArrSetBitOff(5,3) = %lu.\n", BitArrSetBitOff(ba,2));								
	}
	
	ba = 10;
	if (2 != BitArrSetBitOff(ba,3))
	{
		printf("BitArrSetBitOff failed 2.\n");
		printf("BitArrSetBitOff(10,3) = %lu.\n", BitArrSetBitOff(ba,3));	
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (0 != BitArrSetBitOff(ba,32))
	{
		printf("BitArrSetBitOff failed 3.\n");
		printf("BitArrSetBitOff(2^32) = %lu.\n", BitArrSetBitOff(ba,32));				
	}
	
	ba = 0xFFFFFFFFFFFFFFFFLU; 
	if (0xFEFFFFFFFFFFFFFFLU != BitArrSetBitOff(ba,56))
	{
		printf("BitArrSetBitOff failed 4.\n");
		printf("BitArrSetBitOff(0xFFFFFFFFFFFFFFFLU) = %lu.\n", BitArrSetBitOff(ba,56));		
	}
}

void TestBitArrSetBit()
{	
	bitarray_t ba = 0;
	if (8 != BitArrSetBit(ba,3,1))
	{
		printf("BitArrSetBit failed 1.\n");
		printf("BitArrSetBit(0,3,1) = %lu.\n", BitArrSetBit(ba,3,1));								
	}
	
	ba = 10;
	if (8 != BitArrSetBit(ba,1,0))
	{
		printf("BitArrSetBit failed 2.\n");
		printf("BitArrSetBit(10,1,0) = %lu.\n", BitArrSetBit(ba,1,0));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (0 != BitArrSetBit(ba,31,0))
	{
		printf("BitArrSetBit failed 3.\n");
		printf("BitArrSetBit(2^32,32,0) = %lu.\n", BitArrSetBit(ba,32,0));				
	}
	
	ba = 0xFFFFFFFFFFFFFFFFLU; 
	if (0xFEFFFFFFFFFFFFFFLU != BitArrSetBit(ba,56,0))
	{
		printf("BitArrSetBit failed 4.\n");
		printf("BitArrSetBit(0xFFFFFFFFFFFFFFFLU) = %lu.\n", BitArrSetBit(ba,56,0));		
	}
}

void TestBitArrFlipBit()
{	
	bitarray_t ba = 0;
	if (32 != BitArrFlipBit(ba,5))
	{
		printf("BitArrFlipBit failed 1.\n");
		printf("BitArrFlipBit(0,5) = %lu.\n", BitArrFlipBit(ba,5));								
	}
	
	ba = 10;
	if (8 != BitArrFlipBit(ba,1))
	{
		printf("BitArrFlipBit failed 2.\n");
		printf("BitArrFlipBit(10,1) = %lu.\n", BitArrFlipBit(ba,1));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (0 != BitArrFlipBit(ba,32))
	{
		printf("BitArrFlipBit failed 3.\n");
		printf("BitArrFlipBit(2^32,32) = %lu.\n", BitArrFlipBit(ba,32));				
	}
	
	ba = 0xFEFFFFFFFFFFFFFFLU; 
	if (0xFFFFFFFFFFFFFFFFLU != BitArrFlipBit(ba,56))
	{
		printf("BitArrFlipBit failed 4.\n");
		printf("BitArrFlipBit(0xFFFFFFFFFFFFFFFLU) = %lu.\n", BitArrFlipBit(ba,56));		
	}
}

void TestBitArrFlipAllBits()
{	
	bitarray_t ba = 0;
	if (0xFFFFFFFFFFFFFFFFLU != BitArrFlipAllBits(ba))
	{
		printf("BitArrFlipAllBits failed 1.\n");
		printf("BitArrFlipAllBits(0) = %lu.\n", BitArrFlipAllBits(ba));								
	}
	
	ba = 0xFFFFFFFFFFFFFFFELU;
	if (1 != BitArrFlipAllBits(ba))
	{
		printf("BitArrFlipAllBits failed 2.\n");
		printf("BitArrFlipAllBits(10) = %lu.\n", BitArrFlipAllBits(ba));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (0xFFFFFFFFFFFFFFFFLU - 4294967296 != BitArrFlipAllBits(ba))
	{
		printf("BitArrFlipAllBits failed 3.\n");
		printf("BitArrFlipAllBits(2^32) = %lu.\n", BitArrFlipAllBits(ba));				
	}
	
	ba = 1; 
	if (0xFFFFFFFFFFFFFFFELU != BitArrFlipAllBits(ba))
	{
		printf("BitArrFlipAllBits failed 4.\n");
		printf("BitArrFlipAllBits(1) = %lu.\n", BitArrFlipAllBits(ba));		
	}
}

void TestBitArrSetAllBitsOn()
{
	bitarray_t ba = 0LU;
	if (0xFFFFFFFFFFFFFFFFLU != BitArrSetAllBitsOn(ba))
	{
		printf("BitArrSetAllBitsOn failed 1.\n");
		printf("BitArrSetAllBitsOn(0) = %lu.\n", BitArrSetAllBitsOn(ba));								
	}
	ba = 0xFFFFFFFFFFFFFFFFLU;
	if (0xFFFFFFFFFFFFFFFFLU != BitArrSetAllBitsOn(ba))
	{
		printf("BitArrSetAllBitsOn failed 1.\n");
		printf("BitArrSetAllBitsOn(0) = %lu.\n", BitArrSetAllBitsOn(ba));								
	}	
}

void TestBitArrSetAllBitsOff()
{
	bitarray_t ba = 0LU;
	if (0LU != BitArrSetAllBitsOff(ba))
	{
		printf("BitArrSetAllBitsOff failed 1.\n");
		printf("BitArrSetAllBitsOff(0) = %lu.\n", BitArrSetAllBitsOff(ba));								
	}
	ba = 0xFFFFFFFFFFFFFFFFLU;
	if (0LU != BitArrSetAllBitsOff(ba))
	{
		printf("BitArrSetAllBitsOff failed 1.\n");
		printf("BitArrSetAllBitsOff(0) = %lu.\n", BitArrSetAllBitsOff(ba));								
	}	
}

void TestBitArrSwapBits()
{
	bitarray_t ba = 0;
	if (0 != BitArrSwapBits(ba,2,3))
	{
		printf("BitArrSwapBits failed 1.\n");
		printf("BitArrSwapBits(0,2,3) = %lu.\n", BitArrSwapBits(ba,2,3));								
	}
	
	ba = 0xFFFFFFFFFFFFFFFELU;
	if (0x7FFFFFFFFFFFFFFFLU != BitArrSwapBits(ba,63,0))
	{
		printf("BitArrSwapBits failed 2.\n");
		printf("BitArrSwapBits(0xFFFFFFFFFFFFFFFELU,63,0) = %lu.\n", BitArrSwapBits(ba,63,0));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (2147483648/* 2^31 */ != BitArrSwapBits(ba,31,32))
	{
		printf("BitArrSwapBits failed 3.\n");
		printf("BitArrSwapBits(2^32) = %lu.\n", BitArrSwapBits(ba,31,30));				
	}
	
	ba = 1; 
	if (0x8000000000000000LU != BitArrSwapBits(ba,0,63))
	{
		printf("BitArrSwapBits failed 4.\n");
		printf("BitArrSwapBits(1,0,63) = %lu.\n", BitArrSwapBits(ba,0,63));		
	}
}

void TestBitArrRotateBitsRight()
{
	bitarray_t ba = 0;
	if (0 != BitArrRotateBitsRight(ba,3))
	{
		printf("BitArrRotateBitsRight failed 1.\n");
		printf("BitArrRotateBitsRight(0,3) = %lu.\n", BitArrRotateBitsRight(ba,3));								
	}
	
	ba = 0xFFFFFFFFFFFFFFFELU;
	if (0xDFFFFFFFFFFFFFFFLU != BitArrRotateBitsRight(ba,3))
	{
		printf("BitArrRotateBitsRight failed 2.\n");
		printf("BitArrRotateBitsRight(0xFFFFFFFFFFFFFFFELU,3) = %lu.\n", BitArrRotateBitsRight(ba,3));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (2147483648/* 2^31 */ != BitArrRotateBitsRight(ba,65))
	{
		printf("BitArrRotateBitsRight failed 3.\n");
		printf("BitArrRotateBitsRight(2^32) = %lu.\n", BitArrRotateBitsRight(ba,31));				
	}
	
	ba = 1; 
	if (0x1000000000000000LU != BitArrRotateBitsRight(ba,4))
	{
		printf("BitArrRotateBitsRight failed 4.\n");
		printf("BitArrRotateBitsRight(1,0) = %lu.\n", BitArrRotateBitsRight(ba,4));		
	}		
}
void TestBitArrRotateBitsLeft()
{
	bitarray_t ba = 0;
	if (0 != BitArrRotateBitsLeft(ba,3))
	{
		printf("BitArrRotateBitsLeft failed 1.\n");
		printf("BitArrRotateBitsLeft(0,3) = %lu.\n", BitArrRotateBitsLeft(ba,3));								
	}
	
	ba = 0xFFFFFFFFFFFFFFFELU;
	if (0xFFFFFFFFFFFFFFF7LU != BitArrRotateBitsLeft(ba,3))
	{
		printf("BitArrRotateBitsLeft failed 2.\n");
		printf("BitArrRotateBitsLeft(0xFFFFFFFFFFFFFFFELU,3) = %lu.\n", BitArrRotateBitsLeft(ba,3));						
	}		
	
	ba = 4294967296; /* 2^32 */
	
	if (8589934592/* 2^33 */ != BitArrRotateBitsLeft(ba,65))
	{
		printf("BitArrRotateBitsLeft failed 3.\n");
		printf("BitArrRotateBitsLeft(2^32) = %lu.\n", BitArrRotateBitsLeft(ba,31));				
	}
	
	ba = 1; 
	if (0x0000000000000010LU != BitArrRotateBitsLeft(ba,4))
	{
		printf("BitArrRotateBitsRight failed 4.\n");
		printf("BitArrRotateBitsRight(1,0) = %lu.\n", BitArrRotateBitsLeft(ba,4));		
	}		
}
