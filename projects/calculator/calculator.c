
/****************************
 *   Author   : Ran Shieber *
 *   Reviewer : 		    *
 *	 Status   : Sent	    *
 *	 Project  : Calculator
 *			  State Machine *
 ****************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <stdlib.h> /* strtod */
#include <ctype.h> /* isspace */

#include "stack.h"
#include "stack.c"
#include "arithmetic_functions.h"
#include "calculator.h"

#define UNUSED(x) (void)(x)

#define NUM_OF_CHARS 256

enum state{WAIT_FOR_NUM, WAIT_FOR_OP, ERROR, END};

typedef stack_t *calc_stack_t;

typedef calc_errno_t (*operation_function)(char **input, calc_stack_t calc_stack);

/*************************************************************************
								 										 *
				      Forward Declarations								 *
																		 *
*************************************************************************/
calc_errno_t DefaultAction(char **input, calc_stack_t calc_stack);
calc_errno_t PushNumber(char **input, calc_stack_t calc_stack);
calc_errno_t PushOperator(char **input, calc_stack_t calc_stack);
calc_errno_t PushUnary(char **input, calc_stack_t calc_stack);
calc_errno_t Fold(char **input, calc_stack_t calc_stack);
calc_errno_t ClosedParenFold(char **input, calc_stack_t calc_stack);
calc_errno_t PushOperatorAndFold(char **input, calc_stack_t calc_stack);

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
		
		StateAndFuncLUT[c][WAIT_FOR_NUM].operation_func = DefaultAction;
		StateAndFuncLUT[c][WAIT_FOR_OP].operation_func = DefaultAction;
	}
	
	StateAndFuncLUT['1'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['1'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['2'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['2'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['3'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['3'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['4'][WAIT_FOR_NUM].operation_func = PushNumber;
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
	
	StateAndFuncLUT['('][WAIT_FOR_NUM].operation_func = PushOperator;
	StateAndFuncLUT['('][WAIT_FOR_NUM].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['.'][WAIT_FOR_NUM].operation_func = PushNumber;
	StateAndFuncLUT['.'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['+'][WAIT_FOR_NUM].operation_func = PushUnary;
	StateAndFuncLUT['+'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;	
	
	StateAndFuncLUT['-'][WAIT_FOR_NUM].operation_func = PushUnary;
	StateAndFuncLUT['-'][WAIT_FOR_NUM].next_state = WAIT_FOR_OP;		
	
	StateAndFuncLUT['\0'][WAIT_FOR_OP].operation_func = Fold;
	StateAndFuncLUT['\0'][WAIT_FOR_OP].next_state = END;
	
	StateAndFuncLUT[')'][WAIT_FOR_OP].operation_func = ClosedParenFold;
	StateAndFuncLUT[')'][WAIT_FOR_OP].next_state = WAIT_FOR_OP;
	
	StateAndFuncLUT['+'][WAIT_FOR_OP].operation_func = PushOperatorAndFold;
	StateAndFuncLUT['+'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['-'][WAIT_FOR_OP].operation_func = PushOperatorAndFold;
	StateAndFuncLUT['-'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['*'][WAIT_FOR_OP].operation_func = PushOperatorAndFold;
	StateAndFuncLUT['*'][WAIT_FOR_OP].next_state = WAIT_FOR_NUM;
	
	StateAndFuncLUT['/'][WAIT_FOR_OP].operation_func = PushOperatorAndFold;
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
	HIGHEST/*RELEVANT? FIXME*/
} precedence_t;

typedef calculation_status_t (*arithmetic_function)(double **left_operand, double right_num);

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
	
	ArithmeticLUT['-'].precedence = DEFAULT;
	ArithmeticLUT['-'].arith_fun = ArithmeticFunctionsSubtract;
	
	ArithmeticLUT['*'].precedence = DEFAULT;
	ArithmeticLUT['*'].arith_fun = ArithmeticFunctionsMultiply;

	ArithmeticLUT['/'].precedence = MEDIUM;
	ArithmeticLUT['/'].arith_fun = ArithmeticFunctionsDivide;
	
/*	ArithmeticLUT['('].precedence = DEFAULT;*/
/*	ArithmeticLUT['('].arith_fun = ArithmeticFunctionsDefault;*/

	ArithmeticLUT[')'].precedence = LOWEST;
	ArithmeticLUT[')'].arith_fun = ArithmeticFunctionsDefault;
}

/*************************************************************************
								 										 *
				      STACKS FUNCTIONS									 *
																		 *
*************************************************************************/

enum stack_designation {NUMBERS, OPERATORS};

static calc_errno_t InitStacks(calc_stack_t *stacks, size_t max_num_of_elements)
{
	/* create numbers stack */	
	stacks[NUMBERS] = (calc_stack_t) StackCreate(max_num_of_elements, sizeof(double));
	if (NULL == stacks)
	{
		return CALC_FAILED_ALOC;
	}

	/* create operators stack */
	stacks[OPERATORS] = (calc_stack_t) StackCreate(max_num_of_elements, sizeof(char));
	if (NULL == stacks)
	{
		StackDestroy((stack_t *)stacks[NUMBERS]); stacks[NUMBERS] = NULL;
		return CALC_FAILED_ALOC;
	}
	
	return CALC_SUCCESS;
}

/* destroy the numbers and operators stacks */
static void DestroyStacks(calc_stack_t *stacks)
{
	StackDestroy((stack_t *)stacks[OPERATORS]);
	StackDestroy((stack_t *)stacks[NUMBERS]);
	stacks = NULL;
}

/*************************************************************************
								 										 *
				      SHUNTING YARD										 *
																		 *
*************************************************************************/

static void AdvanceExpression(char **expression)
{
	++(*expression);
}

calc_errno_t Fold(char **input, calc_stack_t calc_stack)
{
	double right_operand = *(double *)StackPeek(calc_stack[NUMBERS]);
	double *left_operand = NULL;
	char operator = *(char *)StackPeek(calc_stack[OPERATORS]);
	calculation_status_t calc_result = CALCULATION_SUCCESS;
	
	assert(NULL != calc_stack);
	
	StackPop(calc_stack[OPERATORS]);
	StackPop(calc_stack[NUMBERS]);
	
	/* left operand remains on the stack since we insert new value in its place */
	left_operand = StackPeek(calc_stack[NUMBERS]);
	
	calc_result = ArithmeticLUT[operator].arith_fun(&left_operand, right_operand);
	
	return calc_result;
}

calc_errno_t PushNumber(char **input, calc_stack_t calc_stack)
{
	double number = 0;
	
	assert(NULL != input);
	assert(NULL != calc_stack);
	
	number = strtod(*input, input);
	
	StackPush(calc_stack[NUMBERS], &number);
	
	return CALC_SUCCESS;
}

calc_errno_t PushOperator(char **input, calc_stack_t calc_stack)
{
	char operator = '0';
	
	assert(NULL != input);
	assert(NULL != calc_stack);
	
	operator = **input;
	StackPush(calc_stack[OPERATORS], &operator); 
	
	AdvanceExpression(input);
	
	return CALC_SUCCESS;	
}

calc_errno_t PushUnary(char **input, calc_stack_t calc_stack)
{
	char **endptr = NULL;
	double number = 0;
	
	assert(NULL != input);
	assert(NULL != calc_stack);
	
	number = strtod(*input, endptr);/* if +/- without number after it */
	if (input == endptr)
	{
		return CALC_ERR_INVALID_EXPRESSION;
	}
	
	input = endptr;
	StackPush(calc_stack[NUMBERS], &number);
	
	return CALC_SUCCESS;
}

calc_errno_t DefaultAction(char **input, calc_stack_t calc_stack)
{
	return CALC_SUCCESS;
}

/*  PARSER */
static char *ParseSpaces(char *input)
{
	assert(NULL != input);
	
	while (isspace(*input))
	{
		++input;
	}
	
	return input;
}

/*************************************************************************
								 										 *
				      CALCULATOR FUNCTION								 *
																		 *
*************************************************************************/
calc_errno_t Calculator(const char *expression, double *result)
{
	char *input = (char *)expression;
	enum state current_state = WAIT_FOR_NUM;
	calc_errno_t cur_calc_errno = CALC_SUCCESS;
	size_t stack_size = strlen(expression);

	calc_stack_t stacks[2] = {NULL};
	
	assert(NULL != expression);
	assert(NULL != result);	
	
	if (CALC_FAILED_ALOC == InitStacks(stacks, stack_size))
	{
		cur_calc_errno = CALC_FAILED_ALOC;
	}
	
	while ((CALC_SUCCESS == cur_calc_errno) && (END != current_state) && (ERROR != current_state))
	{
		char cur_char = '0'; 
		input = ParseSpaces(input);
		cur_char = *input;
		cur_calc_errno = StateAndFuncLUT[cur_char][current_state].operation_func(&input, stacks);

		current_state = StateAndFuncLUT[cur_char][current_state].next_state;
	}
	
	return cur_calc_errno;
}
