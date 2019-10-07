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
// Change GITVER to NO if release.
#define GITVER YES
// Please increase GITPATCH when you change something. (in the code)
#define GITPATCH "4"

#define interrupt(t) __asm {int t}

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
extern char           al, ah, bl, bh, cl, ch, dl, dh;
extern short          ax, bx, cx, dx;
extern int            eax, ebx, ecx, edx;

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
char getch();
void *memset(void*, int, unsigned int);
void *memcpy(void*, const void*, unsigned int);

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

inline void out(short addr, unsigned char b) {
    __asm {
        mov al, b
        mov dx, addr
        out dx, al
    }
}

inline unsigned char in(short addr) {
    char b;
    __asm {
        mov al, b
        mov dx, addr
        in al, dx
    }
    return b;
}

inline regs_t getregs() {
    int meax, mebx, mecx, medx;
    __asm {
        mov meax, eax
        mov mebx, ebx
        mov mecx, ecx
        mov medx, edx
    }
    regs_t r;
    r.eax = meax;
    r.ebx = mebx;
    r.ecx = mecx;
    r.edx = medx;
    return r;
}

inline void setregs(regs_t regs) {
    int meax = regs.eax,
        mebx = regs.ebx,
        mecx = regs.ecx,
        medx = regs.edx;
    __asm {
        mov eax, meax
        mov ebx, mebx
        mov ecx, mecx
        mov edx, medx
    }
}

inline void setcpos(char x, char y) {
    __asm {
        mov ah, 0x02
        mov bh, 0x00
        mov dh, y
        mov dl, x
        int 10h
    }
}

inline void putsat(char *s, const char col, char x, char y) {
    setcpos(x, y);
    puts(s, col);
}

#include "keyset.h"

#endif