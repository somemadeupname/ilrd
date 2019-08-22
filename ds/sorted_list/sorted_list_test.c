#include <stdio.h>
#include "sorted_list.h"

int main()
{
	return 0;
}

void PrintList(sorted_list_t *list)
{
	size_t iter_index = 0;
	sorted_list_iter_t cur_iter = SortedListBegin(list);
	while (!SortedListIsSameIter(SortedListEnd(list), cur_iter))
	{
		printf("[n%lu. data: %d]<-->", iter_index, *(int *)SortedListGetData(cur_iter));
		cur_iter = SortedListNext(cur_iter);
		++iter_index;
	}
	printf("\b \b");
	printf("\b \b");
	printf("\b \b");		
	printf("\b \b");			
	printf("\n");
}  
