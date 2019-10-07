#include "kernel.h"

void kmain();
void int80h();

void _start() {
    kmain();
    asm("hlt");
}

unsigned char *memory = (unsigned char*)0x00500;
unsigned char  curvmode = 0x03;
const char
    black = 0x00,
    blue = 0x01,
    green = 0x02,
    cyan = 0x03,
    red = 0x04,
    magenta = 0x05,
    brown = 0x06,
    gray = 0x07,
    dgray = 0x08,
    lblue = 0x09,
    lgreen = 0x0A,
    lcyan = 0x0B,
    lred = 0x0C,
    lmagenta = 0x0D,
    yellow = 0x0E,
    white = 0x0F;
int            vyptr = 1;
void          *nullptr = 0;
char           lastkey = 0;
bool           keywaiting = NO;

typedef enum
{
    NULLTYPE,
    NORMAL
} boottype_t;

void kmain() {
    boottype_t type = NULLTYPE;
    vmode(0x12);
    printver();
    init_ints();
    while(true) {
        puts("Please choose an option:\n 1. Boot LiamOS normally.\n\nPress a key: ", white);
        char c = getch();
        putc(totxt(c, white));
        puts("\n", black);
        if(c == '1') {
            type = NORMAL;
            break;
        } else {
            putc(totxt(c, lred));
            puts(" is not a valid option\n", red);
        }
    }
}

char getch() {
    char r;
    __asm {
        b:
        mov ah, 0x01
        int 16h
        jz b
        mov ah, 0x00
        int 16h
        mov r, al
    }
    return r;
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

void puts(char *s, char c) {
    int i = 0;
    while(s[i] != 0) {
        char ch = s[i];
        if(s[i] == '\n') putc(totxt('\r', black));
        putc(totxt(ch, c));
        i++;
    }
}

void init_ints() {
    __asm {
        push ds
        mov ax, 0
        mov ds, ax
        cli
        ; init timer
        mov al, 0x36
        out 0x43, al
        mov ax, 1193180/100
        out 0x40, al
        mov al, ah
        out 0x40, al
        mov ax, timer_int
        mov word ptr ds:[0x00], ax
        mov word ptr ds:[0x02], cs
        sti
    }
}

void timer_int() {
    /**
     * Put stuff that needs to happen every 100th 
     * of a second here
     */

    asm("iret"); // ! VERY IMPORTANT!!!!!!!
}

regs_t getregs() {
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