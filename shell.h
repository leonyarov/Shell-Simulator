//Leon Yarovinski *********
//Daniel Grounin 319191680


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h> //provide function readline() that reads a line of text from user and returns it as a dynamically aclocated string.
#include <readline/history.h> // manage the command history line

typedef struct parseInfo
{
    char *cmd;
    char **args;
} parseInfo;

// Read line from the console, print the symbol before
char *readline(char *symbol);

parseInfo* parse(char *line);

void executeCommand(parseInfo *info);