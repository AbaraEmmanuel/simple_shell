#include "main.h"


/**
 * _getenv - prts env to standard output
 *
 * @env: enviroment
 *
 */

void _getenv(char **env)
{
	size_t run = 0;

	while (env[run])
	{
		write(STDOUT_FILENO, env[run], _strlen(env[run]));
		write(STDOUT_FILENO, "\n", 1);
		run++;
	}
}

/**
 * lsh_setenv - Set environment variable
 * @args: List of args. args[0] is "setenv". args[1] is the variable name.
 * args[2] is the value.
 * Return: 0 on success, -1 on failure
 */
int lsh_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv: Invalid arguments\n");
		return (-1);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}

/**
 * lsh_unsetenv - Unset environment variable
 * @args: List of args. args[0] is "unsetenv". args[1] is the variable name.
 * Return: 0 on success, -1 on failure
 */
int lsh_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unsetenv: Variable name not provided\n");
		return (-1);
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}
