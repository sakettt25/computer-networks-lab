// UDP Echo Client - Sends messages and receives echoed responses
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"  // localhost
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char message[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    int bytesSent, bytesReceived;
    int serverAddrLen = sizeof(serverAddr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("UDP Echo Client\n");
    printf("Connected to server at %s:%d\n", SERVER_IP, PORT);
    printf("Type messages to send to the echo server.\n");
    printf("Type 'quit' to exit.\n\n");

    while (1) {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);
        
        // Remove newline character from input
        message[strcspn(message, "\n")] = 0;
        
        // Check for exit condition
        if (strcmp(message, "quit") == 0) {
            printf("Exiting client...\n");
            break;
        }
        
        // Skip empty messages
        if (strlen(message) == 0) {
            continue;
        }

        printf("Sending: \"%s\"\n", message);

        // Send message to server
        bytesSent = sendto(clientSocket, message, strlen(message), 0, 
                          (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        
        if (bytesSent == SOCKET_ERROR) {
            printf("Send failed. Error Code: %d\n", WSAGetLastError());
            continue;
        }

        // Receive echoed response from server
        bytesReceived = recvfrom(clientSocket, response, BUFFER_SIZE - 1, 0, 
                                (struct sockaddr*)&serverAddr, &serverAddrLen);
        
        if (bytesReceived == SOCKET_ERROR) {
            printf("Receive failed. Error Code: %d\n", WSAGetLastError());
            continue;
        }
        
        response[bytesReceived] = '\0';  // Null-terminate the response
        printf("Server echoed: \"%s\"\n\n", response);
    }

    // Clean up
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
