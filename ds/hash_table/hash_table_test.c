#include <stdio.h> /* printf fopen fclose perror*/
#include <assert.h>
#include <string.h> /* strcmp 	strncpy */
#include <sys/stat.h> /* stat */
#include <stdlib.h> /* malloc free */


#include "hash_table.h"

#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");
#define TRUE 1
#define FALSE 0
#define UNUSED(x) (void)(x)

#define PRINT_ERROR START_RED printf("ERROR in %s.\n", func_name); END_RED

#define PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE \
{\
	int a = 1;\
	expect_int(1,1,"hi");\
	expect_size_t(1lu,1lu,"hi");\
	expect_NULL(NULL,"hi");\
	expect_Not_NULL(&a, "hi");\
}

#define VALID_ALPHA_CHARS_NUM 173

/*const char *DICT_PATH = "/usr/share/dict/american-english";*/
const char *DICT_PATH = "/home/student0/ran-shieber/ds/hash_table/adictionary";

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
/* hash func */
size_t FirstLetterHashFunc(void *key)
{
	char *str_key = NULL;
	
	assert(NULL != key);
	
	str_key = (char *)key;
	
	return (str_key[0]-65) % VALID_ALPHA_CHARS_NUM;
}
/* 2nd hash func */
size_t SumOfAsciiHash(void *key)
{
	char *str_key = NULL;
	int sum = 0;
	
	assert(NULL != key);
	
	str_key = (char *)key;
	
	
	while (NULL != str_key)
	{
		sum += *str_key;
		++str_key;
	}
	
	return sum;
}

/* cmp func */
int StrCmpFunc(const void *key1, const void *key2)
{	
	assert(NULL != key1);
	assert(NULL != key2);
	
	return strcmp((char *)key1, (char *)key2);
}
/* hash and cmp funcs test */
void FuncsTest()
{
	char *str1 = "A";
	char *str2 = "z";
	
	printf("%ld\n", FirstLetterHashFunc(str1));
	printf("%ld\n", FirstLetterHashFunc(str2));
	printf("%d\n", StrCmpFunc(str1, str2));		
}
/* action func */
int PrintString(void *table_data, void *param)
{
	UNUSED(param);
	printf("%s\n", (char *) table_data);
	
	return 0;
}

/* action func */
int FailPrintString(void *table_data, void *param)
{
	UNUSED(param);
	
	if (0 == strcmp((char *)table_data, "hello"))
	{
		return 1;
	}
	printf("%s\n", (char *)table_data);
	
	return 0;
}

/*************************************************************************
								 										 *
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/

void HashTableCreate_test();
void HashTableInsert_test();
void HashTableRemove_test();
void HashTableSize_test();
void HasTableFind_test();
void HasTableForEach_test();	
void HasTableForEachFail_test();

void Dictionary_test();

int main()
{
	PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE	  	   	
	
/*	FuncsTest();*/

	HashTableCreate_test();
	
	HashTableInsert_test();	
	
	HashTableSize_test();
	
	HashTableRemove_test();
	
	HasTableFind_test();
	
/*	HasTableForEach_test();*/

/*	HasTableForEachFail_test();*/

	Dictionary_test();

	return 0;
}

/*function to get size of the file.*/
/*long int FindSize(const char *file_name)*/
/*{*/
/*    struct stat st;*/
/*     */
    /* get the size using stat() */
/*     */
/*    if (0  == stat(file_name, &st))*/
/*    {*/
/*        return (st.st_size);*/
/*    }*/
/*    return -1;*/
/*}*/

static void GetWord(char **words, size_t word_idx ,char *src)
{
	size_t size = 1;
	size_t char_idx = 0;
	while (src[char_idx] != '\n' && src[char_idx] != '\0')
	{
		++size;
		++char_idx;
	}
	
	words[word_idx] = (char *)malloc(sizeof(char) * size);/* TODO check if fails */
	strncpy(words[word_idx], src, size);
	*(words[word_idx] + size - 1) = '\0';
/*	printf("key: %ld\n", SumOfAsciiHash(words[word_idx]));*/
}

static void FreeWords(char **words, size_t num_words)
{
	size_t word_idx = 0;
	for (word_idx = 0; word_idx < num_words; ++word_idx)
	{
/*		printf("%ld: %s\n", word_idx, words[word_idx]);		*/
		free(words[word_idx]); /*words[word_idx] = NULL;*/
	}
	free(words); words = NULL;
}
#define BUFFER_SIZE 40
static void ClearBuffer(char *buffer)
{
	size_t c = 0;
	for (c = 0; c < BUFFER_SIZE; ++c)
	{
		buffer[c] = '\0';
	}
}

