#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * struct BuiltinCommand - A structure of builtins functions
 * @name: Name of builtins function
 * @execute: A pointer to builtins function
 */
typedef struct BuiltinCommand
{
	char *name;
	int (*execute)(char *arg);
} BuiltinCommand_t;

/**
 * struct Shell - A structure of shell
 * @file_name: Name of program
 * @user_input: A buffer to stock stdin string
 * @tokens: Split user_input with delimiter
 * @exit_code: Exit code of shell
 * @is_interactive: If is interactive mode or no-interactive mode
 */
typedef struct Shell
{
	char *file_name;
	char *user_input;
	char **tokens;
	int exit_code;
	int is_interactive;
} Shell_t;

int trim(char *text);
char *input();
char *get_executable_path(char *executable);

char **make_tokens(char *input);
void free_all(char **array);

int execute_command(char **tokens);

Shell_t *get_shell_instance(void);
int shell_exit(int code);
int get_builtin_command(char **token);

#endif
