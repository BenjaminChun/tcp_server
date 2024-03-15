#include "../include/Request.h"

Request::Request(const std::string& uniqueID, int opcode, const std::string& pathName)
    : uniqueID(uniqueID), opcode(opcode), pathName(pathName) {}
