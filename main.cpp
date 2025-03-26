#include "main.h"
#include "deflib/deflib.h"

#define OPTION_NAME 0
#define OPTION_VALUE 1

void Program::Main(StringArray args) {
    File f("text.txt", File::OpenMode::Read, false);
    ByteArray ba = ByteArray();
    f.read(ba, f.size()+1);

    DefCon::PrintLine(Cvt::ToString(ba));
}


