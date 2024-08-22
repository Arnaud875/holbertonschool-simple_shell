#include "main.h"

static Shell_t shell_instance = {
	NULL,
	NULL,
	NULL,
	0,
	0,
};

/**
 * get_shell_instance - Get shell instance
 * Return: shell instance
 */
Shell_t *get_shell_instance(void)
{
	return (&shell_instance);
}

/**
 * shell_exit - Exit process and free shell
 * @code: Exit code
 * Return: 1
 */
int shell_exit(int code)
{
	if (get_shell_instance()->user_input)
		free(get_shell_instance()->user_input);
	if (get_shell_instance()->tokens)
		free_all(get_shell_instance()->tokens);

	exit(code);
}

/**
 * cd - Change the directory of root process
 * @arg: Path of the directory
 * Return: 1 if success or -1
 */
static int cd(char *arg)
{
	char *buffer = NULL;

	if (!arg)
	{
		buffer = getcwd(NULL, 0);
		if (!buffer)
			shell_exit(-1);

		arg = buffer;
	}

	if (chdir((char *)arg) == -1)
	{
		if (buffer)
			free(buffer);

		get_shell_instance()->exit_code = 2;
		return (1);
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
static int env(char *arg)
{
	size_t i;
	(void)arg;

	for (i = 0; __environ[i]; i++)
		printf("%s\n", __environ[i]);

	return (1);
}

/**
 * get_builtin_command - Get builtins function if exists
 * @tokens: A tokens list include builtins function name and optional arguments
 * Return: 0 if builtins function not found or 1/-1
 */
int get_builtin_command(char **tokens)
{
	int i;

	BuiltinCommand_t builtins[] = {
		{"env", env},
		{"cd", cd},
		{NULL, NULL},
	};

	if (strcmp(tokens[0], "exit") == 0)
		shell_exit(shell_instance.exit_code);

	for (i = 0; builtins[i].name != NULL; i++)
		if (strcmp(builtins[i].name, tokens[0]) == 0)
			return (builtins[i].execute(tokens[1]));

	return (0);
}
