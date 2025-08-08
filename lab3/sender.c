// sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <IP> <Sender Port> <Receiver Port>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int sender_port = atoi(argv[2]);
    int receiver_port = atoi(argv[3]);

    int sockfd;
    struct sockaddr_in sender_addr, receiver_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&sender_addr, 0, sizeof(sender_addr));
    sender_addr.sin_family = AF_INET;
    sender_addr.sin_port = htons(sender_port);
    sender_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&sender_addr, sizeof(sender_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(receiver_port);
    receiver_addr.sin_addr.s_addr = inet_addr(ip);

    socklen_t addr_len = sizeof(receiver_addr);

    while (1)
    {
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&receiver_addr, addr_len);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         NULL, NULL);
        buffer[n] = '\0';
        printf("Receiver: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }
    }

    close(sockfd);
    return 0;
}
