#include "board.h"

Board::Board(int rows, int cols): rows(rows), cols(cols), cells(rows, std::vector<char>(cols, ' ')) {}

void Board::setCell(int x, int y, char c) { cells[y][x] = c; }

char Board::getCell(int x, int y) const { return cells[y][x]; }

int Board::getHeight() const { return rows; }

int Board::getWidth() const { return cols; }

void Board::clear() {
    for (auto &row: cells) {
        row = std::vector<char>(cols, ' ');
    }
}

int Board::clearRows() {
    int rowsCleared = 0;
    
    for (auto rowIt = cells.begin(); rowIt != cells.end(); ) {
        bool full = true;
        for (auto cell: *rowIt) {
            if (cell == ' ') {
                full = false;
                break;
            }
        }

        if (full) {
            rowIt = cells.erase(rowIt);
            cells.insert(cells.begin(), std::vector<char>(cols, ' '));
            ++rowsCleared;
        } else {
            ++rowIt;
        }
    }

    return rowsCleared;
}

bool Board::isInside(int x, int y) const { return ((x >= 0 && x < cols) && (y >= 0 && y < rows)); }
