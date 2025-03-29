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
     * Prints str to the stdout console and enters a new line.
     */
    static void PrintLine(const string& str);
    /**
     * Prints str to the stdout console without line-breaking.
     */
    static void Print(const string& str);
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
