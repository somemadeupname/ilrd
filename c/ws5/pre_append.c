#include <stdio.h>

int main(int argc, char *argv[])
{
	char * filename = "/home/shieber/test/pre_append";
	char * text_to_preappend = "test";
	FILE * file_p = fopen(filename, "w+");
	rewind(file_p);
	fputs("test", file_p);
	fclose(file_p);
	return 0;
}
