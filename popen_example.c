#include <stdio.h>
#include <stdlib.h>

int main() {
  // Command to execute
  const char *command = "ls -l";

  // Open a pipe to the command
  FILE *pipe = popen(command, "r");
  if (pipe == NULL) {
    perror("popen");
    return EXIT_FAILURE;
  }

  // Read the output from the pipe
  char buffer[128];
  while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
    printf("%s", buffer);
  }

  // Close the pipe
  if (pclose(pipe) == -1) {
    perror("pclose");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
