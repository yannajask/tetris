#define NCURSES_WIDECHAR 1
#include "display.h"

Display::Display(Game &subject, int rows, int cols): subject{&subject}, rows{rows}, cols{cols} {
    board = newwin(rows + 2, (cols * 2) + 2, 0, 0);
    drawBorder(board, rows + 2, (cols * 2), 0, 0, "");
    wrefresh(board);

    info = newwin(rows + 2, 10, 0, (rows * 2) + 3);
    drawBorder(info, 6, 10, 0, (cols * 2 + 3), "Next");
    drawBorder(info, 3, 10, rows - 7, (cols * 2 + 3), "Score");
    drawBorder(info, 3, 10, rows - 4, (cols * 2 + 3), "Level");
    drawBorder(info, 3, 10, rows - 1, (cols * 2 + 3), "Lines");
    wrefresh(info);
}

void Display::drawBorder(WINDOW *w, int height, int width, int row, int col, const std::string &text) {
    // darker colour
    mvwhline(w, row, col + 1, 0, width - 2);
    mvwhline(w, row + 1, col, 0, height - 2);
    mvwaddch(w, row, col, ACS_ULCORNER);
    mvwaddch(w, row + height - 1, col, ACS_LLCORNER);
    if (text != "") mvwaddstr(w, row, col + 1, text.c_str()); 

    // lighter colour
    mvwhline(w, row + height - 1, col + 1, 0, width - 2);
    mvwvline(w, row + 1, col + width - 1, 0, height - 2);
    mvwaddch(w, row, col + width - 1, ACS_URCORNER);
    mvwaddch(w, row + height - 1, col + width - 1, ACS_LRCORNER);
}


Display::~Display() {}