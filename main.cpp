#include "main.h"
#include "deflib/deflib.h"

#define OPTION_NAME 0
#define OPTION_VALUE 1

void Program::Main(StringArray args) {
    string s = "option = setting\n";
    s += "option2 = black\n";
    s += "size = 500\n";

    DefCon::PrintLine(s.substring(9, 7));
}


