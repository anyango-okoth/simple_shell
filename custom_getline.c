#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * custom_getline - Read a line of input from the standard input
 *
 * Return:NULL on failure and the line on success
 */

char *custom_getline(void)
{
	static char buffer[1024];
	static size_t buffer_pos;
	static ssize_t chars_read;

	ssize_t chars_read_temp;
	size_t buffer_pos_temp;
	char *line;
	size_t i;

	if (buffer_pos >= (size_t)chars_read)
	{
		chars_read_temp = read(STDIN_FILENO, buffer, sizeof(buffer));
		if (chars_read_temp == -1 || chars_read_temp == 0)
		{
			return (NULL); /* End of file or error occurred */
		}
		buffer_pos = 0;
		chars_read = chars_read_temp;
	}

	line = malloc((size_t)(chars_read - buffer_pos + 1));
	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	i = 0;
	buffer_pos_temp = buffer_pos;
	while (buffer_pos_temp < (size_t)chars_read && buffer[buffer_pos_temp] != '\n')
	{
		line[i++] = buffer[buffer_pos_temp++];
	}

	line[i] = '\0';
	buffer_pos = buffer_pos_temp + 1; /* Skip the newline character */

	return (line);
}

