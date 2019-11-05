
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

#include "tree_ops.h"

void PrintTreeByLevel(const bst_t *tree)
{
	queue_t *queue = QueueCreate();
	
	bst_iter_t node = BSTGetRoot(tree);
	
	QueueEnqueue(queue, node);
	
	while (!QueueIsEmpty(queue))
	{
		 node = QueuePeek(queue);
		 printf("%d ", *(int *)BSTGetData(node));

		 if (NULL != GetLeftChild(node))
		 {
	 		QueueEnqueue(queue, GetLeftChild(node));
		 }
		 
		 if (NULL != GetRightChild(node))
		 {
	 		QueueEnqueue(queue, GetRightChild(node));
		 }
		 
		QueueDequeue(queue);		 
	}
	
	QueueDestroy(queue);
}
