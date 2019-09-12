
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* free malloc */

#include "bst.h"

#define UNUSED(x) (void)(x)

#define TRUE 1
#define FALSE 0

typedef struct bst_node bst_node;

struct bst_node
{
	bst_node *left;
	bst_node *right;
	bst_node *parent;	
	void *data;
};

struct bst
{
	cmp_func_t cmp_func;
	void *param;
	bst_iter_t dummy_head;
};

/*************************************************************************
																		 *
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/
static bst_iter_t BSTGetRoot(const bst_t *bst);
static bst_node *CreateBSTNode(bst_node *left,
						 		bst_node *right,
						 		bst_node *parent,
						 		void *data);
static void DestroyBSTNode(bst_node *node_to_destroy);

static int HasLeftChild(bst_iter_t iter);
static int HasRightChild(bst_iter_t iter);
static bst_iter_t GetLeftChild(bst_iter_t iter);
static bst_iter_t GetRightChild(bst_iter_t iter);
static bst_iter_t GetParent(bst_iter_t iter);
static int IsLeftChild(bst_iter_t iter);
static int IsRightChild(bst_iter_t iter);
static int IsLeaf(bst_iter_t iter);				 		

/* Create new binary search tree */
bst_t *BSTCreate(cmp_func_t cmp_func, void *param)
{

	bst_t *new_bst = NULL;
	bst_iter_t dummy_head = NULL;

	assert(NULL != cmp_func);
	
	dummy_head = (bst_iter_t)CreateBSTNode(NULL,NULL,NULL,NULL);
	if (NULL == dummy_head)
	{
		return NULL;
	}
	
	new_bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == new_bst)
	{
		DestroyBSTNode((bst_node *)dummy_head);
		dummy_head = NULL;
		return NULL;
	}
	
	/* init bst */
	new_bst->cmp_func = cmp_func;
	new_bst->dummy_head = dummy_head;
	new_bst->param = param;	
	
	return new_bst;
}

/* Destroy binary search tree  */
void BSTDestroy(bst_t *bst)
{
	assert(NULL != bst);
	
	if (!BSTIsEmpty(bst))
	{
		DestroyBSTNode(BSTGetRoot(bst));
	}
	
	free(bst->dummy_head);
	free(bst);
}

/* Insert new element to tree */
bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t new_node = NULL;
	assert(NULL != bst);
	
	new_node = (bst_iter_t)CreateBSTNode(NULL, NULL, NULL, data);
	
	if (NULL == new_node)
	{
		return NULL;
	}
	
	if (BSTIsEmpty(bst))
	{
		new_node->parent = bst->dummy_head;
		bst->dummy_head->left = new_node;
	}
	else
	{
		bst_iter_t cur_tree_node = GetLeftChild(bst->dummy_head);
		int is_insertion_done = FALSE;
		
		while (FALSE == is_insertion_done)
		{
			int result = bst->cmp_func(BSTGetData(cur_tree_node),
													BSTGetData(new_node), NULL);
			if (1 == result)
			{
				if (HasLeftChild(cur_tree_node))
				{
					cur_tree_node = GetLeftChild(cur_tree_node);
				}
				else
				{
					new_node->parent = cur_tree_node;
					cur_tree_node->left = new_node;
					is_insertion_done = TRUE;
				}
			}
			else /* if equals or is after */
			{
				if (HasRightChild(cur_tree_node))
				{
					cur_tree_node = GetRightChild(cur_tree_node);
				}
				else
				{
					new_node->parent = cur_tree_node;
					cur_tree_node->right = new_node;
					is_insertion_done = TRUE;
				}
			}
		}
	}
	
	return new_node;
}

/* helper for remove */
void CopyDataFromNodeToNode(bst_iter_t dest, bst_iter_t src)
{
	assert(NULL != dest);
	assert(NULL != src);	
	
	dest->data = BSTGetData(src);
}

