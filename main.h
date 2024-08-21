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
 * struct Command - A structure of builtins functions
 * @name: Name of builtins function
 * @execute: A pointer to builtins function
 */
struct Command
{
	char *name;
	int (*execute)(void *params);
};

char *input(const char *text);
char *get_executable_path(char *executable);

char **make_tokens(char *input, const char *delimiter);
void free_all(char **array);

int execute_command(const char *file_name, char **tokens);

void set_exit_status(int code);
int get_builtins_command(char **token);

#endif
