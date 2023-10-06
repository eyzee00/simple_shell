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
	int readc = 0, check = 0, wordc = 0, exec = 0, status;

	if (argc != 1)
	{
		sub_id = fork();
		if (sub_id == 0)
			execve(argv[1], argv + 1, environ);
		else
			wait(&status);
	}
	while (readc != -1)
	{
		printf("currentuser$: ");
		readc = getline(&buffer, &buffsz, stdin);
		if (readc == -1)
			break;
		sub_id = fork();
		wordc = word_count(buffer);
		if (sub_id == 0)
		{
			check = 1;
			command = tokenizer(buffer);
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
		if (check)
		{
			free(buffer);
			free_memory(command, wordc);
		}
		check = 0;
	}
	free(buffer);
	return (0);
}
