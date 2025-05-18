#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

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

struct User {
    char username[64];
    char password[64];
};

// Warna default
int bg_color = BLACK,
font_color = WHITE,
font_bold = FALSE;

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
void print_newline();
int scan_input(char* buffer, size_t max_len);

void login_menu();
void login();
void createaccount();

int main() {
    setfontcolor(YELLOW);
    puts("PapiKos");
    resetcolor();

    login_menu();
    return 0;
}

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
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) != 0)
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
    printf(ESC"[0m");
    font_color = WHITE;
    bg_color = BLACK;
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

void print_newline() {
    printf("\n");
}

int scan_input(char* buffer, size_t max_len) {
    char temp[1024];
    if (!fgets(temp, sizeof(temp), stdin)) {
        return 0;
    }

    size_t len = strlen(temp);
    if (temp[len - 1] == '\n') {
        temp[len - 1] = '\0';
        len--;
    }

    if (len > max_len) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isalnum(temp[i])) {
            return 0;
        }
    }

    strncpy(buffer, temp, max_len + 1);
    return 1;
}

void login_menu() {
    char c = '0';
    puts("1. Log in");
    puts("2. Create account");
    puts("0. Exit");
    print_newline();
    printf("? ");
    if (!scanf("%c", &c)) {
        return 0;
    }
    int ch = getchar();
    (void)ch;

    switch (c) {
    case '0':
        exit(0);
        break;
    case '1':
        login();
        break;
    case '2':
        createaccount();
        break;
    }
}

void createaccount() {
    struct User new_user;
    char temp_pass[64];
    printf("Masukkan username: ");
    scan_input(new_user.username, 63);
    if (strcmp(new_user.username, "admin") != 0) {
        puts("Username tidak bisa admin.");
        return;
    }

    printf("Masukkan password: ");
    disable_echo();
    scan_input(new_user.password, 63);
    enable_echo();
    printf("Masukkan password yang sama lagi:");
    disable_echo();
    scan_input(temp_pass, 63);
    enable_echo();
    if (strcmp(new_user.password, temp_pass) != 0) {
        puts("Password tidak sesuai!");
        return;
    }
    else {
        puts("Menyimpan akun...");
        FILE* userfile = fopen(new_user.username, "w");
        if (userfile == NULL) {
            puts("Gagal menyimpan file");
            return;
        }
        if (fwrite(&new_user, sizeof(struct User), 1, userfile)) {
            puts("User created");
            fclose(userfile);
        }
        else {
            puts("Failed to create user");
            fclose(userfile);
        }
    }
}

void login() {
    struct User user;
    char temp_user[64];
    char temp_pass[64];

    printf("Masukkan username: ");
    scan_input(temp_user, 63);
    disable_echo();
    printf("Masukkan password: ");
    enable_echo();
    scan_input(temp_pass, 63);

    FILE* userfile = fopen(temp_user, "r");
    if (userfile == NULL) {
        puts("Login gagal");
        return;
    }
    if (fread(&user, sizeof(struct User), 1, userfile)) {
        if (strcmp(user.password, temp_pass) == 0) {
            puts("Login berhasil");
            fclose(userfile);
            return;
        }
        else {
            puts("Login gagal");
            fclose(userfile);
            return;
        }
    }
    else {
        puts("Login gagal");
        fclose(userfile);
        return;
    }
}
