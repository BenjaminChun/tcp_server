#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "./HashMap.h"

class Request {
public:
    int opcode;
    int uniqueID;
    std::string pathName;
    Request(int uniqueID, int opcode, const std::string& pathName);
    // ~Request() = default;
    void process();
    void setPathName();
    bool checkMonitor(HashMap hashmap);
};

#endif // REQUEST_H
