#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  // Command to execute
  const char *command = "ls -l";
//   const char *command = "uptime";
  char *executable2 = "/bin/sh";
  char **args2 = malloc(4 * sizeof(char *));
  args2[0] = executable2;
  args2[1] = "-c";
  args2[2] = NULL;
  args2[3] = NULL;

  // Open a pipe to the command
  FILE *pipe = popen(command, "r");
  if (pipe == NULL) {
    perror("popen");
    return EXIT_FAILURE;
  }

  // Read the output from the pipe
  char buffer[128];
  size_t totalLength = 0;
  char *tmp = NULL;

  while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
    size_t lineLength = strlen(buffer);
    char *newTmp = realloc(tmp, totalLength + lineLength + 1); // +1 for null terminator
    if (newTmp == NULL) {
      perror("realloc");
      free(tmp);
      return EXIT_FAILURE;
    }
    tmp = newTmp;

    // Concatenate the new line to tmp
    strcpy(tmp + totalLength, buffer);
    totalLength += lineLength;
  }

  printf("buffer=\n%s\n", tmp);

  // Close the pipe
  if (pclose(pipe) == -1) {
    perror("pclose");
    free(tmp);
    free(args2);
    return EXIT_FAILURE;
  }

  // Copy the concatenated buffer to args2[2]
  args2[2] = tmp;

  printf("args2=\n%s\n", args2[2]);

    
  // You can uncomment the following lines to test execv
  // if (execv(executable2, args2) == -1) {
  //   perror("execv");
  //   free(args2);
  //   return EXIT_FAILURE;
  // }

  // Don't forget to free the allocated memory

  free(args2);

  return EXIT_SUCCESS;
}
