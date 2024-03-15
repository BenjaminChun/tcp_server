#include "../include/ReadRequest.h"
#include <iostream>

ReadRequest::ReadRequest(const std::string& uniqueID, int opcode, const std::string& pathName, int offset, int numBytesToRead)
    : Request(uniqueID, opcode, pathName), offset(offset), numBytesToRead(numBytesToRead) {}

void ReadRequest::process() {
    // Implement processing for ReadRequest
    std::cout << "Processing ReadRequest for " << pathName << " with offset " << offset << " and numBytesToRead " << numBytesToRead << std::endl;
}
