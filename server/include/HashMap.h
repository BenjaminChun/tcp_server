#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <utility> // For std::pair

class HashMap {
private:
    std::unordered_map<std::string, std::pair<std::string, std::chrono::system_clock::time_point>> hashMap;

public:
    void insert(const std::string& key, const std::string& machineID, const std::chrono::system_clock::time_point& expiryTime);
    void removeIfExpired();
    void printAll();
    bool contains(const std::string& key);
};

#endif // HASHMAP_H
