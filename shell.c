//Leon Yarovinski *********
//Daniel Grounin 319191680

#include "shell.h"


// Read line from the console, print the symbol before
char *readline(char *symbol)
{
    size_t bufsize = 1024;
    char *line = NULL;
    printf("%s ", symbol);
    getline(&line, &bufsize, stdin);
    return line;
}

parseInfo* parse(char *line)
{
    char *token;       // temporary token pointer
    parseInfo cmds[2]; // amout of commands required to store (2)
    char *pipes[2];    // command pipes temp pointer

    char *pipe = strtok(line, "|"); // get the first command

    // Seperate the line by pipes '|'
    for (int i = 0; pipe != NULL || i < 2; i++)
    {
        pipes[i] = pipe;
        pipe = strtok(NULL, "|");
    }

    for (int i = 0; i < 2; i++)
    {
        // get the command - cat, touch, wc etc...
        token = strtok(pipes[i], " ");
        cmds[i].cmd = token;

        // go through command arguments - -t, -s, >, directories
        for (int j = 0; token != NULL; j++)
        {
            token = strtok(NULL, " ");

            // allocate new space for an arg token
            cmds[i].args = (char **)realloc(cmds[i].args, (j + 1) * sizeof(char *));

            // assign token based on type

            // token is char arg
            if (token[0] == '-')
                cmds[i].args[j] = &token[1];
            // token is path or special symbol > or <
            else
                cmds[i].args[j] = token;
        }
    } 

    return cmds;
}

void executeCommand(parseInfo *info)
{
    for (size_t i = 0; i < 2; i++)
    {
        char* cmd = info[i].cmd;
        
    }
    
}