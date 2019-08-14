#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "slist.h"

slist_node_t *SListCreateNode(void *data, slist_node_t *next)
{
	slist_node_t *head = (slist_node_t *)malloc(sizeof(slist_node_t));
	
	if (NULL == head)
	{
		return NULL;
	}
	head->next_node = next;
	head->data = data;
	return head;
}

void SListFreeAll(slist_node_t *head)
{
	slist_node_t *cur_node = head;
	
	while (NULL != cur_node)
	{
		slist_node_t *next = cur_node->next_node;
		free(cur_node); cur_node = NULL;
		cur_node = next;
	}
}

static void SwapNodeData(slist_node_t *node1, slist_node_t *node2)
{
	void *data_temp = NULL;
	assert(NULL != node1);
	assert(NULL != node2);
	
	data_temp = node1->data;
	node1->data = node2->data;
	node2->data = data_temp;
}

slist_node_t *SListInsert(slist_node_t *current_node, slist_node_t *new_node)
{
	
	assert(NULL != new_node); 
	assert(NULL != current_node);
	
	SwapNodeData(current_node, new_node);
	
	new_node->next_node = current_node->next_node;
	current_node->next_node = new_node;
		
	return current_node;
}

slist_node_t *SListInsertAfter(slist_node_t *current_node,
														slist_node_t *new_node)
{
	
	if (NULL == new_node)
	
	{
		return NULL;	
	}
	new_node->next_node = current_node->next_node;
	current_node->next_node = new_node;
	
	return current_node;
}

slist_node_t *SListFind(slist_node_t *head, cmp_func cmp, const void *data)
{
	slist_node_t *cur_node = head;
	assert(NULL != head);
	
	while (NULL != cur_node)
	{
		if (0 == cmp(cur_node->data, data))
		{
			return cur_node;
		}
		cur_node = cur_node->next_node;
	}
	
	return NULL;
}

/*
 * Remove links from node 
 * param head : pointer to node to remove - can't be the last node.
 * Return : pointer to the removed node
 * Errors : if head is the last node, behaviour is undifined
 */
slist_node_t *SListRemove(slist_node_t *head)
{
	slist_node_t *removed_node = NULL;
	assert (NULL != head);
	assert (NULL != head->next_node);
	
	SwapNodeData(head, head->next_node);
	removed_node = head->next_node;
	head->next_node = head->next_node->next_node;
	
	removed_node->next_node = NULL;
	
	return removed_node;
}


/*
 * Remove links from and to node after a given node
 *  param head : pointer to node pointing to node to remove 
 * Return : pointer to the removed node
 *			if node has no node after it - return NULL
 * Errors : none
 */
slist_node_t *SListRemoveAfter(slist_node_t *head)
{
	if (NULL == head->next_node)
	{
		return NULL;
	}
	return SListRemove(head->next_node);
}

size_t SListCount(const slist_node_t *head)
{
	size_t nodes_counter = 0;
	slist_node_t *cur_node = (slist_node_t *) head;
	while (NULL != cur_node)
	{
		cur_node = cur_node->next_node;
		++nodes_counter;
	}
	return nodes_counter;
}

int SListForEach(slist_node_t *head, func_action func, void *param)
{
	int result = 0;
	slist_node_t *cur_node = head;
	
	while(NULL != cur_node)
	{
		result = func(cur_node->data, param);
		if (0 != result)
		{
			return result;
		}
		cur_node = cur_node->next_node;
	}
	return result;
}
