#include "shell.h"

/**
 * cmp_env_name - Compares environment variable name with given name.
 * @nenv: Environment variable name.
 * @name: Given name to compare.
 *
 * Return: Number of characters if match found, otherwise 0.
 */
int cmp_env_name(const char *nenv, const char *name)
{
		int i;

		for (i = 0; nenv[i] != '='; i++)
		{
				if (nenv[i] != name[i])
				{
						return (0);
				}
		}

		return (i + 1);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @name: Name of the environment variable.
 * @_environ: Pointer to the environment variables array.
 *
 * Return: Value of the environment variable, NULL if not found.
 */
char *_getenv(const char *name, char **_environ)
{
		char *ptr_env;
		int i, mov;

		/* Initialize ptr_env and mov */
		ptr_env = NULL;
		mov = 0;

		/* Loop through the environment variables */
		for (i = 0; _environ[i]; i++)
		{
				mov = cmp_env_name(_environ[i], name);
				if (mov)
				{
						ptr_env = _environ[i];
						break;
				}
		}

		return (ptr_env + mov);
}

/**
 * _env - Prints all environment variables.
 * @datash: Pointer to the data_shell structure.
 *
 * Return: Always returns 1.
 */
int _env(data_shell *datash)
{
		int i, j;

		/* Loop through the environment variables */
		for (i = 0; datash->_environ[i]; i++)
		{
				/* Find the length of the current environment variable */
				for (j = 0; datash->_environ[i][j]; j++)
						;

				/* Write the environment variable to STDOUT */
				write(STDOUT_FILENO, datash->_environ[i], j);
				write(STDOUT_FILENO, "\n", 1);
		}

		datash->status = 0;
		return (1);
}

