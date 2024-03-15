#include <iostream>
#include "./include/ReadRequest.h"

int main() {
    // Create a ReadRequest object
    ReadRequest readReq("1234", 1, "/path/to/file.txt", 100, 512);
    // Call process method
    readReq.process();

    return 0;
}
