#include <math.h> /* pow floor */
#include <assert.h> /* assert */

#include "arithmetic_functions.h"

enum stack_designation {NUMBERS, OPERATORS};

#define UNUSED(x) (void)(x)

/*************************************************************************
								 										 *
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/
calc_errno_t ArithmeticFunctionsAdd(double left_operand, double right_operand, stack_t *stacks[]);
calc_errno_t ArithmeticFunctionsSubtract(double left_operand, double right_operand, stack_t *stacks[]);
calc_errno_t ArithmeticFunctionsMultiply(double left_operand, double right_operand, stack_t *stacks[]);
calc_errno_t ArithmeticFunctionsDivide(double left_operand, double right_operand, stack_t *stacks[]);
calc_errno_t ArithmeticFunctionsPower(double base, double power, stack_t *stack[]);
calc_errno_t ArithmeticFunctionsDefault(double left_operand, double right_operand, stack_t *stacks[]);

/*************************************************************************
								 										 *
				      IMPLEMENTATION									 *
																		 *
*************************************************************************/

/* default arithmetic function */
calc_errno_t ArithmeticFunctionsDefault(double left_operand, double right_operand, stack_t *stacks[])
{
	UNUSED(left_operand);
	UNUSED(right_operand);
	UNUSED(stacks);
	
	return CALC_ERR_INVALID_CALCULATION;
}

/* addition */
calc_errno_t ArithmeticFunctionsAdd(double left_operand, double right_operand, stack_t *stacks[])
{
	double result = 0.0f;
	
    assert(NULL != stacks);	
	
	result = left_operand + right_operand;
	
	StackPush(stacks[NUMBERS], &result);
	
	return CALC_SUCCESS;
}

/* subtraction */
calc_errno_t ArithmeticFunctionsSubtract(double left_operand, double right_operand, stack_t *stacks[])
{
	double result = 0.0f;
	
    assert(NULL != stacks);	
	
	result = left_operand - right_operand;
	
	StackPush(stacks[NUMBERS], &result);	
	
	return CALC_SUCCESS;	
}

/* multiplication */
calc_errno_t ArithmeticFunctionsMultiply(double left_operand, double right_operand, stack_t *stacks[])
{
	double result = 0.0f;
	
    assert(NULL != stacks);	
	
	result = left_operand * right_operand;
	
	StackPush(stacks[NUMBERS], &result);	
	
	return CALC_SUCCESS;	
}

/* division */
calc_errno_t ArithmeticFunctionsDivide(double left_operand, double right_operand, stack_t *stacks[])
{
	double result = 0.0f;
	
    assert(NULL != stacks);	
	
	if (0 == right_operand)
	{
		return CALC_ERR_INVALID_CALCULATION;
	}
	
	result = left_operand / right_operand;
	
	StackPush(stacks[NUMBERS], &result);		
	
 	return CALC_SUCCESS;
}

/* power */
calc_errno_t ArithmeticFunctionsPower(double base, double power, stack_t *stacks[])
{
	double result = 0.0f;
	
    assert(NULL != stacks);
    
    if (((0 == base) && (power <= 0)) ||((base < 0) && (floor(power) != power)))
    {
    	return CALC_ERR_INVALID_CALCULATION;
    }
	
	result = pow(base, power);
	
	StackPush(stacks[NUMBERS], &result);			
	
	return CALC_SUCCESS;	
}
