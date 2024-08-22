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
 * multiple_execute - Execute multiple function
 * @tokens: A tokens list
 * Return: Status code of child process
 */
int multiple_execute(char **tokens)
{
	size_t i = 0;
	char *executable_path;
	char *exec_tokens[] = {NULL, NULL};

	for (; tokens[i]; i++)
	{
		executable_path = get_executable_path(tokens[i]);
		if (executable_path)
		{
			exec_tokens[0] = executable_path;
			if (run_process_command(executable_path, exec_tokens) == -1)
			{
				free(executable_path);
				return (-1);
			}
		}
		else
		{
			free(executable_path);
			return (-1);
		}

		free(executable_path);
	}

	return (0);
}

/**
 * execute_command - Check if command exists or builtins and execute
 * @tokens: A tokens list
 * Return: Exit code of child process or 0 if is builtins function
 */
int execute_command(char **tokens)
{
	int status;
	char *executable_path, *possible_executable;

	if (!tokens[0])
		return (-1);

	executable_path = find_executable_path(strdup(tokens[0]));
	if (!executable_path)
	{
		fprintf(stderr, "%s: No such file or directory\n",
				get_shell_instance()->file_name);
		free(executable_path);
		get_shell_instance()->exit_code = 127;
		return (-1);
	}

	if (tokens[1] != NULL)
	{
		possible_executable = find_executable_path(strdup(tokens[1]));
		if (possible_executable)
		{
			free(possible_executable);
			free(executable_path);
			return (multiple_execute(tokens));
		}
	}

	status = run_process_command(executable_path, tokens);
	get_shell_instance()->exit_code = status;
	free(executable_path);

	return (status);
}
