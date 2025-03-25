#include "string.h"
#include "array.h"

#include "main.h"

int main(int argc, char **argv) {
    Array<string> args = Array<string>(argc);

    for(int i=1;i<argc;i++) {
        args[i-1] = argv[i];
    }
    Main(args);
    return 0;
}
