#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    Int32Array ia = { 1, 2, 3, 4, 5 };

    Int32Array subarray = ia.subarray(2, 2);

    for(int i = 0; i < subarray.count(); i++) {
        DefCon::Print(Cvt::ToString(subarray[i]) + " ");
    }
    DefCon::PrintLine("");
}



