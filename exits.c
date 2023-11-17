#include "shell.h"

/**
 * _atoi - function that converts a string to an integer.
 * @s: string to be converted.
 *
 * Return: converted integer.
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned int res = 0;
	int sign = 1;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; s[i] != '\0'; ++i)
		res = res * 10 + s[i] - '0';
	return (sign * res);
}

/**
 * _itoa - function that converts an integer to a string.
 * @n: integer to be converted.
 *
 * Return: converted string.
 */
char *_itoa(int n)
{
	static char str[12];
	int i = 0;
	int sign = n;

	if (n < 0)
		n = -n;
	do {
		str[i++] = n % 10 + '0';
		n /= 10;
	} while (n);
	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
	return (reverse(str));
}

/**
 * reverse - function that reverses a string.
 * @str: string to be reversed.
 *
 * Return: reversed string.
 */
char *reverse(char *str)
{
	int len = _strlen(str);
	int start = 0;
	int end = len - 1;
	char temp;

	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}

/**
 * _strlen - function that returns the length of a string.
 * @s: string to find the length of.
 *
 * Return: length of string.
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

