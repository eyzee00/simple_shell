#include "main.h"
/**
 * builtin_check - checks if the user have entered a supported builtin
 * @buffer: the user input
 * Return: the builtin function to execute if found
 */
int (*builtin_check(char *buffer))(char **env, char *buffer)
{
	builtin_t builtin_list[] = {
		{"exit", exit_handler},
		{"env", env_handler},
		{NULL, NULL}
	};
	int i = 0;

	if (space_check(buffer))
		return (emptycmd_handler);
	while (i < 2)
	{
		if (str_cmp(buffer, builtin_list[i].cmdname))
		{
			return (builtin_list[i].func);
		}
		i++;
	}
	return (NULL);
}
/**
 * exit_handler - handles exit with arguments or without
 * @env: the current environment
 * @buffer: the user inpu
 * Return: (void)
 */
int exit_handler(char **env, char *buffer)
{
	char **command;
	int status = 0;

	command = tokenizer(buffer);
	env = env;
	if (command[1] == NULL)
	{
		free_memory(command, 1);
		free(buffer);
		exit(status);
	}
	else
	{
		status = (int) _atoi(command[1]);
		free_memory(command, 2);
		free(buffer);
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
 * @env: the current process's environment
 * @buffer: buffer
 * Return: (1)
 */
int env_handler(char **env, char *buffer)
{
	int i = 0;

	buffer = buffer;
	while (*(env + i) != NULL)
	{
		write(1, env[i], __strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (1);
}
/**
 * emptycmd_handler - handles the newline character
 * @buffer: the buffer
 * @env: the environment
 * Return: (1)
 */
int emptycmd_handler(char **env, char *buffer)
{
	env = env;
	buffer = buffer;
	return (1);
}
