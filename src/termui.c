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
        continue;
    #elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        struct termios old_attr, new_attr;
        if (tcgetattr(STDIN_FILENO, &old_attr) != 0)
            return EOF;

        new_attr = old_attr;
        new_attr.c_lflag &= ~(ICANON | ECHO);
        if(tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) != 0)
            return EOF;
    #endif

    int ch = getchar();

    #ifdef _WIN32
        continue;
    #elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);
    #endif

    return ch;
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
