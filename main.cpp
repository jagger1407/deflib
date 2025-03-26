#include "main.h"
#include "deflib.h"

void Main(StringArray args) {
    int number = Cvt::ToInt32(args[0]);
    number += 1;
    string str1 = "sex";
    string str2 = "s";
    str2 += "ex";

    DefCon::PrintLine(Cvt::ToString((u8)Cvt::ToInt8("1000")));
}
