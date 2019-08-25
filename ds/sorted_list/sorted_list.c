
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Shaddad	    *
 *	 Status   : Sent	    *
 ****************************/

#include <stdlib.h> /* malloc, free, sizeof */
#include <assert.h> /* assert */

#include "../dlist/dlist.c"
#include "sorted_list.h"

typedef param
{
	is_before cmp;
	void *param;
} param_t;

struct sorted_list
{
	dlist_t *dlist;
	param_t *param;
};

/* Patch to correct past mistakes */
typedef struct patch
{
	void *user_data;
	void *user_param;
	sorted_list_is_match user_func;
} patch_t;

int IsMatchAdaptation(void *data1,const void *patch);
static patch_t PatchInit(void *data, void *param, sorted_list_is_match func);

/* SORTED LIST FUNCTIONS */

sorted_list_t *SortedListCreate(is_before func, const void *param)
{
	sorted_list_t *list = (sorted_list_t *)malloc(sizeof(sorted_list_t)); 
	param_t params = {NULL};
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
	
	list->params->cmp = func;
	list->params->param = (void *)param;
	
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
	sorted_list_iter_t iter_to_insert = {NULL};
	sorted_list_iter_t runner = {NULL};
	sorted_list_iter_t end = {NULL};
	
	assert(NULL != list);
	
	runner.iter = DListBegin(list->dlist);
	end.iter = DListEnd(list->dlist);  
	
	while (!SortedListIsSameIter(runner,end) &&
		  (0 != list->params->cmp(SortedListGetData(runner), 
		  (void *)data, list->params->param)))
	{
		runner = SortedListNext(runner);
	}
	iter_to_insert.iter = DListInsert(list->dlist, runner.iter, (void *)data); 
	
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

	assert(NULL != func);
	assert(NULL != from.iter);
	assert(NULL != to.iter);			
		
	return DListForEach(from.iter, to.iter, func, param);
}                      

sorted_list_iter_t SortedListFind(const sorted_list_t *list,
                                  sorted_list_iter_t from,
                                  sorted_list_iter_t to,
                                  const void *param)
{
	sorted_list_iter_t cur = {NULL};
	
	for (cur = from;
		 !SortedListIsSameIter(cur,to) && 
		 /* exit if searching for value which shoul be before cur */
		 list->params->cmp(SortedListGetData(cur),(void *)param, list->params->param) && 
		 list->params->cmp(SortedListGetData(cur),(void *)param, list->params->param) !=
		 list->params->cmp((void *) param, SortedListGetData(cur), list->params->param);
		 cur = SortedListNext(cur)
		 )
		 {/* empty body */}

	return cur;
}                     

sorted_list_t *SortedListMerge(sorted_list_t *list_dest,
                               sorted_list_t *list_src)
{
	sorted_list_iter_t src_from = {NULL};
	sorted_list_iter_t src_to = {NULL};
	sorted_list_iter_t src_end = {NULL};
	sorted_list_iter_t dest_runner = {NULL};

	assert(NULL != list_dest);
	assert(NULL != list_src);
	
	src_to = SortedListBegin(list_src);
	src_end = SortedListEnd(list_src);
	src_from = src_to;
	dest_runner = SortedListBegin(list_dest);
	
	while(!SortedListIsSameIter(src_to,src_end))
	{
		while(!SortedListIsSameIter(dest_runner,SortedListEnd(list_dest))
			  && 0 == list_dest->cmp(SortedListGetData(src_to),
			  SortedListGetData(dest_runner), NULL))
		{
			dest_runner = SortedListNext(dest_runner);
		}
		
		if (SortedListIsSameIter(dest_runner,SortedListEnd(list_dest)))
		{
			src_to = SortedListEnd(list_src);
		}
		
		while (!SortedListIsSameIter(src_to,src_end)
			   && 0 == list_dest->cmp(SortedListGetData(dest_runner),
			   SortedListGetData(src_to), NULL))
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
                                    sorted_list_is_match func,
                                    const void *data, void *param)
{
<<<<<<< HEAD
	patch_t patch_struct = {NULL};
=======
	sorted_list_iter_t cur = {NULL};
>>>>>>> 204b63be8ab182d6102072edd2f287ad5ef146b8
	
	assert(NULL != from.iter);
	assert(NULL != func);
	
	patch_struct = PatchInit((void *)data, param, func);
	
	from.iter = DListFind(from.iter,to.iter,IsMatchAdaptation,&patch_struct);

	return from;
}                                  

/* ITERATOR FUNCTIONS */

sorted_list_iter_t SortedListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t begin = {NULL};
	
	assert(NULL != list);
	
	begin.iter = DListBegin(list->dlist);
	
	return begin; 
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t end = {NULL};
	
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

int IsMatchAdaptation(void *data1,const void *patch)
{
	patch_t *non_void_patch = (patch_t *) patch;
	
	assert(NULL != patch);
	
			/* the actual adaptation which wraps the comparator */
	return !((non_void_patch->user_func(data1,non_void_patch->user_data,
			  non_void_patch->user_param)));
}
static patch_t PatchInit(void *data, void *param, sorted_list_is_match func)
{	
	patch_t patch = {NULL};

	assert(NULL != func);
	
	patch.user_data = data;
	patch.user_param = param;
	patch.user_func = func;
	
	return patch;
}
