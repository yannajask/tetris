#define NCURSES_WIDECHAR 1
#include "game.h"
#include "block.h"
#include <ncursesw/curses.h>
#include <locale.h>
#include <iostream>
#include <sstream>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

int main(int argc, const char *argv[]) {
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    refresh();
    Game game{BOARD_HEIGHT, BOARD_WIDTH};
    game.play();
    endwin();
    return 0;
}