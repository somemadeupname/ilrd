
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

#include <assert.h> /* assert */
#include <stdio.h>

#include "slist_ops.h"
#include "slist.h" /* slist API */



mslist_node_t *FlipListIterative(mslist_node_t *node)
{
	mslist_node_t *prev = node;
	mslist_node_t *cur = node->next_node;
	mslist_node_t *next = cur->next_node;
	
	if (NULL == node->next_node)
	{
		prev->next_node = NULL;
		cur->next_node = prev;
		return cur;
	}

	assert(NULL != node);
	
	cur->next_node = NULL; /* old head point to NULL */
	
	while (NULL != cur->next_node)
	{
		cur->next_node = prev;
		prev = cur;
		cur = next;
		next = cur->next_node;
	}
	
	cur->next_node = prev;
	
	return cur;
}

mslist_node_t *FlipListRecursive(mslist_node_t *node)
{
	mslist_node_t *new_head = NULL;
	
	if (NULL == node->next_node)
	{
		return node;
	}
	
	new_head = FlipListRecursive(node->next_node);
	node->next_node->next_node = node;
	node->next_node = NULL;
	
	return new_head;
}

mslist_node_t *GetNodeInLoop(mslist_node_t *head)
{
	mslist_node_t *slow = head;
	mslist_node_t *fast = head;
	
	assert(NULL != head);
	
	while ((NULL != fast->next_node) && (NULL != fast->next_node->next_node))
	{
		slow = slow->next_node;
		fast = fast->next_node->next_node;
	
		if (slow == fast)
		{
			return slow;
		}
	}
	
	return NULL;	
}

void FindAndBreakLoop(mslist_node_t *node)
{
	mslist_node_t *node_in_loop = NULL;
	mslist_node_t *cur = node;
	mslist_node_t *anchor = NULL;
	
	assert(NULL != node);
	
	node_in_loop = GetNodeInLoop(node);
	if (NULL == node_in_loop)
	{
		return;
	}
	
	anchor = node_in_loop;                                                                                    
	
	while (cur != node_in_loop)
	{
		for (node_in_loop = node_in_loop->next_node;
			 (node_in_loop != anchor);
			 node_in_loop = node_in_loop->next_node)
			 {
			 	if (node_in_loop->next_node == cur)
			 	{	
			 		/* break the loop */
			 		node_in_loop->next_node = NULL;
			 		return;
			 	}
			 }
		cur = cur->next_node;
	}
}

