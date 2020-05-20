#include <ncurses.h>
#include <iostream>




int main(int argc, char *argv[])
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    box(stdscr, 0, 0);
    attron(COLOR_PAIR(1));
    wbkgd(stdscr, COLOR_PAIR(1)); //윈도우 백그라운드 컬러

    WINDOW *win = subwin(stdscr, 21, 21, 0, 0);// 기본 윈도우 내의 서브윈도우 생성
    init_pair(2, COLOR_BLACK, COLOR_BLUE); //윈도우 백그라운드 컬러
    wborder(win,'1', '1', '1', '1', '2', '2', '2', '2');
    attron(COLOR_PAIR(2));
    wbkgd(win, COLOR_PAIR(2));
    refresh();
    getch();
    delwin(win);
    endwin();


    return 0;
}