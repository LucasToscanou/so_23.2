//Lucas Toscano Pimentel Appolinário Cerqueira
//2110695

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void type_prompt();
void read_command(char **cmd, char *params[]);
void isOriginalCmd(char **cmd);
void fix_path(char **cmd);

int main() {
    char *command;
    char *parameters[256];

    while (TRUE) {
        type_prompt();
        read_command(&command, parameters);
        if (fork() != 0) {
            int status = 0;
            waitpid(-1, &status, 0);
        } else {
            int err = execve(command, parameters, 0);
            if (err == -1) {
                perror("execve");
                exit(1);
            }
        }
        free(command); 
    }

    return 0;
}

void type_prompt() {
    printf("$ ");
}

void read_command(char **cmd, char *params[]) {
    char input[256];

    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *token = strtok(input, " \t\n");
        int i = 0;

        if (token != NULL) {
            *cmd = strdup(token);

            isOriginalCmd(cmd);

            params[i] = strdup(token);
            while ((token = strtok(NULL, " \t\n")) != NULL) {
                params[++i] = strdup(token);
            }

            params[++i] = NULL;
        } 
        else {
            printf("Command not found.\n");
            *cmd = NULL;
        }
    } else {
        printf("Error reading input.\n");
        *cmd = NULL;
    }
}

void isOriginalCmd(char **cmd) {
    char *original_cmds[] = {"echo", "cat", "ls", "more", NULL};

    for (int i = 0; original_cmds[i] != NULL; i++) {
        if (strcmp(*cmd, original_cmds[i]) == 0) {
            fix_path(cmd);
            return;
        }
    }
    return;
}

void fix_path(char **cmd) {
    const char *path_base = "/bin/";

    size_t path_length = strlen(path_base);
    size_t cmd_length = strlen(*cmd);

    char *combined = (char *)malloc(path_length + cmd_length + 1); 

    if (combined == NULL) {
        perror("Memory allocation failed");
        return;
    }

    strcpy(combined, path_base);

    strcat(combined, *cmd);

    free(*cmd);
    *cmd = combined;
}
