// Port Change Experiment - UDP Server
// This server listens on port 9090 (different from usual 8080)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define NEW_PORT 9090        // Changed from usual 8080
#define OLD_PORT 8080        // Original port for reference
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    int clientAddrLen = sizeof(clientAddr);
    int bytesReceived;

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
    serverAddr.sin_port = htons(NEW_PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("=== PORT CHANGE EXPERIMENT ===\n");
    printf("Server is now listening on NEW PORT: %d\n", NEW_PORT);
    printf("Old port was: %d\n", OLD_PORT);
    printf("Waiting for client messages...\n");
    printf("Note: If client uses old port (%d), communication will fail!\n\n", OLD_PORT);

    // Receive message from client
    bytesReceived = recvfrom(serverSocket, buffer, BUFFER_SIZE - 1, 0, 
                            (struct sockaddr*)&clientAddr, &clientAddrLen);
    
    if (bytesReceived == SOCKET_ERROR) {
        printf("Receive failed. Error Code: %d\n", WSAGetLastError());
    } else {
        buffer[bytesReceived] = '\0';  // Null-terminate the received string
        printf("SUCCESS: Received message from client: '%s'\n", buffer);
        
        // Get client IP address
        char* clientIP = inet_ntoa(clientAddr.sin_addr);
        printf("Client IP: %s, Port: %d\n", clientIP, ntohs(clientAddr.sin_port));
        
        // Send acknowledgment back to client
        char response[] = "Message received on NEW PORT 9090!";
        int bytesSent = sendto(serverSocket, response, strlen(response), 0,
                              (struct sockaddr*)&clientAddr, clientAddrLen);
        
        if (bytesSent == SOCKET_ERROR) {
            printf("Send failed. Error Code: %d\n", WSAGetLastError());
        } else {
            printf("Acknowledgment sent back to client.\n");
        }
    }

    // Clean up
    closesocket(serverSocket);
    WSACleanup();
    
    printf("Server shutting down...\n");
    return 0;
}
