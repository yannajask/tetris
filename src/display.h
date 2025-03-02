#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include <ncursesw/curses.h>

class Display {
    private:
        Game *subject;
        const int rows;
        const int cols;

        WINDOW *board;
        WINDOW *info;

        void drawBorder(WINDOW *w, int height, int width, int row, int col, const std::string &text);

    public:
        Display(Game &subject, int rows, int cols);
        ~Display();

        void render();
        void updateInfo();
        void reset();
};

#endif
