#include "defcon.h"

void DefCon::PrintLine() {
    puts("");
}
void DefCon::PrintLine(const string& str) {
    puts(str.c_str());
}
void DefCon::Print(const string& str) {
    printf("%s", str.c_str());
}

void DefCon::Printf(const string& format, ...) {
    char* fmt = format.c_str();
    va_list args;
    va_start(args, fmt);
    vprintf(format.c_str(), args);
    va_end(args);
}

string DefCon::ReadLine() {
    string s(100);

    char c = fgetc(stdin);
    while(c != 0x00 && c != '\n' && c != EOF) {
        s += c;
        c = fgetc(stdin);
    }

    return s;
}

string DefCon::ReadLine(const string& message) {
    Print(message);
    return ReadLine();
}

