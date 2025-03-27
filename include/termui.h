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

#define BLOCK_BLINK     1
#define BLOCK           2
#define UNDERLINE_BLINK 3
#define UNDERLINE       4
#define BAR_BLINK       5
#define BAR             6

struct Termsize {
    int cols;
    int rows;
};

void wait();
int getinput();
void clrscr();
void setfontcolor(int color);
void setbgcolor(int color);

#endif  // TERMUI_H
