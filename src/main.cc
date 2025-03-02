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
    refresh();

    // create the tetris board window
    WINDOW *gameBoard = newwin(BOARD_HEIGHT + 2, (BOARD_WIDTH * 2) + 2, 0, 0);
    box_set(gameBoard, 0, 0);
    wrefresh(gameBoard);

    // create game info window
    WINDOW *gameInfo = newwin(BOARD_HEIGHT + 2, 10, 0, (BOARD_WIDTH * 2) + 3);
    wrefresh(gameInfo);

    WINDOW *nextBlock = subwin(gameInfo, 6, 10, 0, (BOARD_WIDTH * 2) + 3);
    box_set(nextBlock, 0, 0);
    mvwaddwstr(nextBlock, 0, 1, L"Next");
    wrefresh(nextBlock);

    WINDOW *score = subwin(gameInfo, 3, 10, BOARD_HEIGHT - 7, (BOARD_WIDTH * 2) + 3);
    box_set(score, 0, 0);
    mvwaddwstr(score, 0, 1, L"Score");
    wrefresh(score);

    WINDOW *level = subwin(gameInfo, 3, 10, BOARD_HEIGHT - 4, (BOARD_WIDTH * 2) + 3);
    box_set(level, 0, 0);
    mvwaddwstr(level, 0, 1, L"Level");
    wrefresh(level);

    WINDOW *lines = subwin(gameInfo, 3, 10, BOARD_HEIGHT - 1, (BOARD_WIDTH * 2) + 3);
    box_set(lines, 0, 0);
    mvwaddwstr(lines, 0, 1, L"Lines");
    wrefresh(lines);

    Game game(BOARD_HEIGHT, BOARD_WIDTH);
    game.dropBlock();
    game.moveBlockDown();
    game.moveBlockDown();

    while (true) {
        std::stringstream ss;
        ss << game;
        ss.unsetf(std::ios::skipws);
        char pixel;

        int row = 1, col = 1;
        while (ss >> pixel) {
            if (pixel == '\n') {
                row++;
                col = 1;
            } else if (pixel != ' ') {
                mvwaddwstr(gameBoard, row, col, L"██");
                col += 2;
            } else {
                mvwaddwstr(gameBoard, row, col, L"  ");
                col += 2;
            }
        }

        wrefresh(gameBoard);
        if (getch() == 'q') break;
    }

    endwin();
    return 0;
}