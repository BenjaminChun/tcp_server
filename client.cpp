#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error: Failed to create socket" << std::endl;
        return 1;
    }

    // Connect to server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    serverAddr.sin_port = htons(8080); // Server port

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Failed to connect to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to server" << std::endl;

    // Receive data from server
    char buffer[1024] = {0};
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Error: Failed to receive data from server" << std::endl;
    } else {
        std::cout << "Received from server: ";
        for (int i = 0; i < bytesRead; ++i) {
            std::cout << buffer[i];
        }
        std::cout << std::endl;
    }

    // Close socket
    close(clientSocket);

    return 0;
}