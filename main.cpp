#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {

    File f(args[0], File::OpenMode::ReadWrite, false);
    if(!f.isOpen()) {
        DefCon::PrintLine("Opening file failed!");
        return;
    }

    f.seek(0, SEEK_END);
    f.writeLine("\nTesting");
    f.seek(0, SEEK_SET);

    StringArray lines = Cvt::ToString(f.readFile()).split('\n');

    for(int i = 0; i < lines.count(); i++) {
        DefCon::PrintLine(Cvt::ToString(i+1) + ": " + lines[i]);
    }
}



