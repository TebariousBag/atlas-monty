#include "monty.h"

/**
 * 
 * 
 */

void pint(stack_t **stk, unsigned int line_number)
{
	if (*stk == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
		fprintf(stdout, "%d\n", (*stk)->n);
}
