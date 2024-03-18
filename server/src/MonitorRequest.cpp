#include "../include/MonitorRequest.h"
#include <iostream>
#include <vector>
#include <fstream>

MonitorRequest::MonitorRequest(const std::string& uniqueID, int opcode, const std::string& pathName, int lengthOfInterval)
    : Request(uniqueID, opcode, pathName), lengthOfInterval(lengthOfInterval) {}

bool monitorFile(const std::string& filePath, int lengthOfInterval) {
    // Add to hashmap of file:[machine,time]
    return true;
}

void MonitorRequest::setPathName(){
    pathName = "/home/bchun001/tcp_server/file_sys/"+pathName;
}

void MonitorRequest::process() {
    // format the filepath to relative
    setPathName();
    // Implement processing for ReadRequest
    // std::vector<char> buffer(ReadRequest::numBytesToRead);
    // buffer = readFile(ReadRequest::pathName, ReadRequest::offset, ReadRequest::numBytesToRead);

    // Implement processing
    monitorFile(MonitorRequest::pathName,MonitorRequest::lengthOfInterval);
    std::cout << "Processed Monitor for " << pathName << std::endl;
}