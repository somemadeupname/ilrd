/****************************************
 * Title  : Sorting    					*
 * Author : Ran Shieber                 *
 * Group  : OL712                       *
 * Date   : 08/09/2019               	*
 ****************************************/

#ifndef __ILRD_OL712_SORTING_H
#define __ILRD_OL712_SORTING_H

#include <stddef.h> /* size_t */

/*
 * Sorts @arr using insertion sort.
 * @arr: array to sort.
 * @size: number of elements in arr.
 */
void Insertion(int *arr, size_t size);

/*
 * Sorts @arr using selection sort.
 * @arr: array to sort.
 * @size: number of elements in arr.
 */
void Selection(int *arr, size_t size);

/*
 * Sorts @arr using bubble sort.
 * @arr: array to sort.
 * @size: number of elements in arr.
 */
void Bubble(int *arr, size_t size);

/*
 * Sorts @arr using counting sort.
 * @arr: array to sort.
 * @size: number of elements in arr.
 * Note: @max must be greater than @min.
 */
int Counting(int *arr, size_t size, int min, int max);

/*
 * Sorts @arr using counting sort.
 * @arr: array to sort.
 * @size: number of elements in arr.
 * Note: @max must be greater than @min.
 */
int Radix(int *arr, size_t size, unsigned int num_of_bits);

/*
 * Sorts @arr using merge sort
 * @arr: array to sort.
 * @size: number of elements in arr (must be at least 1).
 * @is_before: function to compare elements
 * return: 0 if success, non-zero otherwise
 */
int Merge(int *arr, size_t size, int (*is_before)(int a, int b));

#endif /* __ILRD_OL712_SORTING_H */
