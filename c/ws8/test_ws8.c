#include <stdio.h>

typedef struct 
{
	void *data;
	void (*add)();
	void (*print)();
	void (*free)();
} struct_element;
	

int main()
{
	static struct_element arr[1] =
	{
		{ (void *) 5, &AddInt, &PrintInt, &FreeInt }
	};
	return 0;
}
