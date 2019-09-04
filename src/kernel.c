#include "kernel.h"
#include "kitten_desktop.h"

#define DESKTOPCOL lblue

void kmain();
void int80h();

void _start() {
    kmain();
    asm("hlt");
}

unsigned char *memory = (unsigned char*)0x00500;
unsigned char  curvmode = 0x03;
const char // TODO sort
    black = 0x00,
    white = 0x0F,
    blue = 0x01,
    green = 0x02,
    red = 0x04,
    lblue = 0x09,
    lgreen = 0x0A,
    lred = 0x0C,
    gray = 0x07;
int            vyptr = 1;
void          *nullptr = 0;

const char testimg[5 * 5] = {
    DESKTOPCOL, DESKTOPCOL, DESKTOPCOL, DESKTOPCOL, DESKTOPCOL,
    white, gray, black, gray, white,
    red, green, blue, DESKTOPCOL, DESKTOPCOL,
    lred, lgreen, lblue, DESKTOPCOL, DESKTOPCOL,
    black, black, black, black, black
};

void kmain() {
    __asm {
        cli
        mov ax, int80h
        mov word ptr [0x320], ax
        mov word ptr [0x322], cs
        sti
    }
    vmode(0x13);
    putrect(0, 0, 320, 200, DESKTOPCOL);
}

typedef struct {
    char txt;
    char col;
} txt;

void putc(char txt0) {
    __asm {
        mov ah, 0x0E
        mov al, txt0
        int 10h
    }
}
void putcc(char txt0, char col) {
    __asm {
        mov ah, 0x0E
        mov al, txt0
        mov bl, col
        int 10h
    }
}

void puts(char *txt0) {
    int i = 0;
    while(txt0[i] != 0) {
        if(txt0[i] == '\n') putc('\r');
        putc(txt0[i]);
        i++;
    }
}
void putsc(char *txt0, char col) {
    int i = 0;
    while(txt0[i] != 0) {
        if(txt0[i] == '\n') putc('\r');
        putcc(txt0[i], col);
        i++;
    }
}

void putsc_slo(char *txt0, char col) {
    int i = 0;
    while(txt0[i] != 0) {
        if(txt0[i] == '\n') putc('\r');
        putcc(txt0[i], col);
        sleep(10000);
        i++;
    }
}

void setcpos(int x, int y) {
    __asm {
        mov ah, 0x02
        mov bh, 0
        mov dh, y
        mov dl, x
        int 10h
    }
}

void putpixel(short x, short y, const char col) { // TODO Put this in an asm file.
    __asm {
        mov ah, 0x0C
        mov al, col
        mov bh, 0
        mov cx, x
        mov dx, y
        int 10h
    }
}

void putrect(short x, short y, short xl, short yl, const char col) {
    for(short x0 = x; x0 < xl; x0++) {
        for(short y0 = y; y0 < yl; y0++) {
            __asm {
                mov ah, 0x0C
                mov al, col
                mov bh, 0
                mov cx, x0
                mov dx, y0
                int 10h
            }
        }
    }
}

void putimg(const char img[], short x, short y, short xl, short yl) {
    for(short x0 = x; x0 < xl; x0++) {
        for(short y0 = y; y0 < yl; y0++) {
            char col = img[x0 + y0];
            __asm {
                mov ah, 0x0C
                mov al, col
                mov bh, 0
                mov cx, x0
                mov dx, y0
                int 10h
            }
        }
    }
}

void vmode(char v) {
    __asm {
        mov ah, 0
        mov al, v
        int 10h
    }
    curvmode = v;
}

void sleep(int time) {
    for (int i = 0; i < time; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            asm("nop");
        }
    }
}

void int80h_real() {
    // Only exists for interrupt support.
    __asm {

    }
}

void int80h() {
    __asm {
        mov ax, int80h_real

    }
}

bool c = false;