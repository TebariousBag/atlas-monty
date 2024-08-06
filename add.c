#include "monty.h"

/**
 * 
 * 
 */

void add(stack_t **stack, unsigned int line_number)
{
	int sum;
	int val1;
	int val2;

	stack_t *temp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n",
			line_number);
		freestack(stack);
		exit(EXIT_FAILURE);
	}

	val1 = (*stack)->n;
	val2 = (*stack)->next->n;

	temp = (*stack)->next;
	(*stack)->next = temp->next;
	temp->next = NULL;

	sum = val1 + val2;

	push(sum, stack, line_number);
}
