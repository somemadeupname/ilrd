#include <stddef.h> 	/* for size_t definition */

/* Function declarations */

size_t Strlen (const char* str);
int Strcmp (const char* str1, const char* str2);
char* Strcpy(char *dest, const char *src);
char* Strncpy(char *dest, const char *src, size_t n);
int Strcasecmp(const char *s1, const char *s2);
char *Strchr(const char *s, int c);
char *Strdup(const char *s);
char *Strcat(char *dest, const char *src);
char *Strncat(char *dest, const char *src, size_t n);
char *Strstr(const char *haystack, const char *needle);
int Strncmp(const char *s1, const char *s2, size_t n);
void SevenBoom(int from, int to);
