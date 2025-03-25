#include "main.h"
#include "deflib.h"

void Main(StringArray args) {
    int number = Cvt::ToInt32(args[0]);
    number += 1;
    string str1 = "sex";
    string str2 = "s";
    str2 += "ex";

    DefCon::PrintLine(Cvt::ToString(str1.c_str() == str2.c_str()));
    DefCon::PrintLine(Cvt::ToString(str1 == str2));
}


