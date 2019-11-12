
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Alex M	    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */

/* TODO REMOVE THIS TODO*/
#include <stdio.h>
/* TODO REMOVE THIS TODO*/

#include "avl.h"

#define NUM_CHILDREN 2

typedef struct avl_node avl_node_t;

typedef int (*cmp_func_t)(const void *iter_data, const void *new_data,
																   void *param);

typedef int (*action_func_t)(void *tree_data, void *param);

struct avl_node
{
	void *data;
	size_t height;
	avl_node_t *child[NUM_CHILDREN];
};

struct avl
{
	void *param;
	cmp_func_t cmp_func;
	avl_node_t *dummy_node;
};

typedef enum {LEFT, RIGHT} direction;

enum {AVL_SUCCESS, AVL_FAIL};

/******************************************************************************
*								     										  *
*				      	FORWARD DECLARATIONS       						  	  *
*								      										  *
******************************************************************************/
/* NODE HELPERS */
static avl_node_t *CreateAVLNode(const void *data);
static avl_node_t *DestroyAVLNode(avl_node_t *node_to_destroy);
static int HasRightChild(const avl_node_t *node);
static int HasLeftChild(const avl_node_t *node);
static int HasTwoChildren(const avl_node_t *node);
static void SwapData(avl_node_t *node1, avl_node_t *node2);
static void *GetData(const avl_node_t *node);
static size_t GetNodeHeight(avl_node_t *node);
static avl_node_t *GetPrev(avl_node_t *node);
static avl_node_t *GetChild(avl_node_t *parent_node);

/* AVL HELPERS */
static direction GetDirection(avl_node_t *tree_node,
							  cmp_func_t cmp,
 							  void *param,
 							  const void *data);

/*static */ avl_node_t *AVLGetRoot(const avl_t *avl); /*CHANGE BACK TO STATIC TODO*/
static avl_node_t *RecursiveInsert(avl_node_t *tree_node,
							cmp_func_t cmp,
							void *param,
							avl_node_t *node_to_insert);
static avl_node_t *RemoveNode(avl_node_t *node_to_remove,
								   cmp_func_t cmp,
								   const void *data_to_remove,
								   void *param);							
static void RecursiveDestroy(avl_node_t *node_to_destroy);
static void RecursiveCount(avl_node_t *node, size_t *counter);

int RecursiveForEach(avl_node_t *node,
					 action_func_t func,
					 void *param,
					 int *status);

/* balancing and height functions */
static size_t MaxHeight(avl_node_t *left_child, avl_node_t *right_child);
static void UpdateHeight(avl_node_t *node);
static avl_node_t *Balance(avl_node_t *node);
static int GetBalance(avl_node_t *node);
static avl_node_t *RotateRight(avl_node_t *node);
static avl_node_t *RotateLeft(avl_node_t *node);

/* generic free and null function */
static void *FreeAndNullify(void *pointer_to_free);

/* TODO remove this - for testing purposes only */
int Int(avl_node_t *node);
/* TODO remove this - for testing purposes only */

/******************************************************************************
*								     										  *
*				      	AVL NODE FUNCTIONS	       						  	  *
*								      										  *
******************************************************************************/

static avl_node_t *CreateAVLNode(const void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = (void *)data;
	new_node->height = 1;
	new_node->child[RIGHT] = NULL;
	new_node->child[LEFT] = NULL;
	
	return new_node;
}

static avl_node_t *DestroyAVLNode(avl_node_t *node_to_destroy)
{
	free(node_to_destroy);
	return NULL;
}

/* check if needs to look in LEFT or RIGHT direction */
static direction GetDirection(avl_node_t *tree_node,
							  cmp_func_t cmp,
							  void *param,
	   						  const void *data)
{
	assert(NULL != tree_node);
	assert(NULL != cmp);
	
	if (cmp(tree_node->data, data, param) > 0)
	{
		return LEFT;
	}
	return RIGHT;
}
/* check if node has a right child */
static int HasRightChild(const avl_node_t *node)
{
	assert(NULL != node);
	
	return (NULL != node->child[RIGHT]);
}

static int HasLeftChild(const avl_node_t *node)
{
	assert(NULL != node);
	
	return (NULL != node->child[LEFT]);	
}

