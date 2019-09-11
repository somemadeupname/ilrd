
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */

#include "bst.h"

typedef struct node
{
	bst_node *left;
	bst_node *right;
	bst_node *parent;	
	void *data;
} bst_node;

typedef struct bst
{
	cmp_func_t *cmp_func;
	bst_node *dummy_head;
} bst_t;

/* Forward Declarations */
static bst_node *CreateBSTNode(bst_node *left,
						 		bst_node *right,
						 		bst_node *parent,
						 		void *data);
static void DestroyBSTNode(bst_node *node_to_destroy);						 		
						 
typedef int (*cmp_func_t)(void *iter_data, void *new_data, void *param);
/*
 * Create new binary search tree
 * Param @cmp_func - user comparison function. returns 0 if <iter_data> and 
 *					 <new_data> are equal, positive if <iter_data> is larger 
 *					 or negative if its smaller.
 * Param @param - user param for <is_before> function
 * Return: pointer to new binary search tree
 * Errors: if creation failed, return NULL
 */
 
bst_t *BSTCreate(cmp_func_t cmp_func, void *param)
{

	bst_t *new_bst = NULL;
	bst_node *dummy_head = NULL;
	assert(NULL != cmp_func);
	
	dummy_head = CreateBSTNode(NULL,NULL,NULL,NULL);
	if (NULL == dummy_head)
	{
		return NULL;
	}
	
	new_bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == new_bst)
	{
		return NULL;
	}
	
	/* init bst */
	new_bst->cmp_func = cmp_func;
	new_bst->dummy_head = dummy_head;
	
	return new_bst;
}

/*
 * Check if tree is empty
 * Param  @bst - binary search tree
 * Return : 1 if bst is empty, 0 otherwise
 * Errors : --
 */
int BSTIsEmpty(const bst_t *bst);
{
	assert(NULL != bst);
	return (NULL == BSTNext(bst->dummy_head));
}


/*************************************************************************
																		 *
				      		NODE FUNCTIONS							 	 *
																		 *
*************************************************************************/
/* Create a bst node */
static bst_node *CreateBSTNode(bst_node *left,
						 		bst_node *right,
								bst_node *parent,
								void *data)
{
	bst_node *new_node = (bst_node *)malloc(sizeof(bst_node));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->left = left;
	new_node->right = right;
	new_node->parent = parent;
	new_node->data = data;
	
	return new_node;
}

/* Destroy a bst node */
static void *DestroyBSTNode(bst_node *node_to_destroy)
{
	free(node_to_destroy);
	return NULL;
}

/*************************************************************************
																		 *
			      		Static ITER FUNCTIONS					 	 	 *
																		 *
*************************************************************************/

/*  */
static int HasLeftChild(bst_iter_t iter)
{
	assert(NULL != iter);
	return (NULL != iter->left);
}

/*  */
static int HasRightChild(bst_iter_t iter)
{
	assert(NULL != iter);
	return (NULL != iter->right);
}

/*  */
static bst_iter_t GetLeftChild(bst_iter_t iter)
{
	assert(NULL != iter);
	return iter->left;
}

/*  */
static bst_iter_t GetRightChild(bst_iter_t iter)
{
	assert(NULL != iter);
	return iter->right;
}

/*  */
static bst_iter_t GetParent(bst_iter_t iter)
{
	assert(NULL != iter);
	return iter->parent;
}

/*  */
static int IsLeftChild(bst_iter_t iter)
{
	assert(NULL != iter);
	return IsSameIter(iter, GetLeftChild(GetParent(iter)));
}

/*  */
static int IsRightChild(bst_iter_t iter)
{
	assert(NULL != iter);
	return IsSameIter(iter, GetRightChild(GetParent(iter)));	
}

/*  */
static int IsLeaf(bst_iter_t iter)
{
	assert(NULL != iter);
	return (NULL == GetRightChild(iter) && (NULL ==GetLeftChild(iter)));
}

/*************************************************************************
																		 *
				      		ITER FUNCTIONS							 	 *
																		 *
*************************************************************************/
/*
 * get iter to next larger value
 * Param @Iter - current iter
 * Return : iter to next larger value
 * Errors : if no next iter, return END
 */
bst_iter_t BSTNext(bst_iter_t iter);

/*
 * get iter to prev smaller value
 * Param @Iter - current iter
 * Return : iter to prev smaller value
 * Errors : if iter is first, undefined behaviour
 */
bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t prev = NULL;

	assert(NULL != iter);
	
	if (HasLeftChild(iter)/* || (IsLeaf(iter) && IsRightChild(iter))*/)
	{
		bst_iter_t cur_iter = GetLeftChild(iter);
		
		while (HasRightChild(cur_iter))
		{
			cur_iter = GetRightChild(cur_iter);
		}
		prev = cur_iter;
	}
	
	else if (HasRightChild(iter)/* || (IsLeaf(iter) && IsLeftChild(iter))*/)
	{
		if (IsRightChild(iter))
		{
			prev = GetParent(iter);
		}
		
		else /* is left child*/
		{
			bst_iter_t cur_iter = GetParent(iter);
			
			while(IsLeftChild(cur_iter))
			{
				cur_iter = GetParent(cur_iter);
			}

			prev = GetParent(cur_iter);
		}
	}
	
	return prev;
}

/* get End iter */
bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(NULL != bst);

	return bst->dummy_head;	
}

/* get iter to smallest value */
bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t cur_iter = NULL;
	
	assert(NULL != bst);
	assert(FALSE == BSTIsEmpty(bst));
	
	for (cur_iter = GetLeftChild(bst->dummy_head);/*TODO needs to be implemented in insert of first node (root)*/
		 HasLeftChild(cur_iter);
		 cur_iter = GetLeftChild(cur_iter))
		 { /* Empty Body*/ }
		 
	return cur_iter;	
}

int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2);
