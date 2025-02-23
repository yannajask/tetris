#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "subject.h"
#include <memory>
#include <vector>

class Cell;

class Board: public Subject {
    private:
        const int rows;
        const int cols;
        std::vector<std::vector<std::unique_ptr<Cell>>> cells;

    protected:
        std::vector<std::vector<std::unique_ptr<Cell>>> &grid();

    public:
        Board(int rows, int cols);
        ~Board() = default;

        void render();
        char getState(int x, int y) const override;
};

#endif