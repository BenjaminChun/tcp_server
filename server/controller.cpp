#include <iostream>
#include "./include/ReadRequest.h"
#include "./include/ConnectionModule.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include <list>
#include <string>
#include <utility> // For std::pair
#include "./include/WriteRequest.h"
#include "./include/MonitorRequest.h"
#include <unistd.h> // Include the <unistd.h> header file for the sleep function

// controller listens to a port on start and waits for connection
// on connection
//     calls the marshaller mod -> return the request object
//     find out what type of request
//     process the request accordingly
//     pass the output to the marshaller
//     return to the ip addr
//     continues the connection listening loop

int MAX_RESPONSE_BUFFER_LENGTH = 100;

// create global variable globalhashmap
HashMap globalHashMap;

int main() {
    while (true)
    {
        // TODO test connection with marshaller
        // construct connection module object
        ConnectionModule conn(8080);

        // Accept incoming connections
        int clientSocket = conn.waitForConnection();
        if (clientSocket == -1) {
            return 1; // Exit if accepting connection fails
        }
        // return 2;

        // Receive data
        char receiveBuffer[1024]; // Assuming a maximum buffer size of 1024 bytes
        if (conn.receiveData(receiveBuffer, sizeof(receiveBuffer)) == false) {
            return 1; // Exit if receiving fails
        }

        // TODO Marshaller
        // Instantiate marshaller
        Marshaller marshaller;

        // pass thru unmarshaller
        Request requestObject = Marshaller.unmarshal(receiveBuffer);

        // initialise buffer to store return value from services
        std::vector<char> buffer(MAX_RESPONSE_BUFFER_LENGTH);

        // TODO: Iron out with jx on the return var
        // TODO: change the request interface so that everything is common
        // read
        if (typeid(requestObject)==typeid(ReadRequest)) {
            requestObject.process();
            requestObject.checkMonitor(globalHashMap);
            globalHashMap.printAll();
        }
        // write
        else if (typeid(requestObject)==typeid(WriteRequest)){
            requestObject.process();
        }
        // monitor
        else if (typeid(requestObject)==typeid(MonitorRequest)){
            requestObject.process();
        }
        else {
            // print error message opcode does not exist
            std::cout << "Error: opcode " << requestObject.opcode << " does not exist." << std::endl;
        }

        // after going thru the server service

        // create response object
    }
}