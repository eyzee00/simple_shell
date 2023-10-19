#include "main.h"
/**
 * lexec_handl - handles command execution
 * @check: the file status
 * @cmd: the command entered by the user
 * @argv: name of the shell
 * @wdc: how many words in the command
 * @p: pathlist
 * @c: line count
 * Return: (1) to continue, (0) to resume
 */
int lexec_handl(int check, char **cmd, char *argv, path_t **p, int wdc, int c)
{
	int check2 = 0;

	if (check == 0)
	{
		error_handler(argv, cmd[0], c, -1);
		free_memory(cmd, wdc);
		return (1);
	}
	if (check == 1 || check == -1)
	{
		if (check == -1)
		{
			check2 = executable_locator(p, cmd);
			if (check2 == -1 || check2 == 0)
			{
				error_handler(argv, cmd[0], c, check);
				free_memory(cmd, wdc);
				return (1);
			}
		}
		if (logicexecutor(cmd) != 0)
		{
			free_memory(cmd, wdc);
			return (1);
		}
	}
	return (0);
}
/**
 * initializer - initializes some necessary variables
 * @buffer: user input
 * @cmdc: command count
 * @check: case
 * @del: delimiter
 * Return: (void)
 */
void initializer(char *buffer, int *cmdc, int *check, char *del)
{
	*cmdc = logic_counter(buffer);
	*check = get_del(buffer);
	set_delimiter(*check, del);
}
