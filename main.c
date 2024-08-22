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
int main(int argc, char **argv)
{
	get_shell_instance()->is_interactive = isatty(STDIN_FILENO);
	get_shell_instance()->file_name = argv[0];
	signal(SIGINT, handle_sigint);

	while (1)
	{
		if (argc == 1)
		{
			get_shell_instance()->user_input = input();
			get_shell_instance()->tokens =
				make_tokens(get_shell_instance()->user_input);
		}
		else
			get_shell_instance()->tokens = (argv + 1);

		if (!get_shell_instance()->tokens)
		{
			free(get_shell_instance()->user_input);
			exit(EXIT_FAILURE);
		}

		if (!get_builtin_command(get_shell_instance()->tokens))
			execute_command(get_shell_instance()->tokens);

		if (argc != 1)
			exit(get_shell_instance()->exit_code);

		free(get_shell_instance()->user_input);
		free_all(get_shell_instance()->tokens);
	}

	return (0);
}
