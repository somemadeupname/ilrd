
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

#include "slist_ops.h"

slist_node_t *GetNodeInLoop(slist_node_t *node)
{
	slist_node_t *slow = node;
	slist_node_t *fast = node;
	
	assert(NULL != node);
	
	while (fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next;
	
		if (slow == fast)
		{
			return fast;
		}
	}
	
	return NULL;	
}

void FindAndBreakLoop(slist_node_t *node)
{
	slist_node_t *node_in_loop = NULL;
	slist_node_t *cur = node;
	slist_node_t *anchor = NULL;
	
	assert(NULL != node);
	
	node_in_loop = GetNodeInLoop(node);
	if (NULL == node_in_loop)
	{
		return;
	}
	
	anchor = node_in_loop;
	
	while (cur != node_in_loop)
	{
		for (node_in_loop = node_in_loop->next;
			 (node_in_loop != anchor);
			 node_in_loop = node_in_loop->next)
			 {
			 	if (node_in_loop == cur->next)
			 	{	
			 		/* break the loop */
			 		cur->next = NULL;
			 		return;
			 	}
			 }
			 cur = cur->next;
	}
}

