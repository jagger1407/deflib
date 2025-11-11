#include "defcon.h"

void DefCon::PrintLine() {
    puts("");
}
void DefCon::PrintLine(const u8 c) {
    printf("%c\n", c);
}
void DefCon::PrintLine(const char c) {
    printf("%c\n", c);
}
void DefCon::PrintLine(const s16 val) {
    printf("%d\n", val);
}
void DefCon::PrintLine(const u16 val) {
    printf("%u\n", val);
}
void DefCon::PrintLine(const s32 val) {
    printf("%d\n", val);
}
void DefCon::PrintLine(const u32 val) {
    printf("%u\n", val);
}
void DefCon::PrintLine(const s64 val) {
    printf("%lld\n", val);
}
void DefCon::PrintLine(const u64 val) {
    printf("%llu\n", val);
}
void DefCon::PrintLine(const float val) {
    printf("%f\n", val);
}
void DefCon::PrintLine(const double val) {
    printf("%f\n", val);
}
void DefCon::PrintLine(const string& str) {
    puts(str.c_str());
}
void DefCon::PrintLine(const Array<char>& arr) {
    puts(string((Array<char>)arr).c_str());
}
void DefCon::PrintLine(const Array<u8>& arr) {
    puts(string((Array<u8>)arr).c_str());
}

void DefCon::Print(const u8 c) {
    printf("%c", c);
}
void DefCon::Print(const char c) {
    printf("%c", c);
}
void DefCon::Print(const s16 val) {
    printf("%d", val);
}
void DefCon::Print(const u16 val) {
    printf("%u", val);
}
void DefCon::Print(const s32 val) {
    printf("%d", val);
}
void DefCon::Print(const u32 val) {
    printf("%u", val);
}
void DefCon::Print(const s64 val) {
    printf("%lld", val);
}
void DefCon::Print(const u64 val) {
    printf("%llu", val);
}
void DefCon::Print(const float val) {
    printf("%f", val);
}
void DefCon::Print(const double val) {
    printf("%f", val);
}
void DefCon::Print(const string& str) {
    printf("%s", str.c_str());
}
void DefCon::Print(const Array<char>& arr) {
    printf("%s", string((Array<char>)arr).c_str());
}
void DefCon::Print(const Array<u8>& arr) {
    printf("%s", string((Array<u8>)arr).c_str());
}
void DefCon::Print(const char* ptr) {
    printf("%s", ptr);
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

