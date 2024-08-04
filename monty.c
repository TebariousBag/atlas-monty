#include "monty.h"

/**
 * 
 */

stack_t *stack = NULL;
stack_t *top = NULL;

void push(stack_t **stack, unsigned int line_number, const char *arg)
{
	stack_t *newnode = malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "L%d: malloc failed\n", line_number);
		exit (EXIT_FAILURE);
	}

	newnode->n = atoi(arg);

	if (newnode->n == 0 && strcmp(arg, "0") != 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	newnode->prev = NULL;
	newnode->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = newnode;
	}
	*stack = newnode;
	top = newnode;
}

void pall(stack_t **stack)
{
	stack_t *temp = *stack;

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
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
	unsigned int line_number = 0;
	char *opcode;
	char *arg;


	if (argc != 2) /*make sure there is a file*/
	{
		fprintf(stderr, "Usage: monty file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r"); /*open the file for reading*/

	if (file == NULL) /*errror opening*/
	{
		perror("Error opening file");
		return (EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1) /*read each line of file*/
	{
		line_number++;
		line[strcspn(line, "\n")] = '\0'; /*remove the newline*/

		opcode = strtok(line, " "); /*tokenize line based off spaces*/
		arg = strtok(NULL, " ");

		if (strcmp(opcode, "push") == 0 && arg != NULL)
		{
			push(&stack, atoi(arg), line_number);
		}
		else if (strcmp(opcode, "pall") == 0)
		{
			pall(&stack);
		}
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		}
			
	}

	fclose(file);
	free(line);

	return (EXIT_SUCCESS);
}
