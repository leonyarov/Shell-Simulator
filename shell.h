//Leon Yarovinski *********
//Daniel Grounin 319191680


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parseInfo
{
    char *cmd;
    char **args;
} parseInfo;

// Read line from the console, print the symbol before
char *readline(char *symbol);

parseInfo* parse(char *line);

void executeCommand(parseInfo *info);