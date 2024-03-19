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
#include "./include/marshaller.h"
#include "./include/unmarshaller.h"
#include "./include/ListRequest.h"

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

Request unmarshallRequest(uint8_t **requestBuffer) {
    // int8_t bytesArray[] = {59,-39,-73,-36,0,0,0,2,0,0,0,8,102,105,108,101,46,116,120,116,0,0,0,0,0,0,0,0,0,0,0,23,72,101,108,108,111,10,87,111,114,108,100,90,90,90,90,90,90,10,71,114,101,97,116,0};

    // uint8_t bytesArray2[sizeof(bytesArray)];
    // for (int i = 0; i < sizeof(bytesArray); i++) {
    //     bytesArray2[i] = bytesArray[i];
    // }

    // uint8_t *bufferPtr = bytesArray2;
    // *requestBuffer = bufferPtr;

    Request req(123,1,"test.txt");
    // Change the parameters name as you like
    req.uniqueID = Unmarshaller::unmarshallInt(requestBuffer);
    req.opcode = Unmarshaller::unmarshallInt(requestBuffer);
    // print req opcode
    // std::cout << "IN UNMARSHALL Request opcode: " << req.opcode << std::endl;
    std::string filename = Unmarshaller::unmarshallString(requestBuffer);

    // Switch for specific request to unmarshall
    switch (req.opcode) {
        case 1: {
            ReadRequest ReadRequest(req.uniqueID,req.opcode,filename,Unmarshaller::unmarshallInt(requestBuffer),Unmarshaller::unmarshallInt(requestBuffer));
            return ReadRequest;
        }
        // case 5: {
        //     // add code to initialise the request object and return it
        //     req.offset = Unmarshaller::unmarshallInt(requestBuffer);
        //     req.bytesToReadFrom = Unmarshaller::unmarshallInt(requestBuffer);

        //     return req;
        // }

        case 2: {
            // add code to create back the structure and return it
            int offset = Unmarshaller::unmarshallInt(requestBuffer);
            std::string bytesToWrite = Unmarshaller::unmarshallString(requestBuffer);
            WriteRequest WriteReq(req.uniqueID,req.opcode,filename,offset,bytesToWrite);
            // print uniqueid, opcode, filename, offset, bytestowrite
            // std::cout << "IN UNMARSHAL WriteRequest uniqueID: " << WriteReq.uniqueID << std::endl;
            // std::cout << "IN UNMARSHAL WriteRequest opcode: " << WriteReq.opcode << std::endl;
            // std::cout << "IN UNMARSHAL WriteRequest filename: " << filename << std::endl;
            // std::cout << "IN UNMARSHAL WriteRequest bytestowrite: " << bytesToWrite << std::endl;
            // // print typeid write req
            // std::cout << "IN SWITCH WriteRequest type: " << typeid(WriteReq).name() << std::endl;
            return WriteReq;
        }

        case 3: {
            // add code to create back the structure and return it
            int interval = Unmarshaller::unmarshallInt(requestBuffer);
            MonitorRequest MonitorReq(req.uniqueID,req.opcode,filename,interval);
            return MonitorReq;
        }

        case 4: {
            ListRequest ListReq(req.uniqueID,req.opcode,filename);
            return ListReq;
        }

        default: {
            // std::cout << "IN UNMARSHAL SWITCH Error: opcode " << req.opcode << " does not exist." << std::endl;
            break;
        }
    }
    // delete[] bufferPtr;
    delete[] requestBuffer;  // Not sure delete from where but need to delete[]
                             // the uint8_t buffer
    return req;
}

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
        // pass thru unmarshaller
        // convert to uint8_t
        // char receiveBuffer[1024];

        Request requestObject = unmarshallRequest(reinterpret_cast<uint8_t**>(&receiveBuffer));
        // Request requestObject = Marshaller.unmarshal(receiveBuffer);
        
        // print typeid requestobject
        // std::cout << "Request object type: " << typeid(requestObject).name() << std::endl;

        // initialise buffer to store return value from services
        std::vector<char> buffer(MAX_RESPONSE_BUFFER_LENGTH);

        // TODO: Iron out with jx on the return var
        // TODO: change the request interface so that everything is common
        // read
        if (requestObject.opcode==1 || requestObject.opcode == '1') {
            requestObject.process();
            requestObject.checkMonitor(globalHashMap);
            globalHashMap.printAll();
        }
        // write
        else if (requestObject.opcode==2 || requestObject.opcode == '2'){
            requestObject.process();
            // print executed write
            std::cout << "Executed Write for " << requestObject.pathName << " with offset " << std::endl;
        }
        // monitor
        else if (requestObject.opcode==3 || requestObject.opcode=='3'){
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