#include <stdio.h> /* printf */
#include "vector.h"

#define PRINT_VALUE(X) (printf("value=%d\n", X))
#define CHECK(X,Y) (printf("%d for %s\n", X,Y))
#define CHECK_LD(X,Y) (printf("%lu for %s\n", X,Y))

/* FORWARD DECLARATIONS */
void TestVectorCreateAndDestroy();
void TestVectorPushBack();
void TestVectorGetItemAddress();
void TestVectorSize();
void TestVectorPopBack();
void TestVectorReserve();

int main()
{
	/*
	TestVectorCreateAndDestroy();
	*/
	TestVectorPushBack();	
	/*
	TestVectorGetItemAddress();
	
	TestVectorSize();
	
	TestVectorPopBack();
	
	TestVectorReserve();
	*/
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
	vector_t *vector = VectorCreate(1,4);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	CHECK(VectorPushBack(vector, &a), "VectorPushBack");
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");		
	CHECK(VectorPushBack(vector, &b), "VectorPushBack");
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");		
	CHECK(VectorPushBack(vector, &c), "VectorPushBack");
	CHECK(VectorPushBack(vector, &d), "VectorPushBack");
	
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
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	
	VectorPushBack(vector, &a);

	VectorPushBack(vector, &b);
	
	VectorPushBack(vector, &c);
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	
	VectorPushBack(vector, &d);
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	
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

void TestVectorReserve()
{
	vector_t *vector = VectorCreate(40,4);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	
	int *i_ptr = NULL;
	int *i_ptr2 = NULL;	
	int *i_ptr3 = NULL;		
	int e = 5;
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");
	CHECK_LD(VectorSize(vector), "VectorSize");	
	
	VectorPushBack(vector, &a);

	VectorPushBack(vector, &b);
	
	VectorPushBack(vector, &c);
	
	i_ptr = (int *) VectorGetItemAddress(vector,2);	
	PRINT_VALUE(*i_ptr);	
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	
	VectorPushBack(vector, &d);
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	CHECK_LD(VectorSize(vector), "VectorSize");

	VectorPushBack(vector, &e);
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	CHECK_LD(VectorSize(vector), "VectorSize");
	

	CHECK(VectorPopBack(vector), "VectorPopBack");
	
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	CHECK_LD(VectorSize(vector), "VectorSize");
	i_ptr = (int *) VectorGetItemAddress(vector,1);	
	PRINT_VALUE(*i_ptr);		
	CHECK(VectorPopBack(vector), "VectorPopBack");
	CHECK_LD(VectorSize(vector), "VectorSize");
	i_ptr = (int *) VectorGetItemAddress(vector,0);	
	PRINT_VALUE(*i_ptr);		
	CHECK(VectorPopBack(vector), "VectorPopBack");
	CHECK_LD(VectorCapacity(vector),"VectorCapacity");	
	CHECK_LD(VectorSize(vector), "VectorSize");	

	VectorDestroy(vector);
}
