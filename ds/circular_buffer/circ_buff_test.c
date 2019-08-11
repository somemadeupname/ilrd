#include <stdio.h>
#include "circ_buff.h"

#define PRINT_VALUE(X) (printf("value=%s\n", X))
#define CHECK(X,Y) (printf("%d for %s\n", X,Y))
#define CHECK_LD(X,Y) (printf("%lu for %s\n", X,Y))

/* Forward Declarations */
void TestCircBuffCreate();
void TestCircBuffCapacity();
void TestCircBuffWrite();
void TestCircBuffRead();

int main()
{
	
	TestCircBuffCreate();
	
	TestCircBuffCapacity();
	
	TestCircBuffWrite();
	
	TestCircBuffRead();
	
	return 0;
}

void TestCircBuffCreate()
{
	circ_buff_t *buf = CircBuffCreate(45);
	
	CircBuffDestroy(buf);
}

void TestCircBuffCapacity()
{
	circ_buff_t *buf = CircBuffCreate(55);
	
	CHECK_LD(CircBuffCapacity(buf),"CircBuffCapacity(buf)");
	
	CircBuffDestroy(buf);
}

void TestCircBuffWrite()
{
	char *src = "hello sir how are you";
	circ_buff_t *buf = CircBuffCreate(10);
	
	CHECK_LD(CircBuffCapacity(buf),"CircBuffCapacity(buf)");
	
	CHECK_LD(CircBuffWrite(buf, src, 6), "CircBuffWrite(buf, src, 6)");
	
	CHECK_LD(CircBuffFreeSpace(buf),"CircBuffFreeSpace(buf)");

	CircBuffDestroy(buf);			
}

void TestCircBuffRead()
{
	char *src = "hello sir how are you";
	char dest[20];
	circ_buff_t *buf = CircBuffCreate(7);
	/*PRINT_VALUE(dest);*/	
		
	CHECK_LD(CircBuffWrite(buf, src, 8), "CircBuffWrite(buf, src, 11)");

	CHECK_LD(CircBuffRead(buf, dest, 11), "CircBuffRead(buf, dest, 11)");
	
	/*PRINT_VALUE(dest);*/
	
	CircBuffDestroy(buf);	
}
