#define cls() vmode(curvmode);\
              setcpos(0, 0)
#define true 0b00000001
#define false 0b00000000
#define bool char

void kmain();
void putc(char);
void puts(char*);
void putsc(char*, char);
void putpixel(short, short, char);
void putrect(short, short, short, short, char);
void putgtxt(short, short, char, const char*);
void vmode(char);

void _start() {
    kmain();
    asm("hlt");
}

unsigned char *memory = (unsigned char*)0x00500;
unsigned char  curvmode = 0x03;
const char 
    black = 0x00,
    white = 0x0F,
    blue = 0x01,
    green = 0x02,
    red = 0x04,
    lblue = 0x09,
    lgreen = 0x0A,
    lred = 0x0C,
    gray = 0x07;
int vyptr = 1;
void *nullptr = 0;

void kmain() {
    vmode(0x13);
    for(char i = 0; i < 16; i++) {
        putrect(i * 20, 0, 320, 200, i + 16);
    }
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

void sleep(int);

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

void putpixel(short x, short y, const char col) {
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

void putgtxt(short x, short y, char col, const char *str) {

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

bool c = false;