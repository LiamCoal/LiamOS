int lmain();

void _start() {
    lmain();
    asm("hlt");
}

#include "liamos.h"

int lmain() {
    putchs("Hello World!", 12);
}

