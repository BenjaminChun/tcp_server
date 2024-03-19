#include "../include/unmarshaller.h"

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

std::string Unmarshaller::unmarshallString(uint8_t **buffer) {
    uint32_t netStringLength;
    // memcpy(&netStringLength, *buffer, sizeof(uint32_t));

    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(
        &netStringLength);  // Byte pointer to the netStringLength

    // Loop to manually copy each byte of buffer to netStringLength
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        lengthByte[i] = (*buffer)[i];
    }
    *buffer += sizeof(uint32_t);

    int actualStringLength = ntohl(netStringLength);
    // std::string str(reinterpret_cast<char *>(*buffer), actualStringLength);

    std::string str;
    for (size_t i = 0; i < actualStringLength; ++i) {
        str += (*buffer)[i];
    }

    int paddingSize = calculatePadding(actualStringLength);
    // Advance the pointer
    *buffer += actualStringLength;
    *buffer += paddingSize;

    return str;
}

short Unmarshaller::unmarshallShort(uint8_t **buffer) {
    uint16_t netValue;
    // memcpy(&netValue, *buffer, sizeof(uint16_t));
    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);
    for (int i = 0; i < sizeof(uint16_t); ++i) {
        lengthByte[i] = (*buffer)[i];
    }
    short value = ntohs(netValue);
    *buffer += sizeof(uint32_t);

    return value;
}

int Unmarshaller::unmarshallInt(uint8_t **buffer) {
    uint32_t netValue;
    // memcpy(&netValue, *buffer, sizeof(uint32_t));

    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        lengthByte[i] = (*buffer)[i];
    }
    int value = ntohl(netValue);
    *buffer += sizeof(uint32_t);

    return value;
}

long Unmarshaller::unmarshallLong(uint8_t **buffer) {
    // uint64_t netValue;
    // memcpy(&netValue, *buffer, sizeof(uint64_t));
    uint32_t netValue;
    // memcpy(&netValue, *buffer, sizeof(uint32_t));
    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        lengthByte[i] = (*buffer)[i];
    }
    long value = ntohl(netValue);

    *buffer += sizeof(uint32_t);

    return value;
}

float Unmarshaller::unmarshallFloat(uint8_t **buffer) {
    uint32_t netValue;
    // memcpy(&netValue, *buffer, sizeof(uint32_t));
    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);
    for (int i = 0; i < sizeof(uint32_t); ++i) {
        lengthByte[i] = (*buffer)[i];
    }
    uint32_t value = ntohl(netValue);
    FloatAndInt floatValue;
    floatValue.i = value;
    float fl = floatValue.f;  // Retrieve the original float value from the
                              // IEEE representation
    *buffer += sizeof(uint32_t);
    return fl;
}

long long Unmarshaller::unmarshallLongLong(uint8_t **buffer) {
    uint64_t netValue;
    // memcpy(&netValue, *buffer, sizeof(uint64_t));
    uint8_t *lengthByte = reinterpret_cast<uint8_t *>(&netValue);

    for (int i = 0; i < sizeof(uint64_t); ++i) {
        lengthByte[i] = (*buffer)[i];
    }
    long long value = ntohl(netValue);

    *buffer += sizeof(uint64_t);

    return value;
}

long long Unmarshaller::ntohll(uint64_t netValue) {
    // Ensure the endianness of the system
    uint16_t check = 0x0001;
    if (*(uint8_t *)&check == 0x01) {  // Little endian
        int highPart = ntohl(static_cast<uint32_t>(netValue >> 32));
        int lowPart = ntohl(static_cast<uint32_t>(netValue));
        return (static_cast<long long>(highPart) << 32) | lowPart;
    } else {  // Big endian
        return static_cast<long long>(netValue);
    }
}

// Helper method to calculate padding
int Unmarshaller::calculatePadding(int length) {
    return BOUNDARY_SIZE - (length % BOUNDARY_SIZE);
}

int Unmarshaller::calculatePadding(long long length) {
    return BOUNDARY_SIZE - static_cast<int>(length % BOUNDARY_SIZE);
}
