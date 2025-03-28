#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

// Dawg I swear I tried my hardest not to split main into 2 files
// but this damn compiler wouldn't build it otherwise >:(

#include "deflib/deflib.h"

class Program {
public:
    static void Main(StringArray args);
};

#endif // MAIN_H_INCLUDED
