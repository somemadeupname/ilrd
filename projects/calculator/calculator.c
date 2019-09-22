
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : Shaddad	    *
 *	 Status   : Sent	    *
 *	 Project  : Calculator  *
 ****************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <stdlib.h> /* strtod */
#include <ctype.h> /* isspace */
#include <assert.h> /* assert */

#include "stack.h"
#include "arithmetic_functions.h"
#include "calculator.h"

#define UNUSED(x) (void)(x)

#define NUM_OF_CHARS 256

enum state{WAIT_FOR_NUM, WAIT_FOR_OP, ERROR, END};

typedef calc_errno_t (*operation_function)(char **input, stack_t *stack[]);

/*************************************************************************
								 										 *
				      Forward Declarations								 *
																		 *
*************************************************************************/
static calc_errno_t CheckIfUnary(char **input, stack_t *stacks[]);
static calc_errno_t PushNumber(char **input, stack_t *stacks[]);
static calc_errno_t PushOperator(char **input, stack_t *stacks[]);
static calc_errno_t Fold(stack_t *stacks[]);
static int IsLowerPrecedence(char **input, stack_t *stacks[]);
static calc_errno_t FoldStack(char **input, stack_t *stacks[]);
static calc_errno_t PushParenthesis(char **input, stack_t *stacks[]);
static calc_errno_t FoldParenthesis(char **input, stack_t *stacks[]);
static calc_errno_t InvalidExpressionError(char **input, stack_t *stacks[]);

static char *ParseSpaces(char *input);
static void AdvanceExpression(char **expression);

/*************************************************************************
								 										 *
				      STATE LUT											 *
																		 *
*************************************************************************/

struct state_and_func
{
	operation_function operation_func;
	enum state next_state;
};

static struct state_and_func StateAndFuncLUT[NUM_OF_CHARS][2];

