#include <stdlib.h>
#include "include/termui.h"

int main() {
	setfontcolor(YELLOW);
	puts("PapiKos");
	resetcolor();

	struct Termsize termsize = gettermsize();
	printf("C: %d R:%d\n", termsize.cols, termsize.rows);
	printf("%c\n", getinput());
	return 0;
}