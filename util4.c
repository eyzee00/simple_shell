#include "main.h"
/**
 * alloclist_init - initializes a alloclist
 * Return: (NULL)
 */
alloclist_t *alloclist_init(void)
{
	return (NULL);
}
/**
 * add_node_end - Adds a node to the end of the list
 * @head: the address of the list
 * @address: the data contained in the node
 * Return: the address of the new node added, (NULL)
 * if allocation fails
 */
alloclist_t *add_node_end(alloclist_t **head, void *address)
{
	alloclist_t *node = malloc(sizeof(alloclist_t));
	alloclist_t *iter = *head;

	if (node == NULL)
		return (NULL);
	node->address = (void *) address;
	node->next = NULL;
	if (iter == NULL)
	{
		*head = node;
		return (node);
	}
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = node;
	return (node);
}
/**
 * free_everything - frees the memory allocated
 * @head: the head of the list
 * Return: (void)
 */
void free_everything(alloclist_t **head)
{
	alloclist_t *ptr = *head, *placeholder;

	if (ptr == NULL)
		return;
	while (ptr != NULL)
	{
		placeholder = ptr;
		ptr = ptr->next;
		free(placeholder->address);
		free(placeholder);
	}
	*head = NULL;
}
/**
 * _unsetenv - unsets an environment variable
 * @name: name of the variable to set
 * @head: head of the alloc list
 * Return: (-1) on failure, (1) on success
 */
int _unsetenv(char *name, alloclist_t **head)
{
	unsigned int i = 0, size = 0, check = 0, j = 0;
	char **mod_env, buff[256];
	char **ptr = environ;

	if (name == 0 || *name == 0)
		return (-1);
	if (equal_check(name))
		return (-1);
	while (*(environ + i) != NULL)
	{
		_strncpy(buff, ptr[i], _strlentok(ptr[i]));
		if (str_cmp(buff, name))
		{
			check = i;
			break;
		}
		i++;
	}
	i = 0;
	if (check)
	{
		size = string_count(environ);
		mod_env = malloc(size * sizeof(char *));
		if (mod_env == NULL)
			return (0);
		for (i = 0; j < size - 1; j++, i++)
		{
		if (j != check)
			mod_env[j] = environ[i];
		else
		{
			i++;
			mod_env[j] = environ[i];
		}
		}
		mod_env[size - 1] = NULL;
		add_node_end(head, mod_env);
		environ = mod_env;
	}
	return (1);
}
/**
 * unsetenv_handler - handles the unset builtin
 * @buffer: the user command
 * @head: the head of the alloclist
 * @path: the head of the pathlist
 * Return: always (1)
 */
int unsetenv_handler(char *buffer, alloclist_t **head, path_t **path)
{
	int option = 0, wordc = word_count(buffer);
	char err[256] = "", **command;

	command = tokenizer(buffer);
	path = (path_t **) path;
	if (wordc != 2)
	{
		print_string(command[0], err);
		print_string(": Usage: unsetenv VARNAME\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	option = _unsetenv(command[1], head);
	if (option == -1)
	{
		print_string(command[0], err);
		print_string(": bad variable name\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	if (option == 0)
	{
		print_string(command[0], err);
		print_string(": Memory allocation failed\n", err);
		write(2, err, __strlen(err));
		free_memory(command, wordc);
		return (-1);
	}
	free_memory(command, wordc);
	return (-1);
}
