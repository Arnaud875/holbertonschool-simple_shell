#include "main.h"

/**
 * main - Enter fonction of simple shell
 * @argc: Number of arguments
 * @argv: Program arguments
 * Return: 0 if success
 */
int main(int argc, char **argv)
{
	char *user_input;
	char **tokens;

	(void)argc;

	while (1)
	{
		user_input = input("$");

		if (!user_input)
			break;

		tokens = make_tokens(user_input, " \n");
		if (!tokens)
		{
			free(user_input);
			free_all(tokens);
			exit(EXIT_FAILURE);
		}

		execute_command(argv[0], tokens);

		free(user_input);
		free_all(tokens);
	}

	return (0);
}
