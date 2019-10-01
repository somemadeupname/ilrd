/****************************
 * Author: shaddad Gomid	*
 * Reviewer: Dor			*
 * Status: S				*
 ****************************/
 
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "avl.h"

typedef int (*cmp_func)(const void *tree_data, const void *new_data, void *param);
typedef int (*action_func)(void *tree_data, void *param);

typedef struct avl_node avl_node_t;

enum {LEFT, RIGHT, MAX_CHILDREN};

struct avl_node
{
	void *data;
	size_t height;
	avl_node_t *children[MAX_CHILDREN];
};

struct avl
{
	void *param;
	cmp_func cmp_function;
	avl_node_t *dummy;
};
/******************************************************************************/
/*					  forward sub-functions declaration					  	  */
/******************************************************************************/
/* sub-functions for general use, can be found at the end of this file */

static avl_node_t *GetRoot(const avl_t *avl);
static int GetDirection(int cmp_result);

/******************************************************************************/

/* sub-function of AVLDestroy */
static void DestroyNodes();

/******************************************************************************/

/* sub-functions of AVLInsert */
static avl_node_t* CreateNode(const void *data_to_insert);

avl_node_t *InsertNode(avl_node_t *node, cmp_func cmp_function, 
					   void *param, const void *data_to_insert, int *direction);

/******************************************************************************/

/* sub-functions of AVLRemove */
static avl_node_t *RecAVLRemove(avl_node_t *root, 
				cmp_func cmp_function, const void *data_to_remove, void *param);

/* sub-function of RecAVLRemove */
static avl_node_t *DestroyNode(avl_node_t *node, cmp_func cmp_function, 
									   const void *data_to_remove, void *param);
/* sub-functions of DestroyNode */
static int Has2Children(avl_node_t *node);
static void SwapNodesData(avl_node_t *node_1, avl_node_t *node_2);
static avl_node_t *GetChild(avl_node_t *node);
static avl_node_t *GetMostLeft(avl_node_t *node);

/******************************************************************************/

/* sub-functions for balancing, used in AVLInsert and AVLRemove */
static void UpdateHeight(avl_node_t *node);

static avl_node_t *Rebalance(avl_node_t *node);

static int CheckBalance(avl_node_t *node);			/*						 */
static avl_node_t *RotateRight(avl_node_t *node);	/*Rebalance sub-functions*/
static avl_node_t *RotateLeft(avl_node_t *node);	/*						 */

/* sub-function of UpdateHeight and CheckBalance */ 
static size_t GetHeight(avl_node_t *node);

/******************************************************************************/

/* sub-function of AVLCount */
static size_t RecAVLCount(avl_node_t* node);

/******************************************************************************/

/* sub-function of AVLFind */
static avl_node_t *RecAVLFind(avl_node_t *node, const void *data_to_find,
							cmp_func cmp_function, int cmp_result, void *param);

/******************************************************************************/

/* sub-function of AVLFind */
int RecAVLForEach(avl_node_t * node, void *param, action_func action);

/******************************************************************************/

avl_t *AVLCreate(void *param, cmp_func cmp_function)
{
	avl_t *avl = malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return NULL;
	}
	
	avl->param = param;
	avl->cmp_function = cmp_function;
	avl->dummy = CreateNode(avl->dummy);
	
	return avl;
}

/******************************************************************************/

void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);
		
	DestroyNodes(avl->dummy);
	
	free(avl);
	avl = NULL;
}

static void DestroyNodes(avl_node_t *node)
{	
	if (NULL == node)
	{
		return;
	}
	
	DestroyNodes(node->children[LEFT]);
	DestroyNodes(node->children[RIGHT]);
	
	free(node);
	node = NULL;
}

/******************************************************************************/

int AVLInsert(avl_t *avl, const void *data_to_insert)
{
	int direction = LEFT;
	avl_node_t *root = NULL;
	
	assert(NULL != avl);
	
	if (AVLIsEmpty(avl))
	{
		avl->dummy->children[LEFT] = CreateNode(data_to_insert);
		
		return 0;
	}
	
	root = GetRoot(avl);
	
	avl->dummy->children[LEFT] = InsertNode(root, avl->cmp_function, 
										avl->param, data_to_insert, &direction);
	
	return 0;
}

