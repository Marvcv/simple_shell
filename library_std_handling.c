#include "shell.h"

/*
 * get_len - Gets the length of an integer.
 * @n: The integer value.
 * Return: The length of the integer.
 */
int get_len(int n)
{
	unsigned int n1;
	int length = 1;

	if (n < 0)
	{
		length++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}

	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}

	return (length);
}

/*
 * aux_itoa - Converts an integer to a string.
 * @n: The integer input.
 * Return: The string representation of the integer.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int length = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0'; /* Null-terminate the string */

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-'; /* Set the negative sign at the start of the string */
	}
	else
	{
		n1 = n;
	}

	length--;
	do
	{
		*(buffer + length) = (n1 % 10) + '0'; /* Convert each digit to character and store in reverse */
		n1 = n1 / 10;
		length--;
	} while (n1 > 0);

	return (buffer);
}

/*
 * _atoi - Converts a string to an integer.
 * @s: The string input.
 * Return: The integer value.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, output = 0, is_negative = 1, multiplier = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			is_negative *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		output = output + ((*(s + i) - '0') * multiplier); /* Convert characters to integers */
		multiplier /= 10;
	}

	return (output * is_negative);
}

