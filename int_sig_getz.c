#include "shell.h"

/**
 * get_sigint - Handles the signal for SIGINT.
 * @sig: Signal number.
 */
void get_sigint(int sig)
{
	(void)sig; /*Suppresses unused parameter warning*/
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

