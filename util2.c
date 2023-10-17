#include "main.h"
#include <unistd.h>
/**
 * print_decimal - adds an integer to the buffer
 * @n: the number to be printed
 * @buffer: buffer to append
 * Return: void
 */
void print_decimal(int n, char *buffer)
{
	unsigned int number;
	char curr_char;

	if (n < 0)
	{
		n = -n;
		addto_buff(buffer, '-');
	}

	number = (unsigned int) n / 10;
	if (number)
		print_decimal(number, buffer);
	curr_char = (unsigned int) n % 10 + 48;
	addto_buff(buffer, curr_char);
}
/**
  * file_exist_exec - file exit & executable
  * @command: user command
  * Return: 1 for success -1 if faill
  */
int file_exist_exec(char *command)
{
	if (access(command, F_OK) != -1)
	{
		if (access(command, X_OK) == 0)
			return (1);
		else
			return (0);
	}
	return (-1);
}
/**
 * addto_buff - adds a character to the end of the given buffer
 * @buffer: the buffer to append
 * @c: the character to add to the end of the given buffer
 * Return: (void)
 */
void addto_buff(char *buffer, char c)
{
	int len = __strlen(buffer);

	if (len == 0)
	{
		buffer[0] = c;
		buffer[1] = 0;
		return;
	}
	buffer[len] = c;
	buffer[len + 1] = 0;
}
/**
 * print_string - adds a string to the buffer
 * @string: the string to be added to buffer
 * @buffer: the string to be appended
 * Return: (void)
 */
void print_string(char *string, char *buffer)
{
	int i = 0;

	if (*string == 0)
		return;
	addto_buff(buffer, *string);
	i++;
	print_string(string + i, buffer);
}
/**
 * space_check - checks if the string contains only spaces
 * @buffer: the string we're checking
 * Return: (1) if the string is only spaces, (0) otherwise
 */
int space_check(char *buffer)
{
	int i = 0;

	while (buffer[i] != 0)
	{
		if (buffer[i] != 32 && buffer[i] != 10)
			return (0);
		i++;
	}
	return (1);
}
