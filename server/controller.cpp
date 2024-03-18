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

// controller listens to a port on start and waits for connection
// on connection
//     calls the marshaller mod -> return the request object
//     find out what type of request
//     process the request accordingly
//     pass the output to the marshaller
//     return to the ip addr
//     continues the connection listening loop

int MAX_RESPONSE_BUFFER_LENGTH = 100;

// Define the hashmap type
using HashMapType = std::unordered_map<std::string, std::list<std::pair<std::string, time_t>>>;

// Declare the global hashmap variable
HashMapType globalHashMap;

int main() {

    // // Usage example
    // std::string key = "example_key";
    // std::list<std::pair<std::string, time_t>> value = {{"value1", time(nullptr)}, {"value2", time(nullptr)}};

    // // Insert key-value pair into the global hashmap
    // globalHashMap[key] = value;

    // // Accessing elements in the hashmap
    // std::cout << "Values associated with key '" << key << "':" << std::endl;
    // for (const auto& pair : globalHashMap[key]) {
    //     std::cout << "String: " << pair.first << ", Time: " << pair.second << std::endl;
    // }

    int port = 8080; // Example port
    
    // construct connection module object
    // ConnectionModule conn(port);

    // // Accept incoming connections
    // int clientSocket = conn.waitForConnection();
    // if (clientSocket == -1) {
    //     return 1; // Exit if accepting connection fails
    // }
    // // return 2;

    // Receive data
    // char receiveBuffer[1024]; // Assuming a maximum buffer size of 1024 bytes
    // if (conn.receiveData(receiveBuffer, sizeof(receiveBuffer)) == false) {
    //     return 1; // Exit if receiving fails
    // }

    // pass thru unmarshaller
    // TODO

    // initialise buffer to store return value from services
    std::vector<char> buffer(MAX_RESPONSE_BUFFER_LENGTH);

    // TEST: Create a ReadRequest object
    ReadRequest requestObject = ReadRequest("1234", 1, "file.txt", 0, 10);

    // read
    if (requestObject.opcode == 1) {
        requestObject.process();
        // requestObject.checkMonitor(&globalHashMap);
    }
    // write
    else if (requestObject.opcode == 2){
        requestObject.process();
    }
    // monitor
    else if (requestObject.opcode == 3){
        requestObject.process();
    }
    else {
        // print error message opcode does not exist
        std::cout << "Error: opcode " << requestObject.opcode << " does not exist." << std::endl;
    }

    // after going thru the server service
    
    // create response object
    

    // pass response thru the marshaller
    

    
    // // Create a ReadRequest object
    // ReadRequest readReq("1234", 1, "file.txt", 0, 10);
    // // Call process method
    // readReq.process();

    // return 0;
}