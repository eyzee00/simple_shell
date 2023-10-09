#include "main.h"
/**
 * print_decimal - adds an integer to the buffer
 * @n: the number to be printed
 * @buffer: buffer to append
 * Return: void
 */
void print_decimal(int n, char *buffer)
{
	unsigned int number;
	char curr_char;

	if (n < 0)
	{
		n = -n;
		addto_buff(buffer, '-');
	}

	number = (unsigned int) n / 10;
	if (number)
		print_decimal(number, buffer);
	curr_char = (unsigned int) n % 10 + 48;
	addto_buff(buffer, curr_char);
}
