#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>
#define LEN 256

extern char **environ;

int word_count(char *str);
void free_memory(char **pointer, int n);
char **tokenizer(char *ch);
void fill_row(char **wordlist, int row, char *word);
int _strlen(char *buffer);
int __strlen(char *buffer);
char *_memcpy(char *src, char *dest, unsigned int n);
void one_argc(int status, pid_t sub_id, char **argv);
int file_exist_exec(char *command);
void print_string(char *string, char *buffer);
void addto_buff(char *buffer, char c);
void error_handler(char *argv, char *command);
#endif