#include <math.h> /* pow */

typedef enum calculation_status /*TODO should go to h file */
{
	CALCULATION_SUCCESS,
	CALCULATION_FAIL
} calculation_status_t;

/*************************************************************************
								 										 *
				      FORWARD DECLARATIONS								 *
																		 *
*************************************************************************/
calculation_status_t ArithmeticFunctionsAdd(double **left_operand, double right_operand);
calculation_status_t ArithmeticFunctionsSubtract(double **left_operand, double right_operand);
calculation_status_t ArithmeticFunctionsMultiply(double **left_operand, double right_operand);
calculation_status_t ArithmeticFunctionsDivide(double **left_operand, double right_operand);
calculation_status_t ArithmeticFunctionsPower(double **base, double power);
calculation_status_t ArithmeticFunctionsDefault(double **left_operand, double right_operand);

/*************************************************************************
								 										 *
				      IMPLEMENTATION									 *
																		 *
*************************************************************************/

/* default arithmetic function */
calculation_status_t ArithmeticFunctionsDefault(double **left_operand, double right_operand)
{
	UNUSED(left_operand);
	UNUSED(right_operand);
	
	return CALCULATION_FAIL;
}

/* addition */
calculation_status_t ArithmeticFunctionsAdd(double *left_operand, double right_operand)
{
	**left_operand += right_operand;
	
	return CALCULATION_SUCCESS;
}

/* subtraction */
calculation_status_t ArithmeticFunctionsSubtract(double *left_operand, double right_operand)
{
	**left_operand -= right_operand;
	
	return CALCULATION_SUCCESS;	
}

/* multiplication */
calculation_status_t ArithmeticFunctionsMultiply(double *left_operand, double right_operand)
{
	**left_operand *= right_operand;
	
	return CALCULATION_SUCCESS;	
}

/* division */
calculation_status_t ArithmeticFunctionsDivide(double *left_operand, double right_operand)
{
	if (0 == right_operand)
	{
		return CALCULATION_FAIL;
	}
	
	**left_operand /= right_operand;
	
 	return CALCULATION_SUCCESS;
}

/* power */
calculation_status_t ArithmeticFunctionsPower(double *base, double power)
{
	double temp_base = **base;
	
	**base = pow(temp_base, power);
	
	/*TODO check if not extracting root from negative or non-integer root */
	return CALCULATION_SUCCESS;	
}
