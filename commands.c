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
		perror("Error execute in child process");
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
 * find_executable_path - Get executable path by name
 * @executable: Executable name of path
 * Return: Path of executable or executable argument
 */
char *find_executable_path(char *executable)
{
	char *temp;

	if (access(executable, F_OK) != 0)
	{
		temp = get_executable_path(executable);
		free(executable);
		executable = temp;
	}

	return (executable);
}

/**
 * execute_command - Check if command exists or builtins and execute
 * @tokens: A tokens list
 * Return: Exit code of child process or 0 if is builtins function
 */
int execute_command(char **tokens)
{
	int status;
	char *executable_path;

	if (!tokens[0])
		return (-1);

	executable_path = find_executable_path(strdup(tokens[0]));
	if (!executable_path)
	{
		if (get_shell_instance()->is_interactive)
			fprintf(stderr, "%s: No such file or directory\n",
					get_shell_instance()->file_name);
		else
			fprintf(stderr, "%s: 1: %s: not found\n",
					get_shell_instance()->file_name, tokens[0]);

		free(executable_path);
		get_shell_instance()->exit_code = 127;
		return (-1);
	}

	status = run_process_command(executable_path, tokens);
	get_shell_instance()->exit_code = status;
	free(executable_path);

	return (status);
}
