
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */

#include "avl.h"

#define NUM_CHILDREN 2

typedef struct avl_node avl_node_t;

typedef int (*cmp_func_t)(const void *iter_data, const void *new_data, void *param);

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
static avl_node_t *CreateAVLNode(const void *data);
static avl_node_t *DestroyAVLNode(avl_node_t *node_to_destroy);
static int HasRightChild(const avl_node_t *node);
static void *GetData(const avl_node_t *node);
static direction GetDirection(avl_node_t *tree_node, cmp_func_t cmp, void *param,
																	 void *data);

static avl_node_t *AVLGetRoot(const avl_t *avl);
static void RecursiveInsert(avl_node_t *tree_node,
							cmp_func_t cmp,
							void *param,
							avl_node_t *node_to_insert);
static void RecursiveDestroy(avl_node_t *node_to_destroy);
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
	new_node->height = 0;/*TODO add height in signature? */
	new_node->child[RIGHT] = NULL;
	new_node->child[LEFT] = NULL;
	
	return new_node;
}

static avl_node_t *DestroyAVLNode(avl_node_t *node_to_destroy)
{
	free(node_to_destroy);	

	return NULL;
}

static direction GetDirection(avl_node_t *tree_node, cmp_func_t cmp, void *param,
																	 void *data)
{
	assert(NULL != tree_node);
	assert(NULL != cmp);
	
	if (cmp(tree_node, data, param) > 0)
	{
		return LEFT;
	}
	return RIGHT;
}

static int HasRightChild(const avl_node_t *node)
{
	assert(NULL != node);
	
	return (NULL != node->child[RIGHT]);
}

static void *GetData(const avl_node_t *node)
{
	assert(NULL != node);
	
	return node->data;
}

/******************************************************************************
*								     										  *
*				      		AVL FUNCTIONS	       							  *
*								      										  *
******************************************************************************/

static avl_node_t *AVLGetRoot(const avl_t *avl)
{
	assert(NULL != avl);
	assert(!AVLIsEmpty(avl));
	
	return avl->dummy_node->child[LEFT];
}

/*
 * Create new AVL tree.
 * Param: @cmp_func - user comparison function. Returns 0 if <tree_data> and 
 *					  <new_data> are equal, positive if <tree_data> is after 
 *					  or negative if it's before.
 * Param: @param - user Param: for <cmp_func> function.
 * Return: pointer to new AVL tree.
 * Errors: if memory allocation failed, return NULL.
 */
avl_t *AVLCreate(void *param, int (*cmp_func)(const void *tree_data,
								 			  const void *new_data,
								 			  void *param))
{
	avl_node_t dummy_node = {NULL, 0, NULL};
	avl_t *new_avl = NULL;
	
	assert(cmp_func != NULL);
	
	new_avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == new_avl)
	{
		return NULL;
	}
	
	/* init avl */
	new_avl->cmp_func = cmp_func;
	new_avl->param = param;
	new_avl->dummy_node = &dummy_node;
	
	return new_avl;	
}

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
/* 
 * POST-ORDER.
 * Destroy AVL tree.
 * Param: @avl - pointer to AVL tree.
 */
void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
	
	RecursiveDestroy(AVLGetRoot(avl));
	
	free(avl); avl = NULL;
}

static void RecursiveInsert(avl_node_t *tree_node,
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
	}
	else
	{
		RecursiveInsert(tree_node->child[dir], cmp, param, node_to_insert);
	}
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
	
	RecursiveInsert(AVLGetRoot(avl), avl->cmp_func, avl->param, node_to_insert);
	
	return AVL_SUCCESS;	
}

/* Check if tree is empty */
int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == avl->dummy_node->child[LEFT]);
}

