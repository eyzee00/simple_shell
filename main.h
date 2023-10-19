#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#define LEN 1256
/*global variables*/
extern char **environ;
/**
 * struct alloclist_s - a linked list containing memory addresses
 * to free
 * it save time
 * @address: address to free
 * @next: pointer to the next element inn the list
 */
typedef struct alloclist_s
{
	void *address;
	struct alloclist_s *next;
} alloclist_t;
/**
 * struct path_s - defines a path directory
 * path object
 * @name: the name of the directory
 * @next: a pointer to the next directory in the PATH
 */
typedef struct path_s
{
	char *name;
	struct path_s *next;
} path_t;
/**
 * struct builtin_s - defines a builtin element
 * @cmdname: builtin name
 * @func: the assossiated function
 */
typedef struct builtin_s
{
	char *cmdname;
	int (*func)(char *buffer, alloclist_t **head, path_t **path);
} builtin_t;
/*functions*/
alloclist_t *alloclist_init(void);

/*count functions*/
int line_counter(char *str);
int _strlen(char *buffer);
int __strlen(char *buffer);
int word_count(char *str);
int _strlentok(char *str);
int string_count(char **env);
int cmd_counter(char *str);

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
int _setenv(char *name, char *value, alloclist_t **head);
int equal_check(char *str);
void set_entry(char *buffer, char *name, char *value);
char *_strncpy(char *dest, char *src, int n);
void free_env(char **environ, int n);
int space_check(char *buffer);
void allocfreer(void);
alloclist_t *alloclist_init(void);
void free_everything(alloclist_t **head);
alloclist_t *add_node_end(alloclist_t **head, void *address);
int _unsetenv(char *name, alloclist_t **head);
char **commandtok(char *ch, char *del);
char *filetobuff(char **argv, alloclist_t **head);
void arg_err(char **argv, int option, char **command, int line);
void fill_row_def(char **wordlist, int row, char *word);
void *_calloc(unsigned int nmemb, unsigned int size);
int str_cmp_df(char *s1, char *s2);
char *fill_string(char *dirname, char *command, char *newcommand);
void executor(char **command);
int alpha_check(char *str);
void sigint_handler(int sig);
void ultimate_free(path_t **path, alloclist_t **head, char *buffer);
void exit_arg_err(char *argv, char **command, int option);
void var_set(char *buffer, int *check, char ***command);
int exec_handl(int check, char **cmd, char *argv, path_t **p, int wdc, int c);
int semicolon_check(char *str);
char **cmdtok(char *ch);
void fill_row_cmd(char **wordlist, int row, char *word);
void multicmd_hand(char *buffer, char *argv, path_t **p, alloclist_t **head);
char *_strtok(char *str, char *delimiter);
void replacer(alloclist_t **head, char *buff3, char **command, int wordc);
char **logictok(char *ch, char *del);
int logic_check(char *str);
void fill_row_logic(char **wordlist, int row, char *word);
int get_del(char *buffer);
int logic_counter(char *str);
void logic_hand(char *buffer, char *argv, path_t **p, alloclist_t **head);
int logicexecutor(char **command);
int lexec_handl(int check, char **cmd, char *argv, path_t **p, int wdc, int c);
void set_delimiter(int check, char *del);
void initializer(char *buffer, int *cmdc, int *check, char *del);

/*mode handler functions*/
void interactive_mode(char *argv);
void argument_mode(char **argv);
void noninteractive_mode(FILE *file, char **argv);

/*built-in handler functions*/
int (*bltn_chck(char *buff))(char *buffer, alloclist_t **head, path_t **path);
int exit_handler(char *buffer, alloclist_t **head, path_t **path);
int env_handler(char *buffer, alloclist_t **head, path_t **path);
int emptycmd_handler(char *buffer, alloclist_t **head, path_t **path);
int setenv_handler(char *buffer, alloclist_t **head, path_t **path);
int unsetenv_handler(char *buffer, alloclist_t **head, path_t **path);
int cd_handler(char *buffer, alloclist_t **head, path_t **path);
void cd_err(char **command, char *argv, int wordc);

/*PATH handler functions*/
char *_getenv(const char *name);
path_t *add_node_end_path(path_t **head, char *dirname);
void free_pathlist(path_t **head);
int executable_locator(path_t **head, char **command);
path_t *path_creator(path_t **head);

#endif
