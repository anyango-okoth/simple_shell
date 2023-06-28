#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * executeCommand - Executes commands provided in the @args array
 *                  within the context of the shell environment.
 *
 * @args: An array of command arguments.
 * @envp: The environment variables (unused).
 *
 * Description:
 * This function supports two types of commands: "cd" and general commands.
 * The "cd" command changes the directory based on args[1].
 * The general command creates a child process using fork().
 */
void executeCommand(char *args[], char *envp[])
{
	if (args[0] != NULL)
	{
		if (strcmp(args[0], "cd") == 0)
		{
			/* Handle 'cd' command separately */
			if (args[1] == NULL || strcmp(args[1], "~") == 0)
				args[1] = getenv("HOME");
			else if (strcmp(args[1], "-") == 0)
				args[1] = getenv("OLDPWD");

			if (chdir(args[1]) == 0)
			{
				/* Update current directory environment variables */
				char currentDir[1024];

				getcwd(currentDir, sizeof(currentDir));
				setenv("PWD", currentDir, 1);
				setenv("OLDPWD", getenv("PWD"), 1);
			}
			else
			{
				fprintf(stderr, "Failed to change directory\n");
			}
		}
		else
		{
			/* Fork and execute the command */
			pid_t pid = fork();

			if (pid < 0)
			{
				fprintf(stderr, "Fork failed\n");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				/* Child process executes the command */
				execvp(args[0], args);
				fprintf(stderr, "Failed to execute command\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				/* Parent process waits for the child to complete */
				wait(NULL);
			}
		}
	}
	(void)envp; /* Avoid "unused parameter" warning */
}
