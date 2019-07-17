#include <stdio.h> /* getchar printf*/
#include <stdlib.h> /* system */

#define ESC 27
#define T_UPPER 116
#define T_LOWER 84
#define A_UPPER 65
#define A_LOWER 97

void IfElse()
{
	char key_down = 0;
	while (ESC != key_down)
	{
		key_down = getchar();
		if (A_UPPER == key_down || A_LOWER == key_down )
		{
			printf("%c pressed.\n", key_down);
		}
		else if (T_UPPER == key_down || T_LOWER == key_down )
		{
			printf("%c pressed.\n", key_down);
		}
	}
}

void SwitchCase()
{
	char key_down = 0;
	while (ESC != key_down)
	{
		key_down = getchar();
		switch (key_down)
		{
			case (A_UPPER):
				printf("%c pressed.\n", key_down);
				break;
			case (A_LOWER):
				printf("%c pressed.\n", key_down);
				break;
			case (T_UPPER):
				printf("%c pressed.\n", key_down);
				break;
			case (T_LOWER):
				printf("%c pressed.\n", key_down);
				break;	
		}
	}
}

int main()
{
	system("stty -icanon -echo");
	IfElse();	
	SwitchCase();
	system("stty icanon echo");
	return 0;
}
