#ifndef UNMARSHALLER_H
#define UNMARSHALLER_H

// #include <WinSock2.h>

#include <cstdint>
#include <cstring>
#include <string>

class Unmarshaller {
   public:
    /**
     * @brief Unmarshalls a string from a uint32* buffer.
     *
     * @param buffer Buffer from which the string is to be retrieved, pointer to
     * pointer to keep track of the position of buffer.
     * @return Retrieved string.
     */
    static std::string unmarshallString(uint8_t **buffer);

    /**
     * @brief Unmarshalls a short integer from a uint32* buffer.
     *
     * @param buffer Buffer from which the short integer is retrieved.
     * @return Retrieved short integer.
     */
    static short unmarshallShort(uint8_t **buffer);

    /**
     * @brief Unmarshalls an integer from a uint32* buffer.
     *
     * @param buffer Buffer from which the integer is retrieved.
     * @return Retrieved integer.
     */
    static int unmarshallInt(uint8_t **buffer);

    /**
     * @brief Unmarshalls a long integer from a uint32* buffer.
     *
     * @param buffer Buffer from which the long integer is retrieved.
     * @return Retrieved long integer.
     */
    static long unmarshallLong(uint8_t **buffer);

    /**
     * @brief Unmarshalls a float from a uint32* buffer.
     *
     * @param buffer Buffer from which the float is retrieved.
     * @return Retrieved float.
     */
    static float unmarshallFloat(uint8_t **buffer);

    /**
     * @brief Unmarshalls a lon g long integer from a uint32* buffer.
     *
     * @param buffer Buffer from which the long long integer is retrieved.
     * @return Retrieved long long interger.
     */
    static long long unmarshallLongLong(uint8_t **buffer);

    /**
     * @brief Converts a uint64_t value to host byte order and casts it to a
     * long long integer.
     *
     * @param buffer uint64 value to be converted to a long long integer.
     * @return Converted long long integer.
     */
    static long long ntohll(uint64_t netValue);

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