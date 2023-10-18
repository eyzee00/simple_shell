#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char *_getenv(const char *name);
extern char **environ;
int str_cmp(char *s1, char *s2);
char *_strtok(char *str, char *delimiter);
/********************************/
int main(void)
{
	char buff[] = "ls -la ; ls -la ; ls -la\n";
	char *ptr;
	
	ptr = _strtok(buff, ";");
	printf("%s| %d\n", ptr, (unsigned int) strlen(ptr));
	ptr = _strtok(NULL, ";");
	printf("%s| %d\n", ptr, (unsigned int) strlen(ptr));
	ptr = _strtok(NULL, ";");
	printf("%s| %d", ptr, (unsigned int) strlen(ptr));
	return (0);
}
/*********************************/
/**
 * _strtok - custom strtok to make Julian satisfied
 * @str: the buffer to tokenize
 * @delimiter: a pointer to the delimiter
 * Return: the next token
 */
char *_strtok(char *str, char *delimiter)
{
	static char *buffiter = NULL;
	char *buffstart;
	int i = 0;

	if (str != NULL)
		buffiter = str;
	if (buffiter == NULL || *buffiter == '\0')
		return NULL;
	while (*(buffiter + i) != 0 && *(buffiter + i) == *delimiter)
        	i++;
	buffiter = buffiter + i;
	i = 0;
	buffstart = buffiter;
	while (*(buffiter + i) != 0 && *(buffiter + i) != *delimiter)
		i++;
	buffiter = buffiter + i;
	i = 0;
	if (*buffiter == *delimiter)
	{
		*buffiter = '\0';
		i++;
		buffiter = buffiter + i;
	}
	return (buffstart);
}
char *_getenv(const char *name)
{
	int i = 0, j = 0;

	while (environ[i] != NULL)
	{
		if (str_cmp((char *) name, environ[i]))
		{
		while (environ[i][j] != '=')
			j++;
		j++;
		return (environ[i] + j);
		}
		i++;
	}
	return (NULL);
}
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
