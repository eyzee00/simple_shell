#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
extern char **environ;
int main(void)
{
	/* create variables */
	pid_t current_pid;
	pid_t child_pid;
	int status;
	int i;


	/* creating arguement factor */
	char *argv[] = {"/bin/ls","-l", "/tmp", NULL};

	/* create five child process*/
	for ( i = 0; i < 5; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			printf("Error \n");
			exit(1);
		}
		if (child_pid == 0)
		{
			execve(argv[0], argv, environ);
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
