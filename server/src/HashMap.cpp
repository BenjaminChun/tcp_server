#include "../include/HashMap.h"

void HashMap::insert(const std::string& key, const std::string& machineID, const std::chrono::system_clock::time_point& expiryTime) {
    hashMap[key] = std::make_pair(machineID, expiryTime);
}

void HashMap::removeIfExpired() {
    auto now = std::chrono::system_clock::now();
    for (auto it = hashMap.begin(); it != hashMap.end(); ) {
        if (it->second.second < now) {
            it = hashMap.erase(it);
        } else {
            ++it;
        }
    }
}

void HashMap::printAll() {
    for (const auto& entry : hashMap) {
        std::cout << "Key: " << entry.first << ", MachineID: " << entry.second.first << ", ExpiryTime: " << std::chrono::system_clock::to_time_t(entry.second.second) << std::endl;
    }
}

bool HashMap::contains(const std::string& keyToCheck) {
    // Remove expired entries
    removeIfExpired();

    // Check if the parameter is a key
    auto it = hashMap.find(keyToCheck);
    if (it != hashMap.end()) {
        // Key found, return false
        return false;
    } else {
        // Key not found, return true
        return true;
    }
}
