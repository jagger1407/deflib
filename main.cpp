#include "string.h"
#include <stdio.h>

int Main(int argc, string* args) {
    puts(args[0].c_str());

    return 0;
}

#if 1 // call main
int main(int argc, char **argv) {
    string args[argc-1];

    for(int i=1;i<argc;i++) {
        args[i-1] = argv[i];
    }

    return Main(argc, args);
}
#endif
