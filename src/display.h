#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include <ncursesw/curses.h>
#include <map>

class Game;

class Display {
    private:
        Game *subject;

        WINDOW *mainWindow;
        WINDOW *board;
        WINDOW *nextBlock;
        WINDOW *gameInfo;

        const bool rgb;
        std::map<char, int> colorMap;
        void initColorMap();

        void drawBorder(WINDOW *w, int height, int width, int row, int col, const std::string &text, bool shadow = false);

    public:
        Display(Game *subject, int rows, int cols);
        ~Display();

        void render();
        void updateNextBlock();
        void updateInfo();
};

#endif
