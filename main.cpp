#include "main.h"
#include "deflib/deflib.h"

#define OPTION_NAME 0
#define OPTION_VALUE 1

void Program::Main(StringArray args) {
    string s = "option = setting\n";
    s += "option2 = black\n";
    s += "size = 500\n";

    StringArray sa = s.split("\n");

    for(int i=0;i<sa.count();i++) {
        StringArray option = sa[i].split(" = ");
        if(option.count() >= 2) {
            DefCon::PrintLine(sa[i].split(" = ")[OPTION_VALUE]);
        }
    }
}


