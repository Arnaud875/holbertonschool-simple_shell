#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void free_all(char **array)
{
	size_t i = 0;

	for (; array[i]; i++)
		free(array[i]);
	free(array);
}

char *input(const char *text)
{
	char *buffer = NULL;
	size_t bufferLen = 0;

	if (!text)
		exit(EXIT_FAILURE);

	if (isatty(0))
	{
		printf("%s ", text);
		fflush(stdout);
	}

	if (getline(&buffer, &bufferLen, stdin) == -1)
	{
		if (buffer)
			free(buffer);
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

char **split(char *input, const char *delimiter)
{
	size_t i = 0, j = 0, stringSize = 0;
	size_t tokensLen = 0;
	char **tokens, *token;

	if (!input || !delimiter)
		exit(EXIT_FAILURE);

	for (i = 0; input[i]; i++)
		if (input[i] == *delimiter)
			tokensLen++;

	tokens = (char **)malloc((tokensLen + 2) * sizeof(void *));
	if (!tokens)
		exit(EXIT_FAILURE);

	for (token = strtok(input, delimiter); token;
		 token = strtok(NULL, delimiter))
	{
		stringSize = strlen(token) + 1;
		tokens[j] = (char *)malloc(stringSize * sizeof(char));
		if (!tokens[j])
		{
			free_all(tokens);
			exit(EXIT_FAILURE);
		}

		strcpy(tokens[j], token);
		j++;
	}

	tokens[j] = NULL;
	return (tokens);
}

void aexit(void) { _exit(0); }

void env(void)
{
	size_t i;

	for (i = 0; __environ[i]; i++)
		printf("%s\n", __environ[i]);
}

char *get_executable_path(char *executable)
{
	size_t i = 0, size;
	char *buffer = NULL, *path_copy, *var;

	for (i = 0; __environ[i]; i++)
	{
		if (strncmp(__environ[i], "PATH=", 5) == 0)
		{
			path_copy = strdup(__environ[i] + 5);
			if (!path_copy)
				exit(EXIT_FAILURE);

			for (var = strtok(path_copy, ":"); var; var = strtok(NULL, ":"))
			{
				size = strlen(var) + strlen(executable) + 2;
				buffer = (char *)malloc(size * sizeof(char));
				if (!buffer)
				{
					free(path_copy);
					exit(EXIT_FAILURE);
				}

				strcpy(buffer, var);
				strcat(buffer, "/");
				strcat(buffer, executable);

				if (access(buffer, F_OK) == 0)
				{
					free(path_copy);
					return (buffer);
				}

				free(buffer);
				buffer = NULL;
			}

			free(path_copy);
			break;
		}
	}

	return (NULL);
}

void execute_command(char **tokens)
{
	char *executable_path;
	pid_t proc;

	if (!tokens[0])
		return;

	executable_path = tokens[0];

	if (access(executable_path, F_OK) != 0)
		executable_path = get_executable_path(executable_path);

	if (!executable_path)
	{
		fprintf(stderr, "Command not found: %s\n", tokens[0]);
		return;
	}

	proc = fork();
	if (proc == 0)
	{
		execve(executable_path, tokens, __environ);
		exit(EXIT_FAILURE);
	}
	else if (proc > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("fork");
	}

	if (executable_path != tokens[0])
		free(executable_path);
}

int main(void)
{
	char *userInput;
	char **tokens;

	while (1)
	{
		userInput = input("$");
		tokens = split(userInput, " \n");
		printf("%s\n", tokens[0]);

		if (!tokens[0])
		{
			free(userInput);
			free_all(tokens);
			continue;
		}

		if (strcmp(tokens[0], "exit") == 0)
		{
			free(userInput);
			free_all(tokens);
			aexit();
		}
		else if (strcmp(tokens[0], "env") == 0)
			env();
		else
			execute_command(tokens);

		free(userInput);
		free_all(tokens);
	}

	return (0);
}
