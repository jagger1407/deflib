#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    ArrayList<u16> list;
    list.add(0x1234);
    list.add(0xabcd);

    ArrayList<u8> ul = list.reinterpret<u8>();

    for(int i=0;i<4;i++) {
        string s = string::Format("%02x ", ul[i]).toUpper();
        DefCon::Print(s);
    }
    DefCon::PrintLine();
}



