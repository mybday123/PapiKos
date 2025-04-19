#include <stdio.h>
#include "../include/termui.h"

#ifdef _WIN32
    #include <Windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif

// Warna default
int bg_color = BLACK,
    font_color = WHITE,
    font_bold = FALSE;

void wait() {
    while (fgetc(stdin) != '\n')
        continue;
}

// Wrapper getch()
int getinput() {
    int ch;
    #ifdef _WIN32
        ch = _getch();
    #elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        struct termios old_attr, new_attr;
        if (tcgetattr(STDIN_FILENO, &old_attr) != 0)
            return EOF;

        new_attr = old_attr;
        new_attr.c_lflag &= ~(ICANON | ECHO);
        if(tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) != 0)
            return EOF;

        ch = getchar();

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

// Matikan input agar tidak bisa dilihat pas diketik
void disable_echo() {
    #ifdef _WIN32
        HANDLE attr = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(attr, &mode);
        SetConsoleMode(attr, mode & ~(ENABLE_ECHO_INPUT));
    #elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        struct termios attr;
        if (tcgetattr(STDIN_FILENO, &attr) != 0)
            return;
        attr.c_lflag &= ~ECHO;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) != 0)
            return;
    #endif
}

// Hidupkan lagi
void enable_echo() {
    #ifdef _WIN32
        HANDLE attr = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(attr, &mode);
        SetConsoleMode(attr, mode | ENABLE_ECHO_INPUT);
    #elif defined(__unix__) || defined(__APPLE__) || defined(__linux__)
        struct termios attr;
        if (tcgetattr(STDIN_FILENO, &attr) != 0)
            return;
        attr.c_lflag |= ECHO;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &attr) != 0)
            return;
    #endif
}