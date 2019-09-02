#include <stdio.h>
#include <assert.h>
#include <stdlib.h> /* malloc free */

#include "vsa.h"
#include "test_template.h"

/* Forward Declarations */

void VSAInit_Sanity_test();
void VSAInit_AlignedMemory_test();
void VSAInit_NotAlignedMemory_test();
void VSAInit_EndIsAligned_test();
void VSAInit_EndIsNotAligned_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE
	
	VSAInit_Sanity_test();
	
	return 0;
}

void VSAInit_Sanity_test()
{
	size_t memory_size = 35;
	int *i = (int *) malloc (memory_size);
	vsa_t *new_vsa = VSAInit(i,memory_size);
	
	free(i);
}
