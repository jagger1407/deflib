#include "main.h"
#include "deflib/deflib.h"
#include <windows.h>

void printList(ArrayList<int> arr) {
    DefCon::Print("{ " + Cvt::ToString(arr[0]));
    for(int i=1;i<arr.count();i++) {
        DefCon::Print(", " + Cvt::ToString(arr[i]));
    }
    DefCon::Print(" }\n");
}

void Program::Main(StringArray args) {
    Stopwatch w = Stopwatch();
    w.start();
    Sleep(1200);
    w.stop();

    DefCon::Printf("Program took %lld seconds.\n", w.elapsed_secs());
}




