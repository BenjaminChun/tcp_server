#include "../include/Request.h"

Request::Request(int uniqueID, int opcode, const std::string& pathName)
    : uniqueID(uniqueID), opcode(opcode), pathName(pathName) {}

void Request::process() {
    // Implement processing
    std::cout << "Processing for " << pathName << std::endl;
};

void Request::setPathName() {
    // Implement setting pathName
    std::cout << "Setting pathName for " << pathName << std::endl;
};

bool Request::checkMonitor(HashMap hashmap) {
    // Implement checking for monitor
    std::cout << "Checking for monitor for " << pathName << std::endl;
    return false;
};