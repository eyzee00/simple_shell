#include "main.h"
/**
 * cmd_counter - countes the number of commands
 * @str: the string to operate on
 * Return: the line count
 */
int cmd_counter(char *str)
{
	int i = 0, counter = 0;

	while (*(str + i) != 0)
	{
		if (*(str + i) == ';')
			counter++;
		i++;
	}
	return (counter + 1);
}
/**
 * cmdtok - tokenizes the user's input
 * @ch: strings
 * Return: pointer to commandlist
 */
char **cmdtok(char *ch)
{
	int cmdc = 0, i = 1, char_count = 0;
	char *command = NULL;
	char **commandlist = NULL;

	if (ch == NULL)
		return (NULL);
	cmdc = cmd_counter(ch);
	commandlist = malloc(sizeof(char *) * (cmdc + 1));
	if (commandlist == NULL)
		return (NULL);
	command = _strtok(ch, ";");
	if (command != NULL)
	{
	char_count = __strlen(command);
	*commandlist = _calloc(char_count + 2, sizeof(char));
	if (*commandlist == NULL)
	{
		free(commandlist);
		return (NULL);
	}
	fill_row_cmd(commandlist, 0, command);
	}
	while (i < cmdc)
	{
		command = _strtok(NULL, ";");
		if (command != NULL)
		{
		char_count = __strlen(command);
		*(commandlist + i) = _calloc(char_count + 2, sizeof(char));
		if (*(commandlist + i) == NULL)
		{
			free_memory(commandlist, i);
			return (NULL);
		}
		fill_row_cmd(commandlist, i, command);
		}
		i++;
	}
	commandlist[i] = NULL;
	return (commandlist);
}
/**
  * fill_row_cmd - fill worldlist pointer with words
  * @wordlist: pointer
  * @row: wordlist pointer row
  * @word: content to fill
  */
void fill_row_cmd(char **wordlist, int row, char *word)
{
	int i = 0, j = 0;

	if (word[i] == 32)
		i++;
	while (word[i] != 0)
	{
		if (word[i] != 10 && word[i] != ';')
		{
			wordlist[row][j] = word[i];
			i++;
			j++;
		}
		else
			i++;
	}
	wordlist[row][i] = '\0';
}
/**
 * multicmd_hand - handles multiple commands
 * @buffer: user input
 * @argv: name of the shell
 * @path: pathlist
 * Return: (void)
 */
void multicmd_hand(char *buffer, char *argv, path_t **path)
{
	int cmdc, check, i, wordc;
	char **commandlist, **command;

	cmdc = cmd_counter(buffer);
	commandlist = cmdtok(buffer);
	for (i = 0; i < cmdc; i++)
	{
		var_set(commandlist[i], &wordc, &command);
		check = file_exist_exec(command[0]);
		if (exec_handl(check, command, argv, path, wordc, i))
			continue;
		free_memory(command, wordc);
	}
	free_memory(commandlist, cmdc);
}
/**
 * _strtok - custom strtok to make Julian satisfied
 * @str: the buffer to tokenize
 * @delimiter: a pointer to the delimiter
 * Return: the next token
 */
char *_strtok(char *str, char *delimiter)
{
	static char *buffiter;
	char *buffstart;
	int i = 0;

	if (str != 0)
		buffiter = str;
	if (buffiter == 0 || *buffiter == 0)
		return (NULL);
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
		*buffiter = 0;
		i++;
		buffiter = buffiter + i;
	}
	return (buffstart);
}
