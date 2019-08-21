
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

int SortedListForEach(sorted_list_iter_t from,
					  sorted_list_iter_t to,
                      sorted_list_action_func func,
                      void *param)
{
	sorted_list_iter_t cur;
	int exit_status = 0;
	assert(NULL != func);
	
	for(cur = from;
	    0 == exit_status && !SortedListIsSameIter(cur,to);
	    exit_status = func(SortedListGetData(cur), param),
	    cur = SortedListNext(cur)
	    )
	{ /* empty body */ }
	
	return exit_status;
}                      

sorted_list_iter_t SortedListFind(const sorted_list_t *list,
                                  sorted_list_iter_t from,
                                  sorted_list_iter_t to,
                                  const void *param)
{
	sorted_list_iter_t cur;
	/* optimization using the fact that the list is sorted */
	if (0 == list->cmp(SortedListGetData(from),(void *)param,NULL))
	{
		return to;
	}
	
	for (cur = from;
		 !SortedListIsSameIter(cur,to) && 
		 list->cmp(SortedListGetData(cur),(void *)param, list->param) >
		 list->cmp((void *) param, SortedListGetData(cur), list->param);
		 cur = SortedListNext(cur)
		 )
		 {/* empty body */}

	return cur;
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

sorted_list_t *SortedListMerge(sorted_list_t *list_dest,
                               sorted_list_t *list_src)
{
	sorted_list_iter_t src_from;
	sorted_list_iter_t src_to;
	sorted_list_iter_t src_end;	
	sorted_list_iter_t dest_runner;

	assert(NULL != list_dest);
	assert(NULL != list_src);
	
	src_to = SortedListBegin(list_src);
	src_end = SortedListEnd(list_src);
	src_from = src_to;
	dest_runner = SortedListBegin(list_dest);
	
	while(!SortedListIsSameIter(src_to,src_end))
	{
		while(!SortedListIsSameIter(dest_runner,SortedListEnd(list_dest)) && 0 == list_dest->cmp(SortedListGetData(src_to),
							 SortedListGetData(dest_runner),
							 NULL))
		{
			dest_runner = SortedListNext(dest_runner);
		}
		
		if (SortedListIsSameIter(dest_runner,SortedListEnd(list_dest)))
		{
			src_to = SortedListEnd(list_src);
		}
		
		while (!SortedListIsSameIter(src_to,src_end) && 0 == list_dest->cmp(SortedListGetData(dest_runner),
							  SortedListGetData(src_to),
							  NULL))
		{
			src_to = SortedListNext(src_to);
		}
							 
		DListSplice(dest_runner.iter, src_from.iter, src_to.iter);
		src_from = SortedListBegin(list_src);
	}
	
	return list_dest;
}                               

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    sorted_list_cmp_func cmp,
                                    const void *data)
{
	sorted_list_iter_t cur;
	
	for (cur = from;
		 (!SortedListIsSameIter(cur,to) && 
		 cmp(SortedListGetData(cur),(void *)data));
		 cur = SortedListNext(cur)
		 )
		 {/* empty body */}

	return cur;
}                                  

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

