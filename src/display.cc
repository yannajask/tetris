#define NCURSES_WIDECHAR 1
#include "display.h"
#include <sstream>

Display::Display(Game *subject, int rows, int cols): subject{subject}, rgb{has_colors()} {
    if (rgb) initColorMap();

    int windowHeight = rows + 10; int windowWidth = (cols * 2) + 19;
    int yMax; int xMax;
    getmaxyx(stdscr, yMax, xMax);
    mainWindow = newwin(windowHeight, windowWidth, (yMax / 2) - (windowHeight / 2), (xMax / 2) - (windowWidth / 2));
    drawBorder(mainWindow, windowHeight - 1, windowWidth - 2, 0, 0, "", true);

    int textOffset = (windowWidth - 26) / 2;
    mvwaddwstr(mainWindow, 1, textOffset, L" _____     _       _");
    mvwaddwstr(mainWindow, 2, textOffset, L"|_   _|___| |_ ___|_|___");
    mvwaddwstr(mainWindow, 3, textOffset, L"  | | | -_|  _|  _| |_ -|");
    mvwaddwstr(mainWindow, 4, textOffset, L"  |_| |___|_| |_| |_|___|");
 
    wrefresh(mainWindow);
    
    board = derwin(mainWindow, rows + 2, (cols * 2) + 2, 6, 2);
    drawBorder(board, rows + 2, (cols * 2) + 2, 0, 0, "");
    render();

    nextBlock = derwin(mainWindow, 4, 10, 6, (cols * 2) + 5);
    drawBorder(nextBlock, 4, 10, 0, 0, "Next");
    updateNextBlock();
    
    gameInfo = derwin(mainWindow, 9, 10, rows - 1, (cols * 2) + 5);
    drawBorder(gameInfo, 3, 10, 0, 0, "Score");
    drawBorder(gameInfo, 3, 10, 3, 0, "Level");
    drawBorder(gameInfo, 3, 10, 6, 0, "Lines");
    updateInfo();

}

Display::~Display() {}

void Display::initColorMap() {
    init_pair(1, 39, 238);    // teal
    init_pair(2, 25, 238);    // blue
    init_pair(3, 208, 238);   // orange
    init_pair(4, 220, 238);   // yellow
    init_pair(5, 112, 238);   // green
    init_pair(6, 90, 238);    // purple
    init_pair(7, 196, 238);   // red
    init_pair(8, 238, 187);   // black
    init_pair(9, 230, 187);  // white
    init_pair(10, 152, 152);
    init_pair(11, 238, 238);

    // to do: maybe move map somewhere else
    colorMap = {{'I', 1},
                {'J', 2},
                {'L', 3},
                {'O', 4},
                {'S', 5},
                {'T', 6},
                {'Z', 7}};

    bkgd(COLOR_PAIR(10));
    assume_default_colors(238, 187);
    refresh();
}

void Display::drawBorder(WINDOW *w, int height, int width, int row, int col, const std::string &text, bool shadow) {
    wattron(w, COLOR_PAIR(8));
    mvwhline(w, row, col + 1, 0, width - 2);
    mvwvline(w, row + 1, col, 0, height - 2);
    mvwaddch(w, row, col, ACS_ULCORNER);
    mvwaddch(w, row + height - 1, col, ACS_LLCORNER);
    if (text != "") mvwaddstr(w, row, col + 1, text.c_str());
    wattroff(w, COLOR_PAIR(8)); 

    if (shadow) {
        wattron(w, COLOR_PAIR(10));
        mvwaddstr(w, row, width, "  ");
        mvwaddstr(w, height, col, "  ");
        wattroff(w, COLOR_PAIR(10));

        wattron(w, COLOR_PAIR(11));
        mvwhline(w, height, col + 2, ' ', width);
        mvwvline(w, row + 1, width, ' ', height);
        mvwvline(w, row + 1, width + 1, ' ', height);
        wattroff(w, COLOR_PAIR(11));
    }

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
            mvwaddwstr(board, row, col, L"█▉");
            wattroff(board, COLOR_PAIR(colorPair));
            col += 2;
        } else {
            wattron(board, COLOR_PAIR(8));
            mvwaddwstr(board, row, col, L"▒▒");
            wattroff(board, COLOR_PAIR(8));
            col += 2;
        }
    }

    wrefresh(board);
}

void Display::updateNextBlock() {
    auto nextCoordinates = subject->getNextBlock()->getCoordinates();
    char nextType = subject->getNextBlock()->getType();

    for (int j = 1; j < 3; ++j) {
        for (int i = 1; i < 5; ++i) {
            if (std::find(nextCoordinates.begin(), nextCoordinates.end(), std::make_pair(i - 1, j - 1)) != nextCoordinates.end()) {
                int colorPair = colorMap[nextType];
                wattron(nextBlock, COLOR_PAIR(colorPair));
                mvwaddwstr(nextBlock, j, (i * 2) - 1, L"█▉");
                wattroff(nextBlock, COLOR_PAIR(colorPair));
            } else {
                wattron(nextBlock, COLOR_PAIR(8));
                mvwaddwstr(nextBlock, j, (i * 2) - 1, L"▒▒");
                wattroff(nextBlock, COLOR_PAIR(8));
            }
        }
    }

    wrefresh(nextBlock);
}

void Display::updateInfo() {
    mvwprintw(gameInfo, 1, 1, "%-8d", subject->getScore());
    mvwprintw(gameInfo, 4, 1, "%-8d", subject->getLevel());
    mvwprintw(gameInfo, 7, 1, "%-8d", subject->getLines());
    wrefresh(gameInfo);
}
