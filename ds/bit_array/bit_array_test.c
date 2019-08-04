#include <stdio.h> /* printf */
#include "bit_array.h"

/* FORWARD DECLARATIONS */
void TestBitArrIsBitSet();
void TestBitArrCountOnBits();
void TestBitArrCountOffBits();
void TestBitArrBitToStr();
void TestBitArrSetBitOn();

/* main */

int main()
{
	
	TestBitArrIsBitSet();

	TestBitArrCountOnBits();
	
	TestBitArrCountOffBits();

	/*
	TestBitArrBitToStr();
	*/
	
	TestBitArrSetBitOn();
	
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
