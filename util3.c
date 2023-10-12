#include "main.h"

/**
 * set_entry - sets an entry with the given name and value
 * @name: the name of the variable
 * @value: the value of the given variable
 * @buffer: where to put the entry in
 * Return: (void)
 */
void set_entry(char *buffer, char *name, char *value)
{
	print_string(name, buffer);
	addto_buff(buffer, 61);
	print_string(value, buffer);
}
/**
 * _strncpy - copies n bytes of src to dest
 * n should be smaller than strlen(dest)
 * if n is bigger than strlen(src)
 * write '\0' in each case after copying src
 * @dest: string receiving the copying
 * @src: string being copied
 * @n: number of bytes copied from src
 * Return: a pointer to the resulting string (dest)
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (src[i] != '\0')
			dest[i] = src[i];
		if (src[i] == '\0')
		{
			while (i < n)
			{
				dest[i] = '\0';
				i++;
			}
			break;
		}
	}
	return (dest);
}
/**
 * free_env - frees environment memory
 * @environ: the environment to free
 * @n: the number of variables in the environment
 * Return: (void)
 */
void free_env(char **environ, int n)
{
	int i = 0;

	while (i < n)
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}
/**
 * string_count - counts how many strings in the env list
 * @env: environment array
 * Return: the count
 */
int string_count(char **env)
{
	int i = 0;

	if (env == NULL)
		return (0);
	while (*(env + i) != NULL)
		i++;
	return (i);
}
