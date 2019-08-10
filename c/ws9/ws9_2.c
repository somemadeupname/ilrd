#include <stdio.h>
#include <stdlib.h> /* */
#include <string.h> /* strlen */
#include <assert.h>
#include <ctype.h> /* isdigit isalpha isspace */

#define UNUSED(x) (void)(x)
#define PLUS 43
#define MINUS 45
#define BASE 10

static int IsSign(char c)
{
	int sign = 0;
	if (PLUS == c)
	{
		sign = 1;
	}	
	else if (MINUS == c)
	{
		sign = -1;
	}
	return sign;
}

int AtoIDecimal(const char *nptr)
{
	char *cur = (char *) nptr;
	int res = 0;
	int sign = 1;
	int found_first_digit = 0;
	int is_still_number = 1;
	int found_first_sign = 0;
	assert(NULL != nptr);
	
	while (cur && is_still_number)
	{
		if (isspace(*cur) && !found_first_digit && !found_first_sign)
		{
			++cur;
		}
		else if (IsSign(*cur) && !found_first_digit)
		{
			if (1 != sign)
			{
				is_still_number = 0;
			}
			found_first_sign = 1;
			sign = IsSign(*cur);
			++cur;
		}
		else if (isdigit(*cur))
		{
			found_first_digit = 1;
			res = BASE * res + (int) (*cur - '0');
			++cur;
		}
		else
		{
			is_still_number = 0;
		}
	}
	return res*sign;
}

static void ReverseString(char *str)
{
	char *reverse = str;
	int temp = 0;
	
	assert (NULL != str);
	str += (strlen(str) - 1);

	while (reverse < str)
	{
		temp = *str;
		*str = *reverse;
		*reverse = temp;
		--str;
		++reverse;
	}
}


char *ItoADecimal(int value, char *str)
{
	/* init values */
	int sign = 0;
	char *str_start = str;
	long long_value = value;
	assert(NULL != str);
	
	sign = (long_value >= 0 ? 1 : (-1));
	long_value *= sign; /* make value positive if negative. no change otherwise */

	/* in case value is 0 */
	if (0 == long_value)
	{
		*str = '0';
		++str;
	}
	
	/* parse over value and extract each digit separately into the str */
	while (long_value > 0)
	{
		*str = (char)(long_value%BASE + '0');
		long_value /= BASE;	
		++str;
	}

	/* if value is negative - add the minus char */
	if (sign < 0)
	{
		*str = '-';
		++str;
	}	
	*str = '\0'; /* append terminating null char */
	
	ReverseString(str_start);
	
	return str_start;
}
/*
int main(int argc, char *argv[])
{
	char str[30];

	
	size_t index = 0;
	
	for (index = 0; index < strlen(argv[1]); ++index)
	{
		printf("IsSign(%c) = %d.\n", (*argv[1] + index), IsSign((*argv[1] + index)));
	}
	printf("atoi() = %d\n", atoi(argv[1]));
	
	UNUSED(argc);
	
	printf("AtoIDecimal(\t%s) = \t%d\n", argv[1], AtoIDecimal(argv[1]));
	printf("atoi \t   (\t%s) = \t%d\n", argv[1], atoi(argv[1]));		
	
	printf("ItoADecimal(%ld) = %s\n", -1234567891L, ItoADecimal(-1234567891L ,str));

	return 0;
}
*/

