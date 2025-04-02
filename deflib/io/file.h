#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "../data/string.h"
#include "../collections/array.h"

#ifdef _WIN32
#include <direct.h>
inline char* realpath(const char* path, char* buffer) {
    return _getcwd(buffer, PATH_MAX);
}
#endif

/**
 * File Class
 */
class File
{
public:
    /**
     * Open Mode for file reading.
     */
    typedef enum {
        /**Open file for reading. The stream is positioned at
         * the beginning of the file.
         */
        Read,
        /**Open for reading and writing. The stream is positioned at
         * the beginning of the file.
         */
        ReadWrite,
        /**Truncate file to zero length or create text file for
         * writing.  The stream is positioned at the beginning of the
         * file.
         */
        CreateWrite,
        /**Open for reading and writing.  The file is created if it
         * does not exist, otherwise it is truncated.  The stream is
         * positioned at the beginning of the file.
         */
        CreateReadWrite,
        /**Open for appending (writing at end of file).  The file is
         * created if it does not exist.  The stream is positioned at
         * the end of the file.
         */
        Append,
        /**Open for reading and appending (writing at end of file).
         * The file is created if it does not exist.  Output is always
         * appended to the end of the file.
         */
        ReadAppend,
    } OpenMode;

#define PATH_MAX 4096

#ifdef _WIN32
#define PATH_SEPERATOR '\\'
#elif defined(__unix__)
#define PATH_SEPERATOR '/'
#endif

    /**
     * Creates an empty/unopened File object.
     */
    File();
    /**
     * Creates an opens a File object for a given file with the given mode.
     */
    File(const string& path, OpenMode mode, bool binary);
    /**
     * Creates and opens a File objects with the given mode passed as a string.
     * arguments are interchangable with fopen().
     */
    File(const string& path, string mode);
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
    s64 seek(s64 offset, s32 whence);
    /**
     * Returns the current position of the file pointer.
     * @note calls ftell() and syncs cached position.
     */
    u64 tell();
    /**
     * Returns the current position of the file pointer.
     * @note doesn't call ftell.
     */
    u64 pos();
    /**
     * Gets the location of this file.
     */
    string location();
    /**
     * Gets the path to this file.
     */
    string path();
    /**
     * Gets the full path to this file.
     */
    string fullPath();
    /**
     * Gets the name of the file.
     */
    string name();
    /**
     * Returns true if the end of the file has been reached.
     */
    bool eof();
    /**
     * Returns true if File object currently has a file open.
     */
    bool isOpen();
    /**
     * Gets the open mode of the currently opened file.
     */
    OpenMode mode();
    /**
     * Opens a file with a given mode.
     * @note if File object was used before, close() must be called beforehand.
     */
    int open(const string& path, OpenMode mode, bool binary);
    /**
     * Opens a file with a given mode.
     * @note if File object was used before, close() must be called beforehand.
     */
    int open(const string& path, string mode);
    /**
     * Closes the file.
     * @note Destructor already calls fclose(),
     * this usually doesn't have to be called manually.
     */
    void close();

    /**
     * @note invalidates rvalue's file pointer!
     */
    File& operator=(const File& f);
    /**
     * Reads n bytes into a buffer.
     * Essentially a wrapper for fread().
     */
    u64 read(Array<byte>& buffer, u64 n);
    /**
     * Reads the whole file into a Byte Array.
     */
    Array<byte> readFile();
    /**
     * Reads a signed 8-bit value from this file.
     */
    char readChar();
    /**
     * Reads an unsigned 8-bit value from this file.
     */
    byte readByte();
    /**
     * Reads a signed 16-bit value from this file.
     */
    s16 readShort();
    /**
     * Reads an unsigned 16-bit value from this file.
     */
    u16 readUnsignedShort();
    /**
     * Reads a signed 32-bit value from this file.
     */
    s32 readInt();
    /**
     * Reads an unsigned 32-bit value from this file.
     */
    u32 readUnsignedInt();
    /**
     * Reads a signed 64-bit value from this file.
     */
    s64 readLong();
    /**
     * Reads an unsigned 64-bit value from this file.
     */
    u64 readUnsignedLong();
    /**
     * Reads a 32-bit precision floating point value from this file.
     */
    f32 readFloat();
    /**
     * Reads a 64-bit precision floating point value from this file.
     */
    f64 readDouble();
    /**
     * Reads one line of text from this file.
     * @note this function starts at the current file pointer position.
     * It does not copy the '\n' character.
     */
    string readLine();

    /**
     * Writes a whole byte array to this file.
     * Returns the total amount of bytes written.
     */
    u64 write(Array<u8> bytes);
    /**
     * Writes n bytes of a byte array to the file.
     * Returns the total amount of bytes written.
     */
    u64 write(Array<u8> bytes, u64 n);
    /**
     * Writes a signed 8-bit value to this file.
     */
    void writeChar(char value);
    /**
     * Writes an unsigned 8-bit value to this file.
     */
    void writeByte(byte value);
    /**
     * Writes a signed 16-bit value to this file.
     */
    void writeShort(s16 value);
    /**
     * Writes an unsigned 16-bit value to this file.
     */
    void writeUnsignedShort(u16 value);
    /**
     * Writes a signed 32-bit value to this file.
     */
    void writeInt(s32 value);
    /**
     * Writes an unsigned 32-bit value to this file.
     */
    void writeUnsignedInt(u32 value);
    /**
     * Writes a signed 64-bit value to this file.
     */
    void writeLong(s64 value);
    /**
     * Writes an unsigned 64-bit value to this file.
     */
    void writeUnsignedLong(u64 value);
    /**
     * Writes a 32-bit precision floating point value to this file.
     */
    void writeFloat(f32 value);
    /**
     * Writes a 64-bit precision floating point value to this file.
     */
    void writeDouble(f64 value);
    /**
     * Writes a string to this file and enters a new line.
     */
    void writeLine(string line);

    /**
     * Resizes the file to the new specified length.
     * If new_length > size, zero-padding is added.
     * If new_length < size, file is truncated.
     */
    void setLength(u64 new_length);
private:
    FILE* _fp;
    string _path;
    string _path_full;
    string _fname;
    u64 _fsize;
    u64 _pos;
    OpenMode _mode;
    bool _binary;
    bool _initialized;

    void initPaths(const string& path);

    Array<string> _modes = {
        "r", "r+",
        "w", "w+",
        "a", "a+"
    };
};

#endif // FILE_H
