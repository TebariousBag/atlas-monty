#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack_t *stack = NULL;

void push(stack_t **stack, unsigned int line_number)
{
	int value;
    stack_t *newnode = malloc(sizeof(stack_t));
	char *arg = strtok(NULL, " ");

	if (!value)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	value = atoi(arg);

    if (newnode == NULL)
    {
        fprintf(stderr, "L%d: malloc failed\n", line_number);
        exit(EXIT_FAILURE);
    }

    newnode->n = value;
    newnode->next = *stack;
    *stack = newnode;
}

void pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
   stack_t *current = *stack;

   while (current)
   {
	printf("%d\n", current->n);
	current = current->next;
   }
}

int main(int argc, char *argv[])
{
    stack = NULL;
    top = NULL;
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
    char *opcode;
    char *arg;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while ((getline(&line, &len, file)) != -1)
    {
        opcode = strtok(line, " ");
        arg = strtok(NULL, " ");

		line_number++;

        if (strcmp(opcode, "push") == 0 && arg != NULL)
		{
			push(&stack, line_number);
		}
		else if (strcmp(opcode, "pall") == 0)
		{
			pall(&stack, line_number);
		}
	}

    fclose(file);
    free(line);

    return EXIT_SUCCESS;
}
