#include <stdio.h>
#include "../include/termui.h"

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif

// Default color
int bg_color = BLACK,
    font_color = WHITE,
    font_bold = FALSE;

void wait() {
    while (fgetc(stdin) != '\n')
        continue;
}

int getinput() {
    #ifdef _WIN32
        _getch();
    #elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        struct termios old_attr, new_attr;
        if (tcgetattr(STDIN_FILENO, &old_attr) != 0)
            return EOF;

        new_attr = old_attr;
        new_attr.c_lflag &= ~(ICANON | ECHO);
        if(tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) != 0)
            return EOF;

    int ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);
        return ch;
    #endif

}

void clrscr() {
    printf(ESC"[2J"ESC"[?6h");
}

void setfontcolor(int color) {
    printf(ESC"[3%dm", color);
    font_color = color;
}

void setbgcolor(int color) {
    printf(ESC"[4%dm", color);
    bg_color = color;
}

void resetcolor() {
    setfontcolor(WHITE);
    setbgcolor(BLACK);
}

void setfontbold(int status) {
    printf(ESC"[%dm", status);
    font_bold = status;
    setfontcolor(font_color);
    setbgcolor(bg_color);
}

struct Termsize gettermsize() {
    struct Termsize termsize;
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int cols, rows;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        termsize.cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        termsize.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        struct winsize win;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        termsize.cols = win.ws_col;
        termsize.rows = win.ws_row;
    #else
        termsize.cols = 0;
        termsize.rows = 0;
    #endif

    return termsize;
}
