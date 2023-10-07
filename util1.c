#include "main.h"
/**
 * __strlen - classic strlen
 * @buffer: the buffer to operate on
 * Return: the length of buffer
 */
int __strlen(char *buffer)
{
	int i = 0;

	if (*buffer == 0)
		return (0);
	while (buffer[i] != 0)
		i++;
	return (i);
}
/**
 * error_handler - handles errors
 * @argv: the name of the shell program
 * @command: the name of the command
 * Return: (void)
 */
void error_handler(char *argv, char *command)
{
	char buffer[256] = "\0";

	print_string(argv, buffer);
	print_string(": 1: ", buffer);
	print_string(command, buffer);
	perror(buffer);
}
