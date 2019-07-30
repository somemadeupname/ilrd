#include <stdio.h> /* printf, sprintf, fprintf */
#include <stdlib.h> /* malloc, realloc, free */
#include <string.h> /* strcat, strcpy */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#define UNUSED(x) (void)(x)
#define MAX_DIGITS_SIZE_OF_INT 12

/************* FUNCTIONS DECLARATIONS *************/
void AddInt(void *data, int input);
void PrintInt(const void *data);
void FreeInt(void *data);

void AddFloat(void *data, int input);
void PrintFloat(const void *data);
void FreeFloat(void *data);

void AddString(void *data, int input);
void PrintString(const void *data);
void FreeString(void *data);

/************* STRUCT DECLARATION *************/
typedef struct 
{
	void *data;
	void (*add)(void *data, int input);
	void (*print)(const void *data);
	void (*free)(void *data);
} struct_element;
	

int main()
{
	/* int input which will be added to each struct_element */
	int input = 6;
	
	/* values which will initialize the data members of the struct_elements */
	int num = 13;
	float f_num = 0.0f;
	
	/* index for the struct element array */
	size_t index = 0;	
	
	/* initialization of struct element array */
	struct_element arr[] =
	{
		/* initializing data member to NULL to allow changing it later  */
		{(void *) NULL, &AddInt, &PrintInt, &FreeInt},
		{(void *) NULL, &AddFloat, &PrintFloat, &FreeFloat},
		{(void *) NULL, &AddString, &PrintString, &FreeString}		
	};
	
	/* intialization of data members the union-esqe object */	
	arr[0].data = *((void **) &num);
	arr[1].data = *((void **) &f_num);
	arr[2].data = (char *) malloc ((5 + MAX_DIGITS_SIZE_OF_INT * sizeof(char)));
	
	/* malloc error handling */
	if (NULL == arr[2].data)
	{
		fprintf (stderr, "Malloc failed.\n");
		return 1;
	}
	
	/* copying string in the second argument of strcpy
	into the data member of the char* element */
	strcpy(arr[2].data, "hello");

	/* the main loop which iterates over the array.
	It adds @input, prints and frees each element */
	for (index = 0; index < (sizeof(arr)/sizeof(arr[0])); ++index)
	{
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
void PrintInt(const void *data)
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
void PrintFloat(const void *data)
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
	char digits[MAX_DIGITS_SIZE_OF_INT]; /* max size of int digits */;
	assert(NULL != data);
	sprintf(digits, "%d", input); /* save input as string into digits */
	strcat (*(char **)data, digits); /* concatenate digits into data */	
}
void PrintString(const void *data)
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
