#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include "board.h"

class TextDisplay: public Observer {
    private:
        Board *board;
        const int rows;
        const int cols;

    public:
        TextDisplay(Board *board, int rows, int cols);
        ~TextDisplay();
        virtual void notify() override;
};

#endif