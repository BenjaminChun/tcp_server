#include "../include/ListRequest.h"
#include <iostream>
#include <vector>
#include <fstream>

ListRequest::ListRequest(int uniqueID, int opcode, const std::string& pathName)
    : Request(uniqueID, opcode, pathName) {}

// TODO: decide implementation need to return what
// void listDirectory(const std::string& filePath) {
    
// }

void ListRequest::setPathName(){
    pathName = "/home/bchun001/tcp_server/file_sys/"+pathName;
}

void ListRequest::process() {
    // format the filepath to relative
    setPathName();
    // Implement processing for ReadRequest
    // std::vector<char> buffer(ReadRequest::numBytesToRead);
    // buffer = readFile(ReadRequest::pathName, ReadRequest::offset, ReadRequest::numBytesToRead);

    // Implement processing
    std::cout << "Listed for " << pathName << std::endl;
}