#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock;
  struct ifreq ifr;
  char *interface = "br-wan"; // Replace with your interface name
  char macaddr[18];
  char command[100];
  char buffer[128];
  FILE *file;

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
  sprintf(macaddr, "%02x:%02x:%02x:%02x:%02x:%02x",
          (unsigned char)ifr.ifr_hwaddr.sa_data[0],
          (unsigned char)ifr.ifr_hwaddr.sa_data[1],
          (unsigned char)ifr.ifr_hwaddr.sa_data[2],
          (unsigned char)ifr.ifr_hwaddr.sa_data[3],
          (unsigned char)ifr.ifr_hwaddr.sa_data[4],
          (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
  printf("MAC Address is %s \n", macaddr);

  snprintf(command, sizeof(command),
           "openssl rsautl -decrypt -inkey /tmp/private.pem -in /tmp/encrypted.bin");
  file = popen(command, "r");
  if (file == NULL) {
    perror("popen");
    return 1;
  }

  // Read and print the output of the command
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("%s", buffer);
  }
  // Close the pipe
  pclose(file);
  if (strstr(buffer, macaddr))
    printf("license is valid and feature 1 enabled\n");
  else
    printf("license is not valid, please install valid license\n");
  return 0;
}
