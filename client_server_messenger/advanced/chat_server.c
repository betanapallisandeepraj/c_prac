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
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

int global_client_socket[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t client_socket_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    int client_index = *((int *)arg);
    int client_socket = global_client_socket[client_index];
    char buffer[BUFFER_SIZE];
    int received;

    while ((received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        pthread_mutex_lock(&client_socket_mutex);
        for (int i = 0; i < client_count; i++) {
            if (global_client_socket[i] != client_socket) {
                send(global_client_socket[i], buffer, received, 0);
            }
        }
        pthread_mutex_unlock(&client_socket_mutex);
    }

    pthread_mutex_lock(&client_socket_mutex);
    for (int i = 0; i < client_count; i++) {
        if (global_client_socket[i] == client_socket) {
            for (int j = i; j < client_count - 1; j++) {
                global_client_socket[j] = global_client_socket[j + 1];
            }
            break;
        }
    }
    client_count--;
    pthread_mutex_unlock(&client_socket_mutex);

    close(client_socket);

    return NULL;
}

int main(int argc, char const *argv[]) {
    int server_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    pthread_t client_thread;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
    	perror("listen");
    	exit(EXIT_FAILURE);
    }

while (1) {
    int new_socket;
    if ((new_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&client_socket_mutex);
    global_client_socket[client_count] = new_socket;
    client_count++;
    pthread_mutex_unlock(&client_socket_mutex);

    int *client_index = malloc(sizeof(*client_index));
    *client_index = client_count - 1;
    if (pthread_create(&client_thread, NULL, handle_client, (void *)client_index) < 0) {
        perror("could not create thread");
        exit(EXIT_FAILURE);
    }
}

return 0;
}

