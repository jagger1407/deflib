#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    string s = "SOME.PACK";

    s = s.toLower();

    if(s.endsWith(".pak")) {
        DefCon::PrintLine("string is a pak");
    }
    else {
        DefCon::PrintLine("packwatch failed rip bozo");
    }
}


