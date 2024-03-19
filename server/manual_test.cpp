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
        // // TODO test connection with marshaller
        // // construct connection module object
        // ConnectionModule conn(8080);

        // // Accept incoming connections
        // int clientSocket = conn.waitForConnection();
        // if (clientSocket == -1) {
        //     return 1; // Exit if accepting connection fails
        // }
        // // return 2;

        // // Receive data
        // char receiveBuffer[1024]; // Assuming a maximum buffer size of 1024 bytes
        // if (conn.receiveData(receiveBuffer, sizeof(receiveBuffer)) == false) {
        //     return 1; // Exit if receiving fails
        // }

        // pass thru unmarshaller
        // TODO

        // initialise buffer to store return value from services
        std::vector<char> buffer(MAX_RESPONSE_BUFFER_LENGTH);

        // TEST to remove: Create a ReadRequest object
        MonitorRequest requestObject = MonitorRequest("1234", 3, "file.txt", 1000);
        // monitor file.txt
        requestObject.process(globalHashMap);
        // create readrequest
        ReadRequest requestObject2 = ReadRequest("1234", 1, "file.txt", 0, 10);
        // read and check if file is being monitored
        requestObject2.process();
        if (requestObject2.checkMonitor(globalHashMap)){
            // find the machine that registered
            // send the file to the machine
        };
        globalHashMap.printAll();

        // TODO: Iron out with jx on the return var
        // // read
        // if (typeid(requestObject)==typeid(ReadRequest)) {
        //     requestObject.process();
        //     requestObject.checkMonitor(globalHashMap);
        //     globalHashMap.printAll();
        // }
        // // write
        // else if (typeid(requestObject)==typeid(WriteRequest)){
        //     requestObject.process();
        // }
        // // monitor
        // else if (typeid(requestObject)==typeid(MonitorRequest)){
        //     requestObject.process();
        // }
        // else {
        //     // print error message opcode does not exist
        //     std::cout << "Error: opcode " << requestObject.opcode << " does not exist." << std::endl;
        // }

        // after going thru the server service

        // create response object
    }
}