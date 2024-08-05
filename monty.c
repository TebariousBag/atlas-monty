#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack_t *stack = NULL;

void push(stack_t **stack, unsigned int line_number)
{
    int value;
    char *arg = strtok(NULL, " \t\n");

    if (!arg)
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = atoi(arg);

    stack_t *newnode = malloc(sizeof(stack_t));
    if (!newnode)
    {
        fprintf(stderr, "L%d: malloc failed\n", line_number);
        freestack(stack);
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

void pall(stack_t **stack, unsigned int line_number)
{
    (void)line_number;
    stack_t *current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

char *parse_line(char *line)
{
    char *opcode = strtok(line, " \t\n");
    char *args = strtok(NULL, " \t\n");

    // Concatenate opcode and args into a single string
    char *command = malloc(strlen(opcode) + strlen(args) + 2); // +2 for spaces and null terminator
    strcpy(command, opcode);
    strcat(command, " ");
    strcat(command, args ? args : "");

    return command;
}

int main(int argc, char *argv[])
{
    stack = NULL;
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
    unsigned int i;
    char *command;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    instruction_t instructions[] =
    {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}
    };

    while ((getline(&line, &len, file)) != -1)
    {
        line_number++;
        command = parse_line(line);

        // Manually parse the opcode and arguments
        char *opcode = strtok(command, " ");
        char *args = strchr(command, ' ') ? strdup(strchr(command, ' ') + 1) : NULL;

        if (!opcode || strcmp(opcode, "push") != 0)
        {
            line_number++;
            fprintf(stderr, "L%d: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }

        if (args && strcmp(args, "") == 0)
        {
            fprintf(stderr, "L%d: missing argument for push\n", line_number);
            exit(EXIT_FAILURE);
        }

        // Now you can use opcode and args as needed
        // For example, to push an integer:
        if (strcmp(opcode, "push") == 0)
        {
            int value = atoi(args);
            // Call push function or equivalent logic here
        }

        free(command);
        free(args); // Don't forget to free the dynamically allocated args
        free(line);
    }

    fclose(file);
    freestack(&stack);

    return EXIT_SUCCESS;
}
