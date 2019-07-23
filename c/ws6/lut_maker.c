#include <stdio.h>
#include "ws6.h"

int main()
{
	size_t index = 0;
	for (index = 0; index < 256; ++index)
	{
		printf("%u\n", ByteMirrorLooped(index));
	}
	
	return 0;
}
