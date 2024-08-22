#include "main.h"

/**
 * handle_sigint - Intercept signal (Ctrl+C)
 * @sig: Signal code
 */
void handle_sigint(int sig)
{
	(void)sig;

	if (get_shell_instance()->user_input)
		free(get_shell_instance()->user_input);
	exit(get_shell_instance()->exit_code);
}

/**
 * main - Enter fonction of simple shell
 * @argc: Number of arguments
 * @argv: Program arguments
 * Return: 0 if success
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	get_shell_instance()->is_interactive = isatty(STDIN_FILENO);
	signal(SIGINT, handle_sigint);

	while (1)
	{
		get_shell_instance()->user_input = input();
		get_shell_instance()->tokens = make_tokens(get_shell_instance()->user_input);

		if (!get_shell_instance()->tokens)
		{
			free(get_shell_instance()->user_input);
			exit(EXIT_FAILURE);
		}

		if (!get_builtin_command(get_shell_instance()->tokens))
			execute_command(argv[0], get_shell_instance()->tokens);

		free(get_shell_instance()->user_input);
		free_all(get_shell_instance()->tokens);
	}

	return (0);
}
