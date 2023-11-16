#include "shell.h"

/**
 * get_builtin - Finds the appropriate built-in function based on command
 * @cmd: Command to be checked against built-ins
 * Return: Pointer to the appropriate built-in function
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },         /* Handles 'env' command */
		{ "exit", exit_shell },  /* Handles 'exit' command */
		{ "setenv", _setenv },   /* Handles 'setenv' command */
		{ "unsetenv", _unsetenv }, /* Handles 'unsetenv' command */
		{ "cd", cd_shell },      /* Handles 'cd' command */
		{ "help", get_help },    /* Handles 'help' command */
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].f);
}

