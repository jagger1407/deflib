#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    string s = "SOME.PACK";

    s = s.toLower();

    ByteArray ba = { 0xFF, 0xBB, 0x00 };

    DefCon::Printf("0x%02x\n", ba[2]);
}


