// Kernel stripped of its start capabilities.

#include "kernel.h"

unsigned char *memory = (unsigned char*)0x00500;
unsigned char  curvmode = 0x13;
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

char getch() {
    char r;
    // This is the only place this is used, so its fine here.
    __asm {
        back:
        mov ah, 0x01
        int 16h
        jz back
        mov ah, 0x00
        int 16h
        mov r, ah
    }
    keybeep();
    return keyset[r];
}

char *getstr(char ending) {
    char *ret = (char*)0x9100; // Get memory pointer
    memset(ret, 0, 0x100); // Fill that with 256 zeros
    int i = 0; // +i variable
    while(true) {
        char c = getch();
        if(c == '\b' && i > 0) {
            puts("\b \b", black);
            i--;
            ret[i] = 0;
        } else if(c == ending) {
            puts("\n", black);
            return ret;
        } else if(i < 0x100) {
            putc(totxt(c, white));
            ret[i] = c;
            i++;
        }
    }
}

void vmode(unsigned char v) {
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

void *memset(void *dest, char x, unsigned int size) {
    for (int i = 0; i < size / sizeof(int); i++)
    {
        ((char*)dest)[i] = x;
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
    '\e', // LShift pressed, don't do anything
    // '\\', // * Backslash "nonus"
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
    0, // PrintScr
    0, // Alt
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
    0, // Grey-... wat // TODO Liam just figured out these are keypad buttons...
    0, // Left pressed, don't do anything
    0, // KeyPad, don't do anything
    0, // Right pressed, don't do anything
    0, // Another Grey one (grey+) // TODO Liam just figured out these are keypad buttons...
    0, // End pressed, don't do anything
    0, // Down pressed, don't do anything
    0, // PgDn pressed, don't do anything
    0, // Insert pressed, don't do anything
    0, // Delete pressed, don't do anything
    0, // SysReq pressed, don't do anything
    0, // F11 (version 2?) pressed, don't do anything
    '\\',
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
    0, // * "non-U.S."
    0, // * "non-U.S."
    0, // * "non-U.S."
    0, // * "non-U.S."
    0, // * "non-U.S."
    0, // * "non-U.S."
    0, // * "non-U.S."
    0, // * "non-U.S."
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
