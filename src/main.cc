#define NCURSES_WIDECHAR 1
#include "../include/game.h"
#include <ncursesw/curses.h>
#include <locale.h>
#include <iostream>

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

    try {
        Game game{BOARD_HEIGHT, BOARD_WIDTH};
        game.play();
        endwin();
        return 0;
    }

    catch (std::runtime_error &e) {
        endwin();
        std::cerr << e.what() << std::endl;
        return 1;
    }
}