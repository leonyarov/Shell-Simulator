//Leon Yarovinski *********
//Daniel Grounin 319191680



#include "funcs.h"
#define GRN "\e[0;32m"
#define BGRN "\e[1;32m"
#define BLU "\e[0;34m"
#define BBLU "\e[1;34m"
#define WHT "\e[0;37m"
#define RED "\033[0;31m"
#define READ 0
#define WRITE 1


void printPath(){
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    char * user = getenv("USER");
    printf( RED"%s:",user);
    printf(BLU"%s:",cwd);
    printf(WHT);
}





parseInfo* parse(char* line){
    parseInfo* info = (parseInfo*)malloc(sizeof(parseInfo));
    info->pipe_index = -1;
    info->command = NULL; // Initialize command to NULL
    
    // Check for empty line
    if (strcmp(line,"") == 0){
        info->command = (char**)malloc(sizeof(char*)); // Allocate memory for an empty command
        info->command[0] = strdup(""); // Set the first element to an empty string
        info->size = 1;
        return info;
    }
   
    int size = 0; // Number of words
    char* temp = strtok(line, " "); // Tokenize the line string using space as delimiter
    while(temp != NULL){
        info->command = (char**)realloc(info->command, sizeof(char*) * (size + 1)); // Resize command array
        info->command[size] = strdup(temp); // Allocate memory and copy token to command array
        size++;
        temp = strtok(NULL, " "); // Continue tokenizing
    }
    info->size = size;
    info->command = (char**)realloc(info->command, sizeof(char*) * (size + 1)); // Resize command array to add NULL
    info->command[size] = NULL; // Set last element to NULL
    
    // Check if the command is "cd" and add "/" if needed
    if(strcmp(info->command[0], "cd") == 0 && (size == 1 || strcmp(info->command[1], "~") == 0)){
        info->command[1] = strdup(getenv("HOME"));
    }

    return info;
}






void executeCommand(parseInfo* info) {
    // If pipe
    if (info->pipe_index != -1) {
        execute_pipe(info->pipe_index, info->command[0]);
    }
    // If the command is empty - exit
    else if (strcmp(info->command[0], "") == 0) {
        exit(1);
    }
    // If the command is "cat" with redirection
    else if (strcmp(info->command[0], "cat") == 0 && strcmp(info->command[1], ">") == 0) {
        execute_cat(info);
    }
    // General case - use execvp on the command
    else {
        // List of supported commands
        char* supported_commands[] = { "pwd", "nano", "cat", "wc", "cp", "clear", "grep", "wget", "ls", "tree" };

        // Check if the command is supported
        int i;
        for (i = 0; i < sizeof(supported_commands) / sizeof(supported_commands[0]); i++) {
            if (strcmp(info->command[0], supported_commands[i]) == 0) {
                if (execvp(info->command[0], info->command) < 0) {
                    printf("Failed to execute the '%s' command\n", info->command[0]);
                }
            }
        }
        printf("%s is not supported! \n", info->command[0]);
    }
    exit(1);
}

void execute_cat(parseInfo* info) {
    // Check if the file name exists
    if (info->command[2] == NULL) {
        printf("bash: syntax error near unexpected token `newline'\n");
        exit(1);
    }

    // Open file for writing
    FILE* fptr = fopen(info->command[2], "w");
    if (fptr == NULL) {
        printf("error - could not open %s\n", info->command[2]);
        exit(1);
    }

    // Read input from terminal and write to file
    char buffer[1024];
    while (fgets(buffer, 1024, stdin) != NULL) {
        fprintf(fptr, "%s", buffer);
    }
    fclose(fptr);
    exit(1);
}

void execute_pipe(int pipe_index, char* line) {
    parseInfo* info1, * info2;
    char* line1 = strdup(line);
    char* line2 = strdup(line + pipe_index + 1);
    line1[pipe_index - 1] = '\0';
    line2[strlen(line) - pipe_index - 1] = '\0';

    info1 = parse(line1);
    info2 = parse(line2);

    int p[2];
    pipe(p);
    int childPid = fork();

    if (childPid == 0) { // Child process
        close(p[READ]);
        dup2(p[WRITE], WRITE);
        executeCommand(info1);
    }
    else {
        close(p[WRITE]);
        dup2(p[READ], READ);
        waitpid(childPid, NULL, 0);
        if (strcmp(info2->command[0], "exit") == 0 || strcmp(info2->command[0], "cd") == 0)
            exit(1);
        executeCommand(info2);
    }
}


void freeInfo(parseInfo* info) {
    if (info == NULL) return;

    for (int i = 0; i < info->size; i++) {
        free(info->command[i]);
    }
    free(info->command);
    free(info);
}

