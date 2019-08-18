#include <stdio.h>	/* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#define IN_FIRST (-1)
#define IN_SECOND (-2)
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
		
		if ( value == IN_THIRD )
		{
			chars_in_arrays[((int) arr[index])] = 0;
		}
		else if (value == IN_SECOND && (0 == chars_in_arrays[((int) arr[index])]))
		{
			chars_in_arrays[((int) arr[index])] = 0;
		}
		else
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
			printf("%c",(int)index);/* print the char using the index */
		}
	}
	printf("\n");
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
	char str1[] = "46gvI5aGDH$&^*(*AhelloA";
	char str2[] = "1a23!!!!lbicfg";
	char str3[] = "543146hjmngpo";
	
	PrintLettersOnlyInFirst2Arrs(str1, str2, str3);
	return 0;
}
*/
