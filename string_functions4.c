#include "shell.h"

/**
 * strtow - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string
 * @d: The delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	/* Check for edge cases where input string is NULL or empty */
	if (str == NULL || str[0] == 0)
		return (NULL);

	/* Set default delimiter if not provided */
	if (!d)
		d = " ";

	/* Count the number of words in the string */
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	/* Return NULL if no words found */
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Parse the string and extract individual words */
	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip leading delimiters */
		while (is_delim(str[i], d))
			i++;

		/* Count characters in the current word */
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		/* Allocate memory for the current word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			/* Free memory on failure and return NULL */
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy characters of the current word to the allocated memory */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0; /* Null-terminate the word */
	}

	s[j] = NULL; /* Null-terminate the array of strings */
	return (s);
}

/**
 * strtow2 - Splits a string into words using a single delimiter.
 * @str: The input string
 * @d: The delimiter
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	/* Check for edge cases where input string is NULL or empty */
	if (str == NULL || str[0] == 0)
		return (NULL);

	/* Count the number of words in the string */
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

	/* Return NULL if no words found */
	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Parse the string and extract individual words */
	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip leading and consecutive delimiters */
		while (str[i] == d && str[i] != d)
			i++;

		/* Count characters in the current word */
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		/* Allocate memory for the current word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			/* Free memory on failure and return NULL */
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy characters of the current word to the allocated memory */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0; /* Null-terminate the word */
	}

	s[j] = NULL; /* Null-terminate the array of strings */
	return (s);
}

