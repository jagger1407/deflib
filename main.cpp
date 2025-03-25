#include "string.h"
#include "array.h"
#include "defcon.h"

void Main(Array<string> args) {
    string str = "";

    str += args[0];

    DefCon::PrintLine("Word: " + str);
    DefCon::Printf("String Length: %d\n", str.length());
    DefCon::PrintLine("Reverse: " + str.reverse());
}

