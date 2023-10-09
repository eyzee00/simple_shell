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
void error_handler(char *argv, char *command, int counter)
{
	char buffer[256] = "\0";

	print_string(argv, buffer);
	print_string(": ", buffer);
	print_decimal(counter, buffer);
	print_string(": ", buffer);
	print_string(command, buffer);
	perror(buffer);
}
int line_counter(char *str)
{
	int i = 0, counter = 0;

	while (str[i] != '\0')
	{
		if (str[i] == 10)
			counter++;
		i++;
	}
	return (counter);
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
void stdin_handler(FILE *file, int *status, char *argv)
{
	pid_t child_id;
	char *line = 0;
	char **command, special[] = "\n";
	size_t buffsz = (size_t) LEN;
	int wordc, readc = 0, counter = 0;

	while (readc != -1)
	{
		readc = getline(&line, &buffsz, file);
		if (readc == -1)
			break;
		counter++;
		if (str_cmp(line, special))
			continue;
		wordc = word_count(line);
		command = tokenizer(line);
		if (file_exist_exec(command[0]) == 1)
		{
			child_id = fork();
			if (child_id == 0)
				execve(command[0], command, environ);
			else
				wait(status);
		}
		else
			error_handler(argv, command[0], counter);
		free_memory(command, wordc);
	}
	free(line);
}
