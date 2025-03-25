#ifndef STRING_H
#define STRING_H

#include "types.h"
#include <stdlib.h>

// Arbitrarily chosen idk
// If the operator + or +/ is called with a char,
// This is the amount of space that the array length will be increased by.
// This way, realloc() will only be called every 20th appendage ideally.
#define INC_STEP 20

/**
 * String Class
 * wrapper class for a char array, but with swag yk
 */
class string
{
public:
    /**
     * Creates a string object.
     *  Every Value will be 0/NULL.
     */
    string();
    /**
     * Creates a string object with the given text.
     */
    string(const char* str);
    /**
     * Creates a string object by copying another one.
     */
    string(const string& str);
    /**
     * Creates a string object with a starting size.
     *  @note Length will still be 0.
     */
    string(u32 initial_size);
    /**
     * Destructor.
     */
    ~string();
    /**
     * Returns the amount of characters in this string
     *  excluding the null terminator.
     */
    u32 length() const;
    /**
     * Returns the underlying C-Style String (char*).
     */
    char* c_str() const;

    string& operator=(const char* str);
    string& operator=(string& str);

    friend string operator+(const string& left, const char* right);
    friend string operator+(const char* left, const string& right);
    friend string operator+(const string& left, const string& right);
    friend string operator+(const string& left, const char right);
    friend string operator+(const char left, const string& right);

    string& operator+=(const char* str);
    string& operator+=(const string& str);
    string& operator+=(const char ch);

    char& operator[](u32 index);

    /**
     * Returns a reversed version of this string.
     * @note This will not overwrite the original string.
     */
    string reverse();

    /**
     * Loops through the char* and counts the amount of characters.
     *  Essentially a custom strlen().
     */
    static u32 len(const char* str);
    /**
     * Copies n bytes from dest to src.
     *  Essentially a custom memcpy().
     *  @note Does not stop when encountering a null terminator.
     */
    static char* ncopy(char* dest, const char* src, u32 n);
private:
    u32 _len;
    char* _c_ptr;
    char* _cur;
    u32 _real_len;

    inline static u32 _prev_len = 0;
    inline static char* _prev_ptr = (char*)NULL;
    static char* initptr(u32 len);
    char* inclen(u32 length);
};
/**
 * String Class
 * wrapper class for a char array, but with swag yk
 */
typedef string String;

#endif // STRING_H
