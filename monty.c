#include "monty.h"

/**
 * 
 */

stack_t *head = NULL;

void push(stack_t **stack, int value)
{
	stack_t *newnode = malloc(sizeof(stack_t));
	if (!newnode)
	{
		fprintf(stderr, "malloc failure\n");
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

	initstack(); /*initialize stack*/

	
	while ((read = getline(&line, &len, file)) != -1)
	{
		line[strcspn(line, "\n")] = '\0'; /*removing newline*/

		char *opcode = strtok(line, " \t\n"); /*tokenize line with delimeters*/

		if (strcmp(opcode, "push") == 0)
		{
			int value = atoi(strtok(NULL, " \t\n"));

			if (value == 0 || strcmp(opcode, "push") != 0)
			{
				fprintf(stderr, "L%d: usage: push integer\n", __LINE__);
				exit(EXIT_FAILURE);
			}
			push(&head, value);
		}
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", __LINE__, opcode);
			exit(EXIT_FAILURE);
		}

	}

	free(line);
	fclose(file);
	freestack(head);

	return (EXIT_SUCCESS);
}