void Dictionary_test()
{
/*	long int buffer_size = FindSize(DICT_PATH);*/
	static char temp_buffer[BUFFER_SIZE] = {'\0'};
		
	FILE *dict = fopen(DICT_PATH, "r");
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);
	char c = '0';
	size_t char_index = 0;
	char **words = (char **)malloc(sizeof(char**));
	size_t word_idx = 0;
	
	if (NULL == dict)
	{
		perror("Failure opening file.\n");
	}
	
	c = fgetc(dict);
	while (EOF != c)
	{
		while ('\n' != c)
		{
			temp_buffer[char_index] = c;
			c = fgetc(dict);
			++char_index;
		}
		
		GetWord(words, word_idx, temp_buffer);
		
		HashTableInsert(ht, words[word_idx]);
		printf("i:%ld ,word: %s\n", word_idx, words[word_idx]);
		++word_idx;
		ClearBuffer(temp_buffer);
		char_index = 0;
		c = fgetc(dict);
	}
	
/*	HashTableForEach(ht, PrintString, NULL);*/
/*	PrintBucketSizes(ht);*/
	
	HashTableDestroy(ht);		
	FreeWords(words, word_idx);
	fclose(dict);
}

void HasTableForEachFail_test()
{
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);

	HashTableInsert(ht, "aello");
	HashTableInsert(ht, "bello");
	HashTableInsert(ht, "cello");
	HashTableInsert(ht, "dello");		
	HashTableInsert(ht, "hello");
	HashTableInsert(ht, "xello");
	HashTableInsert(ht, "zdllo");
	
	expect_int(HashTableForEach(ht, FailPrintString, NULL),1,"HasTableForEachFail_test1");
	
	HashTableDestroy(ht);	
}

void HasTableForEach_test()
{
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);

	HashTableInsert(ht, "hello");
	HashTableInsert(ht, "lello");
	HashTableInsert(ht, "gello");
	HashTableInsert(ht, "aello");
	HashTableInsert(ht, "bello");		
	HashTableInsert(ht, "dello");
	HashTableInsert(ht, "ddllo");
	
	HashTableForEach(ht, PrintString, NULL);
	
	HashTableDestroy(ht);		
}

void HasTableFind_test()
{
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);

	HashTableInsert(ht, "hello");
	HashTableInsert(ht, "lello");
	HashTableInsert(ht, "gello");
	HashTableInsert(ht, "aello");
	HashTableInsert(ht, "bello");		
	HashTableInsert(ht, "dello");
	HashTableInsert(ht, "ddllo");
	
	expect_Not_NULL(HashTableFind(ht, "dello"), "HasTableFind_test1");
	
/*	expect_NULL(HashTableFind(ht, ""), "HasTableFind_test2");*/	/*empty string kills it FIXME */

	expect_NULL(HashTableFind(ht, "d"), "HasTableFind_test2");
	
	HashTableDestroy(ht);	
}

void HashTableRemove_test()
{
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);

	expect_int(HashTableIsEmpty(ht), 1, "HashTableRemove_test1");	

	HashTableInsert(ht, "hello");
	expect_size_t(HashTableSize(ht), 1, "HashTableRemove_test2");

	HashTableInsert(ht, "lello");
	HashTableInsert(ht, "gello");
	HashTableInsert(ht, "aello");
	HashTableInsert(ht, "bello");		
	HashTableInsert(ht, "dello");
	HashTableInsert(ht, "ddllo");			
	
	expect_size_t(HashTableSize(ht), 7, "HashTableRemove_test3");	
	
	expect_int(HashTableIsEmpty(ht), 0, "HashTableRemove_test4");		
	
	HashTableRemove(ht, "lello");
	
	expect_size_t(HashTableSize(ht), 6, "HashTableRemove_test5");		
	
	HashTableRemove(ht, "lello");
	expect_size_t(HashTableSize(ht), 6, "HashTableRemove_test5");			
	HashTableRemove(ht, "gello");
	expect_size_t(HashTableSize(ht), 5, "HashTableRemove_test5");			
	HashTableRemove(ht, "aello");
	expect_size_t(HashTableSize(ht), 4, "HashTableRemove_test5");			
	HashTableRemove(ht, "bello");		
	expect_size_t(HashTableSize(ht), 3, "HashTableRemove_test5");			
	HashTableRemove(ht, "dello");
	expect_size_t(HashTableSize(ht), 2, "HashTableRemove_test5");			
	HashTableRemove(ht, "ddllo");
	expect_size_t(HashTableSize(ht), 1, "HashTableRemove_test5");			
	
	HashTableDestroy(ht);	
}

void HashTableSize_test()
{
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);

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
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);
	
	HashTableInsert(ht, "hello");
	
	HashTableDestroy(ht);
}

void HashTableCreate_test()
{
	hash_table_t *ht = HashTableCreate (VALID_ALPHA_CHARS_NUM, FirstLetterHashFunc, StrCmpFunc);
	HashTableDestroy(ht);
}
