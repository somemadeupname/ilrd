#include <stdio.h>
#include "vector.h"

#define CHECK(X) (printf("%d\n", X))

/* FORWARD DECLARATIONS */
void TestVectorCreateAndDestroy();

int main()
{
	TestVectorCreateAndDestroy();
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
