#include "board.h"

Board::Board(int rows, int cols): rows(rows), cols(cols), cells(rows, std::vector<char>(cols, ' ')) {}

void Board::setCell(int x, int y, char c) { cells[y][x] = c; }

char Board::getCell(int x, int y) const { return cells[y][x]; }

int Board::getHeight() const { return rows; }

int Board::getWidth() const { return cols; }

void Board::clear() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j] = ' ';
        }
    }
}

int Board::clearRows() {
    int rowsCleared = 0;
    for (int i = 0; i < rows; ++i) {
        bool isFull = true;
        for (int j = 0; j < cols; ++j) {
            if (cells[i][j] == ' ') {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            ++rowsCleared;
            for (int j = 0; j < cols; ++j) {
                cells[i][j] = ' ';
            }
        }

        // need to also move rows down
    }

    return rowsCleared;
}

bool Board::isInside(int x, int y) const { return ((x >= 0 && x < cols) && (y >= 0 && y < rows)); }
