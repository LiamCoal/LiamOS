#ifndef KERNELH
#define KERNELH

#define cls() vmode(curvmode);\
              setcpos(0, 0)
#define true 255
#define false 0
#define bool char
#define DESKTOPCOL lblue
#define YES true
#define NO false

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

typedef struct {
    char txt;
    char col;
} txt;

void vmode(char);
void sleep(int);
void puts(char *c, const char col);

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

#endif