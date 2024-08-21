#include "main.h"

/**
 * input - Read a line of text from standard input.
 * @text: A prompt string to display before
 * reading input. If NULL, no prompt is displayed.
 *
 * Return: A pointer to allocated buffer or NULL
 */
char *input(const char *text)
{
	char *buffer = NULL;
	size_t bufferLen = 0;

	if (!text)
		return (NULL);

	if (isatty(0))
	{
		printf("%s ", text);
		fflush(stdout);
	}

	if (getline(&buffer, &bufferLen, stdin) == -1)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}

	return (buffer);
}
