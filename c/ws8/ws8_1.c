#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* malloc, realloc, free */
#include <string.h> /* strcat */
#include <stddef.h> /* size_t */
#include <assert.h>

#define UNUSED(x) (void)(x)
#define MAX_DIGITS_SIZE_OF_INT 12

/************* FUNCTIONS DECLARATIONS *************/
void AddInt(void *data, int input);
void PrintInt(void *data);
void FreeInt(void *data);

void AddFloat(void *data, int input);
void PrintFloat(void *data);
void FreeFloat(void *data);

void AddString(void *data, int input);
void PrintString(void *data);
void FreeString(void *data);

/************* STRUCT DECLARATION *************/
typedef struct 
{
	void *data;
	void (*add)(void *data, int input);
	void (*print)(void *data);
	void (*free)(void *data);
} struct_element;
	

int main()
{
	int input = 6;
	int num = 13;
	float f_num = 3.7f;
	size_t index = 0;	
	
	struct_element arr[] =
	{
		{(void *) NULL, &AddInt, &PrintInt, &FreeInt},
		{(void *) NULL, &AddFloat, &PrintFloat, &FreeFloat},
		{(void *) NULL, &AddString, &PrintString, &FreeString}		
	};
	
	/* intialization of data members in each union-esqe object */
	
	arr[0].data = *((void **) &num);
	arr[1].data = *((void **) &f_num);
	arr[2].data = (char *) malloc ((5 + MAX_DIGITS_SIZE_OF_INT * sizeof(char)));
	/* check if malloc succeeds*/
	strcpy(arr[2].data, "hello");


	for (index = 0; index < (sizeof(arr)/sizeof(arr[0])); ++index)
	{
		/* TODO remove printf debug */
		printf("working on arr[%ld]:\n", index);
		arr[index].add(&arr[index].data, input);
		arr[index].print(arr[index].data);
		arr[index].free(arr[index].data);
	}
	
	return 0;
}
/************ Int Functions *******************/
void AddInt(void *data, int input)
{
	assert(NULL != data);
	*(int *)data += input;
	
}
void PrintInt(void *data)
{
	assert(NULL != data);
	printf("%d\n", *(int *)&data);
}
void FreeInt(void *data)
{
	assert(NULL != data);	
	UNUSED(&data);
	/* do nothing */
}

/************ Float Functions *******************/
void AddFloat(void *data, int input)
{
	assert(NULL != data);
	*(float *) data += input;
}
void PrintFloat(void *data)
{
	assert(NULL != data);
	printf("%f\n", *(float *)&data);
}
void FreeFloat(void *data)
{	
	UNUSED(&data);
	/* do nothing */
}

/************ String Functions *******************/
void AddString(void *data, int input)
{
	char digits[12]; /* max size of int digits */;
	assert(NULL != data);
	sprintf(digits, "%d", input); /* save input as string into digits */
	strcat (*(char **)data, digits);	
}
void PrintString(void *data)
{
	assert(NULL != data);
	printf("%s\n", (char *)data);
}
void FreeString(void *data)
{
	assert(NULL != data);
	free(data);
	data = NULL;
}
