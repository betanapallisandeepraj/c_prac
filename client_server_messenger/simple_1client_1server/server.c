#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_LEN 1024
#define PORT 8080

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAX_LEN];

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        return -1;
    }

    while (1) {
        memset(buffer, 0, MAX_LEN);
        int valread = read(new_socket, buffer, MAX_LEN);
        printf("Message received: %s\n", buffer);

        memset(buffer, 0, MAX_LEN);
        printf("Enter a message: ");
        fgets(buffer, MAX_LEN, stdin);
        send(new_socket, buffer, strlen(buffer), 0);
    }
    return 0;
}

