
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h>
#include <math.h> /* sqrt */

#include "search.h"

void *BSearchRecursive(const void *key, const void *base, size_t nitems,
					   size_t elm_size, int (*cmp)(const void *, const void *))
{
	void *mid = NULL;
	int cmp_result = 0;

	assert(NULL != base);
	assert(NULL != cmp);
	
	mid = (char *)base + (nitems/2) * elm_size;
	cmp_result = cmp(mid, key);
	
	if (0 == cmp_result)
	{
		return mid;
	}
	if (1 > nitems)
	{
		return NULL;
	}
	
	if (cmp_result < 0)
	{
		void *end = (char *)base + (nitems-1) * elm_size;
		nitems = ((char *)end - (char *)mid + elm_size)/elm_size - 1;
		return BSearchRecursive(key, (char *)mid + elm_size, nitems, elm_size, cmp);
	}
	else /* cmp_result > 0 */
	{
		nitems = (size_t)((char *)((char *)mid - (char *)base))/elm_size;
		return BSearchRecursive(key, base, nitems, elm_size, cmp);
	}
}

void *BSearchIterative(const void *key, const void *base, size_t nitems,
					   size_t elm_size, int (*cmp)(const void *, const void *))
{
	void *left = (void *)base;
	void *right = (char *)base + ((nitems-1) * elm_size);
	
	assert(NULL != base);
	assert(NULL != cmp);	
	
	while (left <= right)
	{
		void *mid = (char *)left + ((nitems-1)/2) * elm_size;
		int cmp_result = cmp(mid, key);
		
		if (0 == cmp_result)
		{
			return mid;
		}
		else if (cmp_result < 0)
		{
			left = (char *)mid + elm_size;
		}
		else /* cmp_result > 0 */
		{
			right = (char *)mid - elm_size;
			
		}
		nitems /= 2;
	}
	
	return NULL;
}

static void *LinearSearch(const void *key, void *from, void *to,
						  size_t elm_size,
						  int (*cmp)(const void *, const void *))
{
	void *runner = from;
	
	assert(NULL != from);
	assert(NULL != cmp);
	
	for (runner = from;
		 runner < to;
		 runner = (char *)runner + elm_size
		)
	{
		int cmp_result = cmp(runner, key);
		
		if (0 == cmp_result)
		{
			return runner;
		}
		else if (0 < cmp_result)
		{
			return NULL;
		}
	}
	return NULL;
}

void *JSearch(const void *key, const void *base, size_t nitems,
			  size_t elm_size, int (*cmp)(const void *, const void *))
{
	void *jumper = (void *)base;
	void *follower = jumper;
	void *end = (char *)base + (nitems * elm_size);
	size_t jump = sqrt(nitems);
	
	assert(NULL != base);
	assert(NULL != cmp);
	
	for (jumper = follower;
		 jumper < end;
		 jumper = ((char *)jumper + (elm_size * jump))
		)
	{
		int cmp_result = cmp(jumper, key);
		
		if (0 == cmp_result)
		{
			return jumper;
		}
		else if (0 > cmp_result)
		{
			follower = jumper;
		}
		else /* 0 > cmp_result */
		{
			return LinearSearch(key, follower, jumper, elm_size, cmp);
		}
	}
	
	return LinearSearch(key, follower, end, elm_size, cmp);
}
