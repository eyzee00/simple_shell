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

	buff3 = buff2;
	wordc = word_count(buffer);
	command = tokenizer(buffer);
	path = (path_t **) path;
	if (wordc == 1)
	{
		buff1 = _getenv("HOME");
		check = chdir(buff1);
		if (check == -1)
		{
			cd_err(command, _getenv("_"), wordc);
			return (1);
		}
		replacer(head, buff3, command, wordc);
	}
	else if (command[1][0] == '-')
	{
		buff1 = _getenv("OLDPWD");
		check = chdir(buff1);
		if (check == -1)
		{
			cd_err(command, _getenv("_"), wordc);
			return (1);
		}
		replacer(head, buff3, command, wordc);
	}
	else
	{
		check = chdir(command[1]);
		if (check == -1)
		{
			cd_err(command, _getenv("_"), wordc);
			return (1);
		}
		replacer(head, buff3, command, wordc);
	}
	return (1);
}
/**
 * cd_err - handles cd errors
 * @command: user command
 * @argv: name of the shell
 * @wordc: word count
 * Return: (void)
 */
void cd_err(char **command, char *argv, int wordc)
{
	char err[256] = "";

	print_string(argv, err);
	print_string(": 1: ", err);
	print_string(command[0], err);
	print_string(": can't cd to ", err);
	print_string(command[1], err);
	print_string("\n", err);
	write(2, err, __strlen(err));
	free_memory(command, wordc);
}
/**
 * replacer - a placeholder function
 * @head: head of the alloclist
 * @buff3: buffer
 * @command: user command
 * @wordc: word count
 * Return: (void)
 */
void replacer(alloclist_t **head, char *buff3, char **command, int wordc)
{
	_setenv("OLDPWD", _getenv("PWD"), head);
	buff3 = getcwd(buff3, 256);
	_setenv("PWD", buff3, head);
	free_memory(command, wordc);
}
