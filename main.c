#include "monty.h"

/**
 * 
 */

int main(int argc, char **argv)
{
	if (argc != 2)	/*if there is no arguement*/
	{
		perror("L<line_number>: usage: push integer"); /*print error asked for*/
		exit(EXIT_FAILURE);
	}
	return(0);
}