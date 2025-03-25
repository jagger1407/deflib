#include "main.h"
#include "deflib.h"

void Main(StringArray args) {
    int number = Cvt::ToInt32(args[0]);
    number += 1;
    string str = "Neue Nummer ist " + Cvt::ToString(number) + ".";
    DefCon::PrintLine(str);
    DefCon::Printf("String Length: %d", str.length());
}


