#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char *_getenv(const char *name);
extern char **environ;
int str_cmp(char *s1, char *s2);

/********************************/
int main(void)
{
	char *buffer, name[] = "PATH";

	buffer = _getenv((const char *) name);

	return (0);
}
/*********************************/
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
