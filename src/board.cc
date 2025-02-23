#include "board.h"
#include <iostream>

Board::Board(int rows, int cols): rows(rows), cols(cols), cells(rows, std::vector<char>(cols, ' ')) {}

void Board::setCell(int x, int y, char c) { cells[x][y] = c; }

char Board::getCell(int x, int y) const { return cells[x][y]; }

void Board::clear() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            cells[i][j] = ' ';
        }
    }
}

int Board::clearRows() {
    int rowsCleared = 0;
    for (int i = 0; i < rows; ++i) {
        bool isFull = true;
        for (int j = 0; j < rows; ++j) {
            if (cells[i][j] == ' ') {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            ++rowsCleared;
            for (int j = 0; j < rows; ++j) {
                cells[i][j] = ' ';
            }
        }

        // need to also move rows down
    }

    return rowsCleared;
}

bool Board::isInside(int x, int y) const { return ((x >= 0 && x < rows) && (y >= 0 && y < cols)); }
