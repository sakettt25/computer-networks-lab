#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"  // localhost
#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char message[] = "Hello Server Saket";
    int bytesSent;

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
    
    // Convert IP address from text to binary form
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Sending message to server: %s\n", message);

    // Send message to server
    bytesSent = sendto(clientSocket, message, strlen(message), 0, 
                      (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    if (bytesSent == SOCKET_ERROR) {
        printf("Send failed. Error Code: %d\n", WSAGetLastError());
    } else {
        printf("Message sent successfully! (%d bytes)\n", bytesSent);
    }

    // Clean up
    closesocket(clientSocket);
    WSACleanup();
    
    printf("Client terminating...\n");
    return 0;
}
