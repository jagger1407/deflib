#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    ByteArray ba1 = { 0x12, 0x34, 0x56, 0x78 };

    ByteArray ba2(4);

    Array<byte>::ArrayCopy(ba2, ba1, 4);

    for(int i=0;i<4;i++) {
        string s = string::Format("%02x ", ba2[i]).toUpper();
        DefCon::Print(s);
    }
    DefCon::PrintLine();
}



