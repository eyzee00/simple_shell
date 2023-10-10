#include "main.h"
/**
 * error_handler - handles errors
 * @argv: the name of the shell program
 * @command: the name of the command
 * @counter: line count
 * @option: error case hint
 * Return: (void)
 */
void error_handler(char *argv, char *command, int counter, int option)
{
	char buffer[256] = "\0";

	print_string(argv, buffer);
	print_string(": ", buffer);
	print_decimal(counter, buffer);
	print_string(": ", buffer);
	print_string(command, buffer);
	if (option == -1)
	{
		write(2, buffer, __strlen(buffer));
		write(2, ": not found\n", 12);
	}
	else
		perror(buffer);
}
/**
 * str_cmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 * Return: (1) if identical, (0) otherwise
 */
int str_cmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != 0 && s2[i] != 0; i++)
		if (s1[i] != s2[i])
			return (0);
	return (1);
}
