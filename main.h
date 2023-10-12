#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>
#define LEN 1256
/*global variables*/
extern char **environ;
static void *target;
/**
 * struct builtin_s - defines a builtin element
 * @cmdname: builtin name
 * @func: the assossiated function
 */
typedef struct builtin_s
{
	char *cmdname;
	int (*func)(char **env, char *buffer);
} builtin_t;

/*count functions*/
int line_counter(char *str);
int _strlen(char *buffer);
int __strlen(char *buffer);
int word_count(char *str);
int _strlentok(char *str);
int string_count(char **env);

/*general purpose functions*/
void free_memory(char **pointer, int n);
char **tokenizer(char *ch);
void fill_row(char **wordlist, int row, char *word);
char *_memcpy(char *src, char *dest, unsigned int n);
int file_exist_exec(char *command);
void print_string(char *string, char *buffer);
void addto_buff(char *buffer, char c);
void error_handler(char *argv, char *command, int counter, int option);
int str_cmp(char *s1, char *s2);
void print_decimal(int n, char *buffer);
int _atoi(char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_setenv(char *name, char *value);
int equal_check(char *str);
void set_entry(char *buffer, char *name, char *value);
char *_strncpy(char *dest, char *src, int n);
void free_env(char **environ, int n);

/*mode handler functions*/
void interactive_mode(char *argv);
void argument_mode(int *status, pid_t sub_id, char **argv);
void noninteractive_mode(FILE *file, int *status, char *argv);

/*built-in handler functions*/
int (*builtin_check(char *buffer))(char **env, char *buffer);
int exit_handler(char **env, char *buffer);
int env_handler(char **env, char *buffer);
int emptycmd_handler(char **env, char *buffer);
int space_check(char *buffer);

#endif
