#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {

    ByteArray ba = { 0x00, 0x00, 0x80, 0x3F };

    DefCon::Printf("C-Style cast to convert: %.1f\n", ((Array<float>)ba)[2]);
    DefCon::Printf("Method to reinterpret (copies the array): %.1f\n", ba.reinterpretCopy<float>()[0]);

    FloatArray fa = ba.reinterpret<float>();

    DefCon::Printf("Method to reinterpret (doesn't copy): %.1f\n", fa[0]);
}