/*sub-function of AVLInsert ***************************************************/
static avl_node_t* CreateNode(const void *data_to_insert)
{
	avl_node_t *new_node = malloc(sizeof(avl_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = (void *)data_to_insert;
	new_node->height = 1;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;	
	
	return new_node;
}

/*sub-function of AVLInsert ***************************************************/
avl_node_t *InsertNode(avl_node_t *node, cmp_func cmp_function, 
						void *param, const void *data_to_insert, int *direction)
{
	int cmp_result = 0;
	
	assert(NULL != node);
	
	cmp_result = cmp_function(node->data, data_to_insert, param);
	*direction = GetDirection(cmp_result);
	if (NULL == node->children[*direction])
	{
		avl_node_t *node_to_insert = CreateNode(data_to_insert);
		if (NULL == node_to_insert)
		{
			return NULL;
		}
		
		node->children[*direction] = node_to_insert;
		UpdateHeight(node);
		
		return node;
	}
	
	node->children[*direction] = InsertNode(node->children[*direction], 
								cmp_function, param, data_to_insert, direction);
	
	UpdateHeight(node);
	
	node = Rebalance(node);
	
	return node;
}

/******************************************************************************/

void AVLRemove(avl_t *avl, const void *data_to_remove)
{
	avl_node_t *root = NULL;
	
	assert(NULL != avl);
	
	root = GetRoot(avl);
	
	if (NULL == root)
	{
		return;
	}

	avl->dummy->children[LEFT]= RecAVLRemove(root, avl->cmp_function, 
													data_to_remove, avl->param);
}

/*AVLRemove sub-function*******************************************************/
static avl_node_t *RecAVLRemove(avl_node_t *root, cmp_func cmp_function, 
										const void *data_to_remove, void *param)
{
	int cmp_result = 0;
	int direction = 0;
	
	if (NULL == root)
	{
		return root;
	}
	
	cmp_result = cmp_function(root->data, data_to_remove, param);
	if (0 == cmp_result)
	{
		return DestroyNode(root, cmp_function, data_to_remove, param);
	}
	
	direction = GetDirection(cmp_result);
	root->children[direction] = RecAVLRemove(root->children[direction], 
										   cmp_function, data_to_remove, param);
	
	UpdateHeight(root);
	
	root = Rebalance(root);
	
	return root;
}

/*RecAVLRemove sub-function****************************************************/
static avl_node_t *DestroyNode(avl_node_t *node, cmp_func cmp_function, 
										const void *data_to_remove, void *param)
{
	assert(NULL != node);
	
	if (Has2Children(node))
	{
		avl_node_t *next_node = GetMostLeft(node->children[RIGHT]);
		SwapNodesData(node, next_node);
		
		node->children[RIGHT] = RecAVLRemove(node->children[RIGHT], 
										   cmp_function, data_to_remove, param);
	}
	else
	{
		avl_node_t *child = GetChild(node);

		free(node);
		node = NULL;
		
		return child;
	}
	
	return node;
}

/*DestroyNode sub-function*****************************************************/
static avl_node_t *GetMostLeft(avl_node_t *node)
{
	if (NULL == node->children[LEFT])
	{
		return node;
	}
	
	return GetMostLeft(node->children[LEFT]);
}

/*DestroyNode sub-function*****************************************************/
static int Has2Children(avl_node_t *node)
{
	assert(NULL != node);
	
	if ((NULL == node->children[RIGHT]) || (NULL == node->children[LEFT]))
	{
		return 0;
	}
	
	return 1;
}

/*DestroyNode sub-function*****************************************************/
static avl_node_t *GetChild(avl_node_t *node)
{
	assert(NULL != node);
	
	if (NULL != node->children[RIGHT])
	{
		return node->children[RIGHT];
	}
	else
	{
		return node->children[LEFT];
	}
}

/*DestroyNode sub-function*****************************************************/
static void SwapNodesData(avl_node_t *node_1, avl_node_t *node_2)
{
	void *tmp = node_1->data;
	node_1->data = node_2->data;
	node_2->data = tmp;
}

/******************************************************************************/

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (NULL == GetRoot(avl));
}

/******************************************************************************/

size_t AVLCount(const avl_t *avl)
{
	size_t count = 0;
	avl_node_t* root = NULL;
	
	assert(NULL != avl);
	
	root = GetRoot(avl);
	
	count = RecAVLCount(root);
	
	return count;
}

/* sub-function of AVLCount****************************************************/
static size_t RecAVLCount(avl_node_t* node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return (   RecAVLCount(node->children[LEFT])
			+  RecAVLCount(node->children[RIGHT]) + 1);
}

/******************************************************************************/

void *AVLFind(const avl_t *avl, const void *data_to_find)
{
	avl_node_t *node = NULL;
	int cmp_result = 0;
	assert(NULL != avl);
	
	node = GetRoot(avl);
	
	cmp_result = avl->cmp_function(node->data, data_to_find, avl->param);
	
	node = RecAVLFind(node, data_to_find, avl->cmp_function, cmp_result, 
																	avl->param);
	
	if (NULL == node)
	{
		return NULL;
	}
	
	return node->data;
}

/* sub-function of AVLFind*****************************************************/
static avl_node_t *RecAVLFind(avl_node_t *node, const void *data_to_find,
							 cmp_func cmp_function, int cmp_result, void *param)
{
	int direction = 0;
	
	if (NULL == node || 0 == cmp_result)
	{
		return node;
	}

	cmp_result = cmp_function(node->data, data_to_find, param);
	if (0 == cmp_result)
	{
		return node;
	}
	
	direction = GetDirection(cmp_result);
	
	node = RecAVLFind(node->children[direction],data_to_find, cmp_function, 
															 cmp_result, param); 
	
	return node;
}

/******************************************************************************/

int AVLForEach(void *param, avl_t *avl, action_func action)
{
	int status = 0;
	avl_node_t *root = NULL;
	
	assert(NULL != avl);
	
	root = GetRoot(avl);
	
	status = RecAVLForEach(root, param, action);
	
	return status;
}

/* sub-function of RecAVLForEach***********************************************/
int RecAVLForEach(avl_node_t * node, void *param, action_func action)
{
	int status = 0;
	
	if (NULL == node)
	{
		return status;
	}
	
	status = RecAVLForEach(node->children[LEFT], param, action);
	
	if (0 != status)
	{
		return status;
	}
	
	status = action(node->data, param);
	if (0 != status)
	{
		return status;
	}
		
	status = RecAVLForEach(node->children[RIGHT], param, action);
	
	return status;
}

/******************************************************************************/
static avl_node_t *Rebalance(avl_node_t *node)
{
	int balance_factor = 0;
	avl_node_t *left_child = NULL;
	avl_node_t *right_child = NULL;
	
	assert(NULL != node);
	
	balance_factor = CheckBalance(node);
	
	left_child = node->children[LEFT];
	right_child = node->children[RIGHT];
	
	if (balance_factor > 1)
	{
		if (NULL != left_child->children[LEFT])
		{
			node = RotateRight(node);
		}
		else if (NULL != left_child->children[RIGHT])
		{
			node->children[LEFT] = RotateLeft(left_child);
			UpdateHeight(node->children[LEFT]);
		}
		
		return node;
	}
	else if (balance_factor < -1)
	{
		if (NULL != right_child->children[RIGHT])
		{
			node = RotateLeft(node);
			UpdateHeight(node);
		}
		else if (NULL != right_child->children[LEFT])
		{
			node->children[RIGHT] = RotateRight(right_child);
			UpdateHeight(node->children[RIGHT]);
			node = RotateLeft(node);
		}
		
		return node;
	}
	
	return node;
}

/*sub-function of Rebalance****************************************************/
static avl_node_t *RotateRight(avl_node_t *node)
{
	avl_node_t *left_child = NULL;
	avl_node_t *left_child_right = NULL;
	
	assert(NULL != node);
	
	left_child = node->children[LEFT];
	left_child_right = left_child->children[RIGHT];
	left_child->children[RIGHT] = node;
	node->children[LEFT] = left_child_right;
	
	UpdateHeight(node);
	
	return left_child;
}

/*sub-function of Rebalance****************************************************/
static avl_node_t *RotateLeft(avl_node_t *node)
{
	avl_node_t *right_child = NULL;
	avl_node_t *right_child_left = NULL;
	
	assert(NULL != node);

	right_child = node->children[RIGHT];
	right_child_left = right_child->children[LEFT];
	right_child->children[LEFT] = node;
	node->children[RIGHT] = right_child_left;
	
	UpdateHeight(node);
	
	return right_child;
}

/*sub-function of Rebalance****************************************************/
static int CheckBalance(avl_node_t *node)
{
	int balance_factor = 0;
	int left_child_height = 0;
	int right_child_height = 0;
	
	assert(NULL != node);
	
	left_child_height = GetHeight(node->children[LEFT]);
	right_child_height = GetHeight(node->children[RIGHT]);
	
	balance_factor = left_child_height - right_child_height;
	
	return balance_factor;
}

/******************************************************************************/

static void UpdateHeight(avl_node_t *node)
{
	size_t left_child_height = 0;
	size_t right_child_height = 0;
	
	assert(NULL != node);
	
	left_child_height = GetHeight(node->children[LEFT]);
	right_child_height = GetHeight(node->children[RIGHT]);
	
	node->height = (left_child_height >= right_child_height) ?
				   (left_child_height + 1) : (right_child_height + 1);
}

/*UpdateHeight and CheckBalance ***********************************************/
static size_t GetHeight(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return node->height;
}

/*sub-functions for general use ***********************************************/

static avl_node_t *GetRoot(const avl_t *avl)
{
	return avl->dummy->children[LEFT];
}

static int GetDirection(int cmp_result)
{
	if (cmp_result > 0)
	{
		return LEFT;
	}
	else
	{
		return RIGHT;
	}
}

