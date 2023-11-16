#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data_shell - Structure to hold shell data
 * @av: Arguments
 * @input: User input
 * @args: Arguments array
 * @status: Status
 * @counter: Counter
 * @_environ: Environment variables
 * @pid: Process ID
 */
typedef struct data_shell
{
    char **av;
    char *input;
    char **args;
    int status;
    int counter;
    char **_environ;
    char *pid;
} data_shell;
/**
 * struct sep_list_s - A structure for separator list
 * @separator: The separator (; | &)
 * @next: Pointer to the next node
 *
 * Description: Structure defining the separator list.
 */
typedef struct sep_list_s
{
    char separator;
    struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - A structure for line list
 * @line: The line content
 * @next: Pointer to the next node
 *
 * Description: Structure defining the line list.
 */
typedef struct line_list_s
{
    char *line;
    struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - Structure defining a variable list
 * @len_var: Length of the variable
 * @val: Value of the variable
 * @len_val: Length of the value
 * @next: Pointer to the next node
 *
 * Description: Structure defining a variable list node.
 */
typedef struct r_var_list
{
    int len_var;
    char *val;
    int len_val;
    struct r_var_list *next;
} r_var;
/**
 * struct builtin_s - Structure defining built-in commands
 * @name: The name of the command
 * @f: Pointer to the function of the command
 *
 * Description: Structure defining the built-in commands along with their names and functions.
 */
typedef struct builtin_s
{
    char *name;
    int (*f)(data_shell *datash);
} builtin_t;

/* a.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* a2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* a */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* ac */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* a2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* a3.c */
void rev_string(char *s);
/* c.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

/* s.c */
char *without_comment(char *in);
void shell_loop(data_shell *datash);

/* r.c */
char *read_line(int *i_eof);

/* s.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* r.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);

/* g.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* ee */
int exec_line(data_shell *datash);
/* c.c */

/**
 * is_cdir - Check if a directory exists.
 * @path: Path to the directory.
 * @i: Integer pointer for error status.
 * Return: Integer value.
 */
int is_cdir(char *path, int *i);

/**
 * _which - Locate a command in the PATH environment.
 * @cmd: Command to search for.
 * @_environ: Environment variable array.
 * Return: A pointer to the command path.
 */
char *_which(char *cmd, char **_environ);

/**
 * is_executable - Check if a command is executable.
 * @datash: Pointer to the data_shell struct.
 * Return: Integer value.
 */
int is_executable(data_shell *datash);

/**
 * check_error_cmd - Check for errors in a command.
 * @dir: Command directory.
 * @datash: Pointer to the data_shell struct.
 * Return: Integer value.
 */
int check_error_cmd(char *dir, data_shell *datash);

/**
 * cmd_exec - Execute a command.
 * @datash: Pointer to the data_shell struct.
 */
int cmd_exec(data_shell *datash);

/* e.c */

/**
 * _getenv - Get the value of an environment variable.
 * @name: Name of the environment variable.
 * @_environ: Environment variable array.
 * Return: A pointer to the value of the variable.
 */
char *_getenv(const char *name, char **_environ);

/**
 * _env - Execute the env builtin command.
 * @datash: Pointer to the data_shell struct.
 * Return: Integer value.
 */
int _env(data_shell *datash);

/**
 * copy_info - Copy information to a string.
 * @name: Name of the variable.
 * @value: Value to be copied.
 * Return: A pointer to the copied string.
 */
char *copy_info(char *name, char *value);

/**
 * set_env - Set the value of an environment variable.
 * @name: Name of the variable.
 * @value: Value to be set.
 * @datash: Pointer to the data_shell struct.
 */
void set_env(char *name, char *value, data_shell *datash);

/**
 * _setenv - Execute the setenv builtin command.
 * @datash: Pointer to the data_shell struct.
 * Return: Integer value.
 */
int _setenv(data_shell *datash);

/**
 * _unsetenv - Execute the unsetenv builtin command.
 * @datash: Pointer to the data_shell struct.
 * Return: Integer value.
 */
int _unsetenv(data_shell *datash);

/* c.c */

/**
 * cd_dot - Change directory to the previous one.
 * @datash: Pointer to the data_shell struct.
 */
void cd_dot(data_shell *datash);

/**
 * cd_to - Change directory to the given path.
 * @datash: Pointer to the data_shell struct.
 */
void cd_to(data_shell *datash);

/**
 * cd_previous - Change directory to the previous one.
 * @datash: Pointer to the data_shell struct.
 */
void cd_previous(data_shell *datash);

/**
 * cd_to_home - Change directory to the home directory.
 * @datash: Pointer to the data_shell struct.
 */
void cd_to_home(data_shell *datash);

/**
 * cd_shell - Execute the cd builtin command.
 * @datash: Pointer to the data_shell struct.
 * Return: Integer value.
 */
int cd_shell(data_shell *datash);

/* gn */

/**
 * get_builtin - Get a pointer to the function of a built-in command.
 * @cmd: Command to find.
 * Return: Pointer to a function.
 */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _.c */

/**
 * exit_shell - Execute the exit builtin command.
 * @datash: Pointer to the data_shell struct.
 * Return: Integer value.
 */
int exit_shell(data_shell *datash);

/* a.c */

/**
 * get_len - Get the length of an integer.
 * @n: Input integer.
 * Return: Length of the integer.
 */
int get_len(int n);

/**
 * aux_itoa - Convert an integer to a string.
 * @n: Input integer.
 * Return: Converted string.
 */
char *aux_itoa(int n);

/**
 * _atoi - Convert a string to an integer.
 * @s: Input string.
 * Return: Converted integer.
 */
int _atoi(char *s);

/* a1.c */

/**
 * strcat_cd - Concatenate strings for the cd command.
 * @datash: Pointer to the data_shell struct.
 * @dest: Destination string.
 * @src1: Source string 1.
 * @src2: Source string 2.
 * Return: Concatenated string.
 */
char *strcat_cd(data_shell *datash, char *dest, char *src1, char *src2);

/**
 * error_get_cd - Get the error message for the cd command.
 * @datash: Pointer to the data_shell struct.
 * Return: Error message string.
 */
char *error_get_cd(data_shell *datash);

/**
 * error_not_found - Get the not found error message.
 * @datash: Pointer to the data_shell struct.
 * Return: Error message string.
 */
char *error_not_found(data_shell *datash);

/**
 * error_exit_shell - Get the exit shell error message.
 * @datash: Pointer to the data_shell struct.
 * Return: Error message string.
 */
char *error_exit_shell(data_shell *datash);
/* a2.c */

/**
 * error_get_alias - Get the error message for alias command.
 * @args: Array of command arguments.
 * Return: Error message string.
 */
char *error_get_alias(char **args);

/**
 * error_env - Get the error message for the env command.
 * @datash: Pointer to the data_shell struct.
 * Return: Error message string.
 */
char *error_env(data_shell *datash);

/**
 * error_syntax - Get the error message for syntax errors.
 * @args: Array of command arguments.
 * Return: Error message string.
 */
char *error_syntax(char **args);

/**
 * error_permission - Get the error message for permission issues.
 * @args: Array of command arguments.
 * Return: Error message string.
 */
char *error_permission(char **args);

/**
 * error_path_126 - Get the error message for 126 path errors.
 * @datash: Pointer to the data_shell struct.
 * Return: Error message string.
 */
char *error_path_126(data_shell *datash);

/* g.c */

/**
 * get_error - Get the error code.
 * @datash: Pointer to the data_shell struct.
 * @eval: Evaluation parameter.
 * Return: Error code.
 */
int get_error(data_shell *datash, int eval);

/**
 * get_sigint - Handle SIGINT signal.
 * @sig: Signal number.
 */
void get_sigint(int sig);

/* a.c */

/**
 * aux_help_env - Display help for env command.
 */
void aux_help_env(void);

/**
 * aux_help_setenv - Display help for setenv command.
 */
void aux_help_setenv(void);

/**
 * aux_help_unsetenv - Display help for unsetenv command.
 */
void aux_help_unsetenv(void);

/**
 * aux_help_general - Display general help information.
 */
void aux_help_general(void);

/**
 * aux_help_exit - Display help for exit command.
 */
void aux_help_exit(void);

/* a2.c */

/**
 * aux_help - Display general help.
 */
void aux_help(void);

/**
 * aux_help_alias - Display help for alias command.
 */
void aux_help_alias(void);

/**
 * aux_help_cd - Display help for cd command.
 */
void aux_help_cd(void);

/* g.c */

/**
 * get_help - Get help information.
 * @datash: Pointer to the data_shell struct.
 * Return: Help information.
 */
int get_help(data_shell *datash);

#endif

