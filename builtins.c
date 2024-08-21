#include "main.h"

static int __exit_status__;

/**
 * set_exit_status - Set exit status code
 * @code: Exit code
 */
void set_exit_status(int code)
{
	__exit_status__ = code;
}

/**
 * aexit - Exit process
 * @arg: Exit status code
 * Return: 1
 */
static int aexit(void *arg)
{
	(void)arg;
	exit(__exit_status__);
}

/**
 * cd - Change the directory of root process
 * @arg: Path of the directory
 * Return: 1 if success or -1
 */
static int cd(void *arg)
{
	char *buffer = NULL;

	if (!arg)
	{
		buffer = getcwd(NULL, 0);
		if (!buffer)
			return (-1);

		arg = buffer;
	}

	if (chdir((char *)arg) == -1)
	{
		if (buffer)
			free(buffer);

		return (-1);
	}

	if (buffer)
		free(buffer);

	return (1);
}

/**
 * env - Print environnment variable
 * @arg: None
 * Return: 1
 */
static int env(void *arg)
{
	size_t i;

	(void)arg;

	for (i = 0; __environ[i]; i++)
		printf("%s\n", __environ[i]);

	return (1);
}

/**
 * get_builtins_command - Get builtins function if exists
 * @tokens: A tokens list include builtins function name and optional arguments
 * Return: 0 if builtins function not found or 1/-1
 */
int get_builtins_command(char **tokens)
{
	int i = 0;

	static struct Command buitlins[] = {
		{"exit", aexit},
		{"env", env},
		{"cd", cd},
		{NULL, NULL},
	};

	for (; buitlins[i].execute; i++)
		if (strcmp(buitlins[i].name, tokens[0]) == 0)
			return (buitlins[i].execute(tokens[1]));

	return (0);
}
