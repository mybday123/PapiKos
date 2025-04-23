#include <stdio.h>
#include <stdlib.h>
#include "include/termui.h"
#include "include/login.h"

int main() {
    setfontcolor(YELLOW);
    puts("PapiKos");
    resetcolor();

    struct Termsize termsize = gettermsize();
    login_menu();
    return 0;
}