#include "monty.h"

/**
 * 
 * 
 */

void pop(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	
	stack_t *temp = *stack;
	*stack = (*stack)->next;

	if (*stack == NULL)
	{
		top = NULL;
	}

	free(temp);
}
