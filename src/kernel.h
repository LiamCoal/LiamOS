#ifndef KERNELH
#define KERNELH

#define cls() vmode(curvmode);\
              setcpos(0, 0)
#define true 255
#define false 0
#define bool char

extern unsigned char *memory;
extern unsigned char  curvmode;
extern const char 
    black,
    white,
    blue,
    green,
    red,
    lblue,
    lgreen,
    lred,
    gray;
extern int            vyptr;
extern void          *nullptr;

void putc(char c);
void puts(char* s);
void putsc(char* s, char col);
void putpixel(short x, short y, char col);
void putrect(short x, short y, short xl, short yl, char col);
void putimg(const char img[], short x, short y, short xl, short yl);
void vmode(char);
void sleep(int);

#endif