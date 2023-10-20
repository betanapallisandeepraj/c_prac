#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_LEN 1024
#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[MAX_LEN];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    while (1) {
        memset(buffer, 0, MAX_LEN);
        printf("Enter a message: ");
        fgets(buffer, MAX_LEN, stdin);
        send(sock, buffer, strlen(buffer), 0);

        memset(buffer, 0, MAX_LEN);
        int valread = read(sock, buffer, MAX_LEN);
        printf("Message received: %s\n", buffer);
    }
    return 0;
}

