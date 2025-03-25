#ifndef CVT_H
#define CVT_H

#include "string.h"

/** Convert Class
 */
class Cvt
{
public:
    /** Converts an int/s32 value into a string.
     */
    static string ToString(s32 number);
    /** Converts a uint/u32 value into a string.
     */
    static string ToString(u32 number);

private:
};

#endif // CVT_H
