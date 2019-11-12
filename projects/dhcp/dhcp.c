
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <string.h> /* memcpy memcmp */ 
#include <stdlib.h> /* malloc free calloc */

#include "dhcp.h"

enum {NOT_AVAILABLE, AVAILABLE};
enum {LEFT, RIGHT} direction;

typedef struct trie_node trie_node_t;
typedef const unsigned char cuchar;
typedef unsigned char uchar;

struct trie_node
{
	trie_node_t *parent;
	trie_node_t *child[];
	int is_available;
};

struct dhcp
{
	trie_node_t root;
	size_t bits_num_in_host;
	cuchar *net_id;
};

/*
 * Create a new DHCP server 
 * Param @net_id : network id
 * Param @num_bits_net_id : num of bits that represent network id, byte alligned
 * Return: pointer to new DHCP server
 * Errors: if memory allocation failed, returns NULL 
 */

dhcp_t *DHCPCreate(unsigned char net_id[BYTES_IN_IP], size_t num_bits_net_id)
{
	dhcp_t *dhcp = NULL;
	uchar req_last_ip[BYTES_IN_IP] = {0};
	uchar req_before_last_ip[BYTES_IN_IP] = {0};
	uchar req_first_ip[BYTES_IN_IP] = {0};
	
	int alloc_reserved_ip_status = 0;

	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (NULL == dhcp)
	{
		return NULL;
	}
	
	dhcp->root = TrieCreateNode(NULL);
	if (NULL == dhcp->root)
	{
		dhcp == FreeAndNullify(dhcp);
		return NULL;
	}
	
	InitReservedAddresses(req_last_ip, req_before_last_ip, req_first_ip, net_id, num_bits_net_id / CHAR_BIT);
	
	alloc_reserved_ip_status = AllocReservedAddresses(req_last_ip, req_before_last_ip, req_first_ip, dhcp);
	
	if (FAIL == alloc_reserved_ip_status)
	{
		dhcp->root = FreeAndNullify(dhcp->root);
		dhcp = FreeAndNullify(dhcp);
		return NULL;
	}
	
	dhcp->bits_num_in_host = BYTES_IN_IP * CHAR_BIT - num_bits_net_id;
	dhcp->net_id = net_id;
	
	return dhcp;
}

