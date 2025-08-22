// Port Change Experiment - Client using CORRECT NEW PORT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define NEW_PORT 9090        // Correct port that matches server
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char message[] = "Hello from client using CORRECT port 9090!";
    char buffer[BUFFER_SIZE];
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
    serverAddr.sin_port = htons(NEW_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("=== CLIENT USING CORRECT PORT ===\n");
    printf("Connecting to server on port: %d\n", NEW_PORT);
    printf("Sending message: %s\n", message);

    // Send message to server
    bytesSent = sendto(clientSocket, message, strlen(message), 0, 
                      (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    if (bytesSent == SOCKET_ERROR) {
        printf("Send failed. Error Code: %d\n", WSAGetLastError());
    } else {
        printf("Message sent successfully! (%d bytes)\n", bytesSent);
        
        // Try to receive response from server
        printf("Waiting for server response...\n");
        
        // Set timeout for receive operation
        int timeout = 5000; // 5 seconds
        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
        
        bytesReceived = recvfrom(clientSocket, buffer, BUFFER_SIZE - 1, 0,
                                (struct sockaddr*)&serverAddr, &serverAddrLen);
        
        if (bytesReceived == SOCKET_ERROR) {
            int error = WSAGetLastError();
            if (error == WSAETIMEDOUT) {
                printf("Timeout: No response from server (this is normal if server doesn't send response)\n");
            } else {
                printf("Receive failed. Error Code: %d\n", error);
            }
        } else {
            buffer[bytesReceived] = '\0';
            printf("SUCCESS: Received response from server: '%s'\n", buffer);
        }
    }

    // Clean up
    closesocket(clientSocket);
    WSACleanup();
    
    printf("Client terminating...\n");
    return 0;
}
