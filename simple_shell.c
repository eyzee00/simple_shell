#include "main.h"
/**
 * main - entry point of our shell
 * @argc: argumen count
 * @argv: argument vector
 * Return: (0) on success
 */
int main(int argc, char **argv)
{
	pid_t sub_id = 0;
	int status;

	if (!isatty(0))
	{
		noninteractive_mode(stdin, &status, argv[0]);
		return (0);
	}
	if (argc != 1)
	{
		argument_mode(&status, sub_id, argv);
		return (0);
	}
	interactive_mode(argv[0]);
	return (0);
}
