#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    string s = string::format("Hello Agent %d", 47);

    DefCon::PrintLine(s);
}