static void InitStateAndFuncLUT()
{
	size_t c = 0;
	
	for (c = 0; c < NUM_OF_CHARS; ++c)
	{
		StateAndFuncLUT[c][WAIT_FOR_NUM].next_state = ERROR;
		StateAndFuncLUT[c][WAIT_FOR_OP].next_state = ERROR;
		
		StateAndFuncLUT[c][WAIT_FOR_NUM].operation_func = InvalidExpressionError;
		StateAndFuncLUT[c][WAIT_FOR_OP].operation_func = InvalidExpressionError;
	}
	
	StateAndFuncLUT['1'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['1'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['2'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['2'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['3'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['3'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['4'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['4'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['5'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['5'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;	
	
	StateAndFuncLUT['6'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['6'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['7'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['7'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['8'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['8'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['9'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['9'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['0'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['0'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['('][WAIT_FOR_NUM].operation_func = PushParenthesis;
	StateAndFuncLUT['('][WAIT_FOR_NUM].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['.'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['.'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['+'][WAIT_FOR_NUM].operation_func = CheckIfUnary;
	StateAndFuncLUT['+'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;	
	
	StateAndFuncLUT['-'][WAIT_FOR_NUM].operation_func = CheckIfUnary;
	StateAndFuncLUT['-'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;		
	
	StateAndFuncLUT['\0'][WAIT_FOR_OP].operation_func = FoldStack;
	StateAndFuncLUT['\0'][WAIT_FOR_OP].next_state = END;
	
	StateAndFuncLUT[')'][WAIT_FOR_OP].operation_func = FoldParenthesis;
	StateAndFuncLUT[')'][WAIT_FOR_OP].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['+'][WAIT_FOR_OP].operation_func = PushOperator;
	StateAndFuncLUT['+'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['-'][WAIT_FOR_OP].operation_func = PushOperator;
	StateAndFuncLUT['-'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['*'][WAIT_FOR_OP].operation_func = PushOperator;
	StateAndFuncLUT['*'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['/'][WAIT_FOR_OP].operation_func = PushOperator;
	StateAndFuncLUT['/'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['^'][WAIT_FOR_OP].operation_func = PushOperator;
	StateAndFuncLUT['^'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
}

/*************************************************************************
								 										 *
				      ARITHMETIC FUNCTIONS LUT							 *
																		 *
*************************************************************************/
typedef enum precedence
{
	DEFAULT,
	LOWEST,
	LOW,
	MEDIUM,
	HIGH,
	HIGHEST
} precedence_t;

typedef calc_errno_t (*arithmetic_function)(double left_operand,
											double right_num,
											stack_t *stack[]);

typedef struct arithmetic_func_and_precedence
{
	precedence_t precedence;
	arithmetic_function arith_fun;
} arithmetic_func_and_precedence_t;

static arithmetic_func_and_precedence_t ArithmeticLUT[NUM_OF_CHARS];

void InitArithmeticFuncLUT()
{
	size_t c = 0;
	
	for (c = 0; c < NUM_OF_CHARS; ++c)
	{
		ArithmeticLUT[c].precedence = DEFAULT;
		ArithmeticLUT[c].arith_fun = ArithmeticFunctionsDefault;
	}
	
	ArithmeticLUT['+'].precedence = LOW;
	ArithmeticLUT['+'].arith_fun = ArithmeticFunctionsAdd;
	
	ArithmeticLUT['-'].precedence = LOW;
	ArithmeticLUT['-'].arith_fun = ArithmeticFunctionsSubtract;
	
	ArithmeticLUT['*'].precedence = MEDIUM;
	ArithmeticLUT['*'].arith_fun = ArithmeticFunctionsMultiply;

	ArithmeticLUT['/'].precedence = MEDIUM;
	ArithmeticLUT['/'].arith_fun = ArithmeticFunctionsDivide;
	
	ArithmeticLUT['('].precedence = LOWEST;

	ArithmeticLUT[')'].precedence = LOWEST;
	
	ArithmeticLUT['^'].precedence = HIGHEST;
	ArithmeticLUT['^'].arith_fun = ArithmeticFunctionsDefault;	
}

/*************************************************************************
								 										 *
				      STACKS FUNCTIONS									 *
																		 *
*************************************************************************/

enum stack_designation {NUMBERS, OPERATORS};

stack_t *STACKS_LUT[2] = {NULL};

static calc_errno_t InitStacks(size_t max_num_of_elements)
{
	stack_t *num_stack = NULL;
	stack_t *op_stack = NULL;	
	
	/* create numbers stack */	
	num_stack = StackCreate(max_num_of_elements, sizeof(double));
	if (NULL == num_stack)
	{
		return CALC_FAILED_ALOC;
	}

	/* create operators stack */
	op_stack = StackCreate(max_num_of_elements, sizeof(char));
	if (NULL == op_stack)
	{
		StackDestroy(num_stack); num_stack = NULL;
		return CALC_FAILED_ALOC;
	}
	
	STACKS_LUT[NUMBERS] = num_stack;
	STACKS_LUT[OPERATORS] = op_stack;
	
	return CALC_SUCCESS;
}

/* destroy the numbers and operators stacks */
static void DestroyStacks(stack_t *stacks[])
{
	StackDestroy(stacks[OPERATORS]);
	StackDestroy(stacks[NUMBERS]);
	stacks = NULL;
}

/*************************************************************************
								 										 *
				      SHUNTING YARD										 *
																		 *
*************************************************************************/
/* LUT to check if unary expression */
static calc_errno_t (*UNARY_LUT[2])() = {InvalidExpressionError, PushNumber};

/* function checks if expression is unary */
static calc_errno_t CheckIfUnary(char **input, stack_t *stacks[])
{
	calc_errno_t status = CALC_SUCCESS;
	
	assert(NULL != stacks);
	assert(NULL != input);
	
	status = UNARY_LUT[0 != isdigit(*(*input + 1))](input, stacks);
	
	return status;
	
}

/* pushes the number into the stack */
static calc_errno_t PushNumber(char **input, stack_t *stacks[])
{
	double number = 0.0f;
	
	assert(NULL != input);
	assert(NULL != stacks);
	
	number = strtod(*input, input);
	
	StackPush(stacks[NUMBERS], &number);
	
	return CALC_SUCCESS;
}

/* pushes the operator into the stack */
static calc_errno_t PushOperator(char **input, stack_t *stacks[])
{
	calc_errno_t return_status = CALC_SUCCESS;
	char operator = '0';
	
	assert(NULL != input);
	assert(NULL != stacks);
	
	operator = **input;
	while ((!StackIsEmpty(stacks[OPERATORS])) && (CALC_SUCCESS == return_status)
					&& IsLowerPrecedence(input, stacks))
	{
		return_status = Fold(stacks);
	}
	
	StackPush(stacks[OPERATORS], &operator);
	
	AdvanceExpression(input);
	
	return CALC_SUCCESS;	
}

/* folds two operands and an operator in the stacks */
static calc_errno_t Fold(stack_t *stacks[])
{
	char operator = '0';
	double right_operand = 0.0f;
	double left_operand = 0.0f;
	calc_errno_t return_status = CALC_SUCCESS;
	
	assert(NULL != stacks);
	
	right_operand = *(double *)StackPeek(stacks[NUMBERS]);
	StackPop(stacks[NUMBERS]);
	
	left_operand = *(double *)StackPeek(stacks[NUMBERS]);
	StackPop(stacks[NUMBERS]);
	
	operator = *(char *)StackPeek(stacks[OPERATORS]);
	/* if operator is parenthesis */
	if (LOWEST == ArithmeticLUT[(int)operator].precedence)
	{
		StackPop(stacks[OPERATORS]);
		return CALC_ERR_INVALID_EXPRESSION;
	}
	
	return_status = ArithmeticLUT[(int)operator].arith_fun(left_operand,
														 right_operand, stacks);
	StackPop(stacks[OPERATORS]);
	
	return return_status;
}

/* checks if the operator in expression has lower/equal precedence to
*  the operator in the stack 												*/
static int IsLowerPrecedence(char **input, stack_t *stacks[])
{
	char operator = '0';
	int expression_prec = 0;
	int stack_prec = 0;
	
	assert(NULL != stacks);
	assert(NULL != input);
	
	operator = **input;
	
	expression_prec = ArithmeticLUT[(int)operator].precedence;
	if (HIGHEST == expression_prec)
	{
		return 0;
	}
	
	operator = *(char *)StackPeek(stacks[OPERATORS]);
	stack_prec = ArithmeticLUT[(int)operator].precedence;
	
	return expression_prec <= stack_prec;
	
}
/* Fold the stack */
static calc_errno_t FoldStack(char **input, stack_t *stacks[])
{
	calc_errno_t status = CALC_SUCCESS;
	
	assert(NULL != input);
	assert(NULL != stacks);
	
	while ((!StackIsEmpty(stacks[OPERATORS])) && (CALC_SUCCESS == status))
	{
		status = Fold(stacks);
	}
	
	return status;
}

/* pushes parenthesis into stack */
static calc_errno_t PushParenthesis(char **input, stack_t *stacks[])
{
	assert(NULL != input);
	assert(NULL != stacks);
	
	StackPush(stacks[OPERATORS], *input);
	
	AdvanceExpression(input);
	
	return CALC_SUCCESS;
}

/* folds the expression in parenthesis in the stack */
static calc_errno_t FoldParenthesis(char **input, stack_t *stacks[])
{
	calc_errno_t status = CALC_SUCCESS;
	
	assert(NULL != input);
	assert(NULL != stacks);
	
	while ((!StackIsEmpty(stacks[OPERATORS]) && (CALC_SUCCESS == status) &&
							   	('(' != *(char *)StackPeek(stacks[OPERATORS]))))
	{
		status = Fold(stacks);
	}
	
	if (StackIsEmpty(stacks[OPERATORS]))
	{
		return CALC_ERR_INVALID_EXPRESSION;
	}
	
	StackPop(stacks[OPERATORS]);
	AdvanceExpression(input);
	
	return status;
}

/* expression for any invalid expression input */
calc_errno_t InvalidExpressionError(char **input, stack_t *stacks[])
{
	UNUSED(stacks);
	UNUSED(input);	
	
	return CALC_ERR_INVALID_EXPRESSION;
}

/*  Parsing Functions */
static char *ParseSpaces(char *input)
{
	assert(NULL != input);
	
	while (isspace(*input))
	{
		++input;
	}
	
	return input;
}

static void AdvanceExpression(char **expression)
{
	++(*expression);
}

/*************************************************************************
								 										 *
				      CALCULATOR FUNCTION								 *
																		 *
*************************************************************************/
calc_errno_t Calculator(const char *expression, double *result)
{
	char *input = NULL;
	enum state current_state = WAIT_FOR_NUM;
	enum state next_state = WAIT_FOR_NUM;
	calc_errno_t cur_calc_errno = CALC_SUCCESS;
	size_t stack_size = 0;
	
	assert(NULL != expression);
	assert(NULL != result);	
	
	input = (char *)expression;
	stack_size = strlen(expression) + 1;
	
	if (CALC_FAILED_ALOC == InitStacks(stack_size))
	{
		cur_calc_errno = CALC_FAILED_ALOC;
	}
	
	InitStateAndFuncLUT();
	
	InitArithmeticFuncLUT();
	
	while ((CALC_SUCCESS == cur_calc_errno) && (END != current_state) &&
													   (ERROR != current_state))
	{
		input = ParseSpaces(input);	
		
		next_state = StateAndFuncLUT[(int)*input][current_state].next_state;
		
		cur_calc_errno = StateAndFuncLUT[(int)*input][current_state].
									operation_func((char **)&input, STACKS_LUT);
		
		current_state = next_state;
		
	}
	
	if (!StackIsEmpty(STACKS_LUT[NUMBERS]))
	{
		*result = *(double *)StackPeek(STACKS_LUT[NUMBERS]);
	}
	
	DestroyStacks(STACKS_LUT);
	
	return cur_calc_errno;
}
