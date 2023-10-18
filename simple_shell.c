#include "main.h"
/**
 * main - entry point of our shell
 * @argc: argumen count
 * @argv: argument vector
 * Return: (0) on success
 */
int main(int argc, char **argv)
{
	if (argc != 1)
	{
		argument_mode(argv);
		return (0);
	}
	if (!isatty(0))
	{
		noninteractive_mode(stdin, argv);
		return (0);
	}
	interactive_mode(argv[0]);
	return (0);
}
