#include "main.h"
/**
 * cd_handler - changes directory
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
			return (-1);
		}
		replacer(head, buff3, command, wordc);
	}
	else if (command[1][0] == '-' && command[1][1] == 0)
	{
		buff1 = _getenv("OLDPWD");
		check = chdir(buff1);
		if (check == -1)
		{
			cd_err(command, _getenv("_"), wordc);
			return (-1);
		}
		replacer(head, buff3, command, wordc);
	}
	else
	{
		check = chdir(command[1]);
		if (check == -1)
		{
			cd_err(command, _getenv("_"), wordc);
			return (-1);
		}
		replacer(head, buff3, command, wordc);
	}
	return (-1);
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
 * replacer - functions for place holder
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
/**
 * logic_check - checks for logical operators
 * @str: the string to be checked
 * Return: (1) if found, (0) if not
 */
int logic_check(char *str)
{
	int i = 0;


	while (str[i] != 0)
	{
		if (str[i] == '&' || str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}
/**
 * logictok - tokenizes the user's input
 * @ch: string
 * @del: delimiter
 * Return: pointer to commandlist
 */
char **logictok(char *ch, char *del)
{
	int cmdc = 0, i = 1, char_count = 0;
	char *command = NULL;
	char **commandlist = NULL;

	if (ch == NULL)
		return (NULL);
	cmdc = logic_counter(ch);
	commandlist = _calloc(sizeof(char *), (cmdc + 1));
	if (commandlist == NULL)
		return (NULL);
	command = _strtok(ch, del);
	if (command != NULL)
	{
	char_count = __strlen(command);
	*commandlist = _calloc(char_count + 2, sizeof(char));
	if (*commandlist == NULL)
	{
		free(commandlist);
		return (NULL);
	}
	fill_row_logic(commandlist, 0, command);
	}
	while (i < cmdc)
	{
		command = _strtok(NULL, del);
		if (command != NULL)
		{
		char_count = __strlen(command);
		*(commandlist + i) = _calloc(char_count + 2, sizeof(char));
		if (*(commandlist + i) == NULL)
		{
			free_memory(commandlist, i);
			return (NULL);
		}
		fill_row_logic(commandlist, i, command);
		}
		i++;
	}
	commandlist[i] = NULL;
	return (commandlist);
}
