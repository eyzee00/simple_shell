#include "main.h"
/**
 * cd_handler - handles changing a directory
 * @buffer: the user commmand
 * @head: head of the alloclist
 * @path: head of the pathlist
 * Return: (1)
 */
int cd_handler(char *buffer, alloclist_t **head, path_t **path)
{
	char **command, *buff1, buff2[256], *buff3;
	int wordc, check;

	wordc = word_count(buffer);
	command = tokenizer(buffer);
	path = (path_t **) path;
	if (wordc == 1 || command[1][0] == '~')
	{
		buff1 = _getenv("HOME");
		check = chdir(buff1);
		if (check == -1)
		{
			cd_err(command, _getenv("_"));
			free_memory(command, wordc);
			return (1);
		}
		buff3 = buff2;
		buff3 = getcwd(buff3, 256);
		_setenv("PWD", buff3, head);
		free_memory(command, wordc);
		return (1);
	}
	else
	{
		check = chdir(command[1]);
		if (check == -1)
		{
			cd_err(command, _getenv("_"));
			free_memory(command, wordc);
			return (1);
		}
		buff3 = buff2;
		buff3 = getcwd(buff3, 256);
		_setenv("PWD", buff3, head);
		free_memory(command, wordc);
		return (1);
	}
	return (1);
}
/**
 * cd_err - handles cd errors
 * @command: user command
 * @argv: name of the shell
 * Return: (void)
 */
void cd_err(char **command, char *argv)
{
	char err[256] = "";

	print_string(argv, err);
	print_string(": 1: ", err);
	print_string(command[0], err);
	print_string(": can't cd to ", err);
	print_string(command[1], err);
	print_string("\n", err);
	write(2, err, __strlen(err));
}
