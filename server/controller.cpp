#include <iostream>
#include "./include/ReadRequest.h"
#include "./include/ConnectionModule.h"
#include <vector>
#include <fstream>

// controller listens to a port on start and waits for connection
// on connection
//     calls the marshaller mod -> return the request object
//     find out what type of request
//     process the request accordingly
//     pass the output to the marshaller
//     return to the ip addr
//     continues the connection listening loop

int MAX_RESPONSE_BUFFER_LENGTH = 100;

int main() {

    int port = 8080; // Example port
    
    // construct connection module object
    ConnectionModule conn(port);

    // Accept incoming connections
    int clientSocket = conn.waitForConnection();
    if (clientSocket == -1) {
        return 1; // Exit if accepting connection fails
    }
    return 2;

    // Receive data
    char receiveBuffer[1024]; // Assuming a maximum buffer size of 1024 bytes
    if (conn.receiveData(receiveBuffer, sizeof(receiveBuffer)) == false) {
        return 1; // Exit if receiving fails
    }

    // pass thru unmarshaller
    // TODO

    // initialise buffer to store return value from services
    std::vector<char> buffer(MAX_RESPONSE_BUFFER_LENGTH);

    // if (requestObject.opcode == 1) {
    //     ReadRequest readreq = request;
    //     buffer = readreq.process();
    // }
    // else if (requestObject.opcode == 2){
        
    // }
    // else if (requestObject.opcode == 3){

    // }
    // else {
    //     error(request opcode does not exist %s , requestobject.opcode);
    // }

    // after going thru the server service
    
    // create response object
    

    // pass response thru the marshaller
    

    
    // // Create a ReadRequest object
    // ReadRequest readReq("1234", 1, "file.txt", 0, 10);
    // // Call process method
    // readReq.process();

    // return 0;
}