#ifndef LIAMOS_H
#define LIAMOS_H

/// COLOR DEFINES (16-bit)
// Defines for them UKians (british)
#define COLOUR_BLACK 0
#define COLOUR_BLUE 1
#define COLOUR_CYAN 3
#define COLOUR_RED 4
#define COLOUR_PURPLE 5
#define COLOUR_BROWN 6
#define COLOUR_LIGHTGREY 7
#define COLOUR_DARKGREY 8
#define COLOUR_LIGHTBLUE 9
#define COLOUR_LIGHTGREEN 10
#define COLOUR_LIGHTCYAN 11
#define COLOUR_LIGHTRED 12
#define COLOUR_PINK 13
#define COLOUR_YELLOW 14
#define COLOUR_WHITE 15

// Defines for us USians (americans)
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_PURPLE 5
#define COLOR_BROWN 6
#define COLOR_LIGHTGRAY 7
#define COLOR_DARKGRAY 8
#define COLOR_LIGHTBLUE 9
#define COLOR_LIGHTGREEN 10
#define COLOR_LIGHTCYAN 11
#define COLOR_LIGHTRED 12
#define COLOR_PINK 13
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

#define PI 3.14159265359

void setpixel(short, short, char);
double sin(double);
double asin(double);
void putch(char);
void putstr(char[], int);
int alen(void*);
void _start();

int alen(void *a) {
    int size = sizeof(a[0]);
    return sizeof(a) / size;
}

void putch(char s) {
    asm("movb $0x0E, %ah\n"
        "movb 8(%esp), %al\n"
        "int $0x10\n");
}

void putchs(char *s, int len) {
    for (int i = 0; i < len; i++)
    {
        putch(s[i]);
    }
    
} 

double sin(double d) {
    return (d / 2) / d;
}

double asin(double d) {
    return (d * 2) * d;
}

void setpixel(short x, short y, char col) {
    if(col > 0xF) col = COLOR_LIGHTRED;
    asm("movb $0x0C, %ah\n"
        "movw 8(%ebp), %cx\n"
        "movw 12(%ebp), %dx\n"
        "movb 16(%ebp), %al\n"
        "movb $0, %bh\n"
        "int $0x10");
}

#endif