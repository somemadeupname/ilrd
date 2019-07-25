#include <stdio.h> /* remove, fopen, fclose, getc, fputs, rename  */
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
int IsDefaultCompare(const char *s1, const char *s2)
{
	UNUSED(s1);
	UNUSED(s2);	
	return 1;
}

/********************* Action functions *********************/

func_exit_status RemoveFile(const char *filename, const char *input)
{
	assert(NULL != filename);
	
	if (0 != remove(filename) )
	{
		perror("remove in RemoveFile failed.\n");
		return fail;
	}

	UNUSED(input);		

	return success;
}

func_exit_status CountLines(const char *filename, const char *input)
{
	FILE* file_p = NULL;
	size_t num_lines = 0;
	char c = '0';

	assert(NULL != filename);	
	
	file_p = fopen(filename, "r");

	if (NULL == file_p)
	{
		perror("fopen failed in CountLines.\n");
		return fail;
	}
	
	while (EOF != c)
	{
		c = getc(file_p);
		if (NEW_LINE == c )
		{
			++num_lines;
		}
	}

	if (0 != fclose(file_p) )
	{
		perror("fclose failed in CountLines.\n");
		return fail;
	}				

	printf("%s has %lu lines.\n", filename, num_lines);
	
	UNUSED(input);	
	
	return success;
}

func_exit_status AppendToFile(const char *filename, const char *text_to_append)
{
	int status = 0;
	FILE* file_p = NULL;
	assert(NULL != filename);	
	assert(NULL != text_to_append);		
	
	file_p = fopen(filename, "a"); /*open in append mode*/
	
	if (NULL == file_p)
	{
		perror("fopen failed in AppendToFile.\n");
		return fail;
	}	
	
	status = fputs (text_to_append, file_p);
	
	if (EOF == status)
	{
		perror("fputs failed in AppendToFile.\n");
		fclose(file_p);
		return fail;
	}	
	status = fputc(NEW_LINE, file_p);
	
	if (EOF == status)
	{
		perror("fputc failed in AppendToFile.\n");
		fclose(file_p);				
		return fail;
	}		
	
	if (0 != fclose(file_p) )
	{
		perror("fclose failed in CountLines.\n");
		return fail;
	}				
	return success;
}

func_exit_status PreAppend (const char *filename, const char *text_to_preappend)
{
	char* temp_filename = "../.temp";
	int status = 0;
	char c = '0';
	char* text_without_char	= NULL;
	FILE* file_p = NULL;
	FILE* temp_file_p = NULL;

	assert(NULL != filename);	
	assert(NULL != text_to_preappend);	
	
	text_without_char = (char *)++text_to_preappend; /*remove the preappend
													command character*/			
	
	file_p = fopen(filename, "r"); 

	if (NULL == file_p)
	{
		perror("fopen failed in PreAppend for existing file.\n");
		return fail;
	}	
	
	temp_file_p = fopen(temp_filename , "a"); /*open in append mode*/
	
	if (NULL == temp_file_p)
	{
		fclose(file_p);			
		perror("fopen failed in PreAppend for new temp file.\n");
		return fail;
	}		

	status = fputs (text_without_char, temp_file_p);
	
	if (EOF == status)
	{
		fclose(file_p);
		fclose(temp_file_p);	
		perror("fputs failed in PreAppend.\n");
		return fail;
	}	
	
	status = fputc(NEW_LINE, temp_file_p); /* add new line at the end */
	
	if (EOF == status)
	{
		perror("fputc failed in PreAppend.\n");
		fclose(file_p);
		fclose(temp_file_p);			
		return fail;
	}			

	c = getc(file_p);
	while (EOF != c)
	{
		fputc (c, temp_file_p);
		c = getc(file_p);
	}
	if (0 != fclose(file_p) )
	{
		perror("fclose failed in PreAppend.\n");
		fclose(temp_file_p);			
		return fail;
	}
	if (0 != fclose(temp_file_p) )
	{
		perror("fclose failed in PreAppend.\n");
		return fail;
	}									
	
	if (0 != remove(filename))
	{
		perror("remove failed in PreAppend.\n");
		return fail;
	}	
		
	if (0 != rename(temp_filename, filename) )
	{
		perror("rename failed in PreAppend.\n");
		return fail;
	}
	
	return success;
}
			

func_exit_status ExitProgram(const char *filename, const char *input)
{
	UNUSED(filename);
	UNUSED(input);	
	return exit;
}

/*************************Print Usage Instructions **************************/

void PrintUserInstructions(const char *filename)
{
	printf("Please enter a string without whitespaces and hit Enter.\n\n\
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
