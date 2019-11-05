
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

#include "tree_ops.h"

void SwapChildren(bst_iter_t parent);
void mirror(bst_t *tree);


void PrintTreeByLevel(const bst_t *tree)
{
	queue_t *queue = NULL;
	bst_iter_t node = NULL; BSTGetRoot(tree);
	
	assert(NULL != tree);
	
	queue = QueueCreate();
	
	node = BSTGetRoot(tree);
	
	QueueEnqueue(queue, node);
	
	while (!QueueIsEmpty(queue))
	{
		 node = QueuePeek(queue);
		 bst_iter_t left, right = NULL;
		 
		 printf("%d ", *(int *)BSTGetData(node));

		 left = GetLeftChild(node);
		 if (NULL != left)
		 {
	 		QueueEnqueue(queue, left);
		 }
		 
		 right = GetRightChild(node);
		 if (NULL != right)
		 {
	 		QueueEnqueue(queue, right);
		 }
		 
		QueueDequeue(queue);		 
	}
	
	QueueDestroy(queue);
}

void mirror(bst_t *tree)
{
	if (NULL == tree)
	{
		return;
	}
	
	RecMirror(BSTGetRoot(tree));
}

bst_iter_t RecMirror(bst_iter_t node)
{
	if (NULL == node)
	{
		return;
	}
	
	RecMirror(GetLeftChild(node));
	RecMirror(GetRightChild(node));
	
	SwapChildren(node);
}

void SwapChildren(bst_iter_t parent)
{
	bst_iter_t temp = GetLeftChild(parent);
	SetLeftChild(parent, GetRightChild(parent));
	SetRightChild(parent, temp);
}
