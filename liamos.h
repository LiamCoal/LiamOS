#ifndef LIAMOS_H
#define LIAMOS_H

char lastrecvio = '\0';

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

#define write_port(num, val) asm("outb %0, $"#val : : "a"(num))
#define read_port(val) asm volatile ( "inb %1, %0" : "=a"(lastrecvio) : "Nb"(val));

void putch(char);
void putstr(char[], int);
int alen(void*);
double sin(double);
double asin(double);
double cos(double);
double acos(double);
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

#define SIN_LOOPS 10
double sin(double d) {
    double res = 0, pow = d, fact = 1;
    for (int i = 0; i < SIN_LOOPS; i++)
    {
        res += pow / fact;
        pow *= -1 * d * d;
        fact *= (2 * (i + 1)) * (2 * (i + 1) + 1);
    }
    return res;
}

double cos(double d) {
    return sin(d + (PI / 2));
}

#pragma region Unfinished

double asin(double d) {
}

double acos(double d) {
}

#pragma endregion

#endif