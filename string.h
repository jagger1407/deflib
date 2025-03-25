#ifndef STRING_H
#define STRING_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * @todo write docs
 */
class string
{
public:
    string();
    string(const char* str);
    string(const string& str);
    u32 length() const;
    char* c_str() const;

    string& operator=(const char* str);
    string& operator=(string& str);

    friend string operator+(string& left, const char* right);
    friend string operator+(const char* left, string& right);
    friend string operator+(string& left, string& right);

    string& operator+=(const char* str);
    string& operator+=(string& str);

    static u32 len(const char* str);
    static char* ncopy(char* dest, const char* src, u32 n);

    // TODO: remove
    static void _puts(const string& str);
private:
    u32 _len;
    char* _c_ptr;

    inline static u32 _prev_len = 0;
    inline static char* _prev_ptr = (char*)NULL;
    static char* initptr(u32 len);
    char* inclen(u32 length);
};


#endif // STRING_H
