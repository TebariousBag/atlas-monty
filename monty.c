#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack_t *stack = NULL;

int main(int argc, char *argv[])
{
    stack = NULL;
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
    unsigned int i;
    char *opcode;

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
        {"pint", pint},
        {NULL, NULL}
    };

    while ((getline(&line, &len, file)) != -1)
    {
        line_number++;
        opcode = strtok(line, " \t\n");

        if (opcode == NULL)
        {
            line_number++;
            fprintf(stderr, "L%d: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }
       for (i = 0; instructions[i].opcode; i++)
       {
        if (strcmp(opcode, instructions[i].opcode) == 0)
        {
            instructions[i].f(&stack, line_number);
            break;
        }
       }
	}

    fclose(file);
    free(line);

    if (stack != NULL)
    {
        freestack(&stack);
    }

    return EXIT_SUCCESS;
}
