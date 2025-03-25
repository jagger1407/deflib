#ifndef DEFCON_H
#define DEFCON_H

#include "string.h"
#include <stdio.h>
#include <stdarg.h>

/** Default Console.
 * No, not the pentagon kind.
 */
class DefCon
{
public:
    static void PrintLine(const string& str);
    static void Print(const string& str);
    static void Printf(const string& format, ...);
    static string ReadLine();
    static string ReadLine(const string& message);
private:
};

#endif // DEFCON_H
