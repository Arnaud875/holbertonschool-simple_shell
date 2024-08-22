#include "main.h"

/**
 * run_process_command - Execute command in child process
 * @executable_path: Path of executable
 * @tokens: A tokens list contains executable path and arguments
 * Return: 0 if sucesss or -1
 */
static int run_process_command(const char *executable_path, char **tokens)
{
	int process_status;
	pid_t process;

	process = fork();
	if (process == -1)
		return (-1);

	if (process == 0)
	{
		execve(executable_path, tokens, __environ);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(process, &process_status, 0);
		if (WIFEXITED(process_status))
			return (WEXITSTATUS(process_status));
		else
			return (-1);
	}

	return (0);
}

/**
 * execute_command - Check if command exists or builtins and execute
 * @file_name: Name of program
 * @tokens: A tokens list
 * Return: Exit code of child process or 0 if is builtins function
 */
int execute_command(const char *file_name, char **tokens)
{
	int status;
	char *executable_path, *temp;

	if (!tokens[0])
		return (-1);

	executable_path = strdup(tokens[0]);

	if (access(executable_path, F_OK) != 0)
	{
		temp = get_executable_path(executable_path);
		free(executable_path);
		executable_path = temp;
	}

	if (!executable_path)
	{
		fprintf(stderr, "%s: No such file or directory\n", file_name);
		free(executable_path);

		get_shell_instance()->exit_code = 127;
		return (-1);
	}

	status = run_process_command(executable_path, tokens);
	get_shell_instance()->exit_code = status;
	free(executable_path);

	return (status);
}
