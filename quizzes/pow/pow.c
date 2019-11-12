
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 ****************************/

unsigned long AddOneBitwise(unsigned long num)
{
	unsigned long mask = 1ul;
	unsigned long result = num;
	
	for (mask = 1ul; result <= num; mask <<= 1)
	{
		if ((result & mask) == mask)
		{
			result &= ~mask;
		}
		else
		{
			result |= mask;
		}
	}

	return result;
}

unsigned long SubtractOneBitwise(unsigned long num)
{
	unsigned long mask = 1ul;
	unsigned long result = num;
	
	for (mask = 1ul; result >= num; mask <<= 1)
	{
		if ((result & mask) == mask)
		{
			result &= ~mask;
		}
		else
		{
			result |= mask;
		}
	}

	return result;
}

unsigned long Addition(unsigned long left_operand, unsigned long right_operand)
{
	unsigned long result = left_operand;
	unsigned long i = 0;
	
	for (i = 0; i < right_operand; i = AddOneBitwise(i))
	{
		result = AddOneBitwise(result);
	}
	
	return result;
}

unsigned long Subtraction(unsigned long left_operand, unsigned long right_operand)
{
	unsigned long result = left_operand;
	unsigned long i = 0;
	
	for (i = 0; i < right_operand; i = AddOneBitwise(i))
	{
		result = SubtractOneBitwise(result);
	}
	
	return result;
}

unsigned long Multiply(unsigned long num, unsigned long factor)
{
	unsigned long result = 0ul;
	unsigned long i = 0;
	
	for (i = 0; i < factor; i = AddOneBitwise(i))
	{
		result = Addition(result, num);
	}
	
	return result;
}
/* Pow implementation */
double Pow(unsigned long base, unsigned long exp)
{
	unsigned long i = 0ul;
	unsigned long result = 1ul;
	
	for (i = 0; i < exp; i = AddOneBitwise(i))
	{
		result = Multiply(result, base);
	}
		
	return result;
}
