#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int word_count(char *str);
void free_memory(char **pointer, int n);

int main()
{
	int n = 0;
	int i = 1;
	int char_count = 0;
	char *word;
	char ch[] = "       ghjjh      hgjhk        huuguuh      ";
	char **wordlist;
	char *del = " ";
	int g = 0;
	
	n = word_count(ch);
	wordlist = malloc(sizeof(char *) * n);
	if (wordlist == NULL)
		return (1);
	word = strtok(ch, del);
	char_count = strlen(word);
	*wordlist = malloc(sizeof(char) * char_count + 1);
	if (*wordlist == NULL)
	{
		free(wordlist);
		return (1);
	}
	while (word[g] != 0)
	{
		wordlist[0][g] = word[g];
		g++;
	}
	wordlist[0][g] = 0;
	while (i < n)
	{
		word = strtok(NULL, del);
		char_count = strlen(word);
		*(wordlist + i) = malloc(sizeof(char) * char_count + 1);
		if (*(wordlist + i) == NULL)
		{
			free_memory(wordlist, i);
			return (1);
		}
		g = 0;
		while (word[g] != 0)
		{
			wordlist[i][g] = word[g];
			g++;
		}
		wordlist[i][g] = 0;
		i++;
	}
	i = 0;
	while (i < n)
	{
		printf("%s\n", *(wordlist + i));
		i++;
	}
	free_memory(wordlist, n);
	return (0);
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
