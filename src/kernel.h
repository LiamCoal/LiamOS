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
#define VERSION "0.0.2a"
#define VERSION_SLEN 6
// Change GITVER to NO if release.
#define GITVER YES
// Please increase GITPATCH when you change something. (in the code)
#define GITPATCH "5"

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
extern const char     keyset[0xFF];

typedef struct {
    char txt;
    char col;
} txt;

typedef struct {
    char name[8];
    char extn[3];
    char file_attr, 
         user_attr,
         del_char;
    short time_created,
          date_created,
          date_accessed,
          access_rights,
          last_mod_time,
          last_mod_date,
          cluster;
    int byte_size;
} dir_entry_t;

typedef struct {
    int eax, ebx, ecx, edx;
} regs_t;

void kmain();
void vmode(unsigned char);
void sleep(int);
void puts(char *c, const char col);
void init_ints();
char getch();
void *memset(void*, char, unsigned int);
void *memcpy(void*, const void*, unsigned int);
void do_boot_proc();
char *getstr(char);
void set_bpb_vars();
dir_entry_t *find_file(const char *name, const char *extn);
void *load_file(const int where, dir_entry_t *dir);

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

inline void keybeep() { // Really short beep for the menuing systems.
    __asm {
        in al, 0x61
        and al, 1111b
        or al, 10b
        out 0x61, al
    }
    sleep(750);
    __asm {
        in al, 0x61
        and al, 1101b
        out 0x61, al
    }
}

inline void diskbeep() { // Here to tell you you're stupid for putting 100 read_disks in a row.
    __asm {
        in al, 0x61
        and al, 1111b
        or al, 10b
        out 0x61, al
    }
    sleep(75);
    __asm {
        in al, 0x61
        and al, 1101b
        out 0x61, al
    }
}

inline void beep() {
    __asm {
        in al, 0x61
        and al, 1111b
        or al, 10b
        out 0x61, al
    }
    sleep(7500);
    __asm {
        in al, 0x61
        and al, 1101b
        out 0x61, al
    }
}

inline void confuzzled() {
    puts("LIAMOS IS CONFUZZLED! POWER OFF!", lred);
    beep();
    // TODO put this asm in a function (power_off?):
    __asm {
        mov ax, 0x1000
        mov ax, ss
        mov sp, 0xf000
        mov ax, 0x5307
        mov bx, 0x0001
        mov cx, 0x0003
        int 0x15
    }
    puts("You're PC does not support auto power off. You may now turn your PC off manually.", yellow);
    while(true);
}

inline char reset_disk(char disk) {
    char retcode = 0;
    __asm {
        mov ah, 0x00
        mov dl, disk
        int 13h
        jnc end
        mov retcode, ah
        end:
    }
    diskbeep();
    return retcode;
}

inline char read_disk(void *data, short sector, char count, char disk, char head) {
    char retcode = 0;
    int data_int = (int)data;
    short segment = data_int >> 16;
    short address = data_int >>  0;
    __asm {
        mov ah, 0x02
        mov al, count
        mov cx, sector
        mov dh, head
        mov dl, disk
        mov bx, segment
        mov es, bx
        mov bx, address
        int 13h
        jnc end
        mov retcode, ah
        end:
    }
    diskbeep();
    return retcode;
}

inline char write_disk(void *data, short sector, char count, char disk, char head) {
    char retcode = 0;
    int data_int = (int)data;
    short segment = data_int >> 16;
    short address = data_int >>  0;
    __asm {
        mov ah, 0x03
        mov al, count
        mov cx, sector
        mov dh, head
        mov dl, disk
        mov bx, segment
        mov es, bx
        mov bx, address
        int 13h
        jnc end
        mov retcode, ah
        end:
    }
    diskbeep();
    return retcode;
}

#endif
