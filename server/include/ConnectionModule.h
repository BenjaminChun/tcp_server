#ifndef CONNECTIONMODULE_H
#define CONNECTIONMODULE_H

#include <netinet/in.h> // Include for sockaddr_in

class ConnectionModule {
private:
    int serverSockfd; // Server socket file descriptor
    int clientSockfd; // Client socket file descriptor
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    socklen_t clientAddrLen;

public:
    ConnectionModule(int port);
    ~ConnectionModule();
    bool waitForConnection();
    bool sendData(const char* data, int dataSize);
    bool receiveData(char* buffer, int bufferSize);
};

#endif /* CONNECTIONMODULE_H */
