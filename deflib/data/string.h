#ifndef STRING_H
#define STRING_H

#include "../types.h"
#include "../collections/array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


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
    /**
     * Returns a char array containing the string.
     * @note includes all null bytes.
     */
    Array<char> charArray();

    string& operator=(const char* str);
    string& operator=(const string& str);
    string& operator=(const Array<char> char_array);

    friend string operator+(const string& left, const char* right);
    friend string operator+(const char* left, const string& right);
    friend string operator+(const string& left, const string& right);
    friend string operator+(const string& left, const char right);
    friend string operator+(const char left, const string& right);

    string& operator+=(const char* str);
    string& operator+=(const string& str);
    string& operator+=(const char ch);

    char& operator[](u32 index);

    bool operator==(const string& str);

    /**
     * Returns a reversed version of this string.
     * @note This will not overwrite the original string.
     */
    string reverse();

    /**
     * Checks whether this string starts with character ch.
     */
    bool startsWith(const char ch);
    /**
     * Checks whether this string starts with string str.
     */
    bool startsWith(const string& str);

    /**
     * Checks whether this string ends with character ch.
     */
    bool endsWith(const char ch);
    /**
     * Checks whether this string ends with string str.
     */
    bool endsWith(const string& str);
    /**
     * Creates a copy of the string with all characters being lowercase.
     */
    string toLower();
    /**
     * Creates a copy of the string with all characters being uppercase.
     */
    string toUpper();
    /**
     * Counts the amount of occurrences of the character ch in the string.
     */
    int countOccurrences(const char ch);
    /**
     * Counts the amount of occurrences of the substring str in the string.
     */
    int countOccurrences(const string& str);
    /**
     * Gets the of occurrences of character ch
     * as an int array containing the index of each occurrence.
     */
    Array<int> getOccurrences(const char ch);
    /**
     * Gets the of occurrences of string str
     * as an int array containing the index of each occurrence.
     */
    Array<int> getOccurrences(const string& str);
    string replace(const char og, const char ch);
    string replace(const char og, const string& str);
    string replace(const string& og, const char ch);
    string replace(const string& og, const string str);
    /**
     * Splits a string using char ch as a seperator.
     */
    Array<string> split(const char ch);
    /**
     * Splits a string using string str as a seperator.
     */
    Array<string> split(const string& str);

    /**
     * Copies n characters of this string into another string starting at index start.
     */
    string substring(u32 start, u32 n);
    /**
     * Copies part of this string starting at index start until the end.
     */
    string substring(u32 start);

    /**
     * Loops through the char* and counts the amount of characters.
     *  Essentially a custom strlen().
     */
    static u32 Len(const char* str);
    /**
     * Compares 2 strings.
     * Returns 0 if both are equal, non-0 if not.
     * Essentially just a custom strcmp().
     */
    static int Compare(const char* str1, const char* str2);
    /**
     * Compares the first n chars of a string.
     * Returns 0 if both are equal, non-0 if not.
     * Essentially just a custom strncmp().
     */
    static int Compare_n(const char* str1, const char* str2, u32 n);
    /**
     * Returns a string with the given format.
     */
    static string Format(const string& fmt, ...);
private:
    u32 _len;
    char* _c_str;
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
