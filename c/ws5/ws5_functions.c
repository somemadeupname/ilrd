#include <stdio.h> /* remove, fopen, fclose, getc, fputs,  */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */
#include "ws5.h"

/********************* Compare functions *********************/

int DoStringsMatch(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
		
	/* return 1 if strings match, otherwise return 0 */
	return !strcmp(s1,s2);
}

int DoCharsMatch(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
	
	/* if chars are identical return 1. 0 otherwise. */
	return (*s1 == *s2);
}

/* default behavior will always return true */
int IsDefaultCompare()
{
	return 1;
}

/********************* Action functions *********************/

command RemoveFile(const char *filename)
{
	/* null assert */
	int status = remove(filename);
	return del;
}

command CountLines(const char *filename)
{
	/* null assert */
	size_t num_lines = 0;
	char c = '0';
	FILE* file_p = fopen(filename, "r");
	/*printf("here1");*/
	/* TODO check file exists */
	
	while (EOF != c)
	{
		c = getc(file_p);
		if (NEW_LINE == c )
		{
			++num_lines;
		}
	}

	fclose(file_p);	

	printf("%s has %lu lines.\n", filename, num_lines);
	
	return count;
}

command AppendToFile(const char *filename, const char *text_to_append)
{
	int status = 0;
	
	/* NULL asserts */
	
	FILE* file_p = fopen(filename, "a"); /*open in append mode*/
	status = fputs (text_to_append, file_p); /* writes string without null char. DOES IT MATTER? */
	fputc(NEW_LINE, file_p); /* add new line at the end TODO check if this fails */
	fclose(file_p);
	return append_default;
}

command PreAppend (const char *filename, char *text_to_preappend)
{
	/*gets seg fault when trying to preappend to non existing file TODO*/
	char* temp_filename = "../.temp";
	int status = 0;
	char c = '0';
	char* text_without_char = ++text_to_preappend; /*remove the preappend
													command character*/
	/* NULL asserts*/
	
	FILE* file_p = fopen(filename, "r"); /*TODO decide which open mode is most correct */
	
	FILE* temp_file_p = fopen(temp_filename , "a"); /*open in append mode*/

	status = fputs (text_without_char, temp_file_p); /* writes string without null char. DOES IT MATTER? */
	fputc(NEW_LINE, temp_file_p); /* add new line at the end TODO check if this fails */

	c = getc(file_p);
	while (EOF != c)
	{
		fputc (c, temp_file_p);
		c = getc(file_p);
	}
	fclose(file_p);
	fclose(temp_file_p);
	remove(filename);
	rename(temp_filename, filename);
	
	return pre_append;
}
			

command ExitProgram()
{
	return exit;
}

/*************************Print Usage Instructions **************************/

void PrintUserInstructions(const char *filename)
{
	printf("Please enter a string and hit Enter.\n\n\
	\t1. Enter \"-remove\" to delete the file.\n\
	\t2. Enter \"-count\" to print the number of lines in the file.\n\
	\t3. Enter \"< following by text\" to pre append text to the file.\n\
	\t4. Enter \"-exit\" to exit the program.\n\
	\t5. Any other string will be appended to the end of the file.\n\
	\n\nFile to work on will be: ");
	START_GREEN
	printf("%s\n", filename);
	END_GREEN
}	
