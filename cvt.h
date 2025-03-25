#ifndef CVT_H
#define CVT_H

#include "string.h"

/**
 * Convert Class
 */
class Cvt
{
public:
    /**
     * Converts an int/s32 value into a string.
     */
    static string ToString(s32 number);
    /**
     * Converts a uint/u32 value into a string.
     */
    static string ToString(u32 number);
    /**
     * Converts a boolean into a string.
     */
    static string ToString(bool b);

    /**
     * Converts a string into an s32.
     */
    static s32 ToInt32(const string& str);
private:
};

#endif // CVT_H
