#include "main.h"
/**
  * fill_row_logic - fill worldlist pointer with words
  * @wordlist: pointer
  * @row: wordlist pointer row
  * @word: content to fill
  */
void fill_row_logic(char **wordlist, int row, char *word)
{
	int i = 0, j = 0;

	while (word[i] == 32 || word[i] == '&' || word[i] == '|')
		i++;
	while (word[i] != 0)
	{
		if (word[i] != 10 && (word[i] != '&' || word[i] != '|'))
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
 * logic_hand - handles multiple commands
 * @buffer: user input
 * @argv: name of the shell
 * @p: pathlist
 * @head: head of the alloclist
 * Return: (void)
 */
void logic_hand(char *buffer, char *argv, path_t **p, alloclist_t **head)
{
	int cmdc = 0, check, check2, i, wordc;
	char **commandlist, **command, del[22] = "";
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	initializer(buffer, &cmdc, &check, del);
	commandlist = logictok(buffer, del);
	for (i = 0; i < cmdc && commandlist[i] != NULL; i++)
	{
		f = bltn_chck(commandlist[i]);
		if (f != NULL)
		{
			if (f(commandlist[i], head, p) == -1)
				break;
			continue;
		}
		var_set(commandlist[i], &wordc, &command);
		check2 = file_exist_exec(command[0]);
		if (check == 1)
		{
		if (lexec_handl(check2, command, argv, p, wordc, i) == 1)
			break;
		}
		else
		{
		if (lexec_handl(check2, command, argv, p, wordc, i) == 1)
			continue;
		else
		{
			free_memory(command, wordc);
			break;
		}
		}
		free_memory(command, wordc);
	}
	free_memory(commandlist, cmdc);
}
/**
 * set_delimiter - sets the delimiter
 * @check: the case
 * @del: the char to be sets
 * Return: (void)
 */
void set_delimiter(int check, char *del)
{
	if (check == 1)
		print_string("&", del);
	else
		print_string("|", del);
}
/**
 * logic_counter - countes the number of commands
 * @str: the string to operate on
 * Return: the line count
 */
int logic_counter(char *str)
{
	int i = 0, counter = 0;

	while (*(str + i) != 0)
	{
		if (*(str + i) == '&' && *(str + i + 1) == '&')
		{
			counter++;
			i++;
		}
		if (*(str + i) == '|' && *(str + i + 1) == '|')
		{
			counter++;
			i++;
		}
		i++;
	}
	return (counter + 1);
}
/**
 * get_del - gets the logical operator
 * @buffer: the user input
 * Return: (1) if AND, (0) if OR
 */
int get_del(char *buffer)
{
	int i = 0;

	while (buffer[i] != 0)
	{
		if (buffer[i] == '&')
			return (1);
		if (buffer[i] == '|')
			return (0);
		i++;
	}
	return (0);
}
/**
 * logicexecutor - executes a command in a child process
 * @command: the command array
 * Return: (void)
 */
int logicexecutor(char **command)
{
	pid_t child_id;
	int status = 0, exec;

	child_id = fork();
	if (child_id == 0)
	{
		exec = execve(command[0], command, environ);
		if (exec == -1)
		{
			perror("execve");
			exit(99);
		}
	}
	else
		wait(&status);
	if (status != 0)
		return (-1);
	return (0);
}
