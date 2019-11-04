#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

#define WORD_SIZE (sizeof(void*))

static size_t GetOffsetToNextAlignedAddress(const void *addr)
{
	
	return ((WORD_SIZE - ((size_t)addr) % WORD_SIZE) % WORD_SIZE);
}

static void CopyWordByWord(char **dest, char **src, size_t *n)
{	
	size_t **w_dest = (size_t **)dest;
	size_t **w_src = (size_t **)src;
	
	assert(NULL != dest);
	assert(NULL != *dest);
	assert(NULL != src);
	assert(NULL != *src);			
	
	while ((*n >= WORD_SIZE))
	{
		**w_dest = **w_src;
		++(*w_dest);
		++(*w_src);
		*n -= WORD_SIZE;
	}
}

static void CopyByteByByte(char **dest, char **src, size_t *n)
{
	assert(NULL != dest);
	assert(NULL != *dest);
	assert(NULL != src);
	assert(NULL != *src);			
	
	while ((0 != *n))
	{
		**dest = **src;
		++(*dest);
		++(*src);
		--(*n);
	}	
}

/*
 * The  memcpy() function copies n bytes from memory area src to memory area
 * dest. The memory areas must not overlap. 
 */
void *Memcpy(void *dest, const void *src, size_t n)
{	
	char *dest_runner = NULL;
	char *src_runner = NULL;
	size_t unaligned_head_bytes = 0;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	dest_runner = (char *)dest;
	src_runner = (char *)src;
	
	/* get the number of unaligned bytes to copy the head */
	
	unaligned_head_bytes = GetOffsetToNextAlignedAddress(dest_runner);
			
	n -= unaligned_head_bytes;
	
	CopyByteByByte(&dest_runner, &src_runner, &unaligned_head_bytes);
	
	CopyWordByWord(&dest_runner, &src_runner, &n);
	
	/* copy tail byte-by-bytes */
	
	CopyByteByByte(&dest_runner, &src_runner, &n);
		
	return dest;	
}
/* HELPER FOR TEST */
static void PrintArr(int *arr, size_t n, const char *name)
{
	size_t i = 0;
	printf("%s \t: {", name);
	for (i = 0; i < n; ++i)
	{
		printf("%d , ", arr[i]);
	}
	printf("\b\b\b}\n");
}

/* HELPER FOR TEST */
static void PrintStr(char *arr, size_t n, const char *name)
{
	size_t i = 0;
	printf("%s \t: {", name);
	for (i = 0; i < n; ++i)
	{
		printf("%c , ", arr[i]);
	}
	printf("\b\b\b}\n");
}

int main()
{
	static int int_src[] = {1,2,3,4,5,6,7};
	static int int_dest[] = {0,0,0,0,0,0,0};
	static char str_src[] = {'v','o','v','a','o','k','!'};
	static char str_dest[] = {0,0,0,0,0,0,0};
	
	static int int_src8[] = {1,2,3,4,5,6,7,8};
	static int int_dest8[] = {0,0,0,0,0,0,0,0};
	static char str_src8[] = {'v','o','v','a','o','k','!','\n'};
	static char str_dest8[] = {0,0,0,0,0,0,0,0};
	
	/* test 1 */
	PrintArr(int_src, 7, "int_src");
	
	Memcpy(int_dest, int_src, 7 * sizeof(int));
	
	PrintArr(int_src, 7, "int_src");
	
	/* test 2 */	
	PrintStr(str_src, 7, "str_src");
	
	Memcpy(int_dest, int_src, 7 * sizeof(char));
	
	PrintStr(str_dest, 7, "str_dest");
	
	/* test 3 */
	PrintArr(int_src8, 8, "int_src8");
	
	Memcpy(int_dest8, int_src8, 8 * sizeof(int));
	
	PrintArr(int_dest8, 8, "int_dest8");
	
	/* test 4 */
	PrintStr(str_src8, 8, "str_src8");
	
	Memcpy(str_dest8, str_src8, 8 * sizeof(char));
	
	PrintStr(str_dest8, 8, "str_dest8");
				
	return 0;
}
