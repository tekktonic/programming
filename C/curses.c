#include <curses.h>

int main(void)
{
    initscr();

    waddstr(curscr, "test thingy");
//    refresh();
    getch();
    endwin();
    return 0;
}


