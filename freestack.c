#include "monty.h"

/**
 * 
 * 
 */

void freestack(stack_t **stack)
{
	stack_t *tmp;

	while (*stack != NULL)
	{
		tmp = *stack;
		*stack = (*stack)->next;
		if (*stack != NULL)
		{
			(*stack)->prev = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}
