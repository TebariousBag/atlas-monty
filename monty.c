#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming freestack is defined elsewhere and frees each node properly
void freestack(stack_t **stack);

int main(int argc, char *argv[])
{
    stack = NULL;
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
    unsigned int i;
    char *opcode;
    char *arg = NULL; // Variable to hold the argument

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
        opcode = strtok(line, " \t\n"); // Parse opcode
        arg = strtok(NULL, " \t\n"); // Parse argument

        if (opcode == NULL || (strcmp(opcode, "push") == 0 && arg == NULL))
        {
            fprintf(stderr, "L%d: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }

        for (i = 0; instructions[i].opcode; i++)
        {
            if (strcmp(opcode, instructions[i].opcode) == 0)
            {
                if (strcmp(instructions[i].opcode, "push") == 0 && arg != NULL)
                {
                    instructions[i].f(&stack, atoi(arg)); // Convert argument to int and pass
                }
                else
                {
                    instructions[i].f(&stack, line_number); // Pass line number for other commands
                }
                break;
            }
        }

        free(line);
    }

    fclose(file);
    freestack(&stack);

    return EXIT_SUCCESS;
}
