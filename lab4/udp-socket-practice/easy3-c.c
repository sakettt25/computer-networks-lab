// UDP Client - Sends lowercase strings to uppercase conversion server
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

    printf("UDP Uppercase Conversion Client\n");
    printf("Connected to server at %s:%d\n\n", SERVER_IP, PORT);

    // Test with different lowercase strings
    char testStrings[][100] = {
        "hello world",
        "this is a test message",
        "computer networks lab",
        "udp socket programming",
        "lowercase to uppercase conversion",
        "quit"
    };

    int numTests = sizeof(testStrings) / sizeof(testStrings[0]);

    for (int i = 0; i < numTests; i++) {
        strcpy(message, testStrings[i]);
        printf("Sending to server: \"%s\"\n", message);

        // Send message to server
        bytesSent = sendto(clientSocket, message, strlen(message), 0, 
                          (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        
        if (bytesSent == SOCKET_ERROR) {
            printf("Send failed. Error Code: %d\n", WSAGetLastError());
            continue;
        }

        // Receive response from server
        bytesReceived = recvfrom(clientSocket, response, BUFFER_SIZE - 1, 0, 
                                (struct sockaddr*)&serverAddr, &serverAddrLen);
        
        if (bytesReceived == SOCKET_ERROR) {
            printf("Receive failed. Error Code: %d\n", WSAGetLastError());
            continue;
        }

        response[bytesReceived] = '\0';  // Null-terminate the response
        printf("Received from server: \"%s\"\n", response);
        printf("-----------------------------------\n");

        // Small delay between messages
        Sleep(1000);  // 1 second delay
    }

    printf("\nTesting complete!\n");

    // Clean up
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
