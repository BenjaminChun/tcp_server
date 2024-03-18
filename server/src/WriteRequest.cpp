#include "../include/WriteRequest.h"
#include <iostream>
#include <vector>
#include <fstream>

WriteRequest::WriteRequest(const std::string& uniqueID, int opcode, const std::string& pathName, int offset, std::vector<char> bytesToWrite)
    : Request(uniqueID, opcode, pathName), offset(offset), bytesToWrite(bytesToWrite) {}

bool writeFile(const std::string& filePath, int offset, const std::vector<char>& bytesToWrite) {
    // Open the file in binary mode for writing
    std::ofstream file(filePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << filePath << std::endl;
        return false;
    }

    // Seek to the specified offset
    file.seekp(offset);

    // Write the bytes to the file
    file.write(bytesToWrite.data(), bytesToWrite.size());

    // Check for any write errors
    if (file.fail()) {
        std::cerr << "Error: Failed to write to file " << filePath << std::endl;
        file.close();
        return false;
    }

    // Close the file
    file.close();

    return true;
}

void WriteRequest::setPathName(){
    pathName = "/home/bchun001/tcp_server/file_sys/"+pathName;
}

void WriteRequest::process() {
    // format the filepath to relative
    setPathName();
    // Implement processing for ReadRequest
    // std::vector<char> buffer(ReadRequest::numBytesToRead);
    // buffer = readFile(ReadRequest::pathName, ReadRequest::offset, ReadRequest::numBytesToRead);

    // Implement processing
    writeFile(WriteRequest::pathName,WriteRequest::offset,WriteRequest::bytesToWrite);
    std::cout << "Processed Write for " << pathName << " with offset " << offset << " and sequence " << std::endl;
}