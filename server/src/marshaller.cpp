#include "../include/marshaller.h"

// #include <winsock2.h>
#include <netinet/in.h>

#include <cstdint>
#include <cstring>
#include <string>
#define BOUNDARY_SIZE 4

// To access the raw bits of the float for IEEE representation
union FloatAndInt {
    float f;
    uint32_t i;
};

void Marshaller::marshallString(uint8_t **buffer, int paddingSize,
                                std::string string) {
    size_t length = string.length();
    uint32_t netLength = htonl(
        static_cast<uint32_t>(length));  // htonl accepts unsigned integers

    // memcpy(*buffer, &netLength, sizeof(uint32_t));

    uint8_t *lengthByte =
        reinterpret_cast<uint8_t *>(&netLength);  // Byte pointer to netLength

    // Loop to manually copy each byte of netLength to buffer
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        (*buffer)[i] = lengthByte[i];
    }
    *buffer += sizeof(uint32_t);
    // memcpy(*buffer, string.c_str(), length);

    // Loop to manually copy each byte of string to buffer
    for (int i = 0; i < length; ++i) {
        (*buffer)[i] = string[i];
    }
    *buffer += length;

    // Add padding to boundary for memory management
    for (int i = 0; i < paddingSize; i++) {
        **buffer = 0;
        *buffer += 1;
    }
}

void Marshaller::marshallShort(uint8_t **buffer, short value) {
    uint16_t netValue = htons(static_cast<uint16_t>(value));
    // memcpy(*buffer, &netValue, sizeof(uint16_t));
    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);

    for (int i = 0; i < sizeof(uint16_t); ++i) {
        (*buffer)[i] = lengthByte[i];
    }
    *buffer += sizeof(uint32_t);
}

void Marshaller::marshallInt(uint8_t **buffer, int value) {
    uint32_t netValue = htonl(static_cast<uint32_t>(value));
    // memcpy(*buffer, &netValue, sizeof(uint32_t));

    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);

    for (int i = 0; i < sizeof(uint32_t); ++i) {
        (*buffer)[i] = lengthByte[i];
    }
    *buffer += sizeof(uint32_t);
}

void Marshaller::marshallLong(uint8_t **buffer, long value) {
    uint32_t netValue = htonl(static_cast<uint32_t>(value));
    // memcpy(*buffer, &netValue, sizeof(uint32_t));

    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);

    for (int i = 0; i < sizeof(uint32_t); ++i) {
        (*buffer)[i] = lengthByte[i];
    }
    *buffer += sizeof(uint32_t);
}

void Marshaller::marshallLongLong(uint8_t **buffer, long long value) {
    // uint64_t netValue = htonll(static_cast<uint64_t>(value));
    // memcpy(*buffer, &netValue, sizeof(uint64_t));
    uint64_t netValue = htonll(static_cast<uint64_t>(value));
    // memcpy(*buffer, &netValue, sizeof(uint64_t));
    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);

    for (int i = 0; i < sizeof(uint64_t); ++i) {
        (*buffer)[i] = lengthByte[i];
    }
    *buffer += sizeof(uint64_t);
}

void Marshaller::marshallFloat(uint8_t **buffer, float value) {
    FloatAndInt floatValue;
    floatValue.f = value;
    uint32_t uintFloat = floatValue.i;  // Get IEEE representation of float
    uint32_t netValue = htonl(uintFloat);
    // memcpy(*buffer, &netValue, sizeof(uint32_t));
    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);

    for (int i = 0; i < sizeof(uint32_t); ++i) {
        (*buffer)[i] = lengthByte[i];
    }
    *buffer += sizeof(uint32_t);
}

uint64_t Marshaller::htonll(uint64_t value) {
    // Ensure the endianness of the system
    uint16_t check = 0x0001;
    if (*(uint8_t *)&check == 0x01) {  // Little endian
        int highPart = htonl(static_cast<uint32_t>(value >> 32));
        int lowPart = htonl(static_cast<uint32_t>(value));
        return (static_cast<uint64_t>(highPart) << 32) | lowPart;
    } else {  // Big endian
        return value;
    }
}

// Helper method to calculate padding
int Marshaller::calculatePadding(int length) {
    return BOUNDARY_SIZE - (length % BOUNDARY_SIZE);
}

int Marshaller::calculatePadding(long long length) {
    return BOUNDARY_SIZE - static_cast<int>(length % BOUNDARY_SIZE);
}