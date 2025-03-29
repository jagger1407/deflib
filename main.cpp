#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    ArrayList<string> list;
    list += "Hello";
    list += "there";
    list += "gang gang";

    string sep = args[0];
    if(sep == "\\n") sep = "\n";

    DefCon::PrintLine(Cvt::ToString(list, sep));
}



