#include "main.h"
/**
 * error_handler - handles errors print statement
 * @argv: the name of the shell program
 * @command: the name of the command
 * @counter: line count
 * @option: error case hint
 * Return: (void)
 */
void error_handler(char *argv, char *command, int counter, int option)
{
	char buffer[256] = "\0";

	print_string(argv, buffer);
	print_string(": ", buffer);
	print_decimal(counter, buffer);
	print_string(": ", buffer);
	print_string(command, buffer);
	if (option == -1)
	{
		write(2, buffer, __strlen(buffer));
		write(2, ": not found\n", 12);
	}
	else
		perror(buffer);
}
/**
 * str_cmp - two strings compared
 * @s1: the first string
 * @s2: the second string
 * Return: (1) if identical, (0) otherwise
 */
int str_cmp(char *s1, char *s2)
{
	int i = 0, j;

	while (s1[i] == 32 && s1[i] != 0)
		i++;
	for (j = 0; s1[i] != 0 && s2[j] != 0; i++, j++)
		if (s1[i] != s2[j])
			return (0);
	return (1);
}
/**
 * _realloc - reallocates a new space in heap memory
 * where the size == new_size
 * @new_size: the size in bytes to allocate
 * @old_size: the size in bytes of the previously allocated memory
 * @ptr: a void pointer to the previously allocated memory
 * Return: (ptr) if new_size == old_size,
 * if (new_size == 0) and (ptr) is not NULL, then free(ptr),
 * if (ptr) is NULL, then the call is equivalent to malloc(new_size)
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_pointer;
	char *old_stuff, *new_stuff;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	if (new_size > old_size)
	{
		new_pointer = malloc(new_size);
		if (new_pointer == NULL)
			return (NULL);
		old_stuff = ptr;
		new_stuff = new_pointer;
		for (i = 0; i < old_size; i++)
			new_stuff[i] = old_stuff[i];
	}
	return (new_pointer);
}
/**
 * _setenv - sets a new environment variable or modifies an
 * existing one
 * @name: name of the variable to set
 * @value: the value of the said variable
 * @head: head of the alloc list
 * Return: (-1) on failure, (1) on success
 */
int _setenv(char *name, char *value, alloclist_t **head)
{
	unsigned int i = 0, size = 0;
	char **mod_env, *newvar, buff[256];
	char **ptr = environ;

	if (name == 0 || *name == 0)
		return (-1);
	if (equal_check(name))
		return (-1);
	while (*(environ + i) != NULL)
	{
		_strncpy(buff, ptr[i], _strlentok(ptr[i]));
		if (str_cmp(buff, name))
		{
		size = (unsigned int) (__strlen(name) + __strlen(value) + 2);
		newvar = malloc(size);
		*newvar = '\0';
		if (newvar == NULL)
			return (0);
		set_entry(newvar, name, value);
		*(ptr + i) = newvar;
		add_node_end(head, (void *) newvar);
		return (1);
		}
		i++;
	}
	i = string_count(ptr);
	mod_env = _realloc(ptr, i * sizeof(char *), (i + 2) * sizeof(char *));
	if (mod_env == NULL)
		return (0);
	add_node_end(head, (void *) mod_env);
	size = (unsigned int) (__strlen(name) + __strlen(value) + 2);
	mod_env[i] = malloc(size * sizeof(char));
	if (mod_env[i] == NULL)
		return (0);
	mod_env[i][0] = '\0';
	set_entry(mod_env[i], name, value);
	mod_env[i + 1] = NULL;
	environ = mod_env;
	add_node_end(head, (void *) mod_env[i]);
	return (1);
}
/**
 * equal_check - checks for the equal character
 * @str: the string to be checked
 * Return: (1) if found, (0) if not
 */
int equal_check(char *str)
{
	int i = 0;

	while (str[i] != 0)
	{
		if (str[i] == 61)
			return (1);
		i++;
	}
	return (0);
}
