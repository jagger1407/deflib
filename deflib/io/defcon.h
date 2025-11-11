#ifndef DEFCON_H
#define DEFCON_H

#include "../data/string.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * Default Console.
 * No, not the pentagon kind.
 */
class DefCon
{
public:
    /**
     * Enters a new line in the console.
     */
    static void PrintLine();
    /**
     * Prints character c to the stdout console and enters a new line.
     */
    static void PrintLine(const u8 c);
    /**
     * Prints character c to the stdout console and enters a new line.
     */
    static void PrintLine(const char c);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const s16 val);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const u16 val);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const s32 val);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const u32 val);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const s64 val);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const u64 val);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const float val);
    /**
     * Prints value val to the stdout console and enters a new line.
     */
    static void PrintLine(const double val);
    /**
     * Prints str to the stdout console and enters a new line.
     */
    static void PrintLine(const string& str);
    /**
     * Prints char array val to the stdout console and enters a new line.
     */
    static void PrintLine(const Array<char>& arr);
    /**
     * Prints char array arr to the stdout console and enters a new line.
     */
    static void PrintLine(const Array<u8>& arr);
    /**
     * Prints string pointed to by ptr to the stdout console and enters a new line.
     */
    static void PrintLine(const char* ptr);
    /**
     * Prints character c to the stdout console.
     */
    static void Print(const u8 c);
    /**
     * Prints character c to the stdout console.
     */
    static void Print(const char c);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const s16 val);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const u16 val);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const s32 val);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const u32 val);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const s64 val);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const u64 val);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const float val);
    /**
     * Prints value val to the stdout console.
     */
    static void Print(const double val);
    /**
     * Prints str to the stdout console.
     */
    static void Print(const string& str);
    /**
     * Prints char array val to the stdout console.
     */
    static void Print(const Array<char>& arr);
    /**
     * Prints char array arr to the stdout console.
     */
    static void Print(const Array<u8>& arr);
    /**
     * Prints string pointed to by ptr to the stdout console.
     */
    static void Print(const char* ptr);
    /**
     * Prints a formatted string to stdout.
     * Essentially a wrapper for the C printf() function.
     */
    static void Printf(const string& format, ...);
    /**
     * Reads one line of user-input from stdin.
     */
    static string ReadLine();
    /**
     * Displays message and reads one line of user-input from stdin.
     */
    static string ReadLine(const string& message);
private:
};

#endif // DEFCON_H
