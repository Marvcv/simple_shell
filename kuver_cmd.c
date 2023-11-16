#include "shell.h"

/**
 * read_line - Reads input from stdin.
 *
 * @i_eof: Pointer to the end of file indicator.
 * Return: Pointer to the input string.
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}

