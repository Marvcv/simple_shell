#include "shell.h"

/**
 * exec_line - Executes the provided command line.
 *
 * @datash: Pointer to the data_shell structure containing command details.
 * Return: 1 on success, 0 on failure.
 */
int exec_line(data_shell *datash)
{
    int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}

