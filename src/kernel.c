void _start() {
    asm("jmp main\n"
        "hlt");
}

unsigned char *memory = (unsigned char*)0x00500;
unsigned char *vgamem = (unsigned char*)0xA0000;
int cur = 0;
const char 
black = 0x00,
white = 0x0F,
blue = 0x01,
green = 0x02,
red = 0x04,
lblue = 0x09,
lgreen = 0x0A,
lred = 0x0C;

inline void setpxl(int x, int y, char col) {
    vgamem[x + (y * 320)] = col;
}

void drawrect(int x0, int y0, int sx, int sy, char col) {
    for (int x = 0; x < sx; x++)
    {
        for (int y = 0; y < sy; y++)
        {
            vgamem[x+x0 + ((y+y0) * 320)] = col;
        }
    }
}

inline void vmode(short v) {
    short a = 0;
    asm("int $0x10" : : "a" (v + (a << 8)));
}

int main() {
    vmode(0x13);
    drawrect(0, 0, 320, 200, lgreen);
}