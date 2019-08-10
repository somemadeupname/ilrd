#include <stdio.h>	/* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#define IN_FIRST (-2)
#define IN_SECOND (-1)
#define IN_THIRD (-3)
#define IN_BOTH_ARRAYS (-2)

#define CHAR_ARRAY_SIZE 256



static signed short chars_in_arrays[CHAR_ARRAY_SIZE] = {0};

/* Forward Declarations */

static void FindCharsInArray(const char *arr, signed short *chars_in_arrays,
															signed short value);
static void PrintFoundChars(const short *chars_in_arrays, size_t array_size);
void PrintLettersOnlyInFirst2Arrs(char *str1, char *str2, char *str3);

void TestPrintLettersOnlyInFirst2Arrs();

/*
Looks for the chars in a given array arr, and set the given value in the 
chars_in_arrays array.
*/
static void FindCharsInArray(const char *arr, signed short *chars_in_arrays,
															 signed short value)
{
	size_t index = 0;
	assert(NULL != arr);
	assert(NULL != chars_in_arrays);
	
	for (index = 0; '\0' != arr[index]; ++index)
	{
		if ( value <= chars_in_arrays[((int) arr[index])])
		{
			chars_in_arrays[((int) arr[index])] = value;
		}
	}
}

/*
Prints the chars who are in both first arrays, but not in the third array
*/
static void PrintFoundChars(const short *chars_in_arrays, size_t array_size)
{
	size_t index = 0;
	assert(NULL != chars_in_arrays);
	
	for (index = 0; index < array_size; ++index)
	{
		if (IN_BOTH_ARRAYS == chars_in_arrays[index])
		{
			printf("%c\n",(int)index);/* print the char using the index */
		}
	}
}

void PrintLettersOnlyInFirst2Arrs(char *str1, char *str2, char *str3)
{
	
	FindCharsInArray(str1, chars_in_arrays, IN_FIRST);
	FindCharsInArray(str2, chars_in_arrays, IN_SECOND);
	FindCharsInArray(str3, chars_in_arrays, IN_THIRD);	
	
	PrintFoundChars	(chars_in_arrays, CHAR_ARRAY_SIZE);
}
/*
int main()
{
	char arr1[] = {'a','b','c','d','\0'};
	char arr2[] = {'a','b','c','d','\0'};
	char arr3[] = {'a','a','c','c','\0'};
	
	PrintLettersOnlyInFirst2Arrs(arr1, arr2, arr3);
	return 0;
}
*/
