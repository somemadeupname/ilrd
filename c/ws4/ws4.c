#include <stdio.h> /* getchar printf*/
#include <stdlib.h> /* system */

#define ESC 27
#define T_UPPER_ASCII 116
#define T_LOWER_ASCII 84
#define A_UPPER_ASCII 65
#define A_LOWER_ASCII 97
#define DISABLE_ECHO "stty -icanon -echo"
#define ENABLE_ECHO "stty icanon echo"

/* forward declarations */
void Foo();
void PrintA();
void PrintT();
void IfElse();
void SwitchCase();
void LUT();

static void (*lut_function[256])() = 
{ Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, PrintA, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, PrintT, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, PrintA, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, PrintT, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo, Foo,
  Foo, Foo, Foo, Foo, Foo, Foo };
  
  
int main()
{
	system(DISABLE_ECHO);
	IfElse();
	SwitchCase();
	LUT();
	system(ENABLE_ECHO);
	return 0;
}

void IfElse()
{
	char key_down = 0;
	printf("If/Else:\n");	
	while (ESC != key_down)
	{
		key_down = getchar();
		if (A_UPPER_ASCII == key_down || A_LOWER_ASCII == key_down )
		{
			PrintA();
		}
		else if (T_UPPER_ASCII == key_down || T_LOWER_ASCII == key_down )
		{
			PrintT();
		}
	}
}

void SwitchCase()
{
	char key_down = 0;
	printf("Switch/Case:\n");	
	while (ESC != key_down)
	{
		key_down = getchar();
		switch (key_down)
		{
			case (A_UPPER_ASCII):
				PrintA();
				break;
			case (A_LOWER_ASCII):
				PrintA();
				break;
			case (T_UPPER_ASCII):
				PrintT();
				break;
			case (T_LOWER_ASCII):
				PrintT();
				break;	
		}
	}
}

void LUT()
{
	int key_down = 0;
	printf("LUT:\n");	
	while (ESC != key_down)
	{
		key_down = getchar();
		(*lut_function[key_down])();
	}
}		

void Foo()
{
	/* function that does nothing */
}

void PrintA()
{
	printf("A pressed\n");
}

void PrintT()
{
	printf("T pressed\n");
}
