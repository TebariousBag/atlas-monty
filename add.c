#include "monty.h"

/**
 * 
 * 
 */

void add(stack_t **stack, unsigned int line_number)
{
	int sum;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n",
			line_number);
		freestack(stack);
		exit(EXIT_FAILURE);
	}

	sum = (*stack)->n + ((*stack)->next)->n;
	pop(stack, line_number);
	pop(stack, line_number);
	push(stack, line_number);
}
