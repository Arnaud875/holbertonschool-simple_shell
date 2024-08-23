#include "main.h"
/**
 * input_user - function for input user in shell.
 * @void: null.
 * Return: ptr_line.
 */
char *input_user(void)
{
	char *ptr_line = NULL;
	size_t ct = 0;
	ssize_t rd;


	if (isatty(STDIN_FILENO))
	{
		printf("$ ");
	}

	rd = getline(&ptr_line, &ct, stdin);

	if (rd == -1)
	{
		perror("Error reading input");
		free(ptr_line);
		exit(EXIT_FAILURE);
	}
	return (ptr_line);
}
