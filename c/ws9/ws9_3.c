#include <stdio.h>	/* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#define IN_FIRST (-2)
#define IN_SECOND (-1)
#define IN_THIRD (-3)



static signed short chars_in_arrays[256] = {0};

/* Forward Declarations */

static void FindCharsInArray(const char *arr, signed short *chars_in_arrays, signed short value);
static void PrintFoundChars(const short *chars_in_arrays, size_t array_size);
void PrintLettersOnlyInFirst2Arrs(char *str1, char *str2, char *str3);

void TestPrintLettersOnlyInFirst2Arrs();

/*
*/
static void FindCharsInArray(const char *arr, signed short *chars_in_arrays, signed short value)
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

static void PrintFoundChars(const short *chars_in_arrays, size_t array_size)
{
	size_t index = 0;
	assert(NULL != chars_in_arrays);
	
	for (index = 0; index < array_size; ++index)
	{
		if (-2 == chars_in_arrays[index])
		{
			printf("%c\n",(int)index);
		}
	}
}

void PrintLettersOnlyInFirst2Arrs(char *str1, char *str2, char *str3)
{
	
	FindCharsInArray(str1, chars_in_arrays, IN_FIRST);
	FindCharsInArray(str2, chars_in_arrays, IN_SECOND);
	FindCharsInArray(str3, chars_in_arrays, IN_THIRD);	
	
	PrintFoundChars	(chars_in_arrays, 256);
}

void TestPrintLettersOnlyInFirst2Arrs()
{
	char str1[] = {'a','a','b','d','\0'};
	char str2[] = {'a','b','c','d','\0'};
	char str3[] = {'a','l','l','q','\0'};
	
	PrintLettersOnlyInFirst2Arrs(str1, str2, str3);	
}

int main()
{
	TestPrintLettersOnlyInFirst2Arrs();
	return 0;
}
