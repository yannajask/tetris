#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
    private:
        const int rows;
        const int cols;
        std::vector<std::vector<char>> cells;

    public:
        Board(int rows, int cols);
        ~Board() = default;

        void setCell(int row, int col, char c);
        char getCell(int row, int col) const;
        int getWidth() const;
        int getHeight() const;

        void clear();
        int clearRows();
        bool isInside(int row, int col) const;
};

#endif
