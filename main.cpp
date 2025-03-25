#include "main.h"
#include "array.h"
#include "defcon.h"
#include "cvt.h"

void Main(StringArray args) {
    int number = Cvt::ToInt32(args[0]);
    number += 1;
    DefCon::PrintLine(Cvt::ToString(number));
}