/* Removes iter from tree */
void BSTRemove(bst_iter_t iter_to_remove)
{
	assert(NULL != iter_to_remove);
	
	/* if iter_to_remove is not in the bst */
	if (NULL == BSTFind(iter_to_remove))
	{
		return;
	}
	
	if (IsLeaf(iter_to_remove))
	{
		bst_iter_t parent = GetParent(iter_to_remove); /*TODO consider moving upwards*/
		
		if (IsLeftChild(iter_to_remove))
		{
			parent->left = NULL;
		}
		else /* IsRightChild */
		{
			parent->right = NULL;
		}
		
		DestroyBSTNode(iter_to_remove);
	}
	/* only has one child */
	else if (HasLeftChild(iter_to_remove) && !HasRightChild(iter_to_remove))
	{
		bst_iter_t parent = GetParent(iter_to_remove);
		if (IsLeftChild(iter_to_remove))
		{
			parent->left = GetLeftChild(iter_to_remove);
		}
		else /* IsRightChild */
		{
			parent->right = GetLeftChild(iter_to_remove);
		}
		
		DestroyBSTNode(iter_to_remove);
	}
	
	else if (HasRightChild(iter_to_remove) && !HasLeftChild(iter_to_remove))
	{
		bst_iter_t parent = GetParent(iter_to_remove);
		if (IsLeftChild(iter_to_remove))
		{
			parent->left = GetRightChild(iter_to_remove);
		}
		else /* IsRightChild */
		{
			parent->right = GetRightChild(iter_to_remove);
		}
		
		DestroyBSTNode(iter_to_remove);
	}
	else /* has two children */
	{
		bst_iter_t prev = BSTPrev(iter_to_remove);
		bst_iter_t prev_parent = GetParent(prev);

		CopyDataFromNodeToNode(iter_to_remove, prev);		
		
		if (IsLeaf(prev))
		{
			if (IsLeftChild(prev))
			{
				parent->left = NULL;
			}
			else /* IsRightChild */
			{
				parent->right = NULL;
			}
		
		DestroyBSTNode(prev);
		}
		
		else /* prev has a child */
		{
			/* can only be left child otherwise its right
			   child will be the prev iter				 */			
			bst_iter_t child = GetLeftChild(prev);
			prev_parent->left = child;
			child->parent = prev_parent;

			DestroyBSTNode(prev);
		}
	}
}

/* Perform <action_func> for each element in <bst>, stops if action returns
non-zero. */
int BSTForEach(bst_t *bst,
			   void *param,
			   bst_iter_t from,
			   bst_iter_t to, 
			   action_func_t action_func)
{
	bst_iter_t cur_iter = NULL;
	int return_status = 0;
	
	assert(NULL != bst);
	assert(NULL != action_func);
	assert(NULL != from);
	assert(NULL != to);
	
	for (cur_iter = from;
		 (!BSTIsSameIter(cur_iter, to)) && (0 == return_status);
		 cur_iter = BSTNext(cur_iter)
		)
	{
		return_status = action_func(BSTGetData(cur_iter), param);
	}
	
	return return_status;
}			   

/* helper for BSTSize */
static int NodeCounter(void *iter_data, void *param)
{
	UNUSED(iter_data);
	*(size_t *)param += 1;
	return 0;
}

static bst_iter_t BSTGetRoot(const bst_t *bst)
{
	assert (NULL != bst);
	
	return bst->dummy_head->left;
}

bst_iter_t BSTFind(bst_t *bst, void *data_to_find)
{
	
	int continue_search = 1;
	bst_iter_t result_iter = NULL;
	bst_iter_t cur_iter = NULL;
	assert(NULL != bst);
	
	cur_iter = BSTGetRoot(bst);
	
	while (continue_search)
	{
		int cmp = bst->cmp_func(BSTGetData(cur_iter), data_to_find, NULL);
		if (1 == cmp)
		{
			if (HasLeftChild(cur_iter))
			{
				cur_iter = GetLeftChild(cur_iter);
			}
			else
			{
				continue_search = FALSE;
			}
		}
		else if (-1 == cmp)
		{
			if (HasRightChild(cur_iter))
			{
				cur_iter = GetRightChild(cur_iter);
			}
			else
			{
				continue_search = FALSE;
			}
		}
		else /* found a match */
		{
			result_iter = cur_iter;
			continue_search = FALSE;
		}
	}
	
	return result_iter;	
}

