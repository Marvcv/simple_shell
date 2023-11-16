#include "shell.h"

/**
 * copy_info - Copies name and value to a new string.
 * @name: Name to be copied.
 * @value: Value to be copied.
 *
 * Return: Pointer to the new string containing name and value.
 */
char *copy_info(char *name, char *value)
{
    char *new;
    int len_name, len_value, len;

    len_name = _strlen(name);
    len_value = _strlen(value);
    len = len_name + len_value + 2;

    new = malloc(sizeof(char) * (len));
    _strcpy(new, name);
    _strcat(new, "=");
    _strcat(new, value);
    _strcat(new, "\0");

    return (new);
}

/**
 * set_env - Sets the environment variable.
 * @name: Name of the variable.
 * @value: Value to be set.
 * @datash: Pointer to the data shell structure.
 *
 * Return: Void.
 */
void set_env(char *name, char *value, data_shell *datash)
{
    int i;
    char *var_env, *name_env;

    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = _strdup(datash->_environ[i]);
        name_env = _strtok(var_env, "=");

        if (_strcmp(name_env, name) == 0)
        {
            free(datash->_environ[i]);
            datash->_environ[i] = copy_info(name_env, value);
            free(var_env);
            return;
        }
        free(var_env);
    }

    datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
    datash->_environ[i] = copy_info(name, value);
    datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - Sets the environment variable.
 * @datash: Pointer to the data shell structure.
 *
 * Return: 1 on success, otherwise error.
 */
int _setenv(data_shell *datash)
{
    if (datash->args[1] == NULL || datash->args[2] == NULL)
    {
        get_error(datash, -1);
        return (1);
    }

    set_env(datash->args[1], datash->args[2], datash);

    return (1);
}

/**
 * _unsetenv - Unsets the environment variable.
 * @datash: Pointer to the data shell structure.
 *
 * Return: 1 on success, otherwise error.
 */
int _unsetenv(data_shell *datash)
{
    char **realloc_environ;
    char *var_env, *name_env;
    int i, j, k;

    if (datash->args[1] == NULL)
    {
        get_error(datash, -1);
        return (1);
    }

    k = -1;
    for (i = 0; datash->_environ[i]; i++)
    {
        var_env = _strdup(datash->_environ[i]);
        name_env = _strtok(var_env, "=");

        if (_strcmp(name_env, datash->args[1]) == 0)
        {
            k = i;
        }
        free(var_env);
    }

    if (k == -1)
    {
        get_error(datash, -1);
        return (1);
    }

    realloc_environ = malloc(sizeof(char *) * (i));
    for (i = j = 0; datash->_environ[i]; i++)
    {
        if (i != k)
        {
            realloc_environ[j] = datash->_environ[i];
            j++;
        }
    }
    realloc_environ[j] = NULL;

    free(datash->_environ[k]);
    free(datash->_environ);
    datash->_environ = realloc_environ;

    return (1);
}

/**
 * check_env - Checks environment variables.
 * @h: Pointer to the head of the r_var list.
 * @in: Input string.
 * @data: Pointer to the data shell structure.
 */
void check_env(r_var **h, char *in, data_shell *data)
{
    int row, chr, j, lval;
    char **_envr;

    _envr = data->_environ;
    for (row = 0; _envr[row]; row++)
    {
        for (j = 1, chr = 0; _envr[row][chr]; chr++)
        {
            if (_envr[row][chr] == '=')
            {
                lval = _strlen(_envr[row] + chr + 1);
                add_rvar_node(h, j, _envr[row] + chr + 1, lval);
                return;
            }

            if (in[j] == _envr[row][chr])
                j++;
            else
                break;
        }
    }

    for (j = 0; in[j]; j++)
    {
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }

    add_rvar_node(h, j, NULL, 0);
}

/**
 * rep_var - Replaces variables in the input string.
 * @input: Input string.
 * @datash: Pointer to the data shell structure.
 * 
 * Return: New input string.
 */
char *rep_var(char *input, data_shell *datash)
{
    r_var *head, *indx;
    char *status, *new_input;
    int olen, nlen;

    status = aux_itoa(datash->status);
    head = NULL;

    olen = check_vars(&head, input, status, datash);

    if (head == NULL)
    {
        free(status);
        return (input);
    }

    indx = head;
    nlen = 0;

    while (indx != NULL)
    {
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    nlen += olen;

    new_input = malloc(sizeof(char) * (nlen + 1));
    new_input[nlen] = '\0';

    new_input = replaced_input(&head, input, new_input, nlen);

    free(input);
    free(status);
    free_rvar_list(&head);

    return (new_input);
}

