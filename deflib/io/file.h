#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "../data/string.h"
#include "../collections/array.h"
/**
 * File Class
 */
class File
{
public:
    typedef enum {
        Read,
        ReadWrite,
        CreateWrite,
        CreateReadWrite,
        Append,
        ReadAppend,
    } OpenMode;

    /**
     * Creates an empty/unopened File object.
     */
    File();
    /**
     * Creates an opens a File object for a given file with the given mode.
     */
    File(const string& path, OpenMode mode, bool binary);
    /**
     * Destructor
     */
    ~File();

    /**
     * Returns the total file size.
     */
    u64 size();
    /**
     * Repositions file pointer to be at whence + offset.
     * @note whence uses SEEK_SET, SEEK_CUR, SEEK_END from stdio.h.
     */
    int seek(s64 offset, s32 whence);
    /**
     * Returns the current position of the file pointer.
     */
    u64 tell();

    u64 read(Array<byte>& buffer, u64 n);
private:
    FILE* _fp;
    string _path;
    string _fname;
    u64 _fsize;

    Array<string> _modes = {
        "r", "r+",
        "w", "w+",
        "a", "a+"
    };
};

#endif // FILE_H
