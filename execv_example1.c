#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int command_number(char *command, size_t len) {
    printf("Command: ");
    fwrite(command, 1, len, stdout);
    printf("\n");
    return 1;
}

void create_command1(char **executable1, char ***args1) {
    char **args2 = malloc(5 * sizeof(char *));

    // Check if memory allocation was successful
    if (args2 == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Set the command and arguments
    *executable1 = "/bin/echo";
    args2[0] = *executable1;
    args2[1] = "123";
    args2[2] = "456";
    args2[3] = "789";
    args2[4] = NULL;

    free(*args1);
    *args1 = args2;
}

void create_command(char **executable1, char ***args1) {
    command_number((*args1)[0], strlen((*args1)[0]));
    create_command1(executable1, args1);
}

int main() {
    // Call the function to get the command and arguments
    char *executable;
    char **args = malloc(4 * sizeof(char *));

    // Set the command and arguments
    executable = "/bin/ls";
    args[0] = executable;
    args[1] = "-l";
    args[2] = "test.c";
    args[3] = NULL;
    create_command(&executable, &args);

    // Execute the command using execv
    if (execv(executable, args) == -1) {
        perror("execv");
        exit(EXIT_FAILURE);
    }

    // This part of the code will only be reached if execv fails
    fprintf(stderr, "Failed to execute command\n");
    exit(EXIT_FAILURE);
}
