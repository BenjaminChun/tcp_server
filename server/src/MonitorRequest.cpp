#include "../include/MonitorRequest.h"
#include <iostream>
#include <vector>
#include <fstream>

MonitorRequest::MonitorRequest(const std::string& uniqueID, int opcode, const std::string& pathName, int lengthOfInterval)
    : Request(uniqueID, opcode, pathName), lengthOfInterval(lengthOfInterval) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::system_clock::duration interval = std::chrono::seconds(lengthOfInterval);
        expiryTime = now + interval; // Calculating expiry time
    }

void MonitorRequest::setPathName(){
    pathName = "/home/bchun001/tcp_server/file_sys/"+pathName;
}

void MonitorRequest::process(HashMap& hashMap) {
    // format the filepath to relative
    setPathName();
    // add to hashmap current file:[machineid, expiry time]
    hashMap.insert(MonitorRequest::pathName, MonitorRequest::uniqueID, MonitorRequest::expiryTime);
    std::cout << "Processed Monitor for " << pathName << std::endl;
}