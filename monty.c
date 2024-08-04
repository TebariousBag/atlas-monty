#include "monty.h"

/**
 * 
 */

stack_t *stack = NULL;
stack_t *top = NULL;

void push(stack_t **stack, int line_number)
{
	stack_t *newnode = malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "malloc failure\n");
		exit (EXIT_FAILURE);
	}

	newnode->n = line_number;
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
		line[strcspn(line, "\n")] = '\0'; /*remove the newline*/

		char *command = strtok(line, " "); /*tokenize line based off spaces*/
		char *number = strtok(NULL, " ");

		if (!command || !number) /*if NULL*/
		{
			fprintf(stderr, "Syntax error\n");
			continue;
		}

		if (strcmp(command, "push") == 0 && number != NULL)
		{
			long num = atol(number);
			if (num <= 0)
			{
				fprintf(stderr, "invalid number");
			}
			push(&stack, num);
		}
		else if (strcmp(command, "pall") == 0)
		{
			pall(&stack);
		}
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", __LINE__, command);
		}
			
	}

	fclose(file);
	free(line);

	return (EXIT_SUCCESS);
}
