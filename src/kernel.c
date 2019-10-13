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
        puts("Please choose an option:\n 1. Boot LiamOS normally.\n 2. Quit.\n\nPress a key: ", white);
        char c = getch();
        keybeep();
        putc(totxt(c, white));
        puts("\n", black);
        if(c == '1') {
            type = NORMAL;
            break;
        } else if(c == '2') {
            __asm {
                mov ax, 0x1000
                mov ax, ss
                mov sp, 0xf000
                mov ax, 0x5307
                mov bx, 0x0001
                mov cx, 0x0003
                int 0x15
            }
            cls();
            putsat("You can now power off your PC.", yellow, 25, 12);
            while(true); // End of execution
        } else {
            putc(totxt(c, lred));
            puts(" is not a valid option\n", red);
        }
    }
    switch (type)
    {
    case NORMAL:
        normalboot();
    default:
        break;
    }
}

char getch() {
    char r;
    __asm {
        back:
        mov ah, 0x01
        int 16h
        jz back
        mov ah, 0x00
        int 16h
        mov r, ah
    }
    return keyset[r];
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

void *memset(void *dest, int x, unsigned int size) {
    for (int i = 0; i < size / sizeof(int); i++)
    {
        ((int*)dest)[i] = x;
    }
    return dest;
}

void *memcpy(void *dest, const void *src, unsigned int size) {
    for (int i = 0; i < size; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
    return dest;
}

void aniboot() {
    // i wont be surprised if there is an error here. if you see one, report it please
    putsat("L", lred, 37, 12);
    sleep(72000);
    putsat("L", lgreen, 37, 12);
    putsat("I", lred, 38, 12);
    sleep(72000);
    putsat("L", lblue, 37, 12);
    putsat("I", lgreen, 38, 12);
    putsat("A", lred, 39, 12);
    sleep(72000);
    putsat("L", white, 37, 12); // Once the char is white, stop messing with it.
    putsat("I", lblue, 38, 12);
    putsat("A", lgreen, 39, 12);
    putsat("M", lred, 40, 12);
    sleep(72000);
    putsat("I", white, 38, 12);
    putsat("A", lblue, 39, 12);
    putsat("M", lgreen, 40, 12);
    // Give the illusion there is a space
    sleep(72000);
    putsat("A", white, 39, 12);
    putsat("M", lblue, 40, 12);
    putsat("O", lred, 42, 12);
    sleep(72000);
    putsat("M", white, 40, 12);
    putsat("O", lgreen, 42, 12);
    putsat("S", lred, 43, 12);
    sleep(72000);
    putsat("O", lblue, 42, 12);
    putsat("S", lgreen, 43, 12);
    sleep(72000);
    putsat("O", white, 42, 12);
    putsat("S", lblue, 43, 12);
    sleep(72000);
    putsat("S", white, 43, 12);
    sleep(72000);
}

void playaniboot() {
    cls();
    aniboot();
    putsat("by Liam Cole (LiamCoal)", dgray, 28, 14);
    sleep(72000);
    putsat("by Liam Cole (LiamCoal)", gray, 28, 14);
    sleep(72000);
    putsat("by Liam Cole (LiamCoal)", white, 28, 14);
    sleep(72000);
    aniboot();
    putsat("by Liam Cole (LiamCoal)", gray, 28, 14);
    sleep(72000);
    putsat("by Liam Cole (LiamCoal)", dgray, 28, 14);
    sleep(72000);
    putsat("by Liam Cole (LiamCoal)", black, 28, 14);
    sleep(72000);
    putsat("LIAM OS", gray, 37, 12);
    sleep(72000);
    putsat("LIAM OS", dgray, 37, 12);
    sleep(72000);
    putsat("LIAM OS", black, 37, 12);
    sleep(72000);
}

void normalboot() {
    playaniboot();
}

const char keyset[0xFF] = {
    0, // KBD buffer full, don't do anything
    0, // ESC pressed, don't do anything
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\b', // Backspace
    '\t', // Tab
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '[',
    ']',
    '\n', // Enter/Return
    0, // Ctrl pressed, don't do anything
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ';',
    0, // Function key, don't do anything
    '\'', // Quote
    '`',
    0, // LShift pressed, don't do anything
    '\\', // Backslash
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    ',',
    '.',
    '/',
    0, // RShift pressed, don't do anything
    0, // Grey*... what does that mean...
    ' ',
    0, // CapsLock pressed, don't do anything
    /**
     * Prepare yourself for the madness you're 
     * about to see...
     */
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // NumLock pressed, don't do anything
    0, // ScrollLock pressed, don't do anything
    0, // Home pressed, don't do anything
    0, // Up pressed, don't do anything
    0, // PgUp pressed, don't do anything
    0, // Grey-... wat
    0, // Left pressed, don't do anything
    0, // KeyPad, don't do anything
    0, // Right pressed, don't do anything
    0, // Another Grey one (grey+)
    0, // End pressed, don't do anything
    0, // Down pressed, don't do anything
    0, // PgDn pressed, don't do anything
    0, // Insert pressed, don't do anything
    0, // Delete pressed, don't do anything
    0, // SysReq pressed, don't do anything
    0, // F11 (version 2?) pressed, don't do anything
    0, // Left \ pressed, don't do anything
    0, // Shouldn't be reached?
    0, // Function key, don't do anything
    0, // F15 (version 47?), don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // -- pressed, what are these keys
    0, // EraseEOF pressed, don't do anything
    0, // Copy/Play pressed, don't do anything
    0, // Shouldn't be reached?
    0, // Shouldn't be reached?
    0, // CrSel pressed, don't do anything
    0, // Yet another weird button ([*])
    0, // ExSel pressed, don't do anything
    0, // -- pressed, again?
    0, // Clear pressed, don't do anything
    0, // "Note2", more like "version 2000000"
    0, // "Note2", more like "version 2000001"
    0, // "Note2", more like "version 2000002"
    0, // "Note2", more like "version 2000003"
    0, // "Note2", more like "version 2000004"
    0, // "Note2", more like "version 2000005"
    0, // "Note2", more like "version 2000006"
    0, // "Note2", more like "version 2000007"
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, // Self tested? Good! But I don't care.
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, // Prefix codes
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Reserved
    0, // ECHO?
    0, // #reserved
    0, // Prefix code
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Reserved
    0, // ACK
    0, 0, // "diag" failures
    0, // RESEND
    0 // Keyboard error
};
