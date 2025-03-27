#ifndef CVT_H
#define CVT_H

#include "data/string.h"
#include "collections/array.h"

/**
 * Conversion Class
 */
class Cvt
{
public:
    /**
     * Converts a boolean into a string.
     */
    static string ToString(bool b);
    /**
     * Converts a char/s8 value into a string.
     */
    static string ToString(char ch);
    /**
     * Converts a uchar/u8/byte value into a string.
     */
    static string ToString(byte value);
    /**
     * Converts a short/s16 value into a string.
     */
    static string ToString(s16 value);
    /**
     * Converts a ushort/u16 value into a string.
     */
    static string ToString(u16 value);
    /**
     * Converts an int/s32 value into a string.
     */
    static string ToString(s32 value);
    /**
     * Converts a uint/u32 value into a string.
     */
    static string ToString(u32 value);
    /**
     * Converts an longlong/s64 value into a string.
     */
    static string ToString(s64 value);
    /**
     * Converts a ulonglong/u64 value into a string.
     */
    static string ToString(u64 value);
    /**
     * Converts a ByteArray/Array<u8> into a string.
     * @note assumes bytes are valid characters.
     * non-valid trailing characters are ignored.
     */
    static string ToString(Array<u8> array);

    /**
     * Converts a string into a char/s8.
     * @note string format must be a number, i.e. "120"
     * non-valid trailing characters are ignored.
     */
    static s8 ToInt8(const string& str);
    /**
     * Converts a string into a short/s16.
     * @note string format must be a number, i.e. "120"
     * non-valid trailing characters are ignored.
     */
    static s16 ToInt16(const string& str);
    /**
     * Converts a string into an int/s32.
     * @note string format must be a number, i.e. "120"
     * non-valid trailing characters are ignored.
     */
    static s32 ToInt32(const string& str);
    /**
     * Converts a string into a longlong/s64.
     * @note string format must be a number, i.e. "120"
     * non-valid trailing characters are ignored.
     */
    static s64 ToInt64(const string& str);
private:
};

#endif // CVT_H
