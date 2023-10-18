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
/**
 * exec_handl - handles command execution
 * @check: the file status
 * @cmd: the command entered by the user
 * @argv: name of the shell
 * @wordc: how many words in the command
 * @p: pathlist
 * Return: (1) to continue, (0) to resume
 */
int exec_handl(int check, char **cmd, char *argv, path_t **p, int wordc)
{
	int check2 = 0;


	if (check == 0)
	{
		error_handler(argv, cmd[0], 1, -1);
		free_memory(cmd, wordc);
		return (1);
	}
	if (check == 1 || check == -1)
	{
		if (check == -1)
		{
			check2 = executable_locator(p, cmd);
			if (check2 == -1 || check2 == 0)
			{
				error_handler(argv, cmd[0], 1, check);
				free_memory(cmd, wordc);
				return (1);
			}
		}
		executor(cmd);
	}

	return (0);
}
/**
 * semicolon_check - checks for the semicolon character
 * @str: the string to be checked
 * Return: (1) if found, (0) if not
 */
int semicolon_check(char *str)
{
	int i = 0;


	while (str[i] != 0)
	{
		if (str[i] == ';')
		{
			while (str[i] != 0)
			{
			if (str[i] == 10)
				return (1);
			if (str[i] == ';' && str[i + 1] == '\n')
			{
				str[i] = 10;
				str[i + 1] = 0;
				return (1);
			}
			i++;
			}
		}
		i++;
	}
	return (0);
}
