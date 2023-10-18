#include "main.h"

/**
 * _getline_command - Get user input from standard input
 * Return: The user's input.
 */
char *_getline_command(void)
{
	char *input_line = NULL;
	size_t line_buffer_size = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	if (getline(&input_line, &line_buffer_size, stdin) == -1)
	{
		free(input_line);
		return (NULL);
	}

	return (input_line);
}
