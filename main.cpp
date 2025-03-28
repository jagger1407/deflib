#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    string s = string::Format("Hello Agent %d", 47);

    DefCon::PrintLine(s);
}



