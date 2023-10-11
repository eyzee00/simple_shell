#include "main.h"
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
	int readc = 0, wordc = 0, status;
	int check;
	int (*f)(char **env, char *buffer);

	while (readc != -1)
	{
		printf("($): ");
		readc = getline(&buffer, &buffsz, stdin);
		if (readc == -1)
			break;
		f = builtin_check(buffer);
		if (f != NULL)
			if (f(environ, buffer))
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
	free(buffer);
}
/**
  * argument_mode - helper function
  * @status: status:wait
  * @sub_id: id
  * @argv: arg vector
  */
void argument_mode(int *status, pid_t sub_id, char **argv)
{
	int check, exec;

	check = file_exist_exec(argv[1]);
	if (check == 1)
	{
		sub_id = fork();
		if (sub_id == 0)
		{
			exec = execve(argv[1], argv + 1, environ);
			if (exec == -1)
			{
				exit(99);
			}
		}
		else
			wait(status);
	}
	else
		error_handler(argv[0], argv[1], 1, check);
}
/**
 * noninteractive_mode - handles the output written into the stdin of the shell
 * by another program i.e(pipes and redirections)
 * @file: the standard input stream, or another file
 * @status: the status of the child process
 * @argv: the name of the shell program
 */
void noninteractive_mode(FILE *file, int *status, char *argv)
{
	pid_t child_id;
	char *line = 0;
	char **command;
	size_t buffsz = (size_t) LEN;
	int wordc, readc = 0, counter = 0, check;
	int (*f)(char **env, char *buffer);

	while (readc != -1)
	{
		readc = getline(&line, &buffsz, file);
		if (readc == -1)
			break;
		counter++;
		f = builtin_check(line);
		if (f != NULL)
		{
			if (f(environ, line))
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
			error_handler(argv, command[0], counter, check);
		free_memory(command, wordc);
	}
	free(line);
}
