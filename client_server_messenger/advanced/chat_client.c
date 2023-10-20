#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *receive_message(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[BUFFER_SIZE];
    int received;

    while ((received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[received] = '\0';
        printf("%s\n", buffer);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    int client_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    int sent;
    pthread_t receive_thread;

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&receive_thread, NULL, receive_message, (void *)&client_socket) < 0) {
        perror("could not create receive thread");
	exit(EXIT_FAILURE);
    }
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    sent = send(client_socket, buffer, strlen(buffer), 0);
    if (sent < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    }

close(client_socket);

return 0;
}