static int HasTwoChildren(const avl_node_t *node)
{
	assert(NULL != node);
	
	return (HasLeftChild(node) && HasRightChild(node));
		
}

/* get node data */
static void *GetData(const avl_node_t *node)
{
	assert(NULL != node);
	
	return node->data;
}

/* get node child. should only be called if node only has one child */
static avl_node_t *GetChild(avl_node_t *parent_node)
{
	if (NULL != parent_node->child[LEFT])
	{
		return parent_node->child[LEFT];
	}
	
	return parent_node->child[RIGHT];
}
/* get the prev node in the avl */
static avl_node_t *GetPrev(avl_node_t *node)
{
	if (NULL == node->child[LEFT])
	{
		return node;
	}
	
	return GetPrev(node->child[LEFT]);
}

/* update the height of givee @node */
static void UpdateHeight(avl_node_t *node)
{
	assert(NULL != node);
	
	node->height = 1 + MaxHeight(node->child[LEFT], node->child[RIGHT]);
}

/* get the maximum height of @node's children */
static size_t MaxHeight(avl_node_t *left_child, avl_node_t *right_child)
{
	size_t max_height = GetNodeHeight(left_child) > GetNodeHeight(right_child) ?
						GetNodeHeight(left_child) : GetNodeHeight(right_child);
	return max_height;
}

/* get current balance of @node */
static int GetBalance(avl_node_t *node)
{
	assert(NULL != node);
	
	return (int)((int)GetNodeHeight(node->child[LEFT])-
									    (int)GetNodeHeight(node->child[RIGHT]));
}

/* get @node height */
static size_t GetNodeHeight(avl_node_t *node)
{	
	return (NULL != node) ? node->height : 0;
}

/* swap data between @node1 and @node2 */
static void SwapData(avl_node_t *node1, avl_node_t *node2)
{
	void *temp_data = NULL;	
	
	assert(NULL != node1);
	assert(NULL != node2);	
	
	temp_data = node1->data;
	node1->data = node2->data;
	node2->data = temp_data;
}


/******************************************************************************
*								     										  *
*				      		AVL FUNCTIONS	       							  *
*								      										  *
******************************************************************************/
/* get root node of avl */
/*static */avl_node_t *AVLGetRoot(const avl_t *avl)
{
	assert(NULL != avl);
	
	return avl->dummy_node->child[LEFT];
}

/* Create new AVL tree */
avl_t *AVLCreate(void *param, int (*cmp_func)(const void *tree_data,
								 			  const void *new_data,
								 			  void *param))
{
	avl_node_t *dummy_node = NULL;
	avl_t *new_avl = NULL;
	
	assert(cmp_func != NULL);
	
	new_avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == new_avl)
	{
		return NULL;
	}
	
	dummy_node = CreateAVLNode(NULL);
	if (NULL == dummy_node)
	{
		new_avl = FreeAndNullify(new_avl);
		return NULL;
	}
	
	/* init avl */
	new_avl->cmp_func = cmp_func;
	new_avl->param = param;
	new_avl->dummy_node = dummy_node;
	
	return new_avl;	
}

/* helper for AVLDestroy */
static void RecursiveDestroy(avl_node_t *node_to_destroy)
{
	if (NULL == node_to_destroy)
	{
		return;
	}

	RecursiveDestroy(node_to_destroy->child[LEFT]);
	RecursiveDestroy(node_to_destroy->child[RIGHT]);
	node_to_destroy = DestroyAVLNode(node_to_destroy);
}

/* Destroy AVL tree */
void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	RecursiveDestroy(AVLGetRoot(avl));
	
	avl->dummy_node = DestroyAVLNode(avl->dummy_node);

	avl = FreeAndNullify(avl);
}

/* helper for AVLDestroy and DestroyAVLNode */
static void *FreeAndNullify(void *pointer_to_free)
{
	free(pointer_to_free);
	return NULL;
}

