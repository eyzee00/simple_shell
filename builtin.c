#include "main.h"
/**
 * bltn_chck - checks if the user have entered a supported builtin
 * @buff: user's command
 * Return: the builtin function to execute if found
 */
int (*bltn_chck(char *buff))(char *buffer, alloclist_t **head, path_t **path)
{
	builtin_t builtin_list[] = {
		{"unsetenv", unsetenv_handler},
		{"setenv", setenv_handler},
		{"exit", exit_handler},
		{"env", env_handler},
		{NULL, NULL}
	};
	int i = 0;

	if (space_check(buff))
		return (emptycmd_handler);
	while (i < 4)
	{
		if (str_cmp(buff, builtin_list[i].cmdname))
			return (builtin_list[i].func);
		i++;
	}
	return (NULL);
}
/**
 * exit_handler - handles exit with arguments or without
 * @head: head of the alloclist
 * @buffer: the user input
 * @path: the head of the pathlist
 * Return: (void)
 */
int exit_handler(char *buffer, alloclist_t **head, path_t **path)
{
	char **command, *err;
	int status = 0, check = 0, wordc;

	wordc = word_count(buffer);
	command = tokenizer(buffer);
	if (command[1] == NULL)
	{
		free_memory(command, wordc);
		ultimate_free(path, head, buffer);
		exit(status);
	}
	else
	{

		check = alpha_check(command[1]);
		if (check)
		{
			err = _getenv("_");
			exit_arg_err(err, command, 0);
			free_memory(command, wordc);
		}
		else
		{
		status = _atoi(command[1]);
		free_memory(command, wordc);
		ultimate_free(path, head, buffer);
		exit(status);
		}
	}
	return (1);
}
/**
 * _atoi - converts a string to integer
 * @s: string to be converted
 * Return: the equivalent integer to s
 */

int _atoi(char *s)
{
	bool isnegative = false, hasnumbers = false;
	unsigned int i, integer = 0;

	for (i = 0; i < (unsigned int)__strlen(s); i++)
	{
		if (s[i] == '-')
		{
			if (!isnegative)
				isnegative = true;
			else
				isnegative = false;
		}
		while (s[i] >= 48 && s[i] <= 57)
		{
			hasnumbers = true;
			integer = integer * 10 + (s[i] - 48);
			i++;
		}
		if (hasnumbers)
			break;
	}
	if (!hasnumbers)
		return (0);

	else
	{
		if (isnegative)
			return (integer * (-1));
		else
			return (integer);
	}
}
/**
 * env_handler - handles printing the environment
 * @buffer: buffer
 * @head: head of the allocation list
 * @path: the head of the pathlist
 * Return: (1)
 */
int env_handler(char *buffer, alloclist_t **head, path_t **path)
{
	int i = 0;

	head = (alloclist_t **) head;
	buffer = (char *) buffer;
	path = (path_t **) path;
	while (*(environ + i) != NULL)
	{
		write(1, environ[i], __strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (1);
}
/**
 * emptycmd_handler - handles the newline character
 * @buffer: the buffer
 * @head: head of the allocation list
 * @path: the head of the pathlist
 * Return: (1)
 */
int emptycmd_handler(char *buffer, alloclist_t **head, path_t **path)
{
	head = (alloclist_t **) head;
	buffer = (char *) buffer;
	path = (path_t **) path;
	return (1);
}
