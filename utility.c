#include "main.h"

/**
 * free_all - Free all memory in array
 * @array: A string array
 */
void free_all(char **array)
{
	size_t i = 0;

	for (; array[i]; i++)
		free(array[i]);
	free(array);
}

/**
 * make_tokens - Split string with delimiter
 * @input: A string to split
 * @delimiter: Delimiter to split string
 * Return: A array to contains tokens of the string with split the delimiter
 */
char **make_tokens(char *input, const char *delimiter)
{
	size_t j = 0, stringSize = 0, tokensLen = 0;
	char **tokens, *token, *ptr;

	if (!input || !delimiter)
		return (NULL);

	for (ptr = input; *ptr; ptr++)
		if (*ptr == delimiter[0])
			tokensLen++;

	tokens = (char **)malloc((tokensLen + 2) * sizeof(void *));
	if (!tokens)
		return (NULL);

	for (token = strtok(input, delimiter); token;
		 token = strtok(NULL, delimiter))
	{
		stringSize = strlen(token) + 1;
		tokens[j] = (char *)malloc(stringSize * sizeof(char));
		if (!tokens[j])
		{
			free_all(tokens);
			return (NULL);
		}

		strcpy(tokens[j], token);
		j++;
	}

	tokens[j] = NULL;
	return (tokens);
}
