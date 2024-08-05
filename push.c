
#include "monty.h"

/**
 * 
 * 
 */
void push(stack_t **stack, unsigned int line_number)
{
	int value;
	char *arg = strtok(NULL, " \t\n");

	if (arg == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	value = atoi(arg);

    stack_t *newnode = malloc(sizeof(stack_t));

    if (newnode == NULL)
    {
        fprintf(stderr, "L%d: malloc failed\n", line_number);
        exit(EXIT_FAILURE);
    }

    newnode->n = value;
    newnode->prev = NULL;
    newnode->next = *stack;
    if (*stack)
    {
        (*stack)->prev = newnode;
    }
    *stack = newnode;
}
