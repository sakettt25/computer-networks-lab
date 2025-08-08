#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr, cliaddr;
    socklen_t len;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Clear and set server address info
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Accept any IP
    server_addr.sin_port = htons(PORT);         // Port

    // Bind socket to the specified port
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP server listening on port %d...\n", PORT);

    len = sizeof(cliaddr);  // Length of client address structure

    // Receive message from client
    int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';  // Null-terminate the received string
    printf("Client says: %s\n", buffer);

    // Send reply to client
    const char *reply = "Hello from server";
    sendto(sockfd, reply, strlen(reply), 0, (const struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
