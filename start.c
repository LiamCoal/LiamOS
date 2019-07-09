int lmain();

void _start() {
    lmain();
    asm("hlt");
}

#include "liamos.h"

int lmain() {
    putchs("This is a secret message.\nWhat", 30);
}

