#ifndef KITTEN_DESKTOPH
#define KITTEN_DESKTOPH

typedef struct {
    short x, y, xl, yl;
} KittenParams;

typedef struct {
    char *title;
    void (*update)(KittenParams);
    KittenParams params;
} KittenWindow;

KittenWindow new_win(short x, short y, short xl, short yl);


#endif