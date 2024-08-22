#include "main.h"

/**
 * input - Read a line of text from standard input.
 * Return: A pointer to allocated buffer or NULL
 */
char *input()
{
	char *buffer = NULL;
	size_t bufferLen = 0;

	if (get_shell_instance()->is_interactive)
	{
		printf("$ ");
		fflush(stdout);
	}

	if (getline(&buffer, &bufferLen, stdin) == -1)
	{
		if (buffer)
			free(buffer);

		if (!get_shell_instance()->is_interactive)
			exit(get_shell_instance()->exit_code);

		exit(get_shell_instance()->exit_code);
	}

	return (buffer);
}

/**
 * trim - test
 * @text: ne
 * Return: oui
 */
int trim(char *text)
{
	while (*text)
	{
		if (*text == ' ' || *text == '\n')
			text++;
		else
			return (1);
	}

	return (0);
}
