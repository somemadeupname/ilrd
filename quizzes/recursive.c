#include <stdio.h>
#include <time.h>

long RecursiveFib(long n)
{
	if (0 == n)
	{
		return 0;
	}
	if (1 == n)
	{
		return 1;
	}
	
	return RecursiveFib(n-2) + RecursiveFib(n-1);
}

size_t RecursiveStrlen(const char *str)
{
	if ('\0' == *str)
	{
		return 0;
	}
	
	return 1lu + RecursiveStrlen(str + 1);
}

int RecStrcmp(const char *s1, const char *s2)
{
	if (('\0' == *s1) && (*s1 == *s2))
	{
		return 0;
	}
	if (*s1 != *s2)
	{
		return *s1 - *s2;
	}
	return RecStrcmp(s1 + 1, s2 + 1);
}

char *RecStrcpy(char *dest, const char *src)
{
	*dest = *src;
	
	if ('\0' != *src)
	{
		RecStrcpy(dest + 1, src + 1);
	}
	
	return dest;
}

char *RecStrcat(char *dest, const char *src)
{
	char *end_original_dest = dest + RecursiveStrlen(dest);
	
	if (NULL != src)
	{
		RecStrcpy(end_original_dest, src);
	}
	
	return dest;
}

static int RecStrNcmp(const char *s1, const char *s2, size_t n)
{
	if (0 == n)
	{
		return 0;
	}
	
	if (('\0' == *s1) && (*s1 == *s2))
	{
		return 0;
	}
	if (*s1 != *s2)
	{
		return *s1 - *s2;
	}
	return RecStrNcmp(s1 + 1, s2 + 1, n-1);
}

char *RecStrstr(const char *haystack, const char *needle)
{
	
	if (0 == RecStrNcmp(haystack, needle, RecursiveStrlen(needle)))
	{
		return (char *)haystack;
	}
	
	return RecStrstr(haystack + 1, needle);
}


int main()
{
	clock_t init = clock();
	clock_t end = 0;
	long n = 0;	
	n = 50;
	RecursiveFib(n);
	end = clock();
	
	printf("%f\n", (double) (end-init)/CLOCKS_PER_SEC);
/*	char *str = "hello";*/
/*	char *s1 = "hi";*/
/*	char *s2 = "hi";*/
/*	char *src = "lala";*/
/*	char dest[7];*/
/*	char *src2 = "lala";*/
/*	char dest2[11] = "hello ";*/
/*	char *needle = "la";*/
/*	char *haystack = "shambalamama";*/

/*	*/
/*	printf("RecursiveStrlen(%s) = %lu.\n", str, RecursiveStrlen(str));*/
/*	*/
/*	s1 = "hello";*/
/*	s2 = "iello";	*/
/*	printf("RecStrcmp(%s,%s) = %d.\n", s1, s2, RecStrcmp(s1, s2));*/
/*	*/
/*	*/
/*	src = "lala";*/
/*	printf("RecStrcpy(%s) = %s.\n", src ,RecStrcpy(dest, src));*/
/*	*/
/*	printf("RecStrcat(%s) = %s.\n", src ,RecStrcat(dest2, src2));*/
/*	*/
/*	printf("RecStrstr(%s,%s) = %s.\n", haystack, needle , RecStrstr(haystack, needle));	*/
	
	return 0;
}
