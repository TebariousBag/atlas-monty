#include "monty.h"

/**
 * 
 * 
 */

void add(stack_t **stack, unsigned int line_number)
{
	int sum;
	stack_t *temp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n",
			line_number);
		freestack(stack);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	(*stack)->next = temp->next;
	temp->next = NULL;
	*stack = temp;

	sum = temp->n + (*stack)->n;

	temp->n = sum;
	temp->next = NULL;
	*stack = temp;
}
