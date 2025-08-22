// Port Change Experiment - Client using WRONG OLD PORT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define OLD_PORT 8080        // Wrong port - server is on 9090!
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char message[] = "Hello from client using WRONG port 8080!";
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
    serverAddr.sin_port = htons(OLD_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("=== CLIENT USING WRONG PORT ===\n");
    printf("Connecting to server on port: %d (but server is on 9090!)\n", OLD_PORT);
    printf("Sending message: %s\n", message);

    // Send message to server
    bytesSent = sendto(clientSocket, message, strlen(message), 0, 
                      (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    if (bytesSent == SOCKET_ERROR) {
        printf("Send failed. Error Code: %d\n", WSAGetLastError());
    } else {
        printf("Message sent successfully! (%d bytes)\n", bytesSent);
        printf("NOTE: Message was sent, but server won't receive it because it's listening on port 9090!\n");
        
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
                printf("EXPECTED RESULT: Timeout - No response because server is not listening on this port!\n");
                printf("EXPLANATION: The server is listening on port 9090, but we sent to port 8080.\n");
                printf("In UDP, the message goes into the void - no error, but no delivery either.\n");
            } else {
                printf("Receive failed. Error Code: %d\n", error);
            }
        } else {
            buffer[bytesReceived] = '\0';
            printf("Unexpected: Received response: '%s'\n", buffer);
        }
    }

    // Clean up
    closesocket(clientSocket);
    WSACleanup();
    
    printf("Client terminating...\n");
    return 0;
}
