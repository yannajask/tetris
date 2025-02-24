#include "board.h"

Board::Board(int rows, int cols): rows(rows), cols(cols), cells(rows, std::vector<char>(cols, ' ')) {}

void Board::setCell(int row, int col, char c) { cells[row][col] = c; }

char Board::getCell(int row, int col) const { return cells[row][col]; }

int Board::getHeight() const { return rows; }

int Board::getWidth() const { return cols; }

void Board::clear() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; cols < cols; ++col) {
            cells[row][col] = ' ';
        }
    }
}

int Board::clearRows() {
    int rowsCleared = 0;
    for (int row = 0; row < rows; ++row) {
        bool isFull = true;
        for (int col = 0; col < cols; ++col) {
            if (cells[row][col] == ' ') {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            ++rowsCleared;
            for (int col = 0; col < cols; ++col) {
                cells[row][col] = ' ';
            }
        }

        // need to also move rows down
    }

    return rowsCleared;
}

bool Board::isInside(int row, int col) const { return ((row >= 0 && row < rows) && (col >= 0 && col < cols)); }
