#include "main.h"
/**
 * tokenizer - tokenize our argument
 * @ch: strings
 * Return: pointer to wordlist
 */
char **tokenizer(char *ch)
{
	int n = 0, i = 1, char_count = 0, g = 0;
	char *word;
	char **wordlist, *del = " ";

	if (ch == NULL)
		return (NULL);
	n = word_count(ch);
	wordlist = malloc(sizeof(char *) * n);
	if (wordlist == NULL)
		return (NULL);
	word = strtok(ch, del);
	char_count = strlen(word);
	*wordlist = malloc(sizeof(char) * char_count + 1);
	if (*wordlist == NULL)
	{
		free(wordlist);
		return (NULL);
	}
	fill_row(wordlist, 0, word);
	while (i < n)
	{
		word = strtok(NULL, del);
		char_count = strlen(word);
		*(wordlist + i) = malloc(sizeof(char) * char_count + 1);
		if (*(wordlist + i) == NULL)
		{
			free_memory(wordlist, i);
			return (NULL);
		}
		fill_row(wordlist, i, word);
		i++;
	}
	return (wordlist);
}

int word_count(char *str)
{
	int i = 0, count = 0;
	int check = 0;

	if (str == 0)
		return (-1);
	if (*str == 0)
		return (0);
	while (str[i] != 0)
	{
		while (str[i] != ' ' && str[i] != 0)
		{
			check = 1;
			i++;
		}
		if (check == 1)
			count++;
		i++;
		check = 0;
	}
	return (count);
}
void free_memory(char **pointer, int n)
{
	int i = 0;

	while (i < n)
	{
		free(*(pointer + i));
		i++;
	}
	free(pointer);
}

void fill_row(char **wordlist, int row, char *word)
{
	int i;

	for (i = 0; word[i] != 0; i++)
	{
		wordlist[row][i] = word[i];
	}
	wordlist[row][i] = '\0';
}
