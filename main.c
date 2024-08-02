#include "monty.h"

/**
 * 
 */

stack_t *stack = NULL;

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newnode = malloc(sizeof(stack_t));
	if (!newnode)
	{
		fprintf(stderr, "malloc failure\n");
		exit (EXIT_FAILURE);
	}

	newnode->n = line_number;
	newnode->prev = NULL;
	newnode->next = *stack;
	if (*stack)
	{
		(*stack)->prev = newnode;
	}
	*stack = newnode;
}

/**
 * main - start of program
 * argc: arg count
 * argv: arg vector
 * Return: success or failure
 */

int main(int argc, char **argv)
{
	FILE *file; /*file stream*/
	char *line = NULL; /*buffer to hold the lines*/
	size_t len = 0; /*size of buffer*/
	ssize_t read; /*what getline sees*/
	unsigned int line_number = 0; /*counting lines*/
	if (argc != 2)	/*if there is no arguement*/

	{
		fprintf(stderr, "L<%d>: usage: push integer\n", line_number); /*print error asked for*/
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r"); /*open file for reading*/
	if (!file)
	{
		perror("Error opening the file");
		return (EXIT_FAILURE);
	}

	instruction_t instructions[] =
	{
		{"push", push},
	};

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++; /*increment the line*/
		char *opcode = strtok(line, " \t\n\r\f\v"); /*tokenize with delimeters*/
		
		if (!opcode)
		{
			fprintf(stderr, "line %u: no opcode", line_number);
		}

		for (unsigned int i = 0; i < sizeof(instructions) / sizeof(instruction_t); i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				instructions[i].f(&stack, line_number);
				break;
			}
		}

	fclose(file);
	free(line);
	freestack(stack);

	return (EXIT_SUCCESS);
}
