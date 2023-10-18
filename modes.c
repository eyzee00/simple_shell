#include "main.h"

static path_t *ptr1;
static alloclist_t *ptr2;
static char *buff;
/**
 * interactive_mode - allows prompt and executes commands
 * @argv: the name of the shell program
 * Return: (void)
 */

void interactive_mode(char *argv)
{
	char **command = NULL;
	alloclist_t *head = NULL;
	path_t *path = NULL;
	int readc = 0, wordc = 0, check, buffsz = LEN;
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	path = path_creator(&path);
	ptr1 = path;
	signal(SIGINT, sigint_handler);
	while (readc != -1)
	{
		ptr2 = head;
		write(1, "($): ", 6);
		readc = getline(&buff, (size_t *) &buffsz, stdin);
		if (readc == -1)
			break;
		if (semicolon_check(buff))
			multicmd_hand(buff, argv, &path, &head);
		else
		{
		f = bltn_chck(buff);
		if (f != NULL)
			if (f(buff, &head, &path) == 1)
				continue;
		var_set(buff, &wordc, &command);
		check = file_exist_exec(command[0]);
		if (exec_handl(check, command, argv, &path, wordc, 1))
			continue;
		free_memory(command, wordc);
		}
	}
	write(1, "\n", 2);
	ultimate_free(&path, &head, buff);
}
/**
  * argument_mode - helper function
  * using variadic
  * @argv: arg vector
  * Return: void
  */
void argument_mode(char **argv)
{
	int check, linec, i = 0, wordc;
	char *buffer = NULL, **commandlist = NULL, **command = NULL;
	alloclist_t *head = NULL;
	path_t *path = NULL;
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	path = path_creator(&path);
	check = access(argv[1], F_OK);
	buffer = filetobuff(argv, &head);
	if (*buffer == 0)
		return;
	if (buffer == NULL)
		perror("malloc");
	linec = line_counter(buffer);
	commandlist = commandtok(buffer, "\n");
	signal(SIGINT, sigint_handler);
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
		if (semicolon_check(commandlist[i]))
			multicmd_hand(commandlist[i], argv[0], &path, &head);
		else
		{
		f = bltn_chck(commandlist[i]);
		if (f != NULL)
			if (f(commandlist[i], &head, &path) == 1)
				continue;
		var_set(commandlist[i], &wordc, &command);
		check = file_exist_exec(command[0]);
		if (exec_handl(check, command, argv[0], &path, wordc, i))
		{
			i++;
			continue;
		}
		free_memory(command, wordc);
		}
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
 * @argv: the name of the shell program
 */
void noninteractive_mode(FILE *file, char **argv)
{
	char *line = 0;
	char **command;
	size_t buffsz = (size_t) LEN;
	alloclist_t *head = NULL;
	path_t *path = NULL;
	int wordc, readc = 0, counter = 0, check;
	int (*f)(char *buffer, alloclist_t **head, path_t **path);

	path = path_creator(&path);
	signal(SIGINT, sigint_handler);
	while (readc != -1)
	{
		readc = getline(&line, &buffsz, file);
		if (readc == -1)
			break;
		counter++;
		if (semicolon_check(line))
			multicmd_hand(line, argv[0], &path, &head);
		else
		{
		f = bltn_chck(line);
		if (f != NULL)
			if (f(line, &head, &path) == 1)
				continue;
		var_set(line, &wordc, &command);
		check = file_exist_exec(command[0]);
		if (exec_handl(check, command, argv[0], &path, wordc, counter))
			continue;
		free_memory(command, wordc);
		}
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
 * sign ints handler
 * @signum: the signal
 * Return: (void)
 */
void sigint_handler(int signum)
{
	free_pathlist(&ptr1);
	free_everything(&ptr2);
	free(buff);
	write(1, "\n", 2);
	signum = 143;
	write(2, "Terminated\n", __strlen("Terminated\n"));
	exit(signum);
}
