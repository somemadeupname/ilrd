/****************************************
 * Title  : 	     					 *
 * Author : 			                 *
 * Group  : OL712						 *
 * Date   : 			               	 *
 ****************************************/
#ifndef __ILRD_OL712_SLIST_OPS_H
#define __ILRD_OL712_SLIST_OPS_H

#include "slist.h"

typedef struct node2 mslist_node_t;

struct node2
{
    int *data;
    mslist_node_t *next_node;
};

void FindAndBreakLoop(mslist_node_t *node);
mslist_node_t *GetNodeInLoop(mslist_node_t *node);
mslist_node_t *FlipListRecursive(mslist_node_t *node);

#endif /* __ILRD_OL712_SLIST_OPS_H */
