#ifndef MARSHALLER_H
#define MARSHALLER_H

// #include <winsock2.h>

#include <cstdint>
#include <cstring>
#include <string>

class Marshaller {
   public:
    /**
     * @brief Marshalls a string into a uint32* buffer.
     *
     * @param buffer Buffer from which the string is to be stored.
     * @param paddingSize Size of padding to be added to the buffer.
     * @param string Stored String.
     */
    static void marshallString(uint8_t **buffer, int paddingSize,
                               std::string string);

    /**
     * @brief Marshalls a short integer into a uint32* buffer.
     *
     * @param buffer Buffer from which the short integer is to be stored.
     * @param value Stored short integer.
     */
    static void marshallShort(uint8_t **buffer, short value);

    /**
     * @brief Marshalls an integer into a uint32* buffer.
     *
     * @param buffer Buffer from which the integer is to be stored.
     * @param value Stored integer.
     */
    static void marshallInt(uint8_t **buffer, int value);

    /**
     * @brief Marshalls a long integer into a uint32* buffer.
     *
     * @param buffer Buffer from which the long integer is to be stored.
     * @param value Stored long integer.
     */
    static void marshallLong(uint8_t **buffer, long value);

    /**
     * @brief Marshalls a long long integer into a uint32* buffer.
     *
     * @param buffer Buffer from which the long long integer is to be stored.
     * @param value Stored long long integer.
     */
    static void marshallLongLong(uint8_t **buffer, long long value);

    /**
     * @brief Marshalls a float into a uint32* buffer.
     *
     * @param buffer Buffer from which the long long integer is to be stored.
     * @param value Stored long long integer.
     */
    static void marshallFloat(uint8_t **buffer, float value);

    /**
     * @brief Converts a uint64_t value from host byte to network byte order.
     *
     * @param value uint64 value to be converted.
     * @return uint64_t value
     */
    static uint64_t htonll(uint64_t value);

    /**
     * @brief Calculates the size of padding for a given data type length.
     *
     * @param length Length of the data type for which padding is added.
     * @return Size of padding.
     */
    static int calculatePadding(int length);
    static int calculatePadding(long long length);
};

#endif