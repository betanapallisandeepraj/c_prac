#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  // Example command with arguments
  char *args[] = {"ls", "-l", NULL};

  // Execute the command using execv
  if (execv("/bin/ls", args) == -1) {
    perror("execv");
    exit(EXIT_FAILURE);
  }

  // This part of the code will only be reached if execv fails
  fprintf(stderr, "Failed to execute command\n");
  exit(EXIT_FAILURE);
}
