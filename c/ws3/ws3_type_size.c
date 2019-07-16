#include <stdio.h>

#define PRINT(type,name) printf("%s is sized %lu.\n", name, sizeof(type));

int main()
{
	PRINT(int,"int")
	PRINT(unsigned int,"unsigned int")
	PRINT(char,"char")
	PRINT(signed char,"signed char")		
	PRINT(unsigned char,"unsigned char")		
	PRINT(long,"long")		
	PRINT(signed long,"signed long")	
	PRINT(unsigned long,"unsigned long")			
	PRINT(float,"float")		
	PRINT(double,"double")	
	PRINT(long double,"long double")	
	PRINT(short,"short")	
	PRINT(unsigned short,"unsigned short")
	PRINT(void *,"void *")	
			
	return 0;
}
