#include "main.h"
#include "array.h"
#include "defcon.h"
#include "cvt.h"

void Main(StringArray args) {
    bool b = true;

    DefCon::PrintLine("Yeah that's pretty " + Cvt::ToString(b));

}

