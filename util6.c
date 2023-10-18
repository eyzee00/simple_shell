#include "main.h"
#include <dirent.h>
/**
 * add_node_end_path - adds a node to the pathlist
 * add to linkedlist
 * @head: the address of the head pointer
 * @dirname: the name of the directory to add
 * Return: the address of the new element
 */
path_t *add_node_end_path(path_t **head, char *dirname)
{
	path_t *node = malloc(sizeof(path_t));
	path_t *iter = *head;

	if (node == NULL)
		return (NULL);
	node->name = _calloc(sizeof(char),  __strlen(dirname) + 1);
	if (node->name == NULL)
		return (NULL);
	_strncpy(node->name, dirname, strlen(dirname));
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
 * executable_locator - checks if the file given exists in the pathlist
 * @head: the head of the pathlist
 * @command: the command entered by the user
 * Return: (void)
 */
int executable_locator(path_t **head, char **command)
{
	path_t *iter = *head;
	struct dirent *dir_entry;
	int check = 0, size = 0;
	char *newcommand;

	if (iter == NULL)
		return (0);
	while (iter != NULL)
	{
		DIR *ptr = opendir(iter->name);

		if (ptr == NULL)
		{
			iter = iter->next;
			continue;
		}
		dir_entry = readdir(ptr);
		while (dir_entry != NULL)
		{
			if (str_cmp_df(dir_entry->d_name, command[0]) == 0)
			{
			check = 1;
			break;
			}
			dir_entry = readdir(ptr);
			check = 0;
		}
		if (check == 1)
		{
			size = __strlen(iter->name) + __strlen(command[0]) + 2;
			newcommand = _calloc(sizeof(char), size);
			command[0] = fill_string(iter->name, command[0], newcommand);
			closedir(ptr);
			return (1);
		}
		closedir(ptr);
		iter = iter->next;
	}
	return (-1);
}
/**
 * path_creator- creates a linked list of PATH directories
 * @head: the head of the pathlist
 * Return: the first element in the pathlist, or (NULL) if PATH is empty
 */
path_t *path_creator(path_t **head)
{
	char *holder, *buffer;

	holder = _getenv("PATH");
	if (holder == NULL || *holder == 0)
		return (NULL);
	buffer = _calloc(sizeof(char), __strlen(holder) + 1);
	if (buffer == NULL)
		return (NULL);
	_strncpy(buffer, holder, __strlen(holder));
	holder = _strtok(buffer, ":");
	add_node_end_path(head, holder);
	while (holder != NULL)
	{
		holder = _strtok(NULL, ":");
		if (holder == NULL)
			continue;
		add_node_end_path(head, holder);
	}
	free(buffer);
	return (*head);
}
/**
 * free_pathlist - frees a pathlist
 * @head: the address of the first element in the list
 * Return: (void)
 */
void free_pathlist(path_t **head)
{
	path_t *iter = *head, *placeholder;

	if (iter == NULL)
		return;
	while (iter != NULL)
	{
		placeholder = iter;
		iter = iter->next;
		free(placeholder->name);
		free(placeholder);
	}
	head = NULL;
}
