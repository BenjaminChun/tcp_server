#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
protected:
    std::string uniqueID;
    int opcode;
    std::string pathName;

public:
    Request(const std::string& uniqueID, int opcode, const std::string& pathName);
    virtual ~Request() = default;

    virtual void process() = 0;
};

#endif // REQUEST_H
