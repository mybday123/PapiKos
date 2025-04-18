#include <stdio.h>
#include <stdlib.h>
#include "include/termui.h"

int main() {
    setfontcolor(YELLOW);
    puts("PapiKos");
    resetcolor();

    struct Termsize termsize = gettermsize();
    printf("C: %d R:%d\n", termsize.cols, termsize.rows);
    char test[1024];
    disable_echo();
    fgets(test, 100, stdin);
    enable_echo();
    fgets(test, 100, stdin);
    return 0;
}