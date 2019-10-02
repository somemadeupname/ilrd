
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/
#include <assert.h>
#include <stdlib.h> /* malloc free */

#include "hash_table.h"
#include "dlist.h"

enum {HASH_TABLE_SUCCESS, HASH_TABLE_FAIL};

struct hash_table
{
	size_t (*hash_func)(void *key);
	int (*cmp_func)(const void *key1, const void *key2);
	size_t num_buckets;
	dlist_t **buckets;
};

/* forward declaration */
static void InitDlists(dlist_t **buckets, int num_of_buckets);

/* Create hash table */
hash_table_t *HashTableCreate(size_t num_of_buckets,
							  size_t (*hash_func)(void *data),
							  int (*hash_cmp_func)(const void *key1,
							  				  	   const void *key2))
{
	hash_table_t *ht = (hash_table_t *)malloc(sizeof(hash_table_t));
	if (NULL == ht)
	{
		return NULL;
	}
	
	assert(num_of_buckets > 0);
	assert(NULL != hash_func);
	assert(NULL != hash_cmp_func);
	
	ht->buckets = (dlist_t **)malloc(num_of_buckets * sizeof(dlist_t*));
	if (NULL == ht->buckets)
	{
		free(ht); ht = NULL;
		return NULL;
	}
	
	InitDlists(ht->buckets, num_of_buckets);
	ht->hash_func = hash_func;
	ht->cmp_func = hash_cmp_func;
	ht->num_buckets = num_of_buckets;	
	
	return ht;
}

/* initialize buckets */
static void InitDlists(dlist_t **buckets, int num_of_buckets)
{
	int alloc_success = 1;
	int bucket = 0;
	
	for (bucket = 0; alloc_success && (bucket < num_of_buckets); ++bucket)
	{
		buckets[bucket] = DListCreate();
		if (NULL == buckets[bucket])
		{
			for (; 0 <= bucket ; --bucket)
			{
				DListDestroy(buckets[bucket]);
			}
			alloc_success = 0;
		}
	}
}

/* Destroy the hash table */
void HashTableDestroy(hash_table_t *hash_table)
{
	size_t bucket = 0;
	
	assert(NULL != hash_table);
	
	for (bucket = 0; bucket < hash_table->num_buckets; ++bucket)
	{	
		if (NULL != hash_table->buckets[bucket])
		{
			DListDestroy(hash_table->buckets[bucket]);
			hash_table->buckets[bucket] = NULL;
		}
	}
	
	free(hash_table->buckets); hash_table->buckets = NULL;
	free(hash_table); hash_table = NULL;
}

/* Insret data to the hash table  */
int HashTableInsert(hash_table_t *hash_table, void *data)
{
	size_t bucket_idx = 0;
	dlist_iter_t end = NULL;
	dlist_iter_t insert_result = NULL;

	assert(NULL != hash_table);
	
	bucket_idx = hash_table->hash_func(data);
	
	end = DListEnd((hash_table->buckets[bucket_idx]));
	insert_result = DListPushFront(hash_table->buckets[bucket_idx], data);
	
	if (DListIsSameIter(insert_result, end))
	{
		return HASH_TABLE_FAIL;
	}
	
	return HASH_TABLE_SUCCESS;	
}

/* Remove data from the hash table */
void HashTableRemove(hash_table_t *hash_table, void *data)
{
	size_t bucket_idx = 0;
	dlist_iter_t found_data = NULL;
	dlist_iter_t begin = NULL;
	dlist_iter_t end = NULL;	
	
	assert(NULL != hash_table);
	
	bucket_idx = hash_table->hash_func(data);
	begin = DListBegin((hash_table->buckets[bucket_idx]));
	end = DListEnd((hash_table->buckets[bucket_idx]));
	
	found_data = DListFind(begin, end, hash_table->cmp_func, data);
	if (!DListIsSameIter(found_data, end))
	{
		DListRemove(found_data);
	}
}

/* Get size of the hash table */
size_t HashTableSize(const hash_table_t *hash_table)
{
	size_t size = 0;
	size_t bucket = 0;	
	
	for (bucket = 0; bucket < hash_table->num_buckets; ++bucket)
	{
		size += DListSize(hash_table->buckets[bucket]);
	}
	
	return size;
}


/* Check if hash table is empty */
int HashTableIsEmpty(const hash_table_t *hash_table)
{
	size_t bucket = 0;	
	
	for (bucket = 0; bucket < hash_table->num_buckets; ++bucket)
	{
		int is_empty = DListIsEmpty(hash_table->buckets[bucket]);
		if (0 == is_empty)
		{
			return is_empty;
		}
	}
	
	return 1;
}

/* Find data in the hash table */
void *HashTableFind(const hash_table_t *hash_table, void *data)
{
	size_t bucket_idx = 0;
	dlist_iter_t found_data = NULL;
	dlist_iter_t begin = NULL;
	dlist_iter_t end = NULL;	
	
	assert(NULL != hash_table);
	
	bucket_idx = hash_table->hash_func(data);
	begin = DListBegin((hash_table->buckets[bucket_idx]));
	end = DListEnd((hash_table->buckets[bucket_idx]));
	
	found_data = DListFind(begin, end, hash_table->cmp_func, data);
	
	return (NULL == found_data) ? NULL : DListIterGetData(found_data);
}

/* Perform @act_func for each element in the hash table */
int HashTableForEach(const hash_table_t *hash_table,
					 int (*act_func)(void *table_data,
					 				 void *param),
					 				 void *param)
{
	size_t bucket_idx = 0;
	int return_status = 0;
	dlist_iter_t begin = NULL;
	dlist_iter_t end = NULL;
	
	for (bucket_idx = 0;
		(bucket_idx < hash_table->num_buckets) && (0 == return_status);
		++bucket_idx)
	{
		begin = DListBegin((hash_table->buckets[bucket_idx]));;
		end = DListEnd((hash_table->buckets[bucket_idx]));	
		return_status =
		DListForEach(begin, end, act_func, param);
	}

	return return_status;	
}
