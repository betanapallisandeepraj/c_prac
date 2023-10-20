#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

int main() {
    int sock;
    struct ifreq ifr;
    char *interface = "br-wan";  // Replace with your interface name

    // Open a socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    // Set the interface name
    strncpy(ifr.ifr_name, interface, IFNAMSIZ);

    // Get the MAC address
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) == -1) {
        perror("ioctl");
        close(sock);
        exit(1);
    }

    // Close the socket
    close(sock);

    // Display the MAC address
    printf("MAC Address of %s: ", interface);
    for (int i = 0; i < 6; i++) {
        printf("%02X", (unsigned char)ifr.ifr_hwaddr.sa_data[i]);
        if (i < 5) {
            printf(":");
        }
    }
    printf("\n");

    return 0;
}
