#include "defcon.h"

void DefCon::PrintLine(const string& str) {
    puts(str.c_str());
}

void DefCon::Printf(const string& format, ...) {
    char* fmt = format.c_str();
    va_list args;
    va_start(args, fmt);
    vprintf(format.c_str(), args);
    va_end(args);
}