/* helper for AVLInsert */
static avl_node_t *RecursiveInsert(avl_node_t *tree_node,
							cmp_func_t cmp,
							void *param,
							avl_node_t *node_to_insert)
{
	direction dir = LEFT;
	
	assert(NULL != tree_node);
	assert(NULL != cmp);
	assert(NULL != node_to_insert);
	
	dir = GetDirection(tree_node, cmp, param, GetData(node_to_insert));
	
	if (NULL == tree_node->child[dir])
	{
		tree_node->child[dir] = node_to_insert;
		UpdateHeight(tree_node);
		
		return tree_node;
	}
	else
	{
		tree_node->child[dir] = RecursiveInsert(tree_node->child[dir], cmp,
														param, node_to_insert);
	}
	
	UpdateHeight(tree_node);
	
	tree_node = Balance(tree_node);
	
	return tree_node;
}

/* Insert new element to tree */
int AVLInsert(avl_t *avl, const void *data_to_insert)
{
	avl_node_t *node_to_insert = NULL;

	assert(NULL != avl);
	
	node_to_insert = CreateAVLNode(data_to_insert);
	if (NULL == node_to_insert)
	{
		return AVL_FAIL;
	}
	
	/* adding the first node */
	if (AVLIsEmpty(avl))
	{
		avl->dummy_node->child[LEFT] = node_to_insert;
		return AVL_SUCCESS;
	}
	
	avl->dummy_node->child[LEFT] = RecursiveInsert(AVLGetRoot(avl),
									 avl->cmp_func, avl->param, node_to_insert);
	
	return AVL_SUCCESS;	
}

/* recursive implementation for AVLRemove */
static avl_node_t *RecursiveRemove(avl_node_t *node_to_check,
								   cmp_func_t cmp,
								   const void *data_to_remove,
								   void *param)
{
	direction dir = LEFT;
	
	if (NULL == node_to_check)
	{
		return NULL;
	}
	
	if (cmp(node_to_check->data, data_to_remove, param) == 0)
	{
		return RemoveNode(node_to_check, cmp, data_to_remove, param);
	}
	
	dir = GetDirection(node_to_check, cmp, param, data_to_remove);
	
	node_to_check->child[dir] = RecursiveRemove(node_to_check->child[dir],
													cmp, data_to_remove, param);
		
	UpdateHeight(node_to_check);
	
	node_to_check = Balance(node_to_check);
	
	return node_to_check;
}

/* helper for RecursiveRemove */
static avl_node_t *RemoveNode(avl_node_t *node_to_remove,
								   cmp_func_t cmp,
								   const void *data_to_remove,
								   void *param)
{
	assert(NULL != node_to_remove);
	assert(NULL != cmp);

	if (HasTwoChildren(node_to_remove))
	{
		avl_node_t *next_node = GetPrev(node_to_remove->child[RIGHT]);
		SwapData(node_to_remove, next_node);
		node_to_remove->child[RIGHT] =
		RecursiveRemove(node_to_remove->child[RIGHT], cmp, data_to_remove,
																		 param);
	}
	else
	{
		avl_node_t *child = GetChild(node_to_remove);
		node_to_remove = DestroyAVLNode(node_to_remove);
		return child;
	}
	
	return node_to_remove;
}
/* balances the avl from given node @node*/
static avl_node_t *Balance(avl_node_t *node)
{
	#define MAX_BALANCE_FACTOR 1
	#define MIN_BALANCE_FACTOR -1
	int balance_factor = 0;
	
	assert(NULL != node);
	
	balance_factor = GetBalance(node);
	
	if (balance_factor > MAX_BALANCE_FACTOR)
	{
		if (HasLeftChild(node->child[LEFT]))
		{
			node = RotateRight(node);
		}
		else if (HasRightChild(node->child[LEFT]))
		{
			node->child[LEFT] = RotateLeft(node->child[LEFT]);
			UpdateHeight(node->child[LEFT]);
		}
		
		return node;
	}
	else if (balance_factor < MIN_BALANCE_FACTOR)
	{
		if (HasRightChild(node->child[RIGHT]))
		{
			node = RotateLeft(node);
			UpdateHeight(node);
		}
		else if (HasLeftChild(node->child[RIGHT]))
		{
			node->child[RIGHT] = RotateRight(node->child[RIGHT]);
			UpdateHeight(node->child[RIGHT]);
			node = RotateLeft(node);
		}
		
		return node;
	}
	
	return node;
	
	#undef MAX_BALANCE_FACTOR
	#undef MIN_BALANCE_FACTOR
}

