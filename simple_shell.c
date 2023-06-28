#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * main - Entry point of the program
 * @argc: The argument count
 * @argv: Array of strings representing the arguments
 * @envp: Array of strings representing the environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *envp[])
{
	if (argc == 1)
	{
		prompt(envp);
	}
	else
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return (0);
}

