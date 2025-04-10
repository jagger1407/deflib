#include "main.h"
#include "deflib/deflib.h"

void printList(ArrayList<int> arr) {
    DefCon::Print("{ " + Cvt::ToString(arr[0]));
    for(int i=1;i<arr.count();i++) {
        DefCon::Print(", " + Cvt::ToString(arr[i]));
    }
    DefCon::Print(" }\n");
}

void Program::Main(StringArray args) {
    File f("text.txt", File::OpenMode::Read, false);

    File file(args[0], "r");

    DefCon::PrintLine(Cvt::ToString(file.readFile()));
    DefCon::PrintLine(file.fullPath());
}



