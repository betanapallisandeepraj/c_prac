#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipe_fd[2];
  pid_t child_pid;

  // Create a pipe
  if (pipe(pipe_fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // Fork a child process
  child_pid = fork();

  if (child_pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (child_pid == 0) {
    // Child process

    // Close the write end of the pipe since the child will only read
    close(pipe_fd[1]);

    // Read from the pipe
    char buffer[256];
    ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));

    if (bytes_read == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    // Null-terminate the string
    buffer[bytes_read] = '\0';

    printf("Child received: %s\n", buffer);

    // Close the read end of the pipe
    close(pipe_fd[0]);

    exit(EXIT_SUCCESS);
  } else {
    // Parent process

    // Close the read end of the pipe since the parent will only write
    close(pipe_fd[0]);

    // Write to the pipe
    const char *message = "Hello, child!";
    ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));

    if (bytes_written == -1) {
      perror("write");
      exit(EXIT_FAILURE);
    }

    // Close the write end of the pipe
    close(pipe_fd[1]);

    // Wait for the child to finish
    wait(NULL);

    exit(EXIT_SUCCESS);
  }

  return 0;
}
