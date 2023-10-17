#include "main.h"
/**
 * str_cmp_df - compares two strings
 * @s1: the first string
 * @s2: the second string
 * Return: (1) if identical, (0) otherwise
 */
int str_cmp_df(char *s1, char *s2)
{
	while (*s1 != 0 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *) s1 - *(unsigned char *) s2);
}
/**
 * fill_string - fills a string
 * @dirname: the directory name
 * @command: command
 * @newcommand: newcommand
 * Return: the resulting string
 */
char *fill_string(char *dirname, char *command, char *newcommand)
{
	*newcommand = 0;
	print_string(dirname, newcommand);
	print_string("/", newcommand);
	print_string(command, newcommand);
	free(command);
	return (newcommand);
}
/**
 * executor - executes a command in a child process
 * @command: the command array
 * Return: (void)
 */
void executor(char **command)
{
	pid_t child_id;
	int status = 0;

	child_id = fork();
	if (child_id == 0)
		execve(command[0], command, environ);
	else
		wait(&status);
}
/**
 * alpha_check - checks for alphabetical chars in a string
 * @str: the string
 * Return: (1) if alphabetical chars exist, (0) otherwise
 */
int alpha_check(char *str)
{
	int i = 0;

	while (str[i] != 0)
	{	
		if (str[i] >= 97 && str[i] <= 122)
			return (1);
		if (str[i] >= 65 && str[i] <= 90)
			return (1);
		i++;
	}
	return (0);
	
}
