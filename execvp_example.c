#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Example command with a pipe symbol
    const char *args[] = {"/bin/sh", "-c", "ls -l | grep 'test'", NULL};

    // Execute the command
    if (execvp(args[0], (char *const *)args) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // This part of the code will only be reached if execvp fails
    fprintf(stderr, "Failed to execute command\n");
    exit(EXIT_FAILURE);
}
