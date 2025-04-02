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
    Int32Array arr = { 5, 8, 1, 2, 7, 9, 6 };
    ArrayList<int> list = arr;
    printList(list);
    list[0] = 50;
    printList(list);
}



