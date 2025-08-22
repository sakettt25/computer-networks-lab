// UDP Echo Server - Sends back whatever message it receives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

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

    printf("UDP Echo Server is running on port %d...\n", PORT);
    printf("Server will echo back any message it receives.\n");
    printf("Press Ctrl+C to stop the server.\n\n");

    // Echo service loop - runs continuously
    while (1) {
        printf("Waiting for client message...\n");
        
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
        printf("Received from %s:%d: \"%s\"\n", clientIP, ntohs(clientAddr.sin_port), buffer);
        
        // Echo the message back to the client
        bytesSent = sendto(serverSocket, buffer, bytesReceived, 0, 
                          (struct sockaddr*)&clientAddr, clientAddrLen);
        
        if (bytesSent == SOCKET_ERROR) {
            printf("Send failed. Error Code: %d\n", WSAGetLastError());
        } else {
            printf("Echoed back: \"%s\" (%d bytes)\n\n", buffer, bytesSent);
        }
    }

    // Clean up (this code won't be reached in the infinite loop)
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}