#ifndef BOARD_H
#define BOARD_H

#include "subject.h"
#include <memory>
#include <vector>

class Board {
    private:
        const int rows;
        const int cols;
        std::vector<std::vector<char>> cells;

    public:
        Board(int rows, int cols);
        ~Board() = default;

        void setCell(int x, int y, char c);
        char getCell(int x, int y) const;

        void clear();
        int clearRows();
        bool isInside(int x, int y) const;
};

#endif
