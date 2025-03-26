#include "deflib/data/string.h"
#include "deflib/collections/array.h"

#include "main.h"

/** This is the real main function,
 *  in order to replicate the java style, I needed some bootstrap code.
 */
int main(int argc, char **argv) {
    Array<string> args = Array<string>(argc);

    for(int i=1;i<argc;i++) {
        args[i-1] = argv[i];
    }
    Program::Main(args);
    return 0;
}
