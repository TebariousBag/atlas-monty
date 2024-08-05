#include "monty.h"

/**
 * 
 * 
 */

void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (stack == NULL || *stack == NULL || (*stk)->next == NULL)
	{
		line_number++;
		fprintf(stderr, "L%d: can't swap, stack too short\n",
			line_number);
		freestack(stack);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
