#include <stdio.h>

int main()
{
	char a = 'a';
	char arr[4] = {'b','c','a','\0'};
	if (a == arr[2])
	{
		printf("%c\n", a);
	}
	return 0;
}
