#include <stdlib.h> /* malloc free */

#include "slist.h"

slist_node_t *SListCreateNode(void *data, slist_node_t *next)
{
	slist_node_t *head = (slist_node_t *)malloc(sizeof(slist_node_t));
	
	if (NULL == head)
	{
		return NULL;
	}
	head->next = next_node;
	head->data = data;
	return head;
}

void SListFreeAll(slist_node_t *head)
{
	slist_node_t cur_node = head;
	slist_node_t next_node = NULL;
	
	while (cur_node)
	{
		if (NULL != cur_node->next)
		{
			next_node = cur_node->next;
		}
		
		free(cur_node); cur_node = NULL;
		cur_mode = next_node;
	}
}

slist_node_t *SListInsert(slist_node_t *current_node, slist_node_t *new_node)
{
	assert(NULL != new_node); /* TODO fix this */
	
	new_node->next = current;
	return new_node;
}

slist_node_t *SListInsertAfter(slist_node_t *current_node,
														slist_node_t *new_node)
{
	
	if (NULL == new_node) /* confirm this TODO*/
	{
		return NULL;	
	}
	new_node->next = current->node->next;
	current_node->next = new_node;
	
	return current_node;
}

slist_node_t *SListFind(slist_node_t *head, cmp_func cmp, const void *data)
{
	slist_node_t *cur_node = head;
	assert(NULL != head);
	
	while (cur_node)
	{
		if (0 == cmp(cur_node->data, data))
		{
			return cur_node;
		}
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
	
}

/*
 * Count how many nodes in linked-list
 * Param : pointer to node 
 * Return : numbers of nodes including starting node
 * Errors : if node has loop, behaviour is undefind
 */
size_t SListCount(const slist_node_t *head)
{
	size_t nodes_counter = 0;
	slist_node_t *cur_node = head;
	while (NULL != cur_node)
	{
		cur_node = cur_node->next; /* check if returns correct number TODO*/
		++nodes_counter;
	}
	return nodes_counter;
}

/*
 * Perform action for each node in the linked-list
 * param head :  pointer to node
 * Param func : pointer to action function
 * Param param : param passing to action func. NULL if there's no param. 
 * Return : 0 for success, else for fail.
 * Return action_func : 0 for success, else for fail.
 * Errors : if node has loop, behaviour is undefined
 */
int SListForEach(slist_node_t *head, func_action func, void *param)
{
	slist_node_t *cur_node = head;
	
	while(NULL != cur_node)
}

