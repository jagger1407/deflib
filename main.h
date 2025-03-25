#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

// Dawg I swear I tried my hardest not to split main into 2 files
// but this damn compiler wouldn't build it otherwise >:(

#include "array.h"
#include "string.h"
typedef Array<string> StringArray;

void Main(StringArray args);

#endif // MAIN_H_INCLUDED
