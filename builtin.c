#include "main.h"
/**
 * builtin_check - checks if the user have entered a supported builtin
 * @buffer: user's command
 * Return: the builtin function to execute if found
 */
int (*builtin_check(char *buffer))(char *buffer, alloclist_t **head)
{
	builtin_t builtin_list[] = {
		{"unsetenv", unsetenv_handler},
		{"setenv", setenv_handler},
		{"exit", exit_handler},
		{"env", env_handler},
		{NULL, NULL}
	};
	int i = 0;

	if (space_check(buffer))
		return (emptycmd_handler);
	while (i < 4)
	{
		if (str_cmp(buffer, builtin_list[i].cmdname))
			return (builtin_list[i].func);
		i++;
	}
	return (NULL);
}
/**
 * exit_handler - handles exit with arguments or without
 * @head: head of the alloclist
 * @buffer: the user inpu
 * Return: (void)
 */
int exit_handler(char *buffer, alloclist_t **head)
{
	char **command;
	int status = 0;

	command = tokenizer(buffer);
	head = head;
	if (command[1] == NULL)
	{
		free_memory(command, 1);
		free(buffer);
		free_everything(head);
		exit(status);
	}
	else
	{
		status = (int) _atoi(command[1]);
		free_memory(command, 2);
		free(buffer);
		free_everything(head);
		exit(status);
	}
	return (0);
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
 * Return: (1)
 */
int env_handler(char *buffer, alloclist_t **head)
{
	int i = 0;

	head = head;
	buffer = buffer;
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
 * Return: (1)
 */
int emptycmd_handler(char *buffer, alloclist_t **head)
{
	head = head;
	buffer = buffer;
	return (1);
}