static trie_node_t *TrieCreateNode(trie_node_t *parent)
{
	trie_node_t *new_node = (trie_node_t *)malloc(sizeof(trie_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;
	new_node->is_available = AVAILABLE;
	
	return new_node;
}

static void *FreeAndNullify(void *pointer_to_free)
{
	free(pointer_to_free);
	return NULL;
}

dhcp_status_t DHCPLease(dhcp_t *dhcp, const unsigned char req_ip[BYTES_IN_IP],
						unsigned char alloc_ip[BYTES_IN_IP])
{
	size_t net_id_bytes = (CHAR_BIT * BYTES_IN_IP - dhcp->bits_num_in_host) / CHAR_BIT;
	int alloc_req_ip_status = 0;
	int get_next_avail_ip_status = 0;
	uchar *new_ip = NULL;
	size_t host_bytes = BYTES_IN_IP - net_id_bytes;
	
	if (!IsSameNetID(req_ip, dhcp->net_id, net_id_bytes))
	{
		return FAIL;
	}
	
	if (IsReqIPAvailable(dhcp->root, host_bytes, req_ip))
	{
		cuchar host_id = req_ip[net_id_bytes];
		alloc_req_ip_status = TrieAllocReqIP(dhcp->root, host_bytes, host_id);
		if (FAIL == alloc_req_ip_status)
		{
			return FAIL;
		}
		
		memcpy(alloc_ip, req_ip, sizeof(uchar)*BYTES_IN_IP);
		return SUCCESS;
	}
	
	new_ip = (uchar *)calloc(sizeof(uchar)*BYTES_IN_IP);
	if (NULL == new_ip)
	{
		return FAIL;
	}
	
	get_next_avail_ip_status = GetNextAvailIP(dhcp->root, host_bytes, &new_ip[net_id_bytes]);
	if (FAIL == get_next_avail_ip_status)
	{
		new_ip = FreeAndNullify(new_ip);
		return FAIL;
	}
	
	alloc_req_ip_status = TrieAllocReqIP(dhcp->root, , host_bytes);
	if (FAIL == get_next_avail_ip_status)
	{
		new_ip = FreeAndNullify(new_ip);
		return FAIL;
	}
	
	memcpy(alloc_ip, req_ip, net_id_bytes * sizeof(uchar));
	memcpy(alloc_ip[net_id_bytes], new_ip, host_bytes * sizeof(uchar));
	
	new_ip = FreeAndNullify(new_ip);
	--dhcp->available_ips;
	
	return SUCCESS;
	}
}

static int IsSameNetID(cuchar *net_id1, cuchar *net_id2, size_t num_bytes_to_cmp)
{
	assert(NULL != net_id1);
	assert(NULL != net_id2);
	
	return memcmp(net_id1, net_id2, num_bytes_to_cmp);
}

static int IsReqIPAvailable(trie_node_t *root, cuchar *req_ip, cuchar *net_id)
{	
	assert(NULL != root);
	assert(NULL != req_ip);
	assert(NULL != net_id);
	
	/*TODO*/
}

int TrieDoesPathExist(trie_node_t *root, cuchar *req_ip, size_t num_bits_in_host)
{
	size_t i = 0;
	size_t j = 0;
	size_t bytes_in_host = num_bits_in_host / CHAR_BIT;	
	trie_node_t *runner = NULL;
	uchar mask = 0x80;
	
	assert(NULL != root);
	assert(NULL != req_ip);
	
	runner = root;
	
	for (i = 0; i < bytes_in_host; ++i)
	{
		for (j = 0; j < CHAR_BIT; ++j, mask >>= 1)
		
		direction dir = ((mask & req_ip[i]) != 0);
		if (NULL == runner->child[dir])
		{
			return 0;
		}
	}
	return 1; /* change to TRUE/FALSE enum */
}

int TrieAllocReqIP(trie_node_t *node, cuchar *host_id, size_t bytes_in_host)
{
	size_t i = 0;
	size_t j = 0;
	trie_node_t *runner = node;
	
	assert(NULL != node);
	assert(NULL != host_id);
	
	for (i = 0; i < bytes_in_host; ++i)
	{		
		uchar mask = 0x80;
		for (j = 0; j < CHAR_BIT; ++j, mask >>= 1)
		{
			direction dir = ((mask & host_id[i]) != 0);
			
			if (NULL == runner->child[dir])
			{
				runner->child[dir] = TrieCreateNode(runner);
				if (NULL == runner->child[dir])
				{
					TrieFreePath(runner);
					return FAIL;
				}
			}
			
			runner = runner->child[dir];
		}
	}
	
	runner->available = NOT_AVAILABLE;
	UpdateAvailabilityOfNodes(runner);
	
	return SUCCESS;	
}

static void TrieFreeNewPath(trie_node_t *node)
{
	trie_node_t *runner = NULL;
	trie_node_t *parent = NULL;
	
	assert(NULL != node);
	
	runner = node;
	
	while (IsLeaf(runner) && !IsRoot(runner))
	{
		parent = runner->parent;
		runner = FreeAndNullify(runner);
		runner = parent;
	}
}

static int IsLeaf(const trie_node_t *node)
{
	assert(NULL != node);
	
	return (!node->child[LEFT] && !node->child[RIGHT]);
}

static int IsRoot(const trie_node_t *node)
{
	assert(NULL != node);
	
	return (NULL == root->parent);
}

static int AreChildrenNotAvailable(const trie_node_t *node)
{
	assert(NULL != node);
	
	return (!node->child[LEFT]->is_available && !node->child[RIGHT]);
}

static int HasTwoChildren(const trie_node_t *node)
{
	assert(NULL != node);
	
	return (node->child[LEFT] && node->child[RIGHT);
}

static int GetNextAvailIP((trie_node_t *root, size_t host_id_bytes, uchar *new_host_id)
{
	size_t i = 0;
	size_t j = 0;
	trie_node_t *runner = NULL;
	int direction = 0;
	
	assert(NULL != root);
	assert(NULL != new_host_id);
	assert(0 < host_id_bytes);
	
	runner = root;
	
	for (i = 0; i < host_id_bytes; ++i)
	{
		uchar mask = 0x80;
		
		for (j = 0;
			 (j < CHAR_BIT) && runner->is_available;
			 ++j, runner = runner->child[direction]
			)
		{
			if (runner->child[LEFT] && runner->child[LEFT]->is_available)
			{
				mask >>= 1;
				direction = LEFT;
			}
			else if (NULL == runner->child[LEFT])
			{
				return SUCCESS;
			}
			else if (runner->child[RIGHT] && runner->child[RIGHT]->is_available)
			{
				new_host_id[i] |= mask; 
				mask >>= 1;
				direction = RIGHT;
			}
			else if (NULL == runner->child[RIGHT])
			{
				new_host_id[i] |= mask;
				return SUCCESS;
			}
		}
	}
	/* Trie is full*/
	return FAIL;
}

dhcp_status_t DHCPRelease(dhcp_t *dhcp, const unsigned char ip_to_release[BYTES_IN_IP])
{
	size_t net_id_bytes = 0;
	size_t host_id_bytes = 0;
	
	assert(NULL != dhcp);
	assert(NULL != ip_to_release);
	
	net_id_bytes = BYTES_IN_IP - (dhcp->host_id_bytes / CHAR_BIT);
	host_id_bytes = BYTES_IN_IP - net_id_bytes;
	
	net_id_bytes = BYTES_IN_IP - (dhcp->host_bytes / CHAR_BIT);
	
	if (!IsSameNetID(net_id_bytes, ip_to_release, dhcp->net_id))
	{
		return ILLEGAL_RELEASE;
	}
	
	if (IsReservedIP(&ip_to_release[net_id_bytes], dhcp->net_id, net_id_bytes))
	{
		return ILLEGAL_RELEASE;
	} 
	
	if (TrieIsPathExist(dhcp->root, dhcp->host_id_bytes / CHAR_BIT, &ip_to_release[net_id_bytes]))
	{
		trie_node_t *leaf_to_release = GetLeaf(dhcp->root, host_id_bytes
		trie_node_t *node_to_update = TrieFreeNewPath(node_to_update);
		
		++dhcp->available_ips;
		return SUCCESS;
	}
	
	return ILLEGAL_RELEASE;
}

static trie_node_t *GetLeaf(const trie_node_t *root, size_t bytes_in_host ,cuchar *path)
{	
	size_t i = 0;
	size_t j = 0;
	trie_node_t *runner = NULL;
	
	host_id_bytes = 0;
	
	assert(NULL != root);
	assert(NULL != path);
	
	runner = root;
	
	for (i = 0; i < host_id_bytes; ++i)
	{
		unsigned char mask = 0x80;
		
		for (j = 0; j < CHAR_BIT && runner->is_available; ++j, mask >>= 1)
		{
			unsigned char direction = (0 != (mask & path[i]));
			
			if (NULL == runner->child[direction])
			{
				return 0; /*not exist*/
			}
			
			runner = runner->child[direction];
		}
	}
	
	return 1; /*exist*/
}
}
