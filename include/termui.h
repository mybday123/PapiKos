#ifndef TERMUI_H
#define TERMUI_H

#define ESC "\x1b"

#define BLACK   0
#define RED     1
#define GREEN   2
#define YELLOW  3
#define BLUE    4
#define MAGENTA 5
#define CYAN    6
#define WHITE   7

#define TRUE    1
#define FALSE   0

struct Termsize {
    int cols;
    int rows;
};

void wait();
int getinput();
void clrscr();
void setfontcolor(int color);
void setbgcolor(int color);
void setfontbold(int status);
void resetcolor();
struct Termsize gettermsize();
void disable_echo();
void enable_echo();

#endif  // TERMUI_H
