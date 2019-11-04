/****************************************
 * Title  : 	     					 *
 * Author : 			                 *
 * Group  : OL712						 *
 * Date   : 			               	 *
 ****************************************/
#ifndef __ILRD_OL712_SLIST_OPS_H
#define __ILRD_OL712_SLIST_OPS_H

#include "slist.h"

void FindAndBreakLoop(slist_node_t *node);
slist_node_t *GetNodeInLoop(slist_node_t *node);
slist_node_t *FlipListRecursive(slist_node_t *node);

#endif /* __ILRD_OL712_SLIST_OPS_H */
