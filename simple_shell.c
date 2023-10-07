#include "main.h"
#include <errno.h>

/**
 * main - entry point of our shell
 * @argc: argumen count
 * @argv: argument vector
 * Return: (0) on success
 */
int main(int argc, char **argv)
{
	pid_t sub_id = 0;
	char **command = NULL, *buffer = NULL;
	size_t buffsz = (size_t)LEN;
	int readc = 0, wordc = 0, exec = 0, status;
	int check;

	if (argc != 1)
		one_argc(status, sub_id, argv);
	while (readc != -1)
	{
		printf("currentuser$: ");
		readc = getline(&buffer, &buffsz, stdin);
		if (readc == -1)
			break;
		wordc = word_count(buffer);
		command = tokenizer(buffer);
		check = file_exist_exec(command[0]);
		if (check == 1)
		{
			sub_id = fork();
			if (sub_id == 0)
			{
				exec = execve(command[0], command, environ);
				if (exec == -1)
				{
					printf("The program %s not found\n", command[0]);
					free_memory(command, wordc);
					free(buffer);
					exit(99);
				}
			}
			else
				wait(&status);
		}
		else
			error_handler(command[0], check);
		free_memory(command, wordc);
	}
	free(buffer);
	return (0);
}
/**
  * one_argc - helper function
  * @status: status
  * @sub_id: id
  * @argv: arg vector
  */
void one_argc(int status, pid_t sub_id, char **argv)
{
	sub_id = fork();
	if (sub_id == 0)
	{
		execve(argv[1], argv + 1, environ);
	}
	else
		wait(&status);
}
/**
  * file_exist - file exit & executable
  * @command: user command
  * Return: 1 for success -1 if faill
  */
int file_exist_exec(char *command)
{
	if (access(command, F_OK) != -1)
	{
		if (access(command, X_OK) == 0)
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}
/**
  * error_handler - handle error output
  * @command: user command
  * @error: file_exist return value
  */
void error_handler(char *command, int error)
{
	if (error == -1)
		perror("file not exist");
	else
		perror("file not executable");
}
