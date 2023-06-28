#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

#define MAX_ARGS 10

/**
 * handleCommandSeparators - Handles command separators (;) in argument array
 * @args: The array of arguments
 * @envp: The environment variables array
 */
void handleCommandSeparators(char *args[], char *envp[])
{
	int i = 0;

	while (args[i] != NULL)
	{
		char *command = args[i];

		if (strcmp(command, ";") == 0)
		{
			args[i] = NULL; /* Terminate the command at the separator */

			/* Execute the command before the separator */
			executeCommand(args, envp);

			/* Move the pointer to the next command after the separator */
			args = &args[i + 1];
			i = -1; /* Start from the beginning of the new command */
		}

		i++;
	}

	/* Execute the last command after the last separator */
	executeCommand(args, envp);
}

/**
 * prompt - Displays the prompt and handles user input
 * @envp: The environment variables array
 */
void prompt(char *envp[])
{
	char *string = NULL;
	size_t n = 0;
	ssize_t numChars;

	char *args[MAX_ARGS + 1]; /* Increased size by 1 for NULL terminator */

	char currentDir[1024]; /* Buffer to store the current directory */

	while (1)
	{
		printf("simple_shell$ ");

		numChars = getline(&string, &n, stdin);
		if (numChars == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}

		if (string[numChars - 1] == '\n')
		{
			string[numChars - 1] = '\0'; /* Remove newline character */
		}

		tokenizeString(string, args, MAX_ARGS);
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				if (args[1] != NULL)
				{
					int exitStatus = atoi(args[1]);

					free(string);
					exit(exitStatus);
				}
				else
				{
					free(string);
					exit(EXIT_SUCCESS);
				}
			}
			else if (strcmp(args[0], "setenv") == 0)
			{
				if (args[1] != NULL && args[2] != NULL)
				{
					if (setenv(args[1], args[2], 1) != 0)
					{
						fprintf(stderr, "Failed to set environment variable\n");
					}
				}
				else
				{
					fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
				}
			}
			else if (strcmp(args[0], "unsetenv") == 0)
			{
				if (args[1] != NULL)
				{
					if (unsetenv(args[1]) != 0)
					{
						fprintf(stderr, "Failed to unset environment variable\n");
					}
				}
				else
				{
					fprintf(stderr, "Usage: unsetenv VARIABLE\n");
				}
			}
			else if (strcmp(args[0], "cd") == 0)
			{
				if (args[1] == NULL || strcmp(args[1], "~") == 0)
				{
					args[1] = getenv("HOME");
				}
				else if (strcmp(args[1], "-") == 0)
				{
					args[1] = getenv("OLDPWD");
				}

				if (chdir(args[1]) == 0)
				{
					getcwd(currentDir, sizeof(currentDir));
					setenv("PWD", currentDir, 1);
					setenv("OLDPWD", getenv("PWD"), 1);
				}
				else
				{
					fprintf(stderr, "Failed to change directory\n");
				}
			}
		}

		handleCommandSeparators(args, envp);
	}
}

