//Leon Yarovinski 206817181
//Daniel Grounin 319191680


#include "shell.c"
#include "tree.c"

int main(int argc, char** argv) {
    int childPid;
    char* cmdLine = NULL;
    parseInfo* info = NULL;

    printf(BGRN"\n---------------STARTING OUR SHELL---------------\n");
    while (1) {
        printPath();
        cmdLine = readline(BGRN" $ ");
        add_history(cmdLine);
        info = parse(cmdLine);

        if (info->command && strcmp(info->command[0], "exit") == 0) {
            freeInfo(info);
            exit(1);
        }
        else if (info->command && strcmp(info->command[0], "cd") == 0) {
            if (chdir(info->command[1]) == -1) {
                printf("%s NOT FOUND\n", info->command[1]);
                freeInfo(info);
            }
            continue;
        }
         else if (info->command && strcmp(info->command[0], "tree") == 0) {
            char current_dir[1024];
            getcwd(current_dir, sizeof(current_dir));
            print_tree(current_dir, 0);
            freeInfo(info);
            continue;
        }

        childPid = fork();

        if (childPid == 0) {
            executeCommand(info);
            freeInfo(info);
        }
        else {
            waitpid(childPid);
        }
    }
}
