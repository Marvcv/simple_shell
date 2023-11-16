/**
 * is_cdir - Checks if the character in path at index i is a directory separator.
 * @path: The string representing the path.
 * @i: Pointer to the index in the path string.
 *
 * Return: Returns 1 if the character at index i in path is a directory separator, otherwise 0.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - Locates the command in the system's PATH directories.
 * @cmd: The command to search for.
 * @_environ: The environment variables.
 *
 * Return: Returns the path to the command if found, otherwise NULL.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * is_executable - Checks if the given command is executable.
 * @datash: The data structure containing shell information.
 *
 * Return: Returns the length of the executable part of the command if executable, else -1.
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}

	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - Checks for errors related to the command.
 * @dir: The directory containing the command.
 * @datash: The data structure containing shell information.
 *
 * Return: Returns 1 if there is an error, otherwise 0.
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}
/**
 * cmd_exec - Executes the command provided in the data_shell structure.
 * @datash: Pointer to data_shell structure containing command information.
 *
 * Return: Returns 1 on successful execution, else returns 1 for errors.
 */
int cmd_exec(data_shell *datash) {
    pid_t pd;
    pid_t wpd;
    int state;
    int exec;
    char *dir;
    (void)wpd;

    exec = is_executable(datash);
    if (exec == -1)
        return (1);
    if (exec == 0) {
        dir = _which(datash->args[0], datash->_environ);
        if (check_error_cmd(dir, datash) == 1)
            return (1);
    }

    pd = fork();
    if (pd == 0) {
        if (exec == 0)
            dir = _which(datash->args[0], datash->_environ);
        else
            dir = datash->args[0];
        execve(dir + exec, datash->args, datash->_environ);
    } else if (pd < 0) {
        perror(datash->av[0]);
        return (1);
    } else {
        do {
            wpd = waitpid(pd, &state, WUNTRACED);
        } while (!WIFEXITED(state) && !WIFSIGNALED(state));
    }

    datash->status = state / 256;
    return (1);
}

