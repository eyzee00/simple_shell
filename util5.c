#include "main.h"
/**
 * commandtok - tokenize our argument
 * split user command in an array
 * @ch: strings
 * @del: delimiter
 * Return: pointer to wordlist
 */
char **commandtok(char *ch, char *del)
{
	int linec = 0, i = 1, char_count = 0;
	char *command = NULL;
	char **commandlist = NULL;

	if (ch == NULL)
		return (NULL);
	linec = line_counter(ch);
	commandlist = malloc(sizeof(char *) * (linec + 1));
	if (commandlist == NULL)
		return (NULL);
	command = _strtok(ch, del);
	if (command != NULL)
	{
	char_count = __strlen(command);
	*commandlist = _calloc(char_count + 2, sizeof(char));
	if (*commandlist == NULL)
	{
		free(commandlist);
		return (NULL);
	}
	fill_row_def(commandlist, 0, command);
	}
	while (i < linec)
	{
		command = _strtok(NULL, del);
		if (command != NULL)
		{
		char_count = __strlen(command);
		*(commandlist + i) = _calloc(char_count + 2, sizeof(char));
		if (*(commandlist + i) == NULL)
		{
			free_memory(commandlist, i);
			return (NULL);
		}
		fill_row_def(commandlist, i, command);
		}
		i++;
	}
	commandlist[i] = NULL;
	return (commandlist);
}
/**
 * arg_err - handles errors in argument mode using options
 * check for possible errors at different options
 * @argv: the argument vector
 * @option: the error code
 * @command: the command if needed
 * @line: the line where the error happened
 * Return: void
 */
void arg_err(char **argv, int option, char **command, int line)
{
	char err[256] = "";

	if (option == -2)
	{
		print_string(argv[0], err);
		print_string(": Usage: ", err);
		print_string(argv[0], err);
		print_string(" FILENAME\n", err);
		write(2, err, __strlen(err));
	}
	else if (option == -1 || option == 0 || option == -5)
	{
		if (option != -5)
			print_string(argv[1], err);
		else
			print_string(argv[0], err);
		print_string(": ", err);
		if (option != -5)
			print_decimal(line + 1, err);
		else
			print_decimal(line, err);
		print_string(": ", err);
		print_string(command[0], err);
		print_string(": ", err);
		print_string("not found\n", err);
		write(2, err, __strlen(err));
	}
	else if (option == 10)
	{
		print_string(argv[0], err);
		print_string(": ", err);
		print_string("0: ", err);
		print_string("cannot open ", err);
		print_string(argv[1], err);
		print_string(": No such file\n", err);
		write(2, err, __strlen(err));
	}
}
/**
  * fill_row_def - fill worldlist pointer with words
  * put words into wordlist pointer
  * @wordlist: pointer
  * @row: wordlist pointer row
  * @word: content to fill
  */
void fill_row_def(char **wordlist, int row, char *word)
{
	int i = 0;

	while (word[i] != 0)
	{
		wordlist[row][i] = word[i];
		i++;
	}
	wordlist[row][i] = '\0';
}
/**
 * _calloc - allocates memory for (nmemb) of elements,
 * each element size in byte is (size)
 * @nmemb: number of elements in the array to be created
 * @size: size of each element in bytes
 * Return: returns (NULL) if nmemb = 0 or size = 0 or
 * if the allocation process fails,
 * returns a void pointer to the memory location otherwise
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *pointer;
	char *set_to_zero;
	unsigned int i;

	if (nmemb == 0 || size == 0)
		return (NULL);
	pointer = malloc(nmemb * size);
	if (pointer == NULL)
		return (NULL);
	set_to_zero = pointer;
	for (i = 0; i < (nmemb * size); i++)
		*(set_to_zero + i) = 0;
	return (pointer);
}
/**
 * _getenv - gets the value of an environment variable
 * values of env inputed
 * @name: the variable name
 * Return: (NULL) if not found, the value otherwise
 */
char *_getenv(const char *name)
{
	int i = 0, j = 0;

	while (environ[i] != NULL)
	{
		if (str_cmp((char *) name, environ[i]))
		{
		while (environ[i][j] != '=')
			j++;
		j++;
		return (environ[i] + j);
		}
		i++;
	}
	return (NULL);
}
