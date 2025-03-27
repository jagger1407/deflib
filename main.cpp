#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {

    File f("../../../../Documents/test.txt", File::OpenMode::Read, false);
    if(!f.isOpen()) {
        DefCon::PrintLine("Opening File failed.");
        return;
    }

    DefCon::PrintLine("Filename: " + f.name());
    DefCon::PrintLine("Given path: " + f.path());
    DefCon::PrintLine("Full path: " + f.fullPath());
    DefCon::PrintLine("Location: " + f.location());
    DefCon::PrintLine("Contents: ");
    DefCon::PrintLine(Cvt::ToString(f.readFile()));
}


