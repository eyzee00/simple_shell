#include "main.h"
#include <unistd.h>

static path_t *ptr1;
static alloclist_t *ptr2;
static char *buff;
/**
 * interactive_mode - provides the user with a prompt and executes commands
 * @argv: the name of the shell program
 * Return: (void)
 */

void interactive_mode(char *argv)
{
	char **command = NULL, *buffer = NULL;
	alloclist_t *head = NULL;
	path_t *path = NULL;
	int readc = 0, wordc = 0, check, check2, buffsz = LEN;
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	path = path_creator(&path);
	ptr1 = path;
	signal(SIGINT, sigint_handler);
	while (readc != -1)
	{
		ptr2 = head;
		write(1, "($): ", 6);
		readc = getline(&buffer, (size_t *) &buffsz, stdin);
		buff = buffer;
		if (readc == -1)
			break;
		f = bltn_chck(buffer);
		if (f != NULL)
			if (f(buffer, &head, &path) == 1)
				continue;
		var_set(buffer, &wordc, &command);
		check = file_exist_exec(command[0]);
		if (check == 1 || check == -1)
		{
			if (check == -1)
			{
				check2 = executable_locator(&path, command);
				if (check2 == -1 || check2 == 0)
				{
					error_handler(argv, command[0], 1, check);
					free_memory(command, wordc);
					continue;
				}
			}
			executor(command);
		}
		free_memory(command, wordc);
	}
	ultimate_free(&path, &head, buffer);
}
/**
  * argument_mode - helper function
  * @argv: arg vector
  * Return: void
  */
void argument_mode(char **argv)
{
	int check, check2, exec, sub_id, status, linec, i = 0, wordc;
	char *buffer = NULL, **commandlist = NULL, **command = NULL;
	alloclist_t *head = NULL;
	path_t *path = NULL;

	path = path_creator(&path);
	check = access(argv[1], F_OK);
	buffer = filetobuff(argv, &head);
	if (*buffer == 0)
		return;
	if (buffer == NULL)
		perror("malloc");
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
		command = tokenizer(commandlist[i]);
		check = file_exist_exec(command[0]);
		if (check == 1 || check == -1)
		{
			if (check == -1)
			{
				check2 = executable_locator(&path, command);
				if (check2 == -1 || check2 == 0)
				{
					error_handler(argv[0], command[0], 1, check);
					free_memory(command, wordc);
					i++;
					continue;
				}
			}
			sub_id = fork();
			if (sub_id == 0)
			{
				exec = execve(command[0], command, environ);
				if (exec == -1)
					exit(99);
			}
			else
				wait(&status);
		}
		free_memory(command, wordc);
		i++;
	}
	free_pathlist(&path);
	if (head != NULL)
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
	alloclist_t *head = NULL;
	path_t *path = NULL;
	int wordc, readc = 0, counter = 0, check, check2;
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	path = path_creator(&path);
	while (readc != -1)
	{
		readc = getline(&line, &buffsz, file);
		if (readc == -1)
			break;
		counter++;
		f = bltn_chck(line);
		if (f != NULL)
		{
			if (f(line, &head, &path))
				continue;
		}
		wordc = word_count(line);
		command = tokenizer(line);
		check = file_exist_exec(command[0]);
		if (check == 1 || check == -1)
		{
			if (check == -1)
			{
				check2 = executable_locator(&path, command);
				if (check2 == -1 || check2 == 0)
				{
					arg_err(argv, -5, command, counter);
					free_memory(command, wordc);
					continue;
				}
			}
			child_id = fork();
			if (child_id == 0)
				execve(command[0], command, environ);
			else
				wait(status);
		}
		free_memory(command, wordc);
	}
	free_pathlist(&path);
	if (head != NULL)
		free_everything(&head);
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
	size_t buffsize = 5000, readc_sum = 0;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		arg_err(argv, 10, NULL, 0);
		return ("");
	}
	buffer = _calloc(buffsize, sizeof(char));
	if (buffer == NULL)
	{
		close(fd);
		return (NULL);
	}
	while (readc != -1)
	{
		readc = read(fd, buffer + readc_sum, buffsize - readc_sum);
		if (readc == -1)
		{
			close(fd);
			free(buffer);
			return (NULL);
		}
		if (readc == 0)
			break;
		readc_sum = readc_sum + (size_t) readc;
		if (readc_sum == buffsize)
		{
			buffsize = buffsize * 2;
			buffer = _realloc(buffer, buffsize / 2, buffsize);
			if (buffer == NULL)
			{
				free(buffer);
				close(fd);
				return (NULL);
			}
		}
	}
	close(fd);
	add_node_end(head, buffer);
	return (buffer);
}
/**
 * sigint_handler - handles the sigint signal
 * @sig: the signal
 * Return: (void)
 */
void sigint_handler(int sig)
{
	free_pathlist(&ptr1);
	free_everything(&ptr2);
	free(buff);
	write(1, "\n", 2);
	exit(sig);
}
