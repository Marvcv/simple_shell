#include "shell.h"

/**
 * main - Entry point for the shell.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	/* Initialize info structure with INFO_INIT */
	info_t info[] = {INFO_INIT};
	int fd = 2;

	/* Inline assembly to modify fd */
	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	/* Check if an argument is provided */
	if (ac == 2)
	{
		/* Open file and handle errors */
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				/* Print error message and exit */
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

	/* Populate environment list */
	populate_env_list(info);
	/* Read history from file */
	read_history(info);
	/* Execute shell */
	hsh(info, av);
	return (EXIT_SUCCESS);
}


