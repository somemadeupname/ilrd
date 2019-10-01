#include <stdio.h>
#include <assert.h>
#include <string.h> /* strcmp */

#include "hash_table.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");
#define TRUE 1
#define FALSE 0

#define PRINT_ERROR START_RED printf("ERROR in %s.\n", func_name); END_RED

#define PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE \
{\
	int a = 1;\
	expect_int(1,1,"hi");\
	expect_size_t(1lu,1lu,"hi");\
	expect_NULL(NULL,"hi");\
	expect_Not_NULL(&a, "hi");\
}

#define LEGAL_ALPHA_BUCKETS 172

/*************************************************************************
								 										 *
				      GENERAL TEST FUNCTIONS							 *
																		 *
*************************************************************************/
void expect_int(int result, int expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%d\nActual: \t%d\n", expected_result, result);
	}	
}

void expect_size_t(size_t result, size_t expected_result, char *func_name)
{
	if (result != expected_result)
	{
		PRINT_ERROR
		printf("Expected: \t%lu\nActual: \t%lu\n", expected_result, result);
	}	
}

void expect_NULL(void *pointer, char *func_name)
{
	if (pointer != NULL)
	{
		PRINT_ERROR
		printf("pointer isn't NULL.\n");
	}	
}

void expect_Not_NULL(void *pointer, char *func_name)
{
	if (pointer == NULL)
	{
		PRINT_ERROR
		printf("pointer isn't NULL.\n");
	}	
}

/*************************************************************************
								 										 *
				      TEST HELPER FUNCTIONS								 *
																		 *
*************************************************************************/
size_t FirstLetterHashFunc(void *key)
{
	char *str_key = NULL;
	
	assert(NULL != key);
	
	str_key = (char *)key;
	
	return (str_key[0] - 65) % LEGAL_ALPHA_BUCKETS;
}
int StrCmpFunc(const void *key1, const void *key2)
{	
	assert(NULL != key1);
	assert(NULL != key2);
	
	return strcmp((char *)key1, (char *)key2);
}

void FuncsTest()
{
	char *str1 = "A";
	char *str2 = "z";
	
	printf("%ld\n", FirstLetterHashFunc(str1));
	printf("%ld\n", FirstLetterHashFunc(str2));
	printf("%d\n", StrCmpFunc(str1, str2));		
}

/*************************************************************************
								 										 *
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/

void HashTableCreate_test();
void HashTableInsert_test();
/*void HashTableRemove_test();*/
void HashTableSize_test();



int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE	  	   	
	
/*	FuncsTest();*/

	HashTableCreate_test();
	
	HashTableInsert_test();	
	
	HashTableSize_test();

	return 0;
}

void HashTableSize_test()
{
	hash_table_t *ht = HashTableCreate (LEGAL_ALPHA_BUCKETS, FirstLetterHashFunc, StrCmpFunc);

	expect_int(HashTableIsEmpty(ht), 1, "HashTableSize_test1");	

	HashTableInsert(ht, "hello");
	expect_size_t(HashTableSize(ht), 1, "HashTableSize_test3");

	HashTableInsert(ht, "lello");
	HashTableInsert(ht, "gello");
	HashTableInsert(ht, "aello");
	HashTableInsert(ht, "bello");		
	HashTableInsert(ht, "dello");
	HashTableInsert(ht, "ddllo");			
	
	expect_size_t(HashTableSize(ht), 7, "HashTableSize_test3");	
	
	expect_int(HashTableIsEmpty(ht), 0, "HashTableSize_test2");		
	
	
	HashTableDestroy(ht);	
}

void HashTableInsert_test()
{
	hash_table_t *ht = HashTableCreate (LEGAL_ALPHA_BUCKETS, FirstLetterHashFunc, StrCmpFunc);
	
	HashTableInsert(ht, "hello");
	
	HashTableDestroy(ht);
}

void HashTableCreate_test()
{
	hash_table_t *ht = HashTableCreate (LEGAL_ALPHA_BUCKETS, FirstLetterHashFunc, StrCmpFunc);
	HashTableDestroy(ht);
}
