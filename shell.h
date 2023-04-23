//Leon Yarovinski *********
//Daniel Grounin 319191680


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


#define GRN "\e[0;32m"
#define BGRN "\e[1;32m"
#define BLU "\e[0;34m"
#define BBLU "\e[1;34m"
#define WHT "\e[0;37m"
#define RED "\033[0;31m"
#define READ 0
#define WRITE 1


typedef struct parseInfo {
    char ** command;
    int size;
    int pipe_index;
}parseInfo;

void print_tree(char *path, int level);
void freeInfo(parseInfo* info);
void printPath();
void execute_cat(parseInfo* info);
parseInfo* parse(char* );
void executeCommand(parseInfo * info);
void execute_pipe(int,char*);
