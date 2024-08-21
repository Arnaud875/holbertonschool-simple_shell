#include "main.h"

/**
 * if_executable_exist - Check if executable exists
 * @token: Value of variable in PATH environnement
 * @executable: Name of executable
 * Return: Path of executable or NULL
 */
static char *if_executable_exist(const char *token, const char *executable)
{
	char *buffer;
	size_t size;

	size = strlen(token) + strlen(executable) + 2;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);

	snprintf(buffer, size, "%s/%s", token, executable);

	if (access(buffer, F_OK) == 0)
		return (buffer);

	free(buffer);
	return (NULL);
}

/**
 * get_executable_path - Get path of executable in PATH environnement
 * @executable: Name of executable
 * Return: Executable path or NULL
 */
char *get_executable_path(char *executable)
{
	size_t i = 0;
	char *buffer, *path_copy, *var;

	for (i = 0; __environ[i]; i++)
	{
		if (strncmp(__environ[i], "PATH=", 5) == 0)
		{
			path_copy = strdup(__environ[i] + 5);
			if (!path_copy)
				return (NULL);

			for (var = strtok(path_copy, ":"); var; var = strtok(NULL, ":"))
			{
				buffer = if_executable_exist(var, executable);
				if (buffer)
				{
					free(path_copy);
					return (buffer);
				}
			}

			free(path_copy);
			break;
		}
	}

	return (NULL);
}
