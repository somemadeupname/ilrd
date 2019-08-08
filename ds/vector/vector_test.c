#include <stdio.h> /* printf */
#include "vector.h"

#define PRINT_VALUE(X) (printf("%d\n", X))
#define CHECK(X,Y) (printf("%d for %s\n", X,Y))
#define CHECK_LD(X,Y) (printf("%lu for %s\n", X,Y))

/* FORWARD DECLARATIONS */
void TestVectorCreateAndDestroy();
void TestVectorPushBack();
void TestVectorGetItemAddress();
void TestVectorSize();
void TestVectorPopBack();

int main()
{
	TestVectorCreateAndDestroy();
	/*
	TestVectorPushBack();	
	
	TestVectorGetItemAddress();
	
	TestVectorSize();
	*/
	TestVectorPopBack();
	
	return 0;
}

void TestVectorCreateAndDestroy()
{
	vector_t *vector = VectorCreate(10,4);
	VectorDestroy(vector);
	
	vector = VectorCreate(0,0);
	VectorDestroy(vector);
	
	vector = VectorCreate(0,5);	
	VectorDestroy(vector);
	
	vector = VectorCreate(1,0);	
	VectorDestroy(vector);
}

void TestVectorPushBack()
{
	vector_t *vector = VectorCreate(4,4);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	/*int e = 5;*/
	CHECK(VectorPushBack(vector, &a), "VectorPushBack");
	CHECK(VectorPushBack(vector, &b), "VectorPushBack");
	CHECK(VectorPushBack(vector, &c), "VectorPushBack");
	CHECK(VectorPushBack(vector, &d), "VectorPushBack");
	/*CHECK(VectorPushBack(vector, &e), "VectorPushBack");*/
	
	VectorDestroy(vector);	
}

void TestVectorGetItemAddress()
{
	vector_t *vector = VectorCreate(4,4);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int *i_ptr = NULL;
	int *i_ptr2 = NULL;	
	int *i_ptr3 = NULL;		
		
	/*int e = 5;*/
	
	VectorPushBack(vector, &a);
	VectorPushBack(vector, &b);
	VectorPushBack(vector, &c);
	VectorPushBack(vector, &d);
	
	i_ptr = (int *) VectorGetItemAddress(vector,0);
	
	PRINT_VALUE(*i_ptr);
	
	i_ptr2 = (int *) VectorGetItemAddress(vector,1);
	
	PRINT_VALUE(*i_ptr2);	
	
	i_ptr3 = (int *) VectorGetItemAddress(vector,2);	
	
	PRINT_VALUE(*i_ptr3);
	
	VectorDestroy(vector);	
}

void TestVectorSize()
{
	vector_t *vector = VectorCreate(4,4);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	CHECK_LD(VectorSize(vector), "VectorSize");	
	VectorPushBack(vector, &a);
	CHECK_LD(VectorSize(vector), "VectorSize");	
	VectorPushBack(vector, &b);
	CHECK_LD(VectorSize(vector), "VectorSize");	
	VectorPushBack(vector, &c);
	CHECK_LD(VectorSize(vector), "VectorSize");	
	VectorPushBack(vector, &d);
	CHECK_LD(VectorSize(vector), "VectorSize");
	VectorDestroy(vector);		
}

void TestVectorPopBack()
{
	vector_t *vector = VectorCreate(4,4);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	int *i_ptr = NULL;
	int *i_ptr2 = NULL;	
	int *i_ptr3 = NULL;		
	/*int e = 5;*/
	VectorPushBack(vector, &a);
	VectorPushBack(vector, &b);
	VectorPushBack(vector, &c);
	VectorPushBack(vector, &d);
	
	i_ptr = (int *) VectorGetItemAddress(vector,3);	
	PRINT_VALUE(*i_ptr);	
	CHECK(VectorPopBack(vector), "VectorPopBack");
	CHECK_LD(VectorSize(vector), "VectorSize");
	i_ptr = (int *) VectorGetItemAddress(vector,2);	
	PRINT_VALUE(*i_ptr);		
	CHECK(VectorPopBack(vector), "VectorPopBack");
	CHECK_LD(VectorSize(vector), "VectorSize");
	i_ptr = (int *) VectorGetItemAddress(vector,1);	
	PRINT_VALUE(*i_ptr);		
	CHECK(VectorPopBack(vector), "VectorPopBack");
	CHECK_LD(VectorSize(vector), "VectorSize");		
	CHECK(VectorPopBack(vector), "VectorPopBack");					
	CHECK_LD(VectorSize(vector), "VectorSize");
	CHECK(VectorPopBack(vector), "VectorPopBack");								
	
	VectorDestroy(vector);	
}