/* Count how many nodes in given binary search tree */
size_t BSTSize(const bst_t *bst)
{
	bst_iter_t from = NULL;
	bst_iter_t to = NULL;	
	size_t counter_init_value = 0;
	size_t *counter = &counter_init_value;
	
	assert(NULL != bst);
	
	from = BSTBegin(bst);
	to = BSTEnd(bst);
	
	BSTForEach((bst_t *)bst, counter, from, to, NodeCounter);
	
	return *counter;
}

/* Check if tree is empty */
int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return (NULL == GetLeftChild(bst->dummy_head));
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
static void DestroyBSTNode(bst_node *node_to_destroy)
{
	if (NULL == node_to_destroy)
	{
		return;
	}
	
	DestroyBSTNode(GetLeftChild(node_to_destroy));
	DestroyBSTNode(GetRightChild(node_to_destroy));	
	free(node_to_destroy);
}

/*************************************************************************
																		 *
			      		Static ITER FUNCTIONS					 	 	 *
																		 *
*************************************************************************/

/*  */
static int HasLeftChild(bst_iter_t iter)
{
	int result = FALSE;
	assert(NULL != iter);
	
	if (NULL != iter->left)
	{
		result = TRUE;
	}
	
	return result;
}

/*  */
static int HasRightChild(bst_iter_t iter)
{
	int result = FALSE;
	assert(NULL != iter);
	
	if (NULL != iter->right)
	{
		result = TRUE;
	}
	
	return result;
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
	
	if (NULL == GetLeftChild(GetParent(iter)))
	{
		return FALSE;
	}
	
	return BSTIsSameIter(iter, GetLeftChild(GetParent(iter)));
}

/*  */
static int IsRightChild(bst_iter_t iter)
{
	assert(NULL != iter);
	
	if (NULL == GetRightChild(GetParent(iter)))
	{
		return FALSE;
	}
	
	return BSTIsSameIter(iter, GetRightChild(GetParent(iter)));	
}

/*  */
static int IsLeaf(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return (NULL == GetRightChild(iter) && (NULL == GetLeftChild(iter)));
}

/*************************************************************************
																		 *
				      		ITER FUNCTIONS							 	 *
																		 *
*************************************************************************/
/* get iter to next value */
bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_iter_t next = NULL;
	
	assert(NULL != iter);
	
	if (HasRightChild(iter))
	{
		bst_iter_t cur_iter = GetRightChild(iter);
		
		while (HasLeftChild(cur_iter))
		{
			cur_iter = GetLeftChild(cur_iter);
		}
		
		next = cur_iter;
	}
	
	else if (!HasRightChild(iter) && IsLeftChild(iter))
	{
		next = GetParent(iter);
	}

	else if (IsLeaf(iter) && IsRightChild(iter))
	{
		bst_iter_t cur_iter = iter;
		
		while (IsRightChild(cur_iter))
		{
			cur_iter = GetParent(cur_iter);
		}
		
		next = GetParent(cur_iter);
	}
	
	return next;
}

/* get iter to prev value */
bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t prev = NULL;

	assert(NULL != iter);
	
	if (HasLeftChild(iter)/* || (IsLeaf(iter) && IsRightChild(iter))*/)/*TODO*/
	{
		bst_iter_t cur_iter = GetLeftChild(iter);
		
		while (HasRightChild(cur_iter))
		{
			cur_iter = GetRightChild(cur_iter);
		}
		prev = cur_iter;
	}
	
	else if (HasRightChild(iter)/* || (IsLeaf(iter) && IsLeftChild(iter))*/)/*TODO*/
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
	
	else if ((IsLeaf(iter) && IsRightChild(iter)))
	{
		prev = GetParent(iter);
	}
	
	else if ((IsLeaf(iter) && IsLeftChild(iter)))
	{
		bst_iter_t cur_iter = iter;
			
		while(IsLeftChild(cur_iter))
		{
			cur_iter = GetParent(cur_iter);
		}

		prev = GetParent(cur_iter);
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
		 { /* Empty Body */ }
		 
	return cur_iter;	
}

/* Get data of iter */
void *BSTGetData(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->data;	
}

int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(NULL != iter1);	
	assert(NULL != iter2);	
	
	return ((BSTGetData(iter1) == BSTGetData(iter2)) &&
									    (GetParent(iter1) == GetParent(iter2)));
}
