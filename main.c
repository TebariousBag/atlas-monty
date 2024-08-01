#include "monty.h"


/**
 * 
 */

void push(stack_t **stack, int value)
{
	stack_t *newnode = malloc(sizeof(stack_t));
	if (!newnode)
	{
		perror("malloc failure");
		exit (EXIT_FAILURE);
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
	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++; /*increment the line*/

		char *opcode = strtok(line, " \t\n\r\f\v"); /*tokenize with delimeters*/

		if (strcmp(opcode, "push") == 0) /*if it finds push, then we will call push and the line number*/
		{
			char *endptr;
			long int value;

			char *token = strtok(NULL, " \t\n\r\f\v");
			value = strtol(token, &endptr, 10);
			if (*endptr != '\0')
			{
				fprintf(stderr, "L<%d>: invalid number format\n", line_number);
				continue;
			}

			push(&stack, value);

		}
		else
		{
			fprintf(stderr, "%d %s\n", line_number, opcode);
		}
	}

	fclose(file);
	free(line);

	return (EXIT_SUCCESS);
}