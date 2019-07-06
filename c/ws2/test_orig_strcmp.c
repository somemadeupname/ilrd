#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[])
{
    /*
    char str1[] = {'a','b','c'};
    char str2[] = {'a','\0','b','c','\0','\0'};
    */
    
    printf("%d\n", strcmp(argv[1], argv[2]));
    
    return 0;
}
