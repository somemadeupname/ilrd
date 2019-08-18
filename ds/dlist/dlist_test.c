#include <stdio.h>
#include <assert.h> /* assert */
#include "dlist.h"

/* Forward Declarations */
int CmpFuncInt(void *data, const void *param);
static int IncrementDataByParam(void *data, void *param); /* action func */

int main()
{
	
	return 0;
}

int CmpFuncInt(void *data, const void *param)
{
	int *d1 = NULL;
	int *d2 = NULL;	
	assert(NULL != data);
	assert(NULL != param);

	d1 = (int *) data;
	d2 = (int *) param;

	return !(*d1 > *d2);/* ! since 0 is success */
}
