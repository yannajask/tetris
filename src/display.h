#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include <ncursesw/curses.h>
#include <map>

class Game;

class Display {
    private:
        Game *subject;

        const int rows;
        const int cols;
        const bool rgb;

        WINDOW *board;
        WINDOW *info;

        std::map<char, int> colorMap;
        void initColorMap();

        void drawBorder(WINDOW *w, int height, int width, int row, int col, const std::string &text);

    public:
        Display(Game *subject, int rows, int cols);
        ~Display();

        void render();
        void updateInfo();
};

#endif
