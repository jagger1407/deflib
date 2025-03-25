#include "string.h"
#include "array.h"
#include "defcon.h"
#include "cvt.h"

void Main(Array<string> args) {

    DefCon::PrintLine(Cvt::ToString(0x80000001));

}

