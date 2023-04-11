//Leon Yarovinski *********
//Daniel Grounin 319191680

#include "shell.c"

int main(int argc, char **argv){
    int childPid;
    char * cmdLine;
    parseInfo *info;
    while (1){

        cmdLine = readline(">");
        info = parse(cmdLine);
        childPid = fork();

        if (childPid == 0){

            executeCommand(info); // calll execvp
        }
        else{
            waitpid(childPid);
        }
    }
    free(cmdLine);
    return 0;
}