#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    string s = "Lmao.xd";
    DefCon::PrintLine(Cvt::ToString(s.endsWith(".xd")));
}


