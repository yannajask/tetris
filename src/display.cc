#define NCURSES_WIDECHAR 1
#include "display.h"
#include <sstream>

Display::Display(Game *subject, int rows, int cols): subject{subject}, rows{rows}, cols{cols} {
    board = newwin(rows + 2, (cols * 2) + 2, 0, 0);
    drawBorder(board, rows + 2, (cols * 2) + 2, 0, 0, "");
    render();

    info = newwin(rows + 2, 10, 0, (cols * 2) + 3);
    drawBorder(info, 4, 10, 0, 0, "Next");
    drawBorder(info, 3, 10, rows - 7, 0, "Score");
    drawBorder(info, 3, 10, rows - 4, 0, "Level");
    drawBorder(info, 3, 10, rows - 1, 0, "Lines");
    updateInfo();
}

Display::~Display() {}

void Display::drawBorder(WINDOW *w, int height, int width, int row, int col, const std::string &text) {
    // darker colour
    mvwhline(w, row, col + 1, 0, width - 2);
    mvwvline(w, row + 1, col, 0, height - 2);
    mvwaddch(w, row, col, ACS_ULCORNER);
    mvwaddch(w, row + height - 1, col, ACS_LLCORNER);
    if (text != "") mvwaddstr(w, row, col + 1, text.c_str()); 

    // lighter colour
    mvwhline(w, row + height - 1, col + 1, 0, width - 2);
    mvwvline(w, row + 1, col + width - 1, 0, height - 2);
    mvwaddch(w, row, col + width - 1, ACS_URCORNER);
    mvwaddch(w, row + height - 1, col + width - 1, ACS_LRCORNER);
}

void Display::render() {
    std::stringstream ss;
    ss << *subject;
    ss.unsetf(std::ios::skipws);

    char pixel;
    int row = 1;
    int col = 1;

    while (ss >> pixel) {
        if (pixel == '\n') {
            ++row;
            col = 1;
        } else if (pixel != ' ') {
            mvwaddwstr(board, row, col, L"██");
            col += 2;
        } else {
            mvwaddwstr(board, row, col, L"  ");
            col += 2;
        }
    }

    wrefresh(board);
}

void Display::updateInfo() {
    // print next block
    auto nextCoordinates = subject->getNextBlock()->getCoordinates();
    char nextType = subject->getNextBlock()->getType();

    for (int j = 1; j < 3; ++j) {
        for (int i = 1; i < 5; ++i) {
            if (std::find(nextCoordinates.begin(), nextCoordinates.end(), std::make_pair(i - 1, j - 1)) != nextCoordinates.end()) {
                mvwaddwstr(info, j, (i * 2) - 1, L"██");
            } else {
                mvwaddwstr(info, j, (i * 2) - 1, L"  ");
            }
        }
    }

    // print score, level, lines
    mvwprintw(info, rows - 6, 1, "%d", subject->getScore());
    mvwprintw(info, rows - 3, 1, "%d", subject->getLevel());
    mvwprintw(info, rows, 1, "%d", subject->getLines());
    wrefresh(info);
}
