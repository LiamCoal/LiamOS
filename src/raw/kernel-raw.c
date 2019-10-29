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

short       bytes_per_sector;
char        sectors_per_cluster;
short       reserved_sectors;
char        fat_count;
short       max_root_entries;
short       sectors_per_fat;
short       hidden_sectors;

void set_bpb_vars() {
    char *bpb = (char*)0x500;
    read_disk(bpb, 0, 2, 0x80, 1);
    sectors_per_cluster = bpb[0x0D];
    fat_count = bpb[0x10];
    short *bpb16 = (short*)bpb;
    bytes_per_sector        = bpb16[0x0B/2];
    reserved_sectors        = bpb16[0x0E/2];
    max_root_entries        = bpb16[0x11/2];
    sectors_per_fat         = bpb16[0x16/2];
    hidden_sectors          = bpb16[0x1C/2];
    if(
            bpb[0x100] == 0x52 &&
            bpb[0x101] == 0x52 &&
            bpb[0x102] == 0x61 &&
            bpb[0x103] == 0x41) {
        // FAT32 not supported
        puts("FAILED\nFAT32 is not supported. Use FAT16.\n", lred);
        confuzzled();
    }
}

dir_entry_t entry;

dir_entry_t *find_file(const char *name, const char *extn) {
    int files_read, start_fn;
    void *disk_chk = (void*)0xB000;
    short sectors_gone_thru = 0;
    read_disk(disk_chk, hidden_sectors+reserved_sectors+(sectors_per_fat*2)+sectors_gone_thru, 1, 0x80, 1);
    while(((char*)disk_chk)[start_fn] != 0) {
        if(start_fn >= 0x200) {
            sectors_gone_thru++;
            read_disk(disk_chk, hidden_sectors+reserved_sectors+(sectors_per_fat*2)+sectors_gone_thru, 1, 0x80, 1);
            start_fn = 0;
        }
        dir_entry_t e = *((dir_entry_t*)((int)disk_chk)+start_fn);
        if(e.name[0] == 0x00) {
            // End of directories and files.
            return nullptr;
        }
        for(int i = 0; i < 8; i++) if(e.name[i] != name[i]) goto after;
        for(int i = 0; i < 3; i++) if(e.extn[i] != extn[i]) goto after;
        entry = e;
        return &entry;
after:
        start_fn += 32;
    }
}

void *read_file(int out, dir_entry_t *dir) {
    short *disk_chk = (void*)0xB000;
    void *output = (void*)out;
    read_disk((void*)disk_chk, hidden_sectors+reserved_sectors+(sectors_per_fat*2), sectors_per_fat, 0x80, 1);
    const short begin = (hidden_sectors+reserved_sectors+(sectors_per_fat*2))+32+((dir->cluster-1)*sectors_per_cluster);
    const short toread = dir->byte_size*bytes_per_sector;
    cont_read_disk((void*)out, begin, toread, 0x80, 1);
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
