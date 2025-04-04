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

    StringArray sa = f.readAllLines();

    DefCon::Printf("Line Count: %d\n", sa.length());
    for(int i=0;i<sa.length();i++) {
        DefCon::Printf("%d: ", sa[i].length());
        DefCon::PrintLine(sa[i]);
    }
}



