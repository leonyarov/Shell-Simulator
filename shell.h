//Leon Yarovinski *********
//Daniel Grounin 319191680



#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef struct parseInfo {
    char ** command;
    int size;
    int pipe_index;
}parseInfo;

void freeInfo(parseInfo* info);
void printPath();
void execute_cat(parseInfo* info);
parseInfo* parse(char* );
void executeCommand(parseInfo * info);
void execute_pipe(int,char*);
