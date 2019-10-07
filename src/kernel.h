#ifndef KERNELH
#define KERNELH

#define cls() vmode(curvmode);\
              setcpos(0, 0)
#define true 1
#define false 0
#define bool char
#define DESKTOPCOL lblue
#define YES true
#define NO false
#define VERSION "0.0.1a"
// Change GITVER to NO if not git version.
#define GITVER YES
// Please increase GITPATCH when you change something. (in the code)
#define GITPATCH "3"

extern unsigned char *memory;
extern unsigned char  curvmode;
extern const char
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    gray,
    dgray,
    lblue,
    lgreen,
    lcyan,
    lred,
    lmagenta,
    yellow,
    white;
extern int            vyptr;
extern void          *nullptr;
extern char           lastkey;
extern bool           keywaiting;

typedef struct {
    char txt;
    char col;
} txt;

typedef struct {
    int eax, ebx, ecx, edx;
} regs_t;

void kmain();
void vmode(char);
void sleep(int);
void puts(char *c, const char col);
void init_ints();
void timer_int();
regs_t getregs();
char getch();

/**
 * Simple inline functions.
 * ¯\_(ツ)_/¯
 */

inline txt totxt(char c, char col) {
    txt t;
    t.txt = c;
    t.col = col;
    return t;
}

inline void putc(txt ch) {
    char t = ch.txt;
    char c = ch.col;
    __asm {
        mov ah, 0x0E
        mov al, t
        mov bh, 0
        mov bl, c
        int 10h
    }
}

inline void printver() {
    puts("LiamOS ", lblue);
    puts("Version ", gray);
    puts(VERSION, green);
    if(GITVER) {
        puts(" Patch ", red);
        puts(GITPATCH, lred);
        puts("\nNot a release.", cyan);
    }
    puts("\n", black);
}

inline void out(short addr, char b) {
    __asm {
        mov al, b
        mov dx, addr
        out dx, al
    }
}

inline char in(short addr) {
    char b;
    __asm {
        mov al, b
        mov dx, addr
        in al, dx
    }
    return b;
}

inline void interrupt(const char t) {
    __asm {
        int t
    }
}

#include "keyset.h"

#endif