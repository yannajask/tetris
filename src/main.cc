#define NCURSES_WIDECHAR 1
#include "game.h"
#include "block.h"
#include "constants.h"
#include <ncursesw/curses.h>
#include <locale.h>
#include <iostream>
#include <sstream>

int main(int argc, const char *argv[]) {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    refresh();

    Game *game = new Game{BOARD_HEIGHT, BOARD_WIDTH};
    //game->dropBlock();
    //game->moveBlockDown();
    //game->moveBlockDown();
    //game->draw();
    game->play();
    
    getch();
    endwin();
    delete game;
    return 0;
}