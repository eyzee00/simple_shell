#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#define LEN 256

extern char **environ;

int word_count(char *str);

void free_memory(char **pointer, int n);

char **tokenizer(char *ch);

void fill_row(char **wordlist, int row, char *word);

int _strlen(char *buffer);

char *_memcpy(char *src, char *dest, unsigned int n);

#endif
