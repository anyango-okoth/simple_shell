#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

#define MAX_ARGS 10

void executeCommand(char *args[], char *envp[]);
void prompt(char *envp[]);
char *custom_getline();
void handleCommandSeparators(char *args[], char *envp[]);
void tokenizeString(char *string, char *args[], size_t maxArgs);

#endif /* MAIN_H */

