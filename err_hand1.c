/**
 * strcat_cd - Concatenates error message components related to 'cd' errors.
 * @datash: Data structure containing shell information.
 * @msg: Message component to be added to the error.
 * @error: Error buffer to store the final error message.
 * @ver_str: String representation of the version.
 *
 * Return: Pointer to the error message.
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	/* Initialize the error message with specific components */
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);

	/* Check if an illegal flag needs to be added */
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	/* Finalize the error message with newline and null terminator */
	_strcat(error, "\n");
	_strcat(error, "\0");

	return (error);
}
/**
 * error_get_cd - Generates error message for 'cd' command errors.
 * @datash: Pointer to data structure containing shell information.
 *
 * Return: Pointer to the generated error message.
 */
char *error_get_cd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(datash->counter);

	/* Determine appropriate error message and length based on the input */
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;

	/* Allocate memory for the error message */
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	/* Generate the error message using strcat_cd function */
	error = strcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}
/**
 * error_not_found - Generates an error message for command not found errors.
 * @datash: Pointer to data structure containing shell information.
 *
 * Return: Pointer to the generated error message.
 */
char *error_not_found(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + 16;

	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");

	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - Generates an error message for shell exit errors.
 * @datash: Pointer to data structure containing shell information.
 *
 * Return: Pointer to the generated error message.
 */
char *error_exit_shell(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;

	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");

	free(ver_str);
	return (error);
}

