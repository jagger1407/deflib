#ifndef DEFLIB_INC
#define DEFLIB_INC

#include "types.h"
#include "cvt.h"

#include "data/string.h"

#include "collections/array.h"
typedef Array<string> StringArray;
typedef Array<char> CharArray;
typedef Array<s16> Int16Array;
typedef Array<s32> Int32Array;
typedef Array<s64> Int64Array;
typedef Array<u8> UInt8Array;
typedef Array<u8> ByteArray;
typedef Array<u16> UInt16Array;
typedef Array<u32> UInt32Array;
typedef Array<u64> UInt64Array;

#include "io/defcon.h"

#endif
