#include "kernel.h"
#include "kitten_desktop.h"

void updatewin(KittenParams p) {
    putrect(p.x, p.y, p.xl, p.yl, black);
    putrect(p.x, p.y, p.xl, p.yl, gray);
    putrect(p.x + 1, p.y + 1, p.xl - 1, p.yl - 1, black);
    putrect(p.x + 2, p.y + 2, p.xl - 2, p.yl - 2, white);
    putrect(p.x, p.y + 7, p.xl, 2, black);
}

KittenWindow new_win(short x, short y, short xl, short yl) {
    KittenWindow w;
    KittenParams p;
    p.x = x;
    p.y = y;
    p.xl = xl;
    p.yl = yl;
    w.update = updatewin;
    w.params = p;
    w.title = "Window";
    w.update(w.params);
    return w;
}