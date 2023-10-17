#include "main.h"
#include <unistd.h>
/**
 * interactive_mode - provides the user with a prompt and executes commands
 * @argv: the name of the shell program
 * Return: (void)
 */
void interactive_mode(char *argv)
{
	pid_t sub_id = 0;
	char **command = NULL, *buffer = NULL;
	size_t buffsz = (size_t)LEN;
	alloclist_t *head = NULL;
	int readc = 0, wordc = 0, status;
	int check;
	int (*f)(char *buffer, alloclist_t **head);

	while (readc != -1)
	{
		printf("($): ");
		readc = getline(&buffer, &buffsz, stdin);
		if (readc == -1)
			break;
		f = builtin_check(buffer);
		if (f != NULL)
			if (f(buffer, &head) == 1)
				continue;
		wordc = word_count(buffer);
		command = tokenizer(buffer);
		check = file_exist_exec(command[0]);
		if (check == 1)
		{
			sub_id = fork();
			if (sub_id == 0)
				execve(command[0], command, environ);
			else
				wait(&status);
		}
		else
			error_handler(argv, command[0], 1, check);
		free_memory(command, wordc);
	}
	if (head != NULL)
		free_everything(&head);
	free(buffer);
}
/**
  * argument_mode - helper function
  * @argv: arg vector
  * Return: void
  */
void argument_mode(char **argv)
{
	int check, exec, sub_id, status, linec, i = 0, wordc;
	char *buffer = NULL, **commandlist = NULL, **command = NULL;
	alloclist_t *head = NULL;
	int (*f)(char *buffer, alloclist_t **head);

	check = access(argv[1], F_OK);
	buffer = filetobuff(argv, &head);
	if (buffer == NULL)
		return;
	linec = line_counter(buffer);
	commandlist = commandtok(buffer, "\n");
	while (i < linec)
	{
		if (commandlist[i] == NULL)
		{
			i++;
			continue;
		}
		if (space_check(commandlist[i]))
		{
			i++;
			continue;
		}
		wordc = word_count(commandlist[i]);
		f = builtin_check(commandlist[i]);
		if (f != NULL)
			if (f(commandlist[i], &head))
				continue;
		command = tokenizer(commandlist[i]);
		check = file_exist_exec(command[0]);
		if (check == 1)
		{
		sub_id = fork();
		if (sub_id == 0)
		{

			exec = execve(command[0], command, environ);
			if (exec == -1)
			{
				exit(99);
			}
		}
		else
			wait(&status);
		}
		else
			arg_err(argv, check, command, i);
		free_memory(command, wordc);
		i++;
	}
	free_everything(&head);
	free_memory(commandlist, linec);
}
/**
 * noninteractive_mode - handles the output written into the stdin of the shell
 * by another program i.e(pipes and redirections)
 * @file: the standard input stream, or another file
 * @status: the status of the child process
 * @argv: the name of the shell program
 */
void noninteractive_mode(FILE *file, int *status, char **argv)
{
	pid_t child_id;
	char *line = 0;
	char **command;
	size_t buffsz = (size_t) LEN;
	alloclist_t **head = NULL;
	int wordc, readc = 0, counter = 0, check;
	int (*f)(char *buffer, alloclist_t **head);

	while (readc != -1)
	{
		readc = getline(&line, &buffsz, file);
		if (readc == -1)
			break;
		counter++;
		f = builtin_check(line);
		if (f != NULL)
		{
			if (f(line, head))
				continue;
		}
		wordc = word_count(line);
		command = tokenizer(line);
		check = file_exist_exec(command[0]);
		if (check == 1)
		{
			child_id = fork();
			if (child_id == 0)
				execve(command[0], command, environ);
			else
				wait(status);
		}
		else
			arg_err(argv, -5, command, counter);
		free_memory(command, wordc);
	}
	free(line);
}
/**
 * filetobuff - reads the content of a file into a buffer
 * @argv: the argument vector
 * @head: the head of the alloclist
 * Return: the buffer allocated
 */
char *filetobuff(char **argv, alloclist_t **head)
{
	int fd, readc = 0;
	char *buffer = "";
	size_t buffer_size = 1024, readc_sum = 0;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		arg_err(argv, 10, NULL, 0);
		return (NULL);
	}
	buffer = _calloc(buffer_size, sizeof(char));
	if (buffer == NULL)
	{
		perror("malloc");
		close(fd);
		return (NULL);
	}
	while (readc != -1)
	{
		readc = read(fd, buffer + readc_sum, buffer_size - readc_sum);
		if (readc == -1)
		{
			perror("read");
			close(fd);
			free(buffer);
			return (NULL);
		}
		if (readc == 0)
			break;
		readc_sum = readc_sum + (size_t) readc;
		if (readc_sum == buffer_size)
		{
			buffer_size *= 2;
			buffer = _realloc(buffer, buffer_size / 2, buffer_size);
			if (buffer == NULL)
			{
				perror("realloc");
				close(fd);
				return (NULL);
			}
		}
	}
	close(fd);
	add_node_end(head, buffer);
	return (buffer);
}
