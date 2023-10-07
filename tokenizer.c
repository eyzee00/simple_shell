#include "main.h"
/**
 * tokenizer - tokenize our argument
 * @ch: strings
 * Return: pointer to wordlist
 */
char **tokenizer(char *ch)
{
	int wordc = 0, i = 1, char_count = 0;
	char *word;
	char **wordlist, del[] = " ";

	if (ch == NULL)
		return (NULL);
	wordc = word_count(ch);
	wordlist = malloc(sizeof(char *) * (wordc + 1));
	if (wordlist == NULL)
		return (NULL);
	word = strtok(ch, del);
	char_count = _strlen(word);
	*wordlist = malloc(sizeof(char) * char_count + 1);
	if (*wordlist == NULL)
	{
		free(wordlist);
		return (NULL);
	}
	fill_row(wordlist, 0, word);
	while (i < wordc)
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
	wordlist[i] = NULL;
	return (wordlist);
}
/**
  * word_count - count word in string removing spaces
  * @str: string
  * Return: count of str
  */
int word_count(char *str)
{
	int i = 0, count = 0;
	int check = 0;

	while (*(str + i) != 0)
	{
		while (str[i] != ' ' && str[i] != 0 && str[i] != 10)
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
/**
  * free_memory - free memory
  * @pointer: point to memory to free
  * @n: count of character
  */
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
/**
  * fill_row - fill worldlist pointer with words
  * @wordlist: pointer
  * @row: wordlist pointer row
  * @word: content to fill
  */
void fill_row(char **wordlist, int row, char *word)
{
	int i = 0, j = 0;

	while (word[i] != 0)
	{
		if (word[i] != 10 && word[i] != 32)
		{
			wordlist[row][j] = word[i];
			j++;
		}
		i++;
	}
	wordlist[row][j] = '\0';
}
/**
  * _strlen - count string length
  * @buffer: strings to count
  * Return: string length
  */
int _strlen(char *buffer)
{
	int i = 0, del = 0;

	while (buffer[i] != 0)
	{
		if (buffer[i] == 10 || buffer[i] == 32)
			del++;
		i++;
	}
	return (i - del);
}
