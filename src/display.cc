#define NCURSES_WIDECHAR 1
#include "display.h"
#include <sstream>

Display::Display(Game *subject, int rows, int cols): subject{subject}, rows{rows}, cols{cols}, rgb{has_colors()} {
    if (rgb) initColorMap();
    
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

void Display::initColorMap() {
    init_pair(1, 39, 0);   // teal
    init_pair(2, 25, 0);   // blue
    init_pair(3, 208, 0);  // orange
    init_pair(4, 220, 0);  // yellow
    init_pair(5, 112, 0);  // green
    init_pair(6, 90, 0);   // purple
    init_pair(7, 196, 0);  // red
    init_pair(8, 0, 255);  // black
    init_pair(9, 231, 255);// white

    colorMap = {{'I', 1},
                {'J', 2},
                {'L', 3},
                {'O', 4},
                {'S', 5},
                {'T', 6},
                {'Z', 7}};

    assume_default_colors(0, 255);
}

void Display::drawBorder(WINDOW *w, int height, int width, int row, int col, const std::string &text) {
    wattron(w, COLOR_PAIR(8));
    mvwhline(w, row, col + 1, 0, width - 2);
    mvwvline(w, row + 1, col, 0, height - 2);
    mvwaddch(w, row, col, ACS_ULCORNER);
    mvwaddch(w, row + height - 1, col, ACS_LLCORNER);
    if (text != "") mvwaddstr(w, row, col + 1, text.c_str());
    wattroff(w, COLOR_PAIR(8)); 

    wattron(w, COLOR_PAIR(9));
    mvwhline(w, row + height - 1, col + 1, 0, width - 2);
    mvwvline(w, row + 1, col + width - 1, 0, height - 2);
    mvwaddch(w, row, col + width - 1, ACS_URCORNER);
    mvwaddch(w, row + height - 1, col + width - 1, ACS_LRCORNER);
    wattroff(w, COLOR_PAIR(9));
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
            int colorPair = colorMap[pixel];
            wattron(board, COLOR_PAIR(colorPair));
            mvwaddwstr(board, row, col, L"██");
            wattroff(board, COLOR_PAIR(colorPair));
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
                int colorPair = colorMap[nextType];
                wattron(info, COLOR_PAIR(colorPair));
                mvwaddwstr(info, j, (i * 2) - 1, L"██");
                wattroff(info, COLOR_PAIR(colorPair));
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