/* performs right rotation */
static avl_node_t *RotateRight(avl_node_t *node)
{
	avl_node_t *left = NULL;
	avl_node_t *left_right = NULL;
	
	assert(NULL != node);
	
	left = node->child[LEFT];
	left_right = left->child[RIGHT];
	left->child[RIGHT] = node;
	node->child[LEFT] = left_right;
	
	UpdateHeight(node);	
	
	return left;
}

/* performs left rotation */
static avl_node_t *RotateLeft(avl_node_t *node)
{
	avl_node_t *right = NULL;
	avl_node_t *right_left = NULL;
	
	assert(NULL != node);
	
	right = node->child[RIGHT];
	right_left = right->child[LEFT];
	right->child[LEFT] = node;
	node->child[RIGHT] = right_left;
	
	UpdateHeight(node);
	
	return right;
}

/* Removes node from tree */
void AVLRemove(avl_t *avl, const void *data_to_remove)
{
	assert(NULL != avl);
	
	avl->dummy_node->child[LEFT] = RecursiveRemove(AVLGetRoot(avl),
									avl->cmp_func, data_to_remove, avl->param);
}

/* Check if tree is empty */
int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == avl->dummy_node->child[LEFT]);
}
/* helper for AVLCount */
static void RecursiveCount(avl_node_t *node, size_t *counter)
{
	if (NULL == node)
	{
		return;
	}
	
	++(*counter);

	RecursiveCount(node->child[LEFT], counter);
	RecursiveCount(node->child[RIGHT], counter);
}


/* PRE-ORDER Count how many nodes in given AVL tree */
size_t AVLCount(const avl_t *avl)
{
	size_t node_counter = 0;

	assert(NULL != avl);
	
	RecursiveCount(AVLGetRoot(avl), &node_counter);
	
	return node_counter;	
}
/* helper for AVLFind */
static void *RecursiveFind(const avl_node_t *tree_node,
						   const void *data_to_find,
						   const avl_t *avl)
{
	direction dir = LEFT;

	assert(NULL != avl);
	
	/* data not found */
	if (NULL == tree_node)
	{
		return NULL;
	}
	
	if (avl->cmp_func(tree_node->data, data_to_find, avl->param) == 0)
	{
		return GetData(tree_node);
	}
	
	dir = GetDirection((avl_node_t *)tree_node, avl->cmp_func, avl->param,
																  data_to_find);
	
	return RecursiveFind(tree_node->child[dir], data_to_find, avl);
}

/* Find data in @avl */
void *AVLFind(const avl_t *avl, const void *data_to_find)
{
	assert(NULL != avl);
	
	return RecursiveFind(AVLGetRoot(avl), data_to_find, avl);
}

/* Perform action_func for each element in @avl */
int AVLForEach(void *param, avl_t *avl, int (*action_func)(void *tree_data,
														   void *param))
{	
	int status = 0;	
		
	assert(NULL != avl);
	assert(NULL != action_func);
	
	return RecursiveForEach(AVLGetRoot(avl), action_func, param, &status);
}
/* helper for AVLForEach */
int RecursiveForEach(avl_node_t *node, action_func_t func, void *param,
																	int *status)
{	
	/* exit as soon as status isn't 0*/
	if (0 != *status)
	{
		return *status;
	}
	
	if (NULL == node)
	{
		return 0;
	}
	
	RecursiveForEach(node->child[LEFT], func, param, status);
	
	*status = func(node->data, param);
	
	return RecursiveForEach(node->child[RIGHT], func, param, status);
}

/* Check height of @avl */
size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);
	
	return GetNodeHeight(AVLGetRoot(avl));
}

/* TODO remove this - for testing purposes only */
void InOrderPrintNodes(avl_node_t *node)
{
	if (NULL == node)
	{
      return;
    }

    InOrderPrintNodes(node->child[LEFT]);
    printf("%d (%ld)\n", *(int*)node->data, GetNodeHeight(node));
    InOrderPrintNodes(node->child[RIGHT]);
}
/* TODO remove this - for testing purposes only */
int Int(avl_node_t *node)
{
/*	assert (NULL != node);*/

	if (node == NULL)
	{
		return 0;
	}
	
	return *(int *)node->data;
}
/* TODO remove this - for testing purposes only */
size_t Height(avl_node_t *node)
{
	if (node == NULL)
	{
		return 0;
	}

	return node->height;
}
