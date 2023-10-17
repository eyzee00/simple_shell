#include "main.h"
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
/**
 * __strlen - classic strlen
 * @buffer: the buffer to operate on
 * Return: the length of buffer
 */
int __strlen(char *buffer)
{
	int i = 0;

	while (buffer[i] != 0)
		i++;
	return (i);
}
/**
 * line_counter - countes the number of lines
 * @str: the string to operate on
 * Return: the line count
 */
int line_counter(char *str)
{
	int i = 0, counter = 0;

	while (*(str + i) != 0)
	{
		if (*(str + i) == 10 && str[i - 1] != 10)
			counter++;
		i++;
	}
	return (counter);
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
		while (str[i] != 0 && str[i] != 32 && str[i] != 10)
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
 * _strlentok - calculates the length of the variable name
 * @str: the string to mesure
 * Return: the length of the string
 */
int _strlentok(char *str)
{
	int i = 0;

	while (str[i] != 0 && str[i] != 61)
		i++;
	return (i);
}
