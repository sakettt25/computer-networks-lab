// UDP Server - Uppercase Conversion Service
// Receives lowercase strings and sends back uppercase versions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctype.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

void convertToUppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    int clientAddrLen = sizeof(clientAddr);
    int bytesReceived, bytesSent;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("UDP Uppercase Conversion Server is running on port %d...\n", PORT);
    printf("Server will convert lowercase strings to uppercase and send them back.\n");
    printf("Waiting for client messages...\n\n");

    while (1) {
        // Receive message from client
        bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE - 1, 0, 
                                (struct sockaddr*)&clientAddr, &clientAddrLen);
        
        if (bytesReceived == SOCKET_ERROR) {
            printf("Receive failed. Error Code: %d\n", WSAGetLastError());
            continue;
        }

        buffer[bytesReceived] = '\0';  // Null-terminate the received string
        
        // Get client IP address
        char* clientIP = inet_ntoa(clientAddr.sin_addr);
        printf("Received from client [%s:%d]: \"%s\"\n", 
               clientIP, ntohs(clientAddr.sin_port), buffer);

        // Convert to uppercase
        convertToUppercase(buffer);
        printf("Converting to uppercase: \"%s\"\n", buffer);

        // Send the uppercase string back to client
        bytesSent = sendto(serverSocket, buffer, strlen(buffer), 0, 
                          (struct sockaddr*)&clientAddr, clientAddrLen);
        
        if (bytesSent == SOCKET_ERROR) {
            printf("Send failed. Error Code: %d\n", WSAGetLastError());
        } else {
            printf("Sent back to client: \"%s\" (%d bytes)\n\n", buffer, bytesSent);
        }
    }

    // Clean up (this won't be reached in the infinite loop)
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}