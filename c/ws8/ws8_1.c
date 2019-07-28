#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc realloc free */
#include <string.h> /* strcat */
#include <stddef.h> /* size_t */

#define UNUSED(x) (void)(x)

/************* FUNCTIONS DECLARATIONS *************/
void AddInt(void *data, void *input);
void PrintInt(void *data);
void FreeInt(void *data);

void AddFloat(void *data, void *input);
void PrintFloat(void *data);
void FreeFloat(void *data);

void AddString(void *data, void *input);
void PrintString(void *data);
void FreeString(void *data);

/************* STRUCT DECLARATION *************/
typedef struct 
{
	void *data;
	void (*add)(void *data, void *input);
	void (*print)(void *data);
	void (*free)(void *data);
} struct_element;
	

int main()
{
	int num = 3;
	int input = 6;
	char *str_input = "55";
	
	float f_num = 3.7f;
	
	struct_element arr[] =
	{
		{ (void *) NULL , &AddInt, &PrintInt, &FreeInt },
		{ (void *) NULL , &AddFloat, &PrintFloat, &FreeFloat },
		{ (void *) NULL , &AddString, &PrintString, &FreeString }		
	};
	
	
	/* will later be a loop */
	
	arr[0].data = &num;
	arr[0].add(arr[0].data, (void *)&input);
	arr[0].print(arr[0].data);
	arr[0].free(arr[0].data);

	arr[1].data = &f_num;
	arr[1].add(arr[1].data, (void *)&input);
	arr[1].print(arr[1].data);
	arr[1].free(arr[1].data);
	
	arr[2].data = (char *) malloc (5 * sizeof(char));
	/* check if malloc succeeds */
	strcpy(arr[2].data,"yolo");
	arr[2].add(arr[2].data, (void *) str_input);
	arr[2].print(arr[2].data);
	arr[2].free(arr[2].data);	
	
	return 0;
}
/************ Int Functions *******************/
void AddInt(void *data, void *input)
{
	/* NULL asserts */
	*(int *) data += *(int *) input;
	
}
void PrintInt(void *data)
{
	/* NULL asserts */
	printf("%d\n", *(int *)data);
}
void FreeInt(void *data)
{
	UNUSED(data);
	/* do nothing */
}

/************ Float Functions *******************/
void AddFloat(void *data, void *input)
{
	/* NULL asserts */
	*(float *) data += *(int *) input;
}
void PrintFloat(void *data)
{
	/* NULL asserts */
	printf("%f\n", *(float *)data);
}
void FreeFloat(void *data)
{
	UNUSED(data);
	/* do nothing */
}

/************ String Functions *******************/
void AddString(void *data, void *input)
{
	/* NULL asserts */
	size_t added_length = strlen((char *) input);
	size_t original_length = strlen((char *) data);	
	
	printf("input=%s\n", (char *) input);
	printf("added_length + original_length + 1=%ld\n", added_length + original_length + 1);
	data = (char *) data;
	data = (char *) realloc (data, added_length + original_length + 1);
	strcat (data, input);
	/* check that strcat worked*/
}
void PrintString(void *data)
{
	/* NULL asserts */
	printf("%s\n", (char *)data);
}
void FreeString(void *data)
{
	/* null asserts */
	free(data);
	data = NULL;
}
