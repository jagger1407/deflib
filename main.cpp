#include "string.h"
#include "array.h"

void Main(Array<string> args) {
    string str = "";

    str += args[0];

    puts(str.c_str());
    printf("string length: %d\n", str.length());
    puts(((string)"Reverse: " + str.reverse()).c_str());
}

