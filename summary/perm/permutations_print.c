#include <stdio.h> /* printf  */

void PrintPermutation(char *str, size_t left, size_t right);

int main()
{
	char str[] = {'h','e','l','l','o'};
	
	char str2[] = {'f','u','d','g','e'};	
	
	PrintPermutation(str, 0, 4);
	
	PrintPermutation(str2, 0, 4);
		
	return 0;
}

void swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void PrintPermutation(char *str, size_t left, size_t right)
{
	size_t i = 0;
	
	if (left == right)
	{
		printf("%s\n", str);
	}
	else
	{
		for (i = left; i <= right; ++i)
		{
			swap(str + left, str + i);
			PrintPermutation(str, left + 1, right);
			swap(str + left, str + i);
		}
	}
}
