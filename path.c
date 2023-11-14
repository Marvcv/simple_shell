#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command
 * @info: The info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters
 * @pathstr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds this cmd in the PATH string
 * @info: The info struct
 * @pathstr: The PATH string
 * @cmd: The cmd to find
 *
 * Return: Full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	/* Check if cmd starts with "./" and is an executable */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		/* Iterate through the PATH string */
		if (!pathstr[i] || pathstr[i] == ':')
		{
			/* Duplicate characters from curr_pos to i */
			path = dup_chars(pathstr, curr_pos, i);

			/* If path is empty, concatenate cmd to it */
			if (!*path)
				_strcat(path, cmd);
			else
			{
				/* Concatenate "/" and cmd to the path */
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			/* Check if the constructed path is an executable */
			if (is_cmd(info, path))
				return (path);

			/* Break if the end of the PATH string is reached */
			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

