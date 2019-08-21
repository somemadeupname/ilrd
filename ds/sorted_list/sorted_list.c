
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Shaddad	    *
 *	 Status   : Sent	    *
 ****************************/

#include <stdlib.h> /* malloc, free, sizeof */
#include <assert.h> /* assert */

#include "../dlist/dlist.c"
#include "sorted_list.h"

struct sorted_list
{
	dlist_t *dlist;
	is_before cmp;
	void *param;
};

sorted_list_t *SortedListCreate(is_before func, const void *param)
{
	sorted_list_t *list = (sorted_list_t *)malloc(sizeof(sorted_list_t)); 
	if(NULL == list)
	{
		return NULL;
	}
	
	list->dlist = DListCreate(); 
	if(NULL == list->dlist)
	{
		free(list); list = NULL; 
		return NULL; 
	}
	
	list->cmp = func;
	list->param = (void *)param;
	
	return list;
}

void SortedListDestroy(sorted_list_t *list)
{
	assert(NULL != list);
	DListDestroy(list->dlist); list->dlist = NULL; 
	free(list); list = NULL;
}

sorted_list_iter_t SortedListInsert(sorted_list_t *list, const void *data)
{
	sorted_list_iter_t iter_to_insert; 
	dlist_iter_t runner = NULL; 
	dlist_iter_t end = NULL;
	
	assert(NULL != list);
	
	runner = DListBegin(list->dlist);
	end = DListEnd(list->dlist);  
	
	while (!DListIsSameIter(runner,end) && /*change to for TODO*/
		  (0 != list->cmp(DListIterGetData(runner), 
		  (void *)data, list->param)))
	{
		runner = DListNext(runner);
	}
	iter_to_insert.iter = DListInsert(list->dlist, runner, (void *)data); 
	
	return iter_to_insert;
}

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter_to_remove)
{
	assert(NULL != iter_to_remove.iter);
	
	iter_to_remove.iter = DListRemove(iter_to_remove.iter);
	
	return iter_to_remove;
}

void *SortedListPopFront(sorted_list_t *list)
{
	assert(NULL != list); 
	return DListPopFront(list->dlist);
}

void *SortedListPopBack(sorted_list_t *list)
{
	assert(NULL != list); 	
	return DListPopBack(list->dlist);
}

int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list); 
	return DListIsEmpty(list->dlist); 
}

size_t SortedListSize(const sorted_list_t *list)
{
	assert(NULL != list); 	
	return DListSize(list->dlist); 
}

/*
 * Perform a function for every element in the sorted list
 * Param from : iterator to start operation from
 * Param to : iterator to stop operation at (not included in comparison)
 * Param param : pointer to additional parameters
 * Param func : pointer to action function
 * Return : last return status. stop operation if func_action return non-zero
 * Errors : if list or function pointers are not valid, behaviour is undefined
 *          if action_func changes sorted data, list behaviour is undefined
 */
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
                      sorted_list_action_func func, void *param);

/*
 * Find element with matching data
 * Param from : iterator to start search from
 * Param to : iterator to stop search at (not included in comparison)
 * Param data : pointer to data to compare
 * Return : iter to first matching element found, iter to to if no match found
 * Errors : if list pointer or one or both iters is not valid,
 *            behaviour is undefined
 */
sorted_list_iter_t SortedListFind(const sorted_list_t *list,
                                  sorted_list_iter_t from,
                                  sorted_list_iter_t to, const void *param);

/*
 * Merge two sorted lists
 * Param list_dest : list to be merged into
 * Param list_src : list to be merged
 *                    (after merging, list_src will be empty but still valid)
 * Return : pointer to merged list_dest
 * Errors : if one or both list pointers are not valid, behaviour is undefined
 *          if list_src and list_dest are sorted differently,
 *            behaviour is undefined
 */
sorted_list_t *SortedListMerge(sorted_list_t *list_dest,
                               sorted_list_t *list_src);

/*
 * Find element with matching data
 * Param from : iterator to start search from
 * Param to : iterator to stop search at (not included in comparison)
 * Param data : pointer to data to compare
 * Param cmp : pointer to compare function
 * Return : iter to first matching element found, iter to to if no match found
 * Errors : if function pointer or one or both iters is not valid,
 *             behaviour is undefined
 */
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    sorted_list_cmp_func cmp, const void *data);

sorted_list_iter_t SortedListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t begin; 
	
	assert(NULL != list);
	
	begin.iter = DListBegin(list->dlist);
	
	return begin; 
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t end;
	
	assert(NULL != list);
	
	end.iter = DListEnd(list->dlist);
	
	return end;
}

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	assert(NULL != iter.iter); 
	
	iter.iter = DListNext(iter.iter);
	
	return iter;
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	assert(NULL != iter.iter); 
	
	iter.iter = DListBack(iter.iter);
	
	return iter;
}

void *SortedListGetData(sorted_list_iter_t iter)
{
	assert(NULL != iter.iter); 
	return DListIterGetData(iter.iter);
}

int SortedListIsSameIter(const sorted_list_iter_t iter1,
                         const sorted_list_iter_t iter2)
{
	return DListIsSameIter(iter1.iter, iter2.iter);
}

