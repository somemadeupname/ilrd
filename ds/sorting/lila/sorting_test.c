#include <stdio.h>

#include "sorting.h"

#define Expect(x) {                                                \
    if (!(x))                                                    \
    {                                                            \
        fprintf(stderr, "Test failed in line %d\n", __LINE__);    \
        return 0;                                                \
    } } /* end of Expects(x) */
    
int InsetrionSortTest();
int SelectionSort();
int BubbleSortNaive();
int InsetrionSortRep();
int BubbleSort();

int main()
{
	InsetrionSortTest();
	SelectionSort();
	BubbleSortNaive();
	InsetrionSortRep();
	BubbleSort();
	
	printf("Good job\n");
		
	return 0;
	
}

int InsetrionSortTest()
{
	int arr[] = {8, 7, 6, 9, 1, 2, 4, 3, 5, 10};
	int i = 0;
	
	Insertion(arr, 10);
	
	for (i = 0; i < 10; ++i)
	{
		Expect((i + 1) == arr[i])
	}
	
	return 0;
}

int InsetrionSortRep()
{
	int arr[] = {8, -3, 6, 9, 1, 4, 4, 3, 5, 10};
	
	Insertion(arr, 10);
	
	Expect((-3) == arr[0])
	Expect((1) == arr[1])
	Expect((3) == arr[2])
	Expect((4) == arr[3])
	Expect((4) == arr[4])
	Expect((5) == arr[5])
	Expect((6) == arr[6])
	Expect((8) == arr[7])
	Expect((9) == arr[8])
	Expect((10) == arr[9])
	
	return 0;
}

int SelectionSort()
{
	int arr[] = {8, 7, 6, 9, 1, 2, 4, 3, 5, 10};
	int i = 0;
	
	Selection(arr, 10);
	
	for (i = 0; i < 10; ++i)
	{
		Expect((i + 1) == arr[i])
	}
	
	return 0;
}

int BubbleSortNaive()
{
	int arr[] = {8, 7, 6, 9, 1, 2, 4, 3, 5, 10};
	int i = 0;
	
	Bubble(arr, 10);
	
	for (i = 0; i < 10; ++i)
	{
		/*printf("%d", arr[i]);*/
		Expect((i + 1) == arr[i])
	}
	
	return 0;
}

int BubbleSort()
{
	int arr[] = {1, 2, 4, 3, 5, 6, 7, 8, 9, 10};
	int i = 0;
	
	Bubble(arr, 10);
	
	for (i = 0; i < 10; ++i)
	{
		/*printf("%d", arr[i]);*/
		Expect((i + 1) == arr[i])
	}
	
	return 0;
}
