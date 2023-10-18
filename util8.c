#include "main.h"
/**
 * exit_arg_err - handles the exit argument error
 * @argv: the name of the shell
 * @command: the exit command
 * Return: (void)
 */
void exit_arg_err(char *argv, char **command)
{
	char err[256] = "";

	print_string(argv, err);
	print_string(": 1: ", err);
	print_string(command[0], err);
	print_string(": Illegal number: ", err);
	print_string(command[1], err);
	print_string("\n", err);
	write(2, err, __strlen(err));
}
/**
 * var_set - sets some variables
 * @buffer: buffer
 * @check: wordc
 * @command: the command to set
 * Return: (void)
 */
void var_set(char *buffer, int *check, char ***command)
{
	*check = word_count(buffer);
	*command = tokenizer(buffer);
}
