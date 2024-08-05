#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack_t *stack = NULL;
stack_t *top = NULL;

void push(stack_t **stack, unsigned int line_number, const char *arg, int *error)
{
    stack_t *newnode = malloc(sizeof(stack_t));
    if (newnode == NULL)
    {
        fprintf(stderr, "L%d: malloc failed\n", line_number);
        *error = 1;
        return;
    }

    newnode->n = atoi(arg);
    if (newnode->n == 0 && strcmp(arg, "0") != 0)
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        *error = 1;
        return;
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
    if (*stack == NULL)
    {
        printf("0\n");
        return;
    }

    printf("%d\n", (*stack)->n);
}

int main(int argc, char **argv)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int line_number = 0;
    char *opcode;
    char *arg;
    int error = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while ((read = getline(&line, &len, file)) != -1)
    {
        opcode = strtok(line, " ");
        arg = strtok(NULL, " ");

        if (strcmp(opcode, "push") == 0 && arg != NULL)
        {
            int converted_arg = atoi(arg);
            if (converted_arg == 0 && strcmp(arg, "0") != 0)
            {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                error = 1;
                break;
            }
            else
            {
                push(&stack, line_number, arg, &error);
                if (!error)
                {
                    line_number++;
                }
            }
        }
        else if (strcmp(opcode, "pall") == 0)
        {
            pall(&stack);
            line_number++;
        }
        else
        {
            fprintf(stderr, "L%d: usage: push int\n", line_number);
            error = 1;
            break;
        }

        if (error)
        {
            break;
        }   
    }

    fclose(file);
    free(line);

    return EXIT_SUCCESS;
}
